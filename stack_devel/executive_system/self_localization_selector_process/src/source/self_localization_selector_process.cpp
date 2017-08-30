/*!*******************************************************************************************
 *  \file       self_localization_selector.cpp
 *  \brief      SelfLocalizationSelector implementation file.
 *  \details    This file implements the SelfLocalizationSelector class.
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

#include "../include/self_localization_selector_process.h"

SelfLocalizationSelector::SelfLocalizationSelector()
{
  mode = ODOMETRY;
}

SelfLocalizationSelector::~SelfLocalizationSelector()
{

}

/*DroneProcess*/
void SelfLocalizationSelector::ownSetUp()
{
  node_handle.param<std::string>("drone_id", drone_id, "1");
  node_handle.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);
  node_handle.param<std::string>("my_stack_directory", my_stack_directory,
                  "~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack");

  ros::NodeHandle private_handle("~");

  private_handle.param<std::string>("change_mode_to_odometry_srv", change_mode_to_odometry_str, "change_self_localization_mode_to_odometry");
  private_handle.param<std::string>("change_mode_to_visual_markers_srv", change_mode_to_visual_markers_str,
                                 "change_self_localization_mode_to_visual_markers");
  private_handle.param<std::string>("odometry_estimated_pose_topic", odometry_estimated_pose_str, "EstimatedPose_droneGMR_wrt_GFF");
  private_handle.param<std::string>("odometry_estimated_speed_topic", odometry_estimated_speed_str, "EstimatedSpeed_droneGMR_wrt_GFF");
  private_handle.param<std::string>("aruco_slam_estimated_pose_topic", aruco_slam_estimated_pose_str, "ArucoSlam_EstimatedPose");
  private_handle.param<std::string>("aruco_slam_estimated_speed_topic", aruco_slam_estimated_speed_str, "ArucoSlam_EstimatedSpeed");
  private_handle.param<std::string>("estimated_pose_topic", estimated_pose_str, "estimated_pose");
  private_handle.param<std::string>("estimated_speed_topic", estimated_speed_str, "estimated_speed");
}

void SelfLocalizationSelector::ownStart()
{
  change_mode_to_odometry_srv = node_handle.advertiseService(change_mode_to_odometry_str,
                                                             &SelfLocalizationSelector::changeModeToOdometryCallback, this);
  change_mode_to_visual_markers_srv = node_handle.advertiseService(change_mode_to_visual_markers_str,
                                                             &SelfLocalizationSelector::changeModeToVisualMarkersCallback, this);
  odometry_estimated_pose_sub = node_handle.subscribe(odometry_estimated_pose_str, 1,
                                                      &SelfLocalizationSelector::odometryEstimatedPoseCallback, this);
  odometry_estimated_speed_sub = node_handle.subscribe(odometry_estimated_speed_str, 1,
                                                       &SelfLocalizationSelector::odometryEstimatedSpeedCallback, this);
  aruco_slam_estimated_pose_sub = node_handle.subscribe(aruco_slam_estimated_pose_str, 1,
                                                             &SelfLocalizationSelector::arucoSlamEstimatedPoseCallback, this);
  aruco_slam_estimated_speed_sub = node_handle.subscribe(aruco_slam_estimated_speed_str, 1,
                                                             &SelfLocalizationSelector::arucoSlamEstimatedSpeedCallback, this);
  estimated_pose_pub = node_handle.advertise<droneMsgsROS::dronePose>(estimated_pose_str, 1);
  estimated_speed_pub = node_handle.advertise<droneMsgsROS::droneSpeeds>(estimated_speed_str, 1);
}

void SelfLocalizationSelector::ownRun()
{
  switch(mode)
  {
    case ODOMETRY:
      estimated_pose_pub.publish(odometry_estimated_pose_msg);
      estimated_speed_pub.publish(odometry_estimated_speed_msg);
      break;
    case VISUAL_MARKERS:
      estimated_pose_pub.publish(aruco_slam_estimated_pose_msg);
      estimated_speed_pub.publish(aruco_slam_estimated_speed_msg);
      break;
  }
}

void SelfLocalizationSelector::ownStop()
{
  change_mode_to_odometry_srv.shutdown();
  change_mode_to_visual_markers_srv.shutdown();
  odometry_estimated_pose_sub.shutdown();
  odometry_estimated_speed_sub.shutdown();
  aruco_slam_estimated_pose_sub.shutdown();
  aruco_slam_estimated_speed_sub.shutdown();
}

/*Callbacks*/
bool SelfLocalizationSelector::changeModeToOdometryCallback(std_srvs::EmptyRequest& request,
                                                            std_srvs::EmptyResponse& response)
{
  mode = ODOMETRY;
  std::cout << "Change mode to ODOMETRY" << std::endl;
  return true;
}

bool SelfLocalizationSelector::changeModeToVisualMarkersCallback(std_srvs::EmptyRequest& request,
                                                                 std_srvs::EmptyResponse& response)
{
  mode = VISUAL_MARKERS;
  std::cout << "Change mode to VISUAL_MARKERS" << std::endl;
  return true;
}

void SelfLocalizationSelector::odometryEstimatedPoseCallback(const droneMsgsROS::dronePose& message)
{
  odometry_estimated_pose_msg = message;
}

void SelfLocalizationSelector::odometryEstimatedSpeedCallback(const droneMsgsROS::droneSpeeds& message)
{
  odometry_estimated_speed_msg = message;
}

void SelfLocalizationSelector::arucoSlamEstimatedPoseCallback(const droneMsgsROS::dronePose& message)
{
  aruco_slam_estimated_pose_msg = message;
}

void SelfLocalizationSelector::arucoSlamEstimatedSpeedCallback(const droneMsgsROS::droneSpeeds& message)
{
  aruco_slam_estimated_speed_msg = message;
}
