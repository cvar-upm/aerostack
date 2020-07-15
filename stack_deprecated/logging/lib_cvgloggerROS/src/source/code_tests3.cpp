//////////////////////////////////////////////////////
//  code_tests3.cpp
//
//  Created on: Jan 21, 2013
//      Author: joselusl
//
//  Last modification on: Jan 21, 2013
//      Author: joselusl
//
//////////////////////////////////////////////////////

#include <iostream>


#include "ros/ros.h"

#include "std_msgs/Header.h"




int main(int argc,char **argv) {

    //Ros Init
    ros::init(argc, argv, "code_tests_cvgloggerROS2");
    ros::NodeHandle n;


    ros::Publisher publisher;
    publisher=n.advertise<std_msgs::Header>("topicName",1, true);

    std_msgs::Header msg;
    unsigned int seq=0;

    ros::Rate rate(2.0);

    try {
        while(ros::ok())
        {
            //Read messages
            ros::spinOnce();

            //Header
            msg.seq=seq++;
            msg.stamp=ros::Time::now();

            //Publish
            publisher.publish(msg);

            //sleep
            rate.sleep();


        }
    } catch (std::exception &ex) {
        std::cout << "[ROSNODE] Exception :" << ex.what() << std::endl;
    }

    return 1;
}
