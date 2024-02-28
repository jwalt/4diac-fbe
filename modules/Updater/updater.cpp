#include <amqpcpp.h>
#include <iostream>
#include <amqpcpp/linux_tcp.h>
#include <json/json.h>
#include <vector>
#include <json/writer.h>
#include <chrono>
#include <poll.h>
#include <unistd.h>

using namespace std;

class AMQPHandler : public AMQP::TcpHandler
{
	private:
		void onConnected(AMQP::TcpConnection* connection) override {
			std::cout << "[AMQP] connected\n";
		}

		void onError(AMQP::TcpConnection* connection, const char* message) override {
			std::cout << "[AMQP] connection error: " << message << "\n";
			exit(1);
		}

		void onClosed(AMQP::TcpConnection* connection) override {
			std::cout << "[AMQP] closed\n";
		}

		void monitor(AMQP::TcpConnection* connection, int fd, int flags) override {
			//cout << "[AMQP] monitoring " << fd << "/" << flags << "\n";
			if (flags & AMQP::readable) {
				fd1 = fd;
			} else {
				if (fd1 == fd) fd1 = -1;
			}
		}

		int fd1 = -1;

	public:
		AMQPHandler() = default;

		int check(int timeout_ms) {
			if (fd1 == -1) return -1;

			pollfd pfd[1];
			pfd[0].fd = fd1;
			pfd[0].events = POLLIN;
			//cout << "."; cout.flush();
			auto res = poll(pfd, 1, timeout_ms);
			//cout << res; cout.flush();
			if (res == 0) return -1;
			if (res == -1) {
				cout << "[AMQP] poll failure\n";
				return -1;
			}

			return pfd[0].fd;
		}
};


struct ArtifactJob {
	string actionID;
	string moduleID;
	string URL;
	string file;
};

static const string EXCHANGE = "updateExchange";
static const string QUEUE = "updateQueue";
static const string PUBLISHER = "dmf.exchange";
static const string USER = "guest";
static const string PASS = "guest";

struct AMQPUpdater {

	AMQPUpdater(string server, string id)
		: handler()
		, address("amqp://"+USER+":"+PASS+ "@"+server+"/")
		, connection(&handler, address)
		, channel(&connection)
		, deviceID(id)
	{
		channel.declareQueue(QUEUE);
		channel.declareExchange(EXCHANGE);
		channel.bindQueue(EXCHANGE, QUEUE, "");
	}

	void registerDevice() {
		AMQP::Table h;
		h["sender"] = deviceID;
		h["type"] = "THING_CREATED";
		h["tenant"] = "DEFAULT";
		h["thingId"] = deviceID;

		auto payload = "{\"name\":\"" + deviceID + "\"}";
		AMQP::Envelope msg(payload.c_str(), payload.size());

		msg.setHeaders(h);
		msg.setContentType("application/json");
		msg.setReplyTo(EXCHANGE);
		std::cout << "[UPD] registering device\n";
		channel.publish(PUBLISHER, "", msg);
	}

	void start() {
		channel.consume(QUEUE)
			.onReceived([=](const auto &arg1, auto arg2, auto arg3) { this->messageCb(arg1, arg2, arg3); })
			.onSuccess([=](auto arg) { this->startCb(arg); })
			.onError([=](auto arg) { this->errorCb(arg); });

	}

	void startCb(const std::string &consumertag) {
		std::cout << "[UPD] checking for new updates\n";
	}

	void errorCb(const char *message) {
		std::cout << "[UPD] update check error: " << message << "\n";
	}

	void messageCb(const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
		channel.ack(deliveryTag);
		AMQP::Table header;
		header = message.headers();
		if ((const std::string&)header.get("thingId") != deviceID) return;

		auto type = (const std::string&)header.get("type");
		auto topic = (const std::string&)header.get("topic");
		if (type == "THING_DELETED") {
			std::cout << "[UPD] The device named " << deviceID << " has been deleted by the server\n";
			exit(0);
		} else if (topic == "DOWNLOAD_AND_INSTALL") {
			processUpdate(message.body());
		} else if (topic == "CANCEL_DOWNLOAD") {
			std::cout<< "[UPD] The update process has been canceled by the server\n";
		}
	}

	void poll() {
		int fd = handler.check(1000);
		if (fd == -1) return;

		connection.process(fd, AMQP::readable);
		download();
	}

	void download() {
		if (!jobs.size()) return;

		setState(jobs[0].actionID, jobs[0].moduleID, "DOWNLOAD");
		for (auto &artifact : jobs) {
			updateDownloadState(artifact.file, "RUNNING");
			system(("./fetch.sh '" + artifact.URL + "'").c_str());
			updateDownloadState(artifact.file, "DOWNLOADED");
			setState(artifact.actionID, artifact.moduleID, "RETRIEVED");
		}

		for (auto &artifact : jobs) {
			setState(artifact.actionID, artifact.moduleID, "RUNNING");
		}
		cout << "[UPD] Starting updated binaries\n";
		sleep(1);
		auto rc = system("./update.sh");
		if (rc) {
			cout << "[UPD] Update did not start successfully. Rolling back.\n";
			system("./rollback.sh");
		} else {
			cout << "[UPD] Update initialized successfully. Finalizing.\n";
			system("./finalize.sh");
		}
		for (auto &artifact : jobs) {
			setState(artifact.actionID, artifact.moduleID, rc?"ERROR":"FINISHED");
		}
		jobs.clear();
	}

	void updateDownloadState(string file, string status) {
		std::string msg, attr;
		if (status == "RUNNING") {
			msg = "Download of "+file+ " has started.";
			attr = "{\"attributes\":{\""+file+"\":\"started\"},\"mode\":\"MERGE\"}";

		} else if (status == "DOWNLOADED"){
			msg = file + " has been downloaded successfully.";
			attr = "{\"attributes\":{\""+file+"\":\"downloaded\"},\"mode\":\"MERGE\"}";

		} else if (status == "ERROR"){
			msg = "The download process of "+file+ " has failed.";
			attr = "{\"attributes\":{\""+file+"\":\"error\"},\"mode\":\"MERGE\"}";

		} else if (status == "CANCELED"){
			msg = "The download process of "+file+ " has been cancelled.";
			attr = "{\"attributes\":{\""+file+"\":\"cancelled\"},\"mode\":\"MERGE\"}";
		}

		updateCustomState(attr);
		cout << "[UPD] " << msg << "\n";
	}

	void updateCustomState(string attr) {
		AMQP::Table headers;
		headers["sender"] = deviceID;
		headers["thingId"] = deviceID;
		headers["type"] = "EVENT";
		headers["tenant"] = "DEFAULT";
		headers["topic"] = "UPDATE_ATTRIBUTES";

		AMQP::Envelope env(attr.c_str(), attr.size());
		env.setContentType("application/json");
		env.setReplyTo(EXCHANGE);
		env.setHeaders(headers);
		channel.publish(PUBLISHER, "", env);
	}

	void setState(string actionID, string moduleID, string newstate) {
		cout << "[UPD] Action " << actionID << " module " << moduleID << " entered new state: " << newstate << "\n";

		AMQP::Table headers;
		headers["sender"] = deviceID;
		headers["thingId"] = deviceID;
		headers["type"] = "EVENT";
		headers["tenant"] = "DEFAULT";
		headers["topic"] = "UPDATE_ACTION_STATUS";

		std::string msg = "{\"actionId\":"+actionID+",\"softwareModuleId\":"+moduleID+",\"actionStatus\":\""+newstate+"\",\"message\":[\"entering state "+newstate+" (Action "+actionID+" Module "+moduleID+")\"]}";
		AMQP::Envelope env(msg.c_str(), msg.size());
		env.setContentType("application/json");
		env.setReplyTo(EXCHANGE);
		env.setHeaders(headers);
		channel.publish(PUBLISHER, "", env);
		updateCustomState("{\"attributes\":{\"STATE\":\""+newstate+"\"},\"mode\":\"MERGE\"}");
	}

	void processUpdate(string msg) {
		Json::Reader reader;
		Json::Value jsondata;
		if (!reader.parse(msg, jsondata)) {
			cout << "[UPD] could not parse update message\n";
			return;
		}
		
		const Json::Value ListSM = jsondata["softwareModules"];
		auto actionID = jsondata["actionId"].asInt64();
		
		std::cout << "\n[UPD] -----------------------------------------------\n";
		std::cout << "[UPD] | Thing: " << deviceID << ", Action: " << actionID << "\n";
		
		ArtifactJob aj;
		aj.actionID = to_string(actionID);
		for (auto i = 0u; i < ListSM.size(); i++) {
			auto moduleID = ListSM[i]["moduleId"].asInt64();
			aj.moduleID = to_string(moduleID);
			std::cout << "[UPD] | ModuleId: " << moduleID << ",  type: " << ListSM[i]["moduleType"]  << ", version: " << ListSM[i]["moduleVersion"] << "\n"; 
			const Json::Value SW = ListSM[i]["artifacts"];
			for (auto j = 0u; j < SW.size(); j++){
				auto linkDL = SW[j]["urls"]["HTTP"].asString();
				auto filename = SW[j]["filename"].asString();
				std::cout << "[UPD] | Filename: " << filename << ", " << "Size: " << SW[j]["size"] << "\n";
				std::cout << "[UPD] | SHA1: " << SW[j]["hashes"]["sha1"] << "\n";
				std::cout << "[UPD] | URL: " << linkDL << "\n";
				aj.URL = linkDL;
				aj.file = filename;
				jobs.push_back(aj);
			}
		}
		std::cout << "[UPD] -----------------------------------------------\n\n";
	}

private:
	AMQPHandler handler;
	AMQP::Address address;
	AMQP::TcpConnection connection;
	AMQP::TcpChannel channel;
	string deviceID;
	int currentPartition = 0;
	vector<ArtifactJob> jobs;
};

int main(int argc, const char *argv[]) {
	if (argc < 3) {
		cerr << "Usage: $0 <server> <deviceID>\n";
		return 1;
	}

	AMQPUpdater channel(argv[1], argv[2]);
	channel.registerDevice();
	channel.start();

	for (;;) {
		channel.poll();
	}

}

