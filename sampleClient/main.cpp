#include <iostream>

#include <SkeletonStreamClient.h>


int main(){

	SkeletonStreamClient client("84.84.84.158");

	while(true){
		client.process();

		if(client.hasSkeleton()){
			auto pos = client.getJointPosition(JointID::HandLeft);
			auto orientation = client.getJointOrientation(JointID::WristLeft);
			auto eulers = glm::eulerAngles(orientation);
			std::cout << "LEFT HAND POS: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
			//std::cout << "LEFT WRIST EULERS: " << eulers.x << ", " << eulers.y << ", " << eulers.z << std::endl;
		}
	}

	return 0;
}
