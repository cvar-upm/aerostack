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

#include "boost/version.hpp"

#include "ros/ros.h"
#include "droneloggerrospublisher.h"
#include "std_msgs/String.h"
#include "droneloggerrostopicsubscriber.h"
#include "droneloggerrosbasicmodule.h"



std::string stringCallback(const std_msgs::String::ConstPtr &msg) { return msg->data; }


int main(int argc,char **argv) {

    std::cout << "Using Boost "
              << BOOST_VERSION / 100000     << "."  // major version
              << BOOST_VERSION / 100 % 1000 << "."  // minior version
              << BOOST_VERSION % 100                // patch level
              << std::endl;


    /* PRUEBA DroneLoggerROSPublisher DroneLoggerROSTopicSubscriber<> */
    {
        //Ros Init
        ros::init(argc, argv, "code_tests_cvgloggerROS");
        ros::NodeHandle n;
        ros::Rate moduleRate(30.0);

        DroneLoggerROSPublisher drone_logger_ros_publisher;
        drone_logger_ros_publisher.open(n);

        DebugStringStacker debug_string_stacker1;
        DebugStringStacker debug_string_stacker2;
        DebugStringStacker debug_string_stacker3;
        DebugStringStacker debug_string_stacker4;
        DebugStringStacker debug_string_stacker5;

        DroneLoggerROSTopicSubscriber<std_msgs::String::ConstPtr> string_topic_subscriber(n, "prueba.molona", DRONE_LOGGER_EVENTSTRING_PUBL, &stringCallback, ros::Time::now(), 1);

        while (ros::ok) {
            ros::spinOnce();

            debug_string_stacker1 << "prueba 1" << std::endl;
            debug_string_stacker2 << "prueba 2" << std::endl;
            debug_string_stacker3 << "prueba 3" << std::endl;
            debug_string_stacker4 << "prueba 4" << std::endl;
            debug_string_stacker5 << "prueba 5" << std::endl;

            debug_string_stacker1 << "end prueba 1" << std::endl;
            debug_string_stacker2 << "end prueba 2" << std::endl;
            debug_string_stacker3 << "end prueba 3" << std::endl;
            debug_string_stacker4 << "end prueba 4, important data" << std::endl; debug_string_stacker4.setPriorityFlag();
            debug_string_stacker5 << "end prueba 5" << std::endl;

//            std::string all_my_debug_strings;
//            bool priority_flag = false;
//            all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings(priority_flag);
//            std::cout << "PRUEBA DebugStringStacker" << std::endl;
//            std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;

            drone_logger_ros_publisher.run();

            std::string all_my_debug_strings;
            bool priority_flag = false;
            all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings(priority_flag, true, 1);
//            std::cout << "PRUEBA DebugStringStacker" << std::endl;
//            std::cout << all_my_debug_strings << "priority_flag:" << priority_flag << std::endl << std::endl;

            moduleRate.sleep();
        }
    }

    return 0;
}
