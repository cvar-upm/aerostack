//////////////////////////////////////////////////////
//  code_tests.cpp
//
//  Created on: Dec 11, 2013
//      Author: jespestana
//
//  Last modification on: Dec 11, 2013
//      Author: jespestana
//
//////////////////////////////////////////////////////

#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Header.h"

void headerCallback(const std_msgs::HeaderConstPtr &msg);

int main(int argc,char **argv) {

    /* PRUEBA DroneLoggerROSPublisher DroneLoggerROSTopicSubscriber<> */
    {
        //Ros Init
        ros::init(argc, argv, "code_tests_cvgloggerROS");
        ros::NodeHandle n;
        ros::Rate moduleRate(30.0);

        ros::Subscriber header_subscriber;
        header_subscriber = n.subscribe("topicName", 1, &headerCallback);

        ros::spin();

//        while (ros::ok) {
//            ros::spinOnce();

////            moduleRate.sleep();
//        }
    }

    return 0;
}

void headerCallback(const std_msgs::HeaderConstPtr &server_msg) {
    ros::Time     current_time   = ros::Time::now();
    ros::Duration current_offset = server_msg->stamp - current_time;

    //std::cout << "current_offset = server_msg->stamp - current_time [nanoseconds]:" << std::setfill('0') << std::setw(9) << current_offset.toNSec() << std::endl;
    std::cout << "[ns]:" << std::setfill(' ') << std::setw(12) << current_offset.toNSec() << std::endl;
}

