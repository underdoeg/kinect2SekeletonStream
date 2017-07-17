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
			zmq::message_t msg;
			socketSubscriber.recv(&msg);
			auto data = reinterpret_cast<uint8_t*>(msg.data());
			unsigned amount = data[0];
			data++;
			std::vector<kinectStream::Skeleton> skeletonsTmp(amount);
			for(unsigned i=0; i<amount; i++){
				skeletonsTmp[i] = *reinterpret_cast<kinectStream::Skeleton*>(data);
				data += sizeof(kinectStream::Skeleton);
			}
			mutex.lock();
			skeletonsThread = skeletonsTmp;
			mutex.unlock();
		}
	});
}

SkeletonStreamClient::~SkeletonStreamClient(){
	bRunThread = false;
	thread.join();
}

void SkeletonStreamClient::process(){
	mutex.lock();
	skeletons = skeletonsThread;
	mutex.unlock();
}

bool SkeletonStreamClient::hasSkeleton(){
	return !skeletons.empty();
}

unsigned SkeletonStreamClient::getNumSkeletons(){
	return skeletons.size();
}

Joint SkeletonStreamClient::getJoint(JointID joint, unsigned skeletonIndex){
	assert(getNumSkeletons() > skeletonIndex && "has no Skeleton");
	return getSkeletonList()[skeletonIndex].joints[static_cast<unsigned short>(joint)];
}

glm::vec3 SkeletonStreamClient::getJointPosition(JointID joint, unsigned skeletonIndex){
	return getJoint(joint, skeletonIndex).position;
}

glm::quat SkeletonStreamClient::getJointOrientation(JointID joint, unsigned skeletonIndex){
	return getJoint(joint, skeletonIndex).orientation;
}

const std::vector<Skeleton> SkeletonStreamClient::getSkeletonList(){
	return skeletons;
}
