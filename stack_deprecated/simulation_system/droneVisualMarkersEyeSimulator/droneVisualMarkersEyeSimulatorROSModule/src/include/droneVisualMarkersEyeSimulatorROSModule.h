//////////////////////////////////////////////////////
//  droneVisualMarkersEyeSimulatorROSModule.h
//
//  Created on: Jan 24, 2014
//      Author: joselusl
//
//  Last modification on: Jan 24, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////


#ifndef _DRONE_VISUAL_MARKERS_EYE_SIMULATOR_ROS_MODULE_H
#define _DRONE_VISUAL_MARKERS_EYE_SIMULATOR_ROS_MODULE_H



//I/O stream
//std::cout
#include <iostream>

//Vector
//std::vector
#include <vector>

//String
//std::string, std::getline()
#include <string>

//String stream
//std::istringstream
//#include <sstream>

//File Stream
//std::ofstream, std::ifstream
//#include <fstream>



//droneVisualMarkersEyeSimulator
#include "droneVisualMarkersEyeSimulator.h"


// ROS
#include "ros/ros.h"


//Drone module
#include "droneModuleROS.h"


////Msgs
//drone pose
#include "droneMsgsROS/dronePoseStamped.h"

//obsVector
#include "droneMsgsROS/obsVector.h"
#include "droneMsgsROS/Observation3D.h"


#include "communication_definition.h"


//Freq
const double FREQ_DRONE_VISUAL_MARKERS_EYE_SIMULATOR = 30.0;




/////////////////////////////////////////
// Class DroneVisualMarkersEyeSimulatorROSModule
//
//   Description:
//
/////////////////////////////////////////
class DroneVisualMarkersEyeSimulatorROSModule : public DroneModule
{	
    //Drone
protected:
    DroneVisualMarkersEyeSimulator MyDroneVisualMarkersEyeSimulator;


    //Subscribers
private:
    ros::Subscriber droneInternalPoseSubs;
    void droneInternalPoseCallback(const droneMsgsROS::dronePoseStamped::ConstPtr& msg);
    


    //Publishers
private:
    ros::Publisher droneObsVectorPubl;
    int publishObsVector();
    droneMsgsROS::obsVector droneObsVectorMsgs;



public:
    DroneVisualMarkersEyeSimulatorROSModule();
    ~DroneVisualMarkersEyeSimulatorROSModule();
	
    void open(ros::NodeHandle & nIn, std::string moduleName);
	void close();

protected:
    bool init();


    //Reset
protected:
    bool resetValues();

    //Start
protected:
    bool startVal();

    //Stop
protected:
    bool stopVal();

    //Run
public:
    bool run();
    

};






#endif
