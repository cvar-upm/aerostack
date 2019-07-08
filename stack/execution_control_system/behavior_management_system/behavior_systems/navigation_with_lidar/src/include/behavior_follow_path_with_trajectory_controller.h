/*!*******************************************************************************************
 *  \file       behavior_follow_path_with_trajectory_controller.h
 *  \brief      This file contains the follow_path_with_trajectory_controller declaration. To obtain more information about
 *              it's definition consult the behavior_follow_path_with_trajectory_controller.cpp file.
 *  \authors    Raul Cruz
 *  \copyright  Copyright (c) 2019 Universidad Politecnica de Madrid. All Rights Reserved
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
#ifndef BEHAVIOR_FOLLOW_PATH_WITH_TRAJECTORY_CONTROLLER_H
#define BEHAVIOR_FOLLOW_PATH_WITH_TRAJECTORY_CONTROLLER_H

// ROS
#include <ros/ros.h>
#include "std_srvs/Empty.h"
#include <droneMsgsROS/droneSpeeds.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <yaml-cpp/yaml.h>
#include <droneMsgsROS/dronePositionRefCommandStamped.h>
#include <droneMsgsROS/dronePositionTrajectoryRefCommand.h>
#include <droneMsgsROS/droneYawRefCommand.h>
#include <droneMsgsROS/droneTrajectoryControllerControlMode.h>
#include <droneMsgsROS/setControlMode.h>
#include <droneMsgsROS/ConsultBelief.h>
#include <tuple>
// Aerostack msgs
#include <aerostack_msgs/BehaviorEvent.h>
#include <droneMsgsROS/dronePose.h>
#include <droneMsgsROS/droneCommand.h>
#include <droneMsgsROS/dronePitchRollCmd.h>
#include <droneMsgsROS/droneDAltitudeCmd.h>
#include <droneMsgsROS/droneDYawCmd.h>
#include<droneMsgsROS/societyPose.h>
#include <aerostack_msgs/BehaviorActivationFinished.h>
#include <aerostack_msgs/RequestProcesses.h>
//Aerostack libraries
#include <cmath>
#include <behavior_execution_controller.h>

namespace navigation_with_lidar
{

class BehaviorFollowPathWithTrajectoryController:public BehaviorExecutionController
{

public:
  BehaviorFollowPathWithTrajectoryController();
  ~BehaviorFollowPathWithTrajectoryController();
private:

  //Congfig variables
  std::string behavior_name_str;
  std::string estimated_pose_str;
  std::string rotation_angles_str;
  std::string controllers_str;
  std::string estimated_speed_str;
  std::string yaw_controller_str;
  std::string service_topic_str;
  std::string drone_position_str;
  std::string mission_point;
  std::string d_pitch_roll_str;
  std::string d_yaw_str;
  std::string d_altitude_str;
  std::string speed_reset_str;
  std::string trajectory_ref_command_str;
  std::string execute_query_srv;
  std::string society_pose_str;
  std::vector<std::string> processes;
  //Subscriber---
  ros::Subscriber estimated_pose_sub;
  ros::Subscriber estimated_speed_sub;
  ros::Subscriber rotation_angles_sub;
  ros::Publisher controllers_pub;
  ros::Publisher yaw_controller_pub;
  ros::Publisher  mission_point_pub;
  ros::ServiceClient mode_service;
  ros::ServiceClient query_client;
  ros::Publisher drone_speeds_reseter_pub;
  ros::Publisher reference_trajectory_pub;
  ros::Subscriber society_pose_sub;
  ros::ServiceClient request_processes_activation_cli;
  ros::ServiceClient request_processes_deactivation_cli;
  //Timer staticity_timer;

  //Message
  droneMsgsROS::dronePose estimated_pose_msg;
  droneMsgsROS::dronePose static_pose;
  droneMsgsROS::dronePose target_position;
  droneMsgsROS::dronePose target_position_first;
  droneMsgsROS::droneSpeeds estimated_speed_msg;
  geometry_msgs::Vector3Stamped rotation_angles_msg;
  droneMsgsROS::dronePositionTrajectoryRefCommand real_trajectory_msg;
  int iterate=0;
  int pass=0;
  int lenght=0;
  bool is_finished;
  bool fail=false;
  bool first_point=false;
  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();
  std::tuple<bool,std::string> ownCheckActivationConditions();
  void estimatedPoseCallBack(const droneMsgsROS::dronePose&);
  void estimatedSpeedCallback(const droneMsgsROS::droneSpeeds&);
  void rotationAnglesCallback(const geometry_msgs::Vector3Stamped&);
  void societyPoseCallback(const droneMsgsROS::societyPose&);
};
}

#endif
