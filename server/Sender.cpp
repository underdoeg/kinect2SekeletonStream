#include "Sender.h"
#include "config.h"

#include <iostream>

using namespace kinectStream;

Sender::Sender(){

	bKeepOnRunning = true;

	thread = std::thread([&] {

		auto protocolPublisher = "tcp://*:"+std::to_string(broadcastPort);

		zmq::context_t context(1);
		zmq::socket_t socketPublisher(context, ZMQ_XPUB);
		try {

			socketPublisher.bind(protocolPublisher);

			while (bKeepOnRunning) {
				zmq::message_t in;

				// check for new subscribers
				while (socketPublisher.recv(&in, ZMQ_DONTWAIT)) {
					std::cout << "New Sender client connected";
				}

				mutex.lock();
				//auto skeletonsCopy = skeletons;
				size_t totalBytes = skeletons.size() * sizeof(Skeleton);
				std::vector<uint8_t> data(totalBytes + 1);
				data[0] = skeletons.size();
				memcpy(data.data() + 1, skeletons.data(), totalBytes);
				mutex.unlock();

				socketPublisher.send(data.data(), totalBytes + 1);

				std::this_thread::sleep_for(std::chrono::milliseconds(int(1. / 60. * 1000)));
			}
			socketPublisher.close();
		}catch (zmq::error_t e) {
			std::cerr << e.what();
		}
	});
}

Sender::~Sender(){
	bKeepOnRunning = false;
	thread.join();
}

void Sender::setSkeletons(const std::vector<Skeleton>& s){
	mutex.lock();
	skeletons = s;
	mutex.unlock();
}
