#include "SkeletonStreamClient.h"
#include <config.h>
#include <zmq.hpp>
#include <iostream>

SkeletonStreamClient::SkeletonStreamClient(const std::string &serverIp){
	bRunThread = true;

	thread = std::thread([&, serverIp]{

			auto protocolSubscriber = "tcp://"+serverIp+":"+std::to_string(kinectStream::broadcastPort);

			zmq::context_t context(1);
			zmq::socket_t socketSubscriber(context, ZMQ_SUB);
			socketSubscriber.connect(protocolSubscriber);
			socketSubscriber.setsockopt(ZMQ_SUBSCRIBE, "hello", 0);

			while(bRunThread){
				//NetworkEntry::List data;

				std::cout << "running" << std::endl;

				zmq::message_t msg;
				socketSubscriber.recv(&msg);

				std::cout << msg.size() << std::endl;
			}
	});
}

SkeletonStreamClient::~SkeletonStreamClient(){
	bRunThread = false;
	thread.join();
}
