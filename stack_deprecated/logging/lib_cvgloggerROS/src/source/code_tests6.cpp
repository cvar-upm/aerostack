//////////////////////////////////////////////////////
//  code_tests.cpp
//
//  Created on: Aug 22, 2015
//      Author: jespestana
//
//////////////////////////////////////////////////////

#include <iostream>
#include "ros/ros.h"
#include <sys/time.h>
#include <time.h>

int main(int argc,char **argv)
{
    //Ros Init
    ros::init(argc, argv, "pruebas");
    ros::NodeHandle n;

//    std::cout << ros::Time::now().toSec() << std::endl;

    ros::Time current_ros_timestamp = ros::Time::now();
    timeval   current_timestamp     ; gettimeofday(&current_timestamp, NULL);       // :-) Always equals to current_ros_timestamp
    timespec  current_timestamp2    ; clock_gettime( clock(), &current_timestamp2); // :-( Frequently not equal to current_ros_timestamp

    std::cout << "current_ros_timestamp, sec:"  << current_ros_timestamp.sec
                                    << " nsec:" << current_ros_timestamp.nsec << std::endl;
    std::cout << "current_timestamp    , sec:"  << current_timestamp.tv_sec
                                    << " nsec:" << current_timestamp.tv_usec << std::endl;
    std::cout << "current_timestamp2   , sec:"  << current_timestamp2.tv_sec
                                    << " nsec:" << current_timestamp2.tv_nsec << std::endl;

    timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    gettimeofday(&tv2, NULL);
//    if (tv2 > tv1) {} // error

    return 0;
}


