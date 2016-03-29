/*!*****************************************************************************
 *  \file    task_based_mission_planner_process.h
 *  \brief   Definition of all the classes used in the file
 *           task_based_mission_planner_process.cpp .
 *   
 *  \author  Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *       Released under license BSD-3.
 ********************************************************************************/
#ifndef TASK_BASED_MISSION_PLANNER
#define TASK_BASED_MISSION_PLANNER

#include <stdio.h>
#include "Mission.h"
#include "EventHandler.h"

 /// ROS ///
#include "ros/ros.h"

/// Messages ///
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/battery.h"
#include "droneMsgsROS/obsVector.h"
#include "droneMsgsROS/distancesToObstacles.h"
#include "droneMsgsROS/actionData.h"
#include "droneMsgsROS/behaviorRequest.h"
#include "droneMsgsROS/dronePose.h"

/// Services ///
#include "std_srvs/Empty.h"

///Drone process///
#include "drone_process.h"

/*!***************************************************************************
 *  \class TaskBasedMissionPlanner
 *  \brief This class represents an abstraction of a mission schedule.
 *****************************************************************************/
class TaskBasedMissionPlanner: public DroneProcess
{	

private:
  Mission      * current_mission;
  Task         * current_task;
  EventHandler * event_handler;
  //Remembered points
  std::vector<duo<std::string, std::vector<double>>> remembered_points;
  //Current pose
  point current_pose;
  //Mission's xml file path
  std::string mission_path;
  //Topic Names
  std::string droneApprovedActionTopicName;
  std::string droneCompletedActionTopicName;
  std::string droneRequestedActionTopicName;
  std::string droneArucoObservationTopicName;
  std::string droneBatteryTopicName;
  std::string droneCurrentPoseTopicName;
  //ROS Node Handler
  ros::NodeHandle n;
  //Subscriber variables
  ros::Subscriber droneApprovedActionSub;
  ros::Subscriber droneCompletedActionSub;
  ros::Subscriber droneArucoObservationSub;
  ros::Subscriber droneBatterySub;
  ros::Subscriber droneCurrentPoseSub;
  //Publisher variables
  ros::Publisher droneRequestedActionPub;
  //Service client variables
  ros::ServiceClient behaviorRequestClient;
  
public:
  //Constructor & Destructor.
  TaskBasedMissionPlanner(int argc, char **argv);
  ~TaskBasedMissionPlanner();
   
  /*!************************************************************************
   *  \brief  This method starts the main mission execution.
   *  \return Void.
   *************************************************************************/
  void startMission();
  //DroneProcess functions.
  virtual void ownOpen();
  virtual void ownRun();
  virtual void ownRecover();

//Auxiliar methods
private:
  /*!************************************************************************
   *  \brief  This method sends a new task through the topics this module
   *          is connected.
   *  \return Void.
   *************************************************************************/
  void sendNewTask();
  /*!************************************************************************
   *  \brief  This method reads the parameters needed from the .launch file.
   *  \return Void.
   *************************************************************************/
  void getParametersFromFile();
  /*!************************************************************************
   *  \brief  When an error occurs, this method is called to abort 
   *          the main mission.
   *  \return Void.
   *************************************************************************/
  void abortMission();
  
  //Topic Callbacks.
  void droneApprovedActionCallback(const droneMsgsROS::actionData &msg);
  void droneCompletedActionCallback(const droneMsgsROS::actionData &msg);
  void droneArucoObservationCallback(const droneMsgsROS::obsVector &msg);
  void droneBatteryCallback(const droneMsgsROS::battery &msg);
  void droneCurrentPoseCallback(const droneMsgsROS::dronePose &msg);
  
};
#endif