#pragma once

#include <atomic>
#include <thread>
#include <vector>
#include <mutex>

#include "types.h"

#include "zmq.hpp"

class Sender{
public:
	Sender();
	~Sender();

	void setSkeletons(const std::vector<kinectStream::Skeleton>& skeletons);

private:
	std::vector<kinectStream::Skeleton> skeletons;
	std::mutex mutex;
	std::thread thread;
	std::atomic_bool bKeepOnRunning;
};

