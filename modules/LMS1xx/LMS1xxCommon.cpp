#include "../../forte/src/arch/devlog.h"
#include "LMS1xxCommon.h"
#include "liblms1xx/LMS1xx.hpp"

#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

static mutex mtx;
static LMS1xx laser;
static const char *startup_state = "LMS1xx is not initialised";

bool running() {
	if (!laser.isConnected()) {
		startup_state = "LMS1xx is not initialised or was disconnected";
		return false;
	}

	if (!startup_state) return true;

	auto status = laser.queryStatus();
	if (status != 7) {
		startup_state = "LMS1xx is connected but not yet ready for operation";
		DEVLOG_DEBUG("Laserscanner status: %i\n", status);
		return false;
	}

	DEVLOG_DEBUG("Laserscanner is up and running\n");
	laser.scanContinous(true);

	startup_state = nullptr;
	return true;
}

const char *LMS1xx_init() {
	lock_guard<mutex> lg(mtx);

	if (running()) return "LMS1xx is already fully initialised";

	if (laser.isConnected()) laser.disconnect();

	laser.connect("192.168.0.1");
	if (!laser.isConnected()) laser.connect("169.254.173.219");
	if (!laser.isConnected()) return "LMS1xx could not be connected";

	laser.scanContinous(false);
	laser.stopMeas();
	laser.login();

	scanCfg scanConfig = laser.getScanCfg();
	DEVLOG_DEBUG("Old laser config:\n");
	DEVLOG_DEBUG("Scanning Frequency: %f Hz, AngleResolution: %f deg\n",
	             scanConfig.scaningFrequency/100.0, scanConfig.angleResolution/10000.0);
	DEVLOG_DEBUG("start Angle: %f,  stop Angle: %f\n",
	             scanConfig.startAngle/10000.0, scanConfig.stopAngle/10000.0);

	scanConfig.scaningFrequency = 5000;
	scanConfig.angleResolution = 5000;
	scanConfig.startAngle = -450000;
	scanConfig.stopAngle = 2250000;

	DEVLOG_DEBUG("New laser config:\n");
	DEVLOG_DEBUG("Scanning Frequency: %f Hz, AngleResolution: %f deg\n",
	             scanConfig.scaningFrequency/100.0, scanConfig.angleResolution/10000.0);
	DEVLOG_DEBUG("start Angle: %f,  stop Angle: %f\n",
	             scanConfig.startAngle/10000.0, scanConfig.stopAngle/10000.0);

	laser.setScanCfg(scanConfig);

	scanDataCfg cc;
	cc.deviceName = false;
	cc.encoder = 0;
	cc.outputChannel = 3;
	cc.remission = true;
	cc.resolution = 0;
	cc.position = false;
	cc.outputInterval = 4;

	laser.setScanDataCfg(cc);

	laser.startDevice();
	laser.startMeas();

	return nullptr;
}

const char *LMS1xx_deinit() {
	lock_guard<mutex> lg(mtx);

	if (!laser.isConnected()) return startup_state;
	laser.disconnect();
	startup_state = "LMS1xx was deinitialised";
	return nullptr;
}

static scanData scan_data;

const char *LMS1xx_fetchLatest() {
	lock_guard<mutex> lg(mtx);

	if (!running()) return startup_state;

	laser.flush();
	if (!laser.getScanData(scan_data)) return "Could not get scan data";
	return nullptr;
}

const char *LMS1xx_measureNearest(uint16_t &val) {
	lock_guard<mutex> lg(mtx);

	if (!running()) return startup_state;

	uint16_t minimum = 0xffff;
	// look at 45°-225° only
	for (int i = 90; i < scan_data.dist_len1 - 90; i++) {
		if (scan_data.dist1[i] > 10 && scan_data.dist1[i] < minimum) {
			minimum = scan_data.dist1[i];
		}
	}

	val = minimum;
	return nullptr;
}

const char *LMS1xx_measureFarthest(uint16_t &val) {
	lock_guard<mutex> lg(mtx);

	if (!running()) return startup_state;

	uint16_t maximum = 0;
	// look at 45°-225° only
	for (int i = 90; i < scan_data.dist_len1 - 90; i++) {
		if (scan_data.dist1[i] > maximum) maximum = scan_data.dist1[i];
	}

	val = maximum;
	return nullptr;
}
