/*!*********************************************************************************
 *  \file       self_localization_selector.h
 *  \brief      SelfLocalizationSelector definition file.
 *  \details    This file contains the SelfLocalizationSelector declaration.
 *              To obtain more information about it's definition consult
 *              the self_localization_selector.cpp file.
 *  \authors    Alberto Camporredondo.
 *  \copyright  Copyright 2017 Universidad Politecnica de Madrid (UPM)
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program. If not, see http://www.gnu.org/licenses/.
 ********************************************************************************/

#ifndef SELF_LOCALIZATION_SELECTOR_PROCESS_H
#define SELF_LOCALIZATION_SELECTOR_PROCESS_H

/*System*/
#include <string>
#include <ros/ros.h>
/*Messages*/
#include <std_srvs/Empty.h>
#include <droneMsgsROS/dronePose.h>
#include <droneMsgsROS/droneSpeeds.h>
/*Aerostack*/
#include <drone_process.h>

/*Mode definition*/
enum Mode {ODOMETRY, VISUAL_MARKERS};

/*Class definition*/
class SelfLocalizationSelector : public DroneProcess
{
public:
  SelfLocalizationSelector();
  ~SelfLocalizationSelector();

private:
  ros::NodeHandle node_handle;
  Mode mode;

  std::string drone_id;
  std::string drone_id_namespace;
  std::string my_stack_directory;
  std::string change_mode_to_odometry_str;
  std::string change_mode_to_visual_markers_str;
  std::string odometry_estimated_pose_str;
  std::string odometry_estimated_speed_str;
  std::string aruco_slam_estimated_pose_str;
  std::string aruco_slam_estimated_speed_str;
  std::string estimated_pose_str;
  std::string estimated_speed_str;

  ros::ServiceServer change_mode_to_odometry_srv;
  ros::ServiceServer change_mode_to_visual_markers_srv;
  ros::Subscriber odometry_estimated_pose_sub;
  ros::Subscriber odometry_estimated_speed_sub;
  ros::Subscriber aruco_slam_estimated_pose_sub;
  ros::Subscriber aruco_slam_estimated_speed_sub;
  ros::Publisher estimated_pose_pub;
  ros::Publisher estimated_speed_pub;

  droneMsgsROS::dronePose odometry_estimated_pose_msg;
  droneMsgsROS::droneSpeeds odometry_estimated_speed_msg;
  droneMsgsROS::dronePose aruco_slam_estimated_pose_msg;
  droneMsgsROS::droneSpeeds aruco_slam_estimated_speed_msg;

private:
  void ownSetUp();
  void ownStart();
  void ownRun();
  void ownStop();

  /*Callbacks*/
private:
  bool changeModeToOdometryCallback(std_srvs::EmptyRequest&, std_srvs::EmptyResponse&);
  bool changeModeToVisualMarkersCallback(std_srvs::EmptyRequest&, std_srvs::EmptyResponse&);
  void odometryEstimatedPoseCallback(const droneMsgsROS::dronePose&);
  void odometryEstimatedSpeedCallback(const droneMsgsROS::droneSpeeds&);
  void arucoSlamEstimatedPoseCallback(const droneMsgsROS::dronePose&);
  void arucoSlamEstimatedSpeedCallback(const droneMsgsROS::droneSpeeds&);
};

#endif
