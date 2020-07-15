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
#include <list>
#include <vector>

#include "debugstringstacker.h"

#include "ros/ros.h"
#include "droneloggerrospublisher.h"
#include "std_msgs/String.h"
#include "droneloggerrostopicsubscriber.h"
#include "droneloggerrosbasicmodule.h"

std::string stringCallback(const std_msgs::String::ConstPtr &msg) { return msg->data; }


int main(int argc,char **argv) {
    /* PRUEBA DroneLoggerROSBasicModule> */

    //Ros Init
    ros::init(argc, argv, "code_tests_cvgloggerROS2");
    ros::NodeHandle n;

    DroneLoggerROSBasicModule drone_logger_ros_basic_module(n);

    try {
        while(ros::ok()) {
            //Read messages
            ros::spinOnce();

            //Run Drone Logger Basic Module
            if(drone_logger_ros_basic_module.run()) {

            }
            drone_logger_ros_basic_module.sleep();
        }
    } catch (std::exception &ex) {
        std::cout << "[ROSNODE] Exception :" << ex.what() << std::endl;
    }

    return 1;
}
