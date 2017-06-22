#pragma once

#include <atomic>
#include <thread>

#include "zmq.hpp"

class Sender{
public:
	Sender();
	~Sender();

private:
	std::thread thread;
	std::atomic_bool bKeepOnRunning;
};

