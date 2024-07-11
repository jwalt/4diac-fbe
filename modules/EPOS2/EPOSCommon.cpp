#include "EPOSCommon.h"
#include "../../forte/src/arch/devlog.h"
#include <string>
#include <mutex>
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

extern "C" {
	// yes, they really were that shortsighted
#define error_t tulibs_error_t
#include <tulibs/error/error.h>
#define class klass
#include <tulibs/usb/usb.h>
#undef class
#include <epos/epos.h>
#include <tulibs/config/config.h>
#include <can/can_usb.h>
#include <epos/position_profile.h>
#include <epos/velocity_profile.h>
#include <epos/velocity.h>
#include <epos/position.h>
#include <epos/error.h>
#include <epos/sensor.h>
#include <epos/motor.h>
#include <epos/home.h>
#include <epos/current.h>
#undef error_t
#define EPOS_STATUS_ERROR 8
}

using namespace std;

struct State {
	enum { PositionRel, PositionAbs, Velocity } mode = PositionRel;
	float speed = 0.0;
};

static struct Guarded {
	void abort() {
		for (auto &entry : nodelist) {
			if (entry) {
				auto &EPOS_node = entry->EPOS_node;
				epos_control_quickstop(&EPOS_node.control);
				epos_device_shutdown(&EPOS_node.dev);
				epos_node_disconnect(&EPOS_node);
				epos_node_destroy(&EPOS_node);
				entry.reset();
			}
		}
	}

private:
	struct Entry {
		epos_node_t EPOS_node;
		State state;
		int open_count = 0;

		bool ref() { return open_count++; }
		bool unref() { return !--open_count; }
	};

	Entry &acquire(uint8_t node) {
		if (!nodelist[node]) {
			nodelist[node].reset(new Entry());
			DEVLOG_DEBUG("Creating node %i\n", node);
		}
		return *(nodelist[node].get());
	}

	void release(uint8_t node) {
		if (!nodelist[node]->open_count) {
			DEVLOG_DEBUG("Releasing node %i\n", node);
			nodelist[node].reset();
		}
	}

	can_device_t CAN_device;
	array<unique_ptr<Entry>, 256> nodelist;
	mutex mtx;
	friend class Guard;
} EPOS;


class Guard {
	lock_guard<mutex> lock;
	Guarded::Entry &entry;

public:
	epos_node_t &node;
	can_device_t &can;
	State &state;

	Guard(Guarded &epos, uint8_t node_id)
		: lock(epos.mtx)
		, entry(epos.acquire(node_id))
		, node(entry.EPOS_node)
		, can(epos.CAN_device)
		, state(entry.state)
	{}

	bool open() { return entry.ref(); }
	bool isOpen() { return !!entry.open_count; }
	bool close() { return entry.unref() ; }
};



static const char *err(const tulibs_error_t &e) {
	if (e.code) {
		auto ret = error_get_description(&e);
		DEVLOG_WARNING("EPOS %s\n", ret);
		return ret;
	}
	return nullptr;
}

static const char *findDevice() {
	static char name[255];

	usb_context_t ctx;
	if (usb_context_init(&ctx)) return nullptr;

	{
		auto *usbdev = usb_context_match_vendor_product(&ctx, 0x0403, 0xa8b0);
		if (!usbdev) return nullptr;

		sprintf(name, "/dev/bus/usb/%03i/%03i", usbdev->bus, usbdev->address);
	}

	usb_context_release(&ctx);

	DEVLOG_DEBUG("EPOS USB device: %s\n", name);
	return name;
}

const char *initDevice(uint8_t node) {
	Guard E(EPOS, node);

	if (!E.open()) {
		if (!E.can.num_references) {
			auto device = findDevice();
			if (!device) return "Could not find device";

			config_t can_config;
			config_init_default(&can_config, &can_default_config);
			config_set_string(&can_config, CAN_USB_PARAMETER_DEVICE, device);
			can_device_init_config(&E.can, &can_config);
			config_clear(&can_config);

			if (E.can.error.code) return err(E.can.error);
		}

		{
			config_t epos_config;
			config_init_default(&epos_config, &epos_default_config);
			config_set_int(&epos_config, EPOS_PARAMETER_DEVICE_NODE_ID, node);
			config_set_bool(&epos_config, EPOS_PARAMETER_DEVICE_RESET, config_param_true);

			epos_node_init_config(&E.node, &E.can, &epos_config);
			config_clear(&epos_config);

			if (E.node.error.code) return err(E.node.error);
		}

		// DON'T USE epos_node_connect, it overwrites the device's saved defaults
		epos_device_open(&E.node.dev);
		if (E.node.dev.error.code) return err(E.node.dev.error);
		if (E.can.error.code) return err(E.can.error);

		DEVLOG_INFO("EPOS Node %i HW/SW version: 0x%04X / 0x%04X, Device Status 0x%04x\n",
		            node,
		            epos_device_get_hardware_version(&E.node.dev),
		            epos_device_get_software_version(&E.node.dev),
		            (uint16_t)epos_device_get_status(&E.node.dev));

		if (epos_device_get_status(&E.node.dev) & EPOS_STATUS_ERROR) {
			epos_device_clear_fault(&E.node.dev);
			epos_device_reset_communication(&E.node.dev);
			DEVLOG_INFO("EPOS Status after clearing fault: 0x%x\n",
			            (uint16_t)epos_device_get_status(&E.node.dev));
		}

		epos_input_setup(&E.node.input);
		epos_control_quickstop(&E.node.control);
		epos_device_shutdown(&E.node.dev);
	}

	return nullptr;
}

const char *deinitDevice(uint8_t node) {
	Guard E(EPOS, node);

	if (!E.isOpen()) return "EPOS device closed more times than opened";

	epos_control_quickstop(&E.node.control);
	epos_device_shutdown(&E.node.dev);

	if (!E.close()) return nullptr;

	epos_node_disconnect(&E.node);
	epos_node_destroy(&E.node);

	return err(E.node.dev.error);
}

static void dumpPosInternal(Guard &E) {
	auto pos = epos_node_get_position(&E.node);
	if (err(E.node.dev.error)) return;
	auto velocity = epos_node_get_velocity(&E.node);
	if (err(E.node.dev.error)) return;
	auto current = epos_node_get_current(&E.node);
	if (err(E.node.dev.error)) return;

	DEVLOG_DEBUG("EPOS Position: %g, Velocity: %g, Current: %g\n", pos, velocity, current);
}

void dumpPos(uint8_t node) {
	Guard E(EPOS, node);
	dumpPosInternal(E);
}

template <typename T>
static T read_register(Guard &E, short index, unsigned char subindex = 0) {
	T ret = 0;
	epos_device_read(&E.node.dev, index, subindex, (uint8_t*)&ret, sizeof(ret));

	return ret;
}

static void dumpInput(Guard &E, epos_input_func_type_t type, const char *name) {
	DEVLOG_INFO("EPOS Input %s: Ch. %i, Pol. %i, Exec %i, Enabled %i, State %i\n",
	            name,
	            epos_input_get_func_channel(&E.node.input, type),
	            epos_input_get_func_polarity(&E.node.input, type),
	            epos_input_get_func_execute(&E.node.input, type),
	            epos_input_get_func_enabled(&E.node.input, type),
	            epos_input_get_func_state(&E.node.input, type));
}

void dumpInfo(uint8_t node) {
	Guard E(EPOS, node);

	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Connected to node %i\n", epos_device_get_id(&E.node.dev));
	DEVLOG_INFO("EPOS HW version: 0x%x (%s)\n",
	            epos_device_get_hardware_version(&E.node.dev),
	            epos_device_names[E.node.dev.type]);
	DEVLOG_INFO("EPOS SW version: 0x%x\n", epos_device_get_software_version(&E.node.dev));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS CAN bitrate: %i\n", epos_device_get_can_bit_rate(&E.node.dev));
	DEVLOG_INFO("EPOS RS232 bitrate: %i\n", epos_device_get_rs232_baud_rate(&E.node.dev));
	DEVLOG_INFO("EPOS Status Word: 0x%x\n", (uint16_t)epos_device_get_status(&E.node.dev));
	DEVLOG_INFO("EPOS Control Word: 0x%x\n", epos_device_get_control(&E.node.dev));
	DEVLOG_INFO("EPOS Misc Config Word: 0x%x\n", epos_device_get_configuration(&E.node.dev));
	DEVLOG_INFO("EPOS Error Code: 0x%x\n", epos_device_get_error(&E.node.dev));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Control Mode: %i\n",
	            read_register<int8_t>(E, EPOS_CONTROL_INDEX_MODE_DISPLAY));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Motor Type: %i\n", epos_motor_get_type(&E.node.motor));
	DEVLOG_INFO("EPOS Motor Max Continuous Current: %imA\n",
	            epos_motor_get_max_continuous_current(&E.node.motor));
	DEVLOG_INFO("EPOS Motor Max Peak Current: %imA\n",
	            epos_motor_get_max_output_current(&E.node.motor));
	DEVLOG_INFO("EPOS Motor Poles: %i\n", epos_motor_get_num_poles(&E.node.motor));
	DEVLOG_INFO("EPOS Motor Max Speed: %i\n", epos_motor_get_max_speed(&E.node.motor));
	DEVLOG_INFO("EPOS Motor Thermal Time Constant: %i\n",
	            epos_motor_get_thermal_time_constant(&E.node.motor));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Current Control P Gain: %i\n",
	            read_register<uint16_t>(E, EPOS_CURRENT_INDEX_CONTROL_PARAMETERS,
	                                    EPOS_CURRENT_SUBINDEX_P_GAIN));
	DEVLOG_INFO("EPOS Current Control I Gain: %i\n",
	            read_register<uint16_t>(E, EPOS_CURRENT_INDEX_CONTROL_PARAMETERS,
	                                    EPOS_CURRENT_SUBINDEX_I_GAIN));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Gear Transmission (software): %f\n", E.node.gear.transmission);
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Sensor Type: %i\n", epos_sensor_get_type(&E.node.sensor));
	DEVLOG_INFO("EPOS Sensor Polarity: %i\n", epos_sensor_get_polarity(&E.node.sensor));
	DEVLOG_INFO("EPOS Sensor Pulses: %i\n", epos_sensor_get_pulses(&E.node.sensor));
	DEVLOG_INFO("EPOS Sensor Supervision: %i\n", epos_sensor_get_supervision(&E.node.sensor));
	DEVLOG_INFO("EPOS Sensor Position: %i\n", epos_sensor_get_position(&E.node.sensor));
	DEVLOG_INFO("EPOS -----------------------------\n");
	uint16_t st, msk, pol, ex;
	epos_device_read(&E.node.dev, EPOS_INPUT_INDEX_FUNCS, EPOS_INPUT_SUBINDEX_STATE, (uint8_t*)&st, sizeof(st));
	epos_device_read(&E.node.dev, EPOS_INPUT_INDEX_FUNCS, EPOS_INPUT_SUBINDEX_MASK, (uint8_t*)&msk, sizeof(msk));
	epos_device_read(&E.node.dev, EPOS_INPUT_INDEX_FUNCS, EPOS_INPUT_SUBINDEX_POLARITY, (uint8_t*)&pol, sizeof(pol));
	epos_device_read(&E.node.dev, EPOS_INPUT_INDEX_FUNCS, EPOS_INPUT_SUBINDEX_EXECUTE, (uint8_t*)&ex, sizeof(ex));
	DEVLOG_INFO("EPOS Funcs: st= %04x mask= %04x pol= %04x exec= %04x\n", st, msk, pol, ex);
	dumpInput(E, epos_input_neg_limit, "Negative Limit Switch");
	dumpInput(E, epos_input_pos_limit, "Positive Limit Switch");
	dumpInput(E, epos_input_home_switch, "Home Switch");
	dumpInput(E, epos_input_pos_marker, "Position Marker");
	dumpInput(E, epos_input_dev_enable, "Device Enable Switch");

	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Home Method: %i\n", read_register<uint8_t>(E, EPOS_HOME_INDEX_METHOD));
	DEVLOG_INFO("EPOS Home Current Threshold: %i\n", read_register<uint16_t>(E, EPOS_HOME_INDEX_CURRENT_THRESHOLD));
	DEVLOG_INFO("EPOS Home Switch Search Velocity: %f\n",
	            epos_gear_to_angular_velocity(
		            &E.node.gear,
		            read_register<uint32_t>(E, EPOS_HOME_INDEX_VELOCITIES, EPOS_HOME_SUBINDEX_SWITCH_SEARCH_VELOCITY)));
	DEVLOG_INFO("EPOS Home Zero Search Velocity: %f\n",
	            epos_gear_to_angular_velocity(
		            &E.node.gear,
		            read_register<uint32_t>(E, EPOS_HOME_INDEX_VELOCITIES, EPOS_HOME_SUBINDEX_ZERO_SEARCH_VELOCITY)));
	DEVLOG_INFO("EPOS Home Acceleration: %f\n",
	            epos_gear_to_angular_acceleration(
		            &E.node.gear,
		            read_register<uint32_t>(E, EPOS_HOME_INDEX_ACCELERATION)));
	DEVLOG_INFO("EPOS Home Offset: %i\n", read_register<int32_t>(E, EPOS_HOME_INDEX_OFFSET));
	DEVLOG_INFO("EPOS Home Position: %i\n", read_register<int32_t>(E, EPOS_HOME_INDEX_OFFSET));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Position Max Following Error: %i\n", read_register<int32_t>(E, EPOS_POSITION_INDEX_MAX_FOLLOWING_ERROR));
	DEVLOG_INFO("EPOS Position Control Parameters: P=%i, I=%i, D=%i, v=%i, a=%i\n",
	            read_register<int16_t>(E, EPOS_POSITION_INDEX_CONTROL_PARAMETERS, EPOS_POSITION_SUBINDEX_P_GAIN),
	            read_register<int16_t>(E, EPOS_POSITION_INDEX_CONTROL_PARAMETERS, EPOS_POSITION_SUBINDEX_I_GAIN),
	            read_register<int16_t>(E, EPOS_POSITION_INDEX_CONTROL_PARAMETERS, EPOS_POSITION_SUBINDEX_D_GAIN),
	            read_register<int16_t>(E, EPOS_POSITION_INDEX_CONTROL_PARAMETERS, EPOS_POSITION_SUBINDEX_VELOCITY_FACTOR),
	            read_register<int16_t>(E, EPOS_POSITION_INDEX_CONTROL_PARAMETERS, EPOS_POSITION_SUBINDEX_ACCELERATION_FACTOR));
	DEVLOG_INFO("EPOS Position Limits: %i - %i\n",
	            read_register<int32_t>(E, EPOS_POSITION_INDEX_SOFTWARE_LIMIT, EPOS_POSITION_SUBINDEX_NEG_LIMIT),
	            read_register<int32_t>(E, EPOS_POSITION_INDEX_SOFTWARE_LIMIT, EPOS_POSITION_SUBINDEX_POS_LIMIT));
	DEVLOG_INFO("EPOS Velocity Control Parameters: P=%i, I=%i\n",
	            read_register<int16_t>(E, EPOS_VELOCITY_INDEX_CONTROL_PARAMETERS, EPOS_VELOCITY_SUBINDEX_P_GAIN),
	            read_register<int16_t>(E, EPOS_VELOCITY_INDEX_CONTROL_PARAMETERS, EPOS_VELOCITY_SUBINDEX_I_GAIN));
	DEVLOG_INFO("EPOS -----------------------------\n");
	DEVLOG_INFO("EPOS Profile Max Velocity: %f\n",
	            epos_gear_to_angular_velocity(
		            &E.node.gear,
		            read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_VELOCITY)));
	DEVLOG_INFO("EPOS Profile Max Acceleration: %f\n",
	            epos_gear_to_angular_acceleration(
		            &E.node.gear,
		            read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_ACCELERATION))/2);
	// No idea why this is off by a factor of (it seems) exactly 2.
	DEVLOG_INFO("EPOS Profile Quickstop Deceleration: %f\n",
	            epos_gear_to_angular_acceleration(
		            &E.node.gear,
		            read_register<int32_t>(E, EPOS_PROFILE_INDEX_QUICKSTOP_DECELERATION)));
	DEVLOG_INFO("EPOS -----------------------------\n");

    auto len = epos_error_get_history_length(&E.node.dev);
    auto history = vector<epos_error_device_t>(len);
    auto used = epos_error_get_history(&E.node.dev, &history[0]);
    for (; used > 0; used--) {
	    DEVLOG_INFO("EPOS Error Log Entry %i: Code 0x%x: %s\n", used, history[used-1].code, history[used-1].message);
    }
}

uint8_t getError(uint8_t node) {
	Guard E(EPOS, node);

	return epos_device_get_error(&E.node.dev);
}

uint16_t getStatus(uint8_t node) {
	Guard E(EPOS, node);

	return epos_device_get_status(&E.node.dev);
}

bool isNegLimit(uint8_t node) {
	Guard E(EPOS, node);

	return epos_input_get_func_state(&E.node.input, epos_input_neg_limit);
}

bool isPosLimit(uint8_t node) {
	Guard E(EPOS, node);

	return epos_input_get_func_state(&E.node.input, epos_input_pos_limit);
}

const char *clearError(uint8_t node) {
	Guard E(EPOS, node);

	epos_device_clear_fault(&E.node.dev);
	epos_device_reset_communication(&E.node.dev);
	epos_device_shutdown(&E.node.dev);
	epos_control_start(&E.node.control);

	DEVLOG_DEBUG("EPOS Status after clearing fault: 0x%x\n",
	            (uint16_t)epos_device_get_status(&E.node.dev));
	return err(E.node.dev.error);
}

// FIXME: this is currently borked
#if 0
const char *homeMotor(uint8_t node) {
	Guard E(EPOS, node);
	auto type = epos_input_pos_limit;

	auto exec = epos_input_get_func_execute(&E.node.input, type);
	auto enabled = epos_input_get_func_enabled(&E.node.input, type);
	if (!exec || !enabled) return "Positive limit switch is not enabled";

	uint8_t method = epos_home_pos_limit;
	if (false
	    || epos_device_shutdown(&E.node.dev)
	    || epos_control_set_mode(&E.node.control, epos_control_homing)
	    || epos_device_write(&E.node.dev, EPOS_HOME_INDEX_METHOD, 0, &method, 1) != 1
	    || epos_home_set_offset(&E.node.dev, -100)
	    || epos_home_set_switch_search_velocity(&E.node.dev, 100)
	    || epos_home_set_zero_search_velocity(&E.node.dev, 100)
	    || epos_home_set_current_threshold(&E.node.dev, 1200)
	    || epos_profile_set_type(&E.node.dev, epos_profile_sinusoidal)
	    || epos_control_start(&E.node.control)
	    || epos_device_set_control(&E.node.dev, EPOS_HOME_CONTROL_START)) return err(E.node.dev.error);

	DEVLOG_DEBUG("EPOS Home Raw: %i\n", read_register<uint8_t>(E, EPOS_HOME_INDEX_METHOD));
	DEVLOG_DEBUG("EPOS Control Mode: %i\n", read_register<int8_t>(E, EPOS_CONTROL_INDEX_MODE_DISPLAY));
	DEVLOG_DEBUG("EPOS Control Word: 0x%x\n", epos_device_get_control(&E.node.dev));
	do {
		this_thread::sleep_for(chrono::milliseconds{1000});
		dumpPosInternal(E);
		DEVLOG_DEBUG("EPOS Status Word: 0x%x\n", (uint16_t)epos_device_get_status(&E.node.dev));
	} while (!(epos_device_get_status(&E.node.dev) & EPOS_HOME_STATUS_REACHED));

	return err(E.node.dev.error);
}
#endif

const char *setZero(uint8_t node) {
	Guard E(EPOS, node);

	uint8_t method = epos_home_actual_position;
	if (false
	    || epos_device_shutdown(&E.node.dev)
	    || epos_control_set_mode(&E.node.control, epos_control_homing)
	    || epos_device_write(&E.node.dev, EPOS_HOME_INDEX_METHOD, 0, &method, 1) != 1
	    || epos_home_set_offset(&E.node.dev, 0)
	    || epos_control_start(&E.node.control)
	    || epos_device_set_control(&E.node.dev, EPOS_HOME_CONTROL_START)) return err(E.node.dev.error);

	DEVLOG_DEBUG("EPOS Home Method: %i\n", read_register<uint8_t>(E, EPOS_HOME_INDEX_METHOD));
	DEVLOG_DEBUG("EPOS Control Mode: %i\n", read_register<int8_t>(E, EPOS_CONTROL_INDEX_MODE_DISPLAY));
	DEVLOG_DEBUG("EPOS Control Word: 0x%x\n", epos_device_get_control(&E.node.dev));
	this_thread::sleep_for(chrono::milliseconds{100});
	dumpPosInternal(E);
	DEVLOG_DEBUG("EPOS Status Word: 0x%x\n", (uint16_t)epos_device_get_status(&E.node.dev));

	return err(E.node.dev.error);
}

const char *moveToPosition(uint8_t node, float targetPosition, bool relative, float speed, float accel) {
	if (speed == 0.0) return moveWithVelocity(node, speed, accel, accel);
	if (relative && speed < 0.0) {
		targetPosition = -targetPosition;
		speed = -speed;
	}

	Guard E(EPOS, node);

	DEVLOG_DEBUG("EPOS moving by %g units at %g with acceleration %g\n", targetPosition, speed, accel);

	auto vlimit = epos_gear_to_angular_velocity(
		&E.node.gear,
		read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_VELOCITY));
	if (vlimit >= 0 && speed > vlimit) return "Maximum speed exceeded";

	auto alimit = epos_gear_to_angular_acceleration(
		&E.node.gear,
		read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_ACCELERATION))/2;
	// No idea why this is off by a factor of (it seems) exactly 2.
	if (alimit >= 0 && accel > alimit) return "Maximum acceleration exceeded";

	epos_position_profile_t profile;

	// Args: pos, speed, accel, decel, type, rel
	epos_position_profile_init(&profile, targetPosition, speed, accel, accel*2, epos_profile_sinusoidal, relative);

	epos_position_profile_start(&E.node, &profile);
	E.state.mode = (relative?State::PositionRel : State::PositionAbs);

	return err(E.node.dev.error);
}

const char *moveWithVelocity(uint8_t node, float targetSpeed, float accel, float decel) {
	Guard E(EPOS, node);

	// suppress redundant control messages
	if (E.state.mode == State::Velocity && E.state.speed == targetSpeed) return nullptr;

	DEVLOG_DEBUG("EPOS moving at speed %g with acceleration %g and deceleration %g\n", targetSpeed, accel, decel);

	auto vlimit = epos_gear_to_angular_velocity(
		&E.node.gear,
		read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_VELOCITY));
	if (vlimit >= 0 && targetSpeed > vlimit) return "Maximum speed exceeded";

	auto alimit = epos_gear_to_angular_acceleration(
		&E.node.gear,
		read_register<int32_t>(E, EPOS_PROFILE_INDEX_MAX_ACCELERATION))/2;
	// No idea why this is off by a factor of (it seems) exactly 2.
	if (alimit >= 0 && accel > alimit) return "Maximum acceleration exceeded";
	if (alimit >= 0 && decel > alimit) return "Maximum acceleration exceeded";

	epos_velocity_profile_t profile;

	// Args: speed, accel, decel, type
	epos_velocity_profile_init(&profile, targetSpeed, accel, decel, epos_profile_sinusoidal);

	epos_velocity_profile_start(&E.node, &profile);
	E.state.mode = State::Velocity;
	E.state.speed = targetSpeed;

	return err(E.node.dev.error);
}


bool isMovementComplete(uint8_t node) {
	Guard E(EPOS, node);

	return !epos_profile_wait(&E.node, 0.0f);
}

const char *waitForMovementComplete(uint8_t node) {
	Guard E(EPOS, node);

	epos_profile_wait(&E.node, 86400.0f);
		
	return err(E.node.dev.error);
}

const char *stopMovement(uint8_t node) {
	Guard E(EPOS, node);

	if (E.state.mode == State::Velocity) epos_velocity_profile_stop(&E.node);
	else epos_position_profile_stop(&E.node);
	epos_control_quickstop(&E.node.control);
	epos_device_shutdown(&E.node.dev);

	return err(E.node.dev.error);
}

const char *getVelocity(uint8_t node, float &val) {
	Guard E(EPOS, node);

	val = epos_node_get_velocity(&E.node);
	
	return err(E.node.dev.error);
}

const char *getPosition(uint8_t node, float &val) {
	Guard E(EPOS, node);

	val = epos_node_get_position(&E.node);

	return err(E.node.dev.error);
}

const char *getCurrent(uint8_t node, float &val) {
	Guard E(EPOS, node);

	val = epos_node_get_current(&E.node);

	return err(E.node.dev.error);
}

void emergencyAbort() {
	EPOS.abort();
}
