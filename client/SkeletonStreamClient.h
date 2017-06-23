#ifndef SKELETONSTREAMCLIENT_H
#define SKELETONSTREAMCLIENT_H

#include <string>
#include <thread>
#include <atomic>

class SkeletonStreamClient{
public:
	SkeletonStreamClient(const std::string& serverIp);
	~SkeletonStreamClient();
private:
	std::thread thread;
	std::atomic_bool bRunThread;
};

#endif // SKELETONSTREAMCLIENT_H
