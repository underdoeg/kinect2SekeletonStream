#ifndef SKELETONSTREAMCLIENT_H
#define SKELETONSTREAMCLIENT_H

#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>

#include "Types.h"

using namespace kinectStream;

class SkeletonStreamClient{
public:
	SkeletonStreamClient(const std::string& serverIp);
	~SkeletonStreamClient();

	void process();
	bool hasSkeleton();
	unsigned getNumSkeletons();
	Joint getJoint(JointID joint, unsigned skeletonIndex=0);
	glm::vec3 getJointPosition(JointID joint, unsigned skeletonIndex=0);
	glm::quat getJointOrientation(JointID joint, unsigned skeletonIndex=0);
	const std::vector<kinectStream::Skeleton> getSkeletonList();
private:
	std::vector<kinectStream::Skeleton> skeletons, skeletonsThread;

	std::thread thread;
	std::atomic_bool bRunThread;
	std::mutex mutex;
};

#endif // SKELETONSTREAMCLIENT_H
