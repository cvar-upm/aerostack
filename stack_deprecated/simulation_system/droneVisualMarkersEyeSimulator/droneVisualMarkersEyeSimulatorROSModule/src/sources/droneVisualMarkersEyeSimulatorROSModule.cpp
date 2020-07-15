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


#include "droneVisualMarkersEyeSimulatorROSModule.h"


using namespace std;


DroneVisualMarkersEyeSimulatorROSModule::DroneVisualMarkersEyeSimulatorROSModule() :
    DroneModule(droneModule::active,FREQ_DRONE_VISUAL_MARKERS_EYE_SIMULATOR)
{
    if(!init())
        cout<<"Error init"<<endl;
        
    return;
}



DroneVisualMarkersEyeSimulatorROSModule::~DroneVisualMarkersEyeSimulatorROSModule()
{
	close();
	return;
}

void DroneVisualMarkersEyeSimulatorROSModule::open(ros::NodeHandle & nIn, std::string moduleName)
{
	//Node
    DroneModule::open(nIn,moduleName);


    //Configuration
    //read file with the aruco list
    if(!MyDroneVisualMarkersEyeSimulator.readVisualMarksDefinitionFile(stackPath+"configs/drone"+stringId+"/arUcoList.xml"))
        return;

    //read file with the pose of the arucos
    if(!MyDroneVisualMarkersEyeSimulator.readVisualMarksPoseFile(stackPath+"configs/drone"+stringId+"/params_localization_obs.xml"))
        return;



    ////subscribers
    droneInternalPoseSubs = n.subscribe(DRONE_VISUAL_MARKS_EYE_SIMULATOR_INTERNAL_POSE, 1, &DroneVisualMarkersEyeSimulatorROSModule::droneInternalPoseCallback, this);


    //////Publishers
    droneObsVectorPubl = n.advertise<droneMsgsROS::obsVector>(DRONE_VISUAL_MARKS_EYE_SIMULATOR_OBSERVATION_VEC_LIST, 1, true);


    //Flag of module opened
    droneModuleOpened=true;


    //Auto-start
    //moduleStarted = true;

	
	//End
	return;
}


bool DroneVisualMarkersEyeSimulatorROSModule::init()
{


    //end
    return true;
}



void DroneVisualMarkersEyeSimulatorROSModule::close()
{
    DroneModule::close();

    return;
}


bool DroneVisualMarkersEyeSimulatorROSModule::resetValues()
{

    return true;
}


bool DroneVisualMarkersEyeSimulatorROSModule::startVal()
{

    //End
    return DroneModule::startVal();
}



bool DroneVisualMarkersEyeSimulatorROSModule::stopVal()
{
    return DroneModule::stopVal();
}



bool DroneVisualMarkersEyeSimulatorROSModule::run()
{
    if(!DroneModule::run())
    {
        //cout<<"Module not started yet!"<<endl;
        return false;
    }


    //Process
    if(!MyDroneVisualMarkersEyeSimulator.run())
        return false;


    //Fill Msgs
    droneObsVectorMsgs.time=ros::Time::now().toSec();
    droneObsVectorMsgs.obs.clear();
    for(unsigned int i=0;i<MyDroneVisualMarkersEyeSimulator.TheObservedVisualMarks.size();i++)
    {
        droneMsgsROS::Observation3D TheVisualMark;
        unsigned int id;
        double x, y, z, yaw, pitch, roll;
        MyDroneVisualMarkersEyeSimulator.TheObservedVisualMarks[i].getId(id);
        MyDroneVisualMarkersEyeSimulator.TheObservedVisualMarks[i].getPose(x, y, z, yaw, pitch, roll);

        TheVisualMark.id=static_cast<int>(id);
        TheVisualMark.x=static_cast<float>(x);
        TheVisualMark.y=static_cast<float>(y);
        TheVisualMark.z=static_cast<float>(z);
        TheVisualMark.yaw=static_cast<float>(yaw);
        TheVisualMark.pitch=static_cast<float>(pitch);
        TheVisualMark.roll=static_cast<float>(roll);
        droneObsVectorMsgs.obs.push_back(TheVisualMark);
    }
    droneObsVectorMsgs.reference_frame = "drone_GMR";
    droneObsVectorMsgs.target_frame    = "aruco_GMR";
    droneObsVectorMsgs.YPR_system      = "wYvPuR";



    //Publish
    if(!publishObsVector())
        return false;


    return true;
}



void DroneVisualMarkersEyeSimulatorROSModule::droneInternalPoseCallback(const droneMsgsROS::dronePoseStamped::ConstPtr& msg)
{
    double x=static_cast<double>(msg->pose.x);
    double y=static_cast<double>(msg->pose.y);
    double z=static_cast<double>(msg->pose.z);
    double yaw=static_cast<double>(msg->pose.yaw);
    double pitch=static_cast<double>(msg->pose.pitch);
    double roll=static_cast<double>(msg->pose.roll);
    MyDroneVisualMarkersEyeSimulator.setPose(x,y,z,yaw,pitch,roll);

    return;
}



int DroneVisualMarkersEyeSimulatorROSModule::publishObsVector()
{
    if(droneModuleOpened==false)
        return 0;


    droneObsVectorPubl.publish(droneObsVectorMsgs);


    return 1;
}

