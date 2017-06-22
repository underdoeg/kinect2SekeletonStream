#include "Sender.h"
#include <iostream>

Sender::Sender(){

	bKeepOnRunning = true;

	thread = std::thread([&] {

		auto protocolPublisher = "tcp://*:5566";

		zmq::context_t context(1);
		zmq::socket_t socketPublisher(context, ZMQ_XPUB);
		try {
			while (bKeepOnRunning) {
				zmq::message_t in;
				while (socketPublisher.recv(&in, ZMQ_DONTWAIT)) {

				}
			}
			socketPublisher.close();
		}catch (zmq::error_t e) {
			std::cerr << e.what();
		}
	});
}


Sender::~Sender(){
}
