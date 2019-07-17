/*!*******************************************************************************************
*  \file       behavior_generate_path_with_occupancy_grid.h
*  \brief      behavior generate path with occupancy grid definition file.
*  \authors    Raul Cruz
*  \maintainer Raul Cruz
*  \copyright  Copyright (c) 2019 Universidad Politecnica de Madrid
*              All Rights Reserved
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* 
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************/
#ifndef behavior_generate_path_with_occupancy_grid_H
#define behavior_generate_path_with_occupancy_grid_H

#include <string>

// ROS
#include <ros/ros.h>

#include <nav_msgs/Path.h>
#include <droneMsgsROS/AddBelief.h>
#include <droneMsgsROS/dronePose.h>
#include <aerostack_msgs/PathWithID.h>
#include <aerostack_msgs/GeneratePath.h>
#include <droneMsgsROS/dronePositionTrajectoryRefCommand.h>
#include <droneMsgsROS/dronePositionRefCommand.h>
#include <droneMsgsROS/GenerateID.h>
#include <yaml-cpp/yaml.h>
#include <droneMsgsROS/RequestProcesses.h>
#include <behavior_execution_controller.h>
#include <aerostack_msgs/RequestProcesses.h>
#include <nodelet/nodelet.h>


namespace navigation_with_lidar
{
class BehaviorGeneratePathWithOccupancyGrid : public BehaviorExecutionController
{
public:
  BehaviorGeneratePathWithOccupancyGrid();
  ~BehaviorGeneratePathWithOccupancyGrid();

private:
  // Communication variables

  ros::ServiceClient request_processes_activation_cli;
  ros::ServiceClient request_processes_deactivation_cli;

  // Publishers, subscribers & servers
  ros::Subscriber path_sub;
  ros::ServiceClient path_client;
  ros::ServiceClient belief_manager_client;
  ros::ServiceClient generate_id_client;

  unsigned int path_id;
  bool is_finished;
  bool bad_args;

  droneMsgsROS::dronePose target_position;

  //Congfig variables

  std::string generated_path_topic_str;
  std::string generate_path_service_str;
  std::string add_belief_service_str;
  std::vector<std::string> processes;

  // BehaviorExecutionController
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();

  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();

  void generatedPathCallback(const aerostack_msgs::PathWithID &path);

  // Utils
  int requestBeliefId();
  void convertPath(const nav_msgs::Path &path, droneMsgsROS::dronePositionTrajectoryRefCommand &return_path);
  std::string serializePath(int id, droneMsgsROS::dronePositionTrajectoryRefCommand &path);
  void addBelief(std::string belief);
  bool grabInputPose(droneMsgsROS::dronePose &position);
  int requestPath(droneMsgsROS::dronePose position);
};
}
#endif
