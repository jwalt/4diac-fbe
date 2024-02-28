@require(Assert, ros, iec61499)
@Assert(iec61499.blockType() == "simple", "This template only works for simple FBs")\
@ros.AssertROSCompatibleInterface()\
@Assert(len(iec61499.interfaces("Plugs")) == 1, "This template requires exactly one Plug")\
@Assert(len(iec61499.interfaces("Sockets")) == 1, "This template requires exactly one Socket")\
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
		auto result = algorithm_@{iec61499.name(sock)}(msg);
		pub_@{iec61499.name(iec61499.interfaces("Plugs")[0])}->publish(result);
	}

	@ros.msgtype(iec61499.interfaces("Plugs")[0]) algorithm_@{iec61499.name(sock)}(@ros.msgtype(sock) msg) {
		// Algorithm code from 4diac
		@iec61499.nativeCode("ROS")
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
