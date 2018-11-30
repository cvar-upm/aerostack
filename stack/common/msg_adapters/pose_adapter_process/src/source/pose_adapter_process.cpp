/*!*******************************************************************************************
 *  \file       pose_adapter_process.cpp
 *  \brief      PoseAdapter implementation file.
 *  \details    This file implements the PoseAdapter class.
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

#include "../include/pose_adapter_process.h"


PoseAdapter::PoseAdapter()
{

}

PoseAdapter::~PoseAdapter()
{

}

/*DroneProcess*/
void PoseAdapter::ownSetUp()
{
  ros::NodeHandle private_handle("~");

  private_handle.param<std::string>("drone_id", drone_id, "1");
  private_handle.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);
  /*private_handle.param<std::string>("geometric_pose", geometric_pose_str, "geometric_pose");
  private_handle.param<std::string>("estimated_pose", estimated_pose_str, "estimated_pose");*/
  private_handle.param<std::string>("trajectoryControllerPoseReferencesRebroadcast", trajectory_controller_geometric_pose_str, "trajectoryControllerPoseReferencesRebroadcast");
  private_handle.param<std::string>("trajectoryControllerPositionReferencesRebroadcast", trajectory_controller_pose_str, "trajectoryControllerPositionReferencesRebroadcast");
  }

void PoseAdapter::ownStart()
{
  /*geometric_pose_pub = node_handle.advertise<geometry_msgs::PoseStamped>('/'+drone_id_namespace+'/'+geometric_pose_str, 1);

  estimated_pose_sub = node_handle.subscribe('/'+drone_id_namespace+'/' + estimated_pose_str, 1, &PoseAdapter::estimatedPoseCallback, this);
*/
  trajectory_controller_geometric_pose_pub = node_handle.advertise<geometry_msgs::PoseStamped>('/'+drone_id_namespace+'/'+trajectory_controller_geometric_pose_str, 1);

  trajectory_controller_pose_sub = node_handle.subscribe('/'+drone_id_namespace+'/' + trajectory_controller_pose_str, 1, &PoseAdapter::trajectoryControllerPoseCallback, this);

}

void PoseAdapter::ownRun()
{



}

void PoseAdapter::ownStop()
{
  estimated_pose_sub.shutdown();
  trajectory_controller_pose_sub.shutdown();
}

/*Callbacks*/

/*
  - Reads from the topic: "estimated_pose"
  - Writes in the topic:  "geometric_pose*/
/*void PoseAdapter::estimatedPoseCallback(const droneMsgsROS::dronePose& msg)
{

  new_pose_msg.pose.position.x = msg.x;
  new_pose_msg.pose.position.y = msg.y;
  new_pose_msg.pose.position.z = msg.z;

  Eigen::Quaternionf q;
  q = Eigen::AngleAxisf(angles::from_degrees(msg.roll), Eigen::Vector3f::UnitX())
      * Eigen::AngleAxisf(angles::from_degrees(msg.pitch), Eigen::Vector3f::UnitY())
      * Eigen::AngleAxisf(angles::from_degrees(msg.yaw), Eigen::Vector3f::UnitZ());
  std::cout << "Quaternion" << std::endl << q.coeffs() << std::endl;
  new_pose_msg.pose.orientation.x = q.x();
  new_pose_msg.pose.orientation.y = q.y();
  new_pose_msg.pose.orientation.z = q.z();
  new_pose_msg.pose.orientation.w = q.w();



  geometric_pose_pub.publish(new_pose_msg);
}
*/
/*
  - Reads from the topic: "trajectoryControllerPositionReferencesRebroadcast"
  - Writes in the topic:  "trajectoryControllerPoseReferencesRebroadcast*/
void PoseAdapter::trajectoryControllerPoseCallback(const droneMsgsROS::dronePose& msg)
{

  new_pose_msg.pose.position.x = msg.x;
  new_pose_msg.pose.position.y = msg.y;
  new_pose_msg.pose.position.z = msg.z;


  Eigen::Quaternionf q;
  q=toQuaternion(msg.yaw, msg.pitch, msg.roll);

  new_pose_msg.pose.orientation.x = q.x();
  new_pose_msg.pose.orientation.y = q.y();
  new_pose_msg.pose.orientation.z = q.z();
  new_pose_msg.pose.orientation.w = q.w();


  trajectory_controller_geometric_pose_pub.publish(new_pose_msg);
}

Eigen::Quaternionf PoseAdapter::toQuaternion( double yaw, double pitch, double roll) // yaw (Z), pitch (Y), roll (X)
{
    // Abbreviations for the various angular functions
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    Eigen::Quaternionf q;
    q.w() = cy * cp * cr + sy * sp * sr;
    q.x() = cy * cp * sr - sy * sp * cr;
    q.y() = sy * cp * sr + cy * sp * cr;
    q.z() = sy * cp * cr - cy * sp * sr;
    return q;
}
