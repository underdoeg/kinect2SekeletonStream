#include <iostream>

#include <SkeletonStreamClient.h>

int main(){

	SkeletonStreamClient client("84.84.84.158");

	while(true){
		client.process();

		if(client.hasSkeleton()){
			auto pos = client.getJointPosition(JointID::HandLeft);
			std::cout << "LEFT HAND: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
		}
	}

	return 0;
}
