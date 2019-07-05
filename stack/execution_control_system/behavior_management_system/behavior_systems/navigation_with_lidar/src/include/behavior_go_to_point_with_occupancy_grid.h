/*!*******************************************************************************************
*  \file       behavior_go_to_point_with_occupancy_grid.h
*  \brief      behavior go to point with occupancy grid definition file.
*  \details     This file contains the BehaviorGoToPointWithOccupancyGrid declaration. To obtain more information about
*              it's definition consult the behavior_go_to_point_with_occupancy_grid.cpp file.
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
#ifndef behavior_go_to_point_with_occupancy_grid_H
#define behavior_go_to_point_with_occupancy_grid_H

#include <string>

// ROS
#include <ros/ros.h>

#include <nav_msgs/Path.h>
#include <droneMsgsROS/dronePose.h>
#include <droneMsgsROS/ConsultBelief.h>
#include <aerostack_msgs/PathWithID.h>
#include <aerostack_msgs/GeneratePath.h>
#include <droneMsgsROS/dronePositionTrajectoryRefCommand.h>
#include <droneMsgsROS/droneYawRefCommand.h>
#include <droneMsgsROS/droneTrajectoryControllerControlMode.h>
#include <droneMsgsROS/dronePositionRefCommand.h>
#include <droneMsgsROS/droneCommand.h>
#include <yaml-cpp/yaml.h>
#include <droneMsgsROS/RequestProcesses.h>
#include <behavior_execution_controller.h>
#include <aerostack_msgs/RequestProcesses.h>
#include <aerostack_msgs/BehaviorActivationFinished.h>

namespace navigation_with_lidar
{
class BehaviorGoToPointWithOccupancyGrid : public BehaviorExecutionController
{
public:
  BehaviorGoToPointWithOccupancyGrid();
  ~BehaviorGoToPointWithOccupancyGrid();

private:

  // Maximum difference between estimated and requested yaw
  const double YAW_TOL = 0.1;
  const double DIST_TOL = 0.3;

  // Communication variables
  ros::ServiceClient request_processes_activation_cli;
  ros::ServiceClient request_processes_deactivation_cli;

  // Ros publishers & subrcribers
  ros::Subscriber estimated_pose_sub;
  ros::Subscriber path_sub;
  ros::Publisher yaw_controller_pub;
  ros::Publisher trajectory_pub;
  ros::Publisher controllers_pub;
  ros::ServiceClient belief_manager_client;
  ros::ServiceClient path_client;

  // Congfig variables
  std::string generated_path_topic_str;
  std::string generate_path_service_str;
  std::string estimated_pose_str;
  std::string yaw_controller_str;
  std::string controllers_topic;
  std::string trajectory_topic;
  std::string execute_query_srv;
  std::vector<std::string> processes;

  // State variables
  bool is_finished;
  bool bad_args;
  bool changing_yaw;
  bool pending_path;
  bool obstacle;
  bool yaw_sent;
  double current_yaw;
  double target_yaw;
  unsigned int path_id;
  droneMsgsROS::dronePose estimated_pose;
  droneMsgsROS::dronePose target_position;
  droneMsgsROS::dronePositionTrajectoryRefCommand current_traj;

  // BehaviorExecutionController
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();

  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();

  // Callbacks
  void generatedPathCallback(const aerostack_msgs::PathWithID &resp_path);
  void estimatedPoseCallBack(const droneMsgsROS::dronePose& msg);
  // Utils - Grabbed from generate path in occupancy grid
  void convertPath(const nav_msgs::Path &path, droneMsgsROS::dronePositionTrajectoryRefCommand &return_path);
  bool grabInputPose(const droneMsgsROS::dronePose estimated_pose, droneMsgsROS::dronePose &position);
  int requestPath(droneMsgsROS::dronePose position);
  // Utils - Grabbed from FollowPathInOccupancyGrid
  void setupTrajectory(droneMsgsROS::dronePositionTrajectoryRefCommand &return_path);
  void setupTopics();
  void setupStartPosition(droneMsgsROS::dronePose &position);
  void setControllerMode();
  bool goalReached(droneMsgsROS::dronePose current, droneMsgsROS::dronePose target);
  double fixYaw(double inputYaw);
  void sendTrajectory(droneMsgsROS::dronePositionTrajectoryRefCommand &traj);
  void sendYaw(double yaw);
  void yawOrRequest();
  void dumpTopicNames();
};
}
#endif
