//////////////////////////////////////////////////////
//  DroneCVIARC14ROSModule_KeypointsNode.h
//
//  Created on: Jul 25, 2014
//      Author: joselusl
//
//  Last modification on: Jul 25, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////



//I/O Stream
//std::cout
#include <iostream>

#include <string>


// ROS
//ros::init(), ros::NodeHandle, ros::ok(), ros::spinOnce()
#include "ros/ros.h"



//ROSModule
#include "droneExamplePackageROSModuleHeader.h"


//Communication Definition -> Deprecated!
//#include "communication_definition.h"

//Nodes names -> Deprecated!
//MODULE_NAME_DRONE_KEYPOINTS_GRID_DETECTOR
//#include "nodes_definition.h"





using namespace std;

int main(int argc, char **argv)
{
    //Init
    ros::init(argc, argv, "NonInitializedNode"); //Say to ROS the name of the node and the parameters
    ros::NodeHandle n; //Este nodo admite argumentos!!

    std::string node_name=ros::this_node::getName();
    cout<<"node name="<<node_name<<endl;

    //CONFIGS
    /*
    //Camera parameters
    std::string camera_calib_param;
    ros::param::get("~camera_calib_param", camera_calib_param);
    cout<<"camera_calib_param="<<camera_calib_param<<endl;
    if ( camera_calib_param.length() == 0)
    {
        cout<<"[ROSNODE] Error with camera calibration paramaters"<<endl;
    }

    //grid parameters
    std::string grid_param;
    ros::param::get("~grid_param", grid_param);
    cout<<"grid_param="<<grid_param<<endl;
    if ( grid_param.length() == 0)
    {
        cout<<"[ROSNODE] Error with grid paramaters"<<endl;
    }
    */

    //TOPICS!!
    /*
    //Camera subscription topic
    std::string camera_topic_name;
    ros::param::get("~camera_topic_name",camera_topic_name);
    cout<<"camera_topic_name="<<camera_topic_name<<endl;
    if (camera_topic_name.length()==0)
    {
        cout<<"[ROSNODE] Error with video subscription topic";
    }

    //Keypoints publ topic
    std::string keypointsPublTopicName;
    ros::param::get("~keypoints_topic_name",keypointsPublTopicName);
    cout<<"keypointsPublTopicName="<<keypointsPublTopicName<<endl;
    if (keypointsPublTopicName.length()==0)
    {
        cout<<"[ROSNODE] Error with publisher topic";
    }
    */

    //Class definition
    DroneExamplePackageROSModule MyDroneExamplePackageROSModule;

    //SETTERS
    /*
    if(!MyDroneExamplePackageROSModule.setCalibCamera(camera_calib_param))
        return 0;

    if(!MyDroneExamplePackageROSModule.setTopicConfigs(camera_topic_name,keypointsPublTopicName))
        return 0;

    if(!MyDroneExamplePackageROSModule.setGridParameters(grid_param))
        return 0;
    */

    //Open!
    MyDroneExamplePackageROSModule.open(n);


    //Loop -> Ashyncronous Module
    while(ros::ok())
    {
        ros::spin();
    }

    return 1;
}

