/*!*********************************************************************************
 *  \file       pose_adapter_process.h
 *  \brief      PoseAdapter definition file.
 *  \details    This file contains the PoseAdapter declaration.
 *              To obtain more information about it's definition consult
 *              the pose_adapter_process.cpp file.
 *  \authors    Daniel Del Olmo.
 *  \copyright  Copyright 2018 Universidad Politecnica de Madrid (UPM)
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

#ifndef POSE_ADAPTER_PROCESS_H
#define POSE_ADAPTER_PROCESS_H

/*System*/
#include <string>
#include <ros/ros.h>
#include <Eigen/Geometry>
#include <angles/angles.h>

/*Messages*/
#include <droneMsgsROS/dronePose.h>
/*Aerostack*/
#include <drone_process.h>
#include <tf/tf.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>

/*Class definition*/
class PoseAdapter : public DroneProcess
{
public:
  PoseAdapter();
  ~PoseAdapter();

private:
  ros::NodeHandle node_handle;

  std::string drone_id;
  std::string drone_id_namespace;
  std::string geometric_pose_str;
  std::string estimated_pose_str;
  std::string trajectory_controller_pose_str;
  std::string trajectory_controller_geometric_pose_str;
  ros::Publisher geometric_pose_pub;
  ros::Subscriber estimated_pose_sub;
  ros::Publisher  trajectory_controller_geometric_pose_pub;
  ros::Subscriber trajectory_controller_pose_sub;

  geometry_msgs::PoseStamped new_pose_msg;
  geometry_msgs::PoseStamped new_trajectory_controller_pose_msg;

  void estimatedPoseCallback(const droneMsgsROS::dronePose&);
  void trajectoryControllerPoseCallback(const droneMsgsROS::dronePose&);
  Eigen::Quaternionf toQuaternion( double yaw, double pitch, double roll);


private:
  void ownSetUp();
  void ownStart();
  void ownRun();
  void ownStop();
};

#endif
