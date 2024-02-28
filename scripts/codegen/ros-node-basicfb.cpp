@require(Assert, ros, iec61499)
@Assert(iec61499.blockType() == "basic", "This template only works for simple FBs")\
@ros.AssertROSCompatibleInterface()\
@ros.AssertROSCompatibleECC()\
#include "rclcpp/rclcpp.hpp"

// Includes for ROS messages (sockets/plugs)
@for sock in iec61499.interfaces("Sockets"):
#include <@ros.include_file(ros.msgtype(sock))>
@end
@for plug in iec61499.interfaces("Plugs"):
#include <@ros.include_file(ros.msgtype(plug))>
@end

// Global declarations from 4diac
@iec61499.nativeCode("ROS:Global")
// End global declarations from 4diac

using std::placeholders::_1;

class @ros.className() : public rclcpp::Node {

@for sock in iec61499.interfaces("Sockets"):
	rclcpp::Subscription<@ros.msgtype(sock)>::SharedPtr sub_@iec61499.name(sock);
@end
@for plug in iec61499.interfaces("Plugs"):
	rclcpp::Publisher<@ros.msgtype(plug)>::SharedPtr pub_@iec61499.name(plug);
@end
	enum class State {
@for state in iec61499.states():
		@iec61499.name(state),
@end
		_NUM_STATES
	} state = @iec61499.name(iec61499.states()[0]);

	// Class declarations from 4diac
	@iec61499.nativeCode("ROS:Class")
	// End class declarations from 4diac

public:
	@{ros.className()}() : Node("@ros.className()") {
		auto default_qos = rclcpp::QoS(rclcpp::SystemDefaultsQoS());

@for sock in iec61499.interfaces("Sockets"):
		sub_@iec61499.name(sock) = this->create_subscription<@ros.msgtype(sock)>("@iec61499.type(sock)", default_qos, std::bind(&@ros.className()::topic_callback_@iec61499.name(sock), this, _1));
@end
@for plug in iec61499.interfaces("Plugs"):
		pub_@iec61499.name(plug) = this->create_publisher<@ros.msgtype(plug)>("@iec61499.type(plug)", 10);
@end
	}

private:
@for sock in iec61499.interfaces("Sockets"):
	void topic_callback_@{iec61499.name(sock)}(@ros.msgtype(sock) msg) {
		// Do the state transition first
		switch (state) {
@for trans in iec61499.transitions(sock):
		case State::@iec61499.name(iec61499.sourceState(trans)):
			state = State::@iec61499.name(iec61499.targetState(trans));
			execute_actions_@{iec61499.name(iec61499.targetState(trans))}(msg);
			break;
@end
		default:
			std::cerr << "Invalid message @iec61499.name(sock) in state " << int(state) << "\n";
		}
	}
@end

@for state in iec61499.states():
@if ros.incoming_message(state) is not None:
	void execute_actions_@{iec61499.name(state)}(@ros.msgtype(ros.incoming_message(state)) msg = @{ros.msgtype(ros.incoming_message(state))}()) {
@for action in iec61499.actions(state):
		{
			auto result = algorithm_@{iec61499.algName(action)}(msg);
			pub_@iec61499.pinName(action)->publish(result);
		}
@end
@else:
	void execute_actions_@{iec61499.name(state)}() {
@for action in iec61499.actions(state):
		{
			auto result = algorithm_@{iec61499.algName(action)}();
			pub_@iec61499.pinName(action)->publish(result);
		}
@end
@end
@for trans in iec61499.outgoingTransitions(state):
@if iec61499.isUnconditional(trans):
		state = State::@iec61499.name(iec61499.targetState(trans));
		execute_actions_@{iec61499.name(iec61499.targetState(trans))}();
@end
@end
	}
@end

@for alg in iec61499.algorithms():
@if ros.incoming_message(alg) is not None:
	@ros.msgtype(ros.outgoing_message(alg)) algorithm_@{iec61499.name(alg)}(@ros.msgtype(ros.incoming_message(alg)) msg) {
@else:
	@ros.msgtype(ros.outgoing_message(alg)) algorithm_@{iec61499.name(alg)}() {
@end
		// Algorithm code from 4diac
		@iec61499.nativeCode("ROS", alg)
		// End algorithm code from 4diac
	}
@end

};

int main(int argc, char *argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<@ros.className()>());
	rclcpp::shutdown();
	return 0;
}
