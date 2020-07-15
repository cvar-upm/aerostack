//////////////////////////////////////////////////////
//  droneVisualMarkersEyeSimulatorNode.h
//
//  Created on: Jan 24, 2014
//      Author: joselusl
//
//  Last modification on: Jan 24, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////





//I/O Stream
//std::cout
#include <iostream>



// ROS
//ros::init(), ros::NodeHandle, ros::ok(), ros::spinOnce()
#include "ros/ros.h"


//Drone Localizer
#include "droneVisualMarkersEyeSimulatorROSModule.h"


//Communication Definition
//MODULE_NAME_LOCALIZER
#include "nodes_definition.h"



using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,MODULE_NAME_DRONE_VISUAL_MARKERS_EYE_SIMULATOR); //Say to ROS the name of the node and the parameters
  	ros::NodeHandle n;

    //Init
    std::cout<<"[ROSNODE] Starting Drone Visual Markers Eye Simulator"<<std::endl;


    //Simulator
    DroneVisualMarkersEyeSimulatorROSModule MyDroneVisualMarkersEyeSimulatorROSModule;
    MyDroneVisualMarkersEyeSimulatorROSModule.open(n,MODULE_NAME_DRONE_VISUAL_MARKERS_EYE_SIMULATOR);


    //Loop
    while(ros::ok())
    {
        //Read ros messages
        ros::spinOnce();

        if(!MyDroneVisualMarkersEyeSimulatorROSModule.run())
        {
            //cout<<"[ROSNODE] Error while running"<<endl;
        }
        MyDroneVisualMarkersEyeSimulatorROSModule.sleep();
    }
    return 1;
}
