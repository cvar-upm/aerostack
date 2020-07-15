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

        ros::Time prueba_time;

//        prueba_time.sec = 0;
//        prueba_time.nsec = 0;
//        if (prueba_time.isZero())
//            std::cout << "prueba_time.isZero()" << std::endl;

        ros::Time init_rostime;
        int32_t inittime__sec;
        int32_t inittime_nsec;
        if ( ros::param::has("/drone_log_init_rostime__sec") && ros::param::has("/drone_log_init_rostime_nsec") ) {
            // init_rostime was initialized
            ros::param::get( "/drone_log_init_rostime__sec", inittime__sec);
            ros::param::get( "/drone_log_init_rostime_nsec", inittime_nsec);
            init_rostime.sec  = inittime__sec;
            init_rostime.nsec = inittime_nsec;
        } else {
            // init_rostime was not initialized
            init_rostime = ros::Time::now();
            inittime__sec = init_rostime.sec;
            inittime_nsec = init_rostime.nsec;
            ros::param::set("/drone_log_init_rostime__sec", inittime__sec);
            ros::param::set("/drone_log_init_rostime_nsec", inittime_nsec);
        }

        while (ros::ok) {
            ros::spinOnce();

            moduleRate.sleep();
        }
    }

    return 0;
}

