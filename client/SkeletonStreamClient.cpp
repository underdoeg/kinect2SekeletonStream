#include "SkeletonStreamClient.h"
#include <config.h>
#include <zmq.hpp>
#include <iostream>

using namespace kinectStream;

SkeletonStreamClient::SkeletonStreamClient(const std::string& serverIp){
	if(!serverIp.empty()) initConnection(serverIp);
}

void SkeletonStreamClient::initConnection(const std::string& serverIp){
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

unsigned SkeletonStreamClient::getSkeletonClosestXZ(float x, float z){
	unsigned ret = 0;
	float dist = std::numeric_limits<float>::max();
	for(unsigned i=0; i<getNumSkeletons(); i++){
		auto p = getJointPosition(JointID::SpineBase, i);
		auto d = glm::distance(glm::vec2{x, z}, glm::vec2{p.x, p.z});
		if(d < dist){
			dist = d;
			ret = i;
		}
	}
	return ret;
}


