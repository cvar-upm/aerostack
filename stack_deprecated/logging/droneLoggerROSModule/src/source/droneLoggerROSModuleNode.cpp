//////////////////////////////////////////////////////
//  droneLoggerROSModuleNode.cpp
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
#include "droneloggerrosmodule.h"
#include "communication_definition.h"

int main(int argc,char **argv) {
    //Ros Init
    ros::init(argc, argv, MODULE_NAME_DRONE_LOGGER);
    ros::NodeHandle n;

    DroneLoggerROSModule drone_logger_ros_module(n);

    try {
        while(ros::ok()) {
            //Read messages
            ros::spinOnce();

            //Run DroneLogger ROSModule
            if(drone_logger_ros_module.run())
            {
            }
            //Sleep
            drone_logger_ros_module.sleep();
        }
    } catch (std::exception &ex) {
        std::cout << "[ROSNODE] Exception :" << ex.what() << std::endl;
    }
    return 1;
}
