#pragma once

#include <array>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace kinectStream{

    enum class JointID : unsigned short{
        SpineBase = 0,
        SpineMid = 1,
        Neck = 2,
        Head = 3,
        ShoulderLeft = 4,
        ElbowLeft = 5,
        WristLeft = 6,
        HandLeft = 7,
        ShoulderRight = 8,
        ElbowRight = 9,
        WristRight = 10,
        HandRight = 11,
        HipLeft = 12,
        KneeLeft = 13,
        AnkleLeft = 14,
        FootLeft = 15,
        HipRight = 16,
        KneeRight = 17,
        AnkleRight = 18,
        FootRight = 19,
        SpineShoulder = 20,
        HandTipLeft = 21,
        ThumbLeft = 22,
        HandTipRight = 23,
        ThumbRight = 24
    };

    struct Joint{
        glm::quat orientation;
        glm::vec3 position;
    };

    struct Skeleton{
        uint64_t id;
        std::array<Joint, 25> joints;
    };

    static const std::vector<std::array<JointID, 2>> jointConnections =
    {
        {{JointID::SpineBase, JointID::SpineMid}},
        {{JointID::SpineMid, JointID::SpineShoulder}},
        {{JointID::SpineShoulder, JointID::Neck}},
        {{JointID::Neck, JointID::Head}},

        // arm right
        {{JointID::SpineShoulder, JointID::ShoulderRight}},
        {{JointID::ShoulderRight, JointID::ElbowRight}},
        {{JointID::ElbowRight, JointID::WristRight}},
        {{JointID::WristRight, JointID::ThumbRight}},
        {{JointID::WristRight, JointID::HandRight}},
        {{JointID::HandRight, JointID::HandTipRight}},

        // arm left
        {{JointID::SpineShoulder, JointID::ShoulderLeft}},
        {{JointID::ShoulderLeft, JointID::ElbowLeft}},
        {{JointID::ElbowLeft, JointID::WristLeft}},
        {{JointID::WristLeft, JointID::ThumbLeft}},
        {{JointID::WristLeft, JointID::HandLeft}},
        {{JointID::HandLeft, JointID::HandTipLeft}},

        // leg right
        {{JointID::SpineBase, JointID::HipRight}},
        {{JointID::HipRight, JointID::KneeRight}},
        {{JointID::KneeRight, JointID::AnkleRight}},
        {{JointID::AnkleRight, JointID::FootRight}},

        // leg left
        {{JointID::SpineBase, JointID::HipLeft}},
        {{JointID::HipLeft, JointID::KneeLeft}},
        {{JointID::KneeLeft, JointID::AnkleLeft}},
        {{JointID::AnkleLeft, JointID::FootLeft}},
    };

}
