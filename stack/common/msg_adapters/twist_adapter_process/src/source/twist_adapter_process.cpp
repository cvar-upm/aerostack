/*!*******************************************************************************************
 *  \file       twist_adapter.cpp
 *  \brief      TwistAdapter implementation file.
 *  \details    This file implements the TwistAdapter class.
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

#include "../include/twist_adapter_process.h"

TwistAdapter::TwistAdapter()
{

}

TwistAdapter::~TwistAdapter()
{

}

/*DroneProcess*/
void TwistAdapter::ownSetUp()
{

  ros::NodeHandle private_handle;

  private_handle.param<std::string>("drone_id", drone_id, "1");
  private_handle.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);

 /* private_handle.param<std::string>("estimated_speed", estimated_speed_str,
                                 "estimated_speed");
  private_handle.param<std::string>("geometric_speed", geometric_speed_str,
                                 "geometric_speed");*/

  private_handle.param<std::string>("trajectoryControllerSpeedReferencesRebroadcast", trajectory_controller_speed_str, "trajectoryControllerSpeedReferencesRebroadcast");
  private_handle.param<std::string>("trajectoryControllerTwistReferencesRebroadcast", trajectory_controller_geometric_speed_str, "trajectoryControllerTwistReferencesRebroadcast");




}

void TwistAdapter::ownStart()
{

    /*estimated_speed_sub = node_handle.subscribe('/'+drone_id_namespace+'/'+estimated_speed_str, 1,
                                                         &TwistAdapter::estimatedSpeedCallback, this);

    geometric_speed_pub = node_handle.advertise<geometry_msgs::Twist>('/'+drone_id_namespace+'/'+geometric_speed_str, 1);
    */

    trajectory_controller_geometric_speed_pub = node_handle.advertise<geometry_msgs::Twist>('/'+drone_id_namespace+'/'+trajectory_controller_geometric_speed_str, 1);

    trajectory_controller_speed_sub = node_handle.subscribe('/'+drone_id_namespace+'/' + trajectory_controller_speed_str, 1, &TwistAdapter::trajectoryControllerSpeedCallback, this);



}

void TwistAdapter::ownRun()
{

}

void TwistAdapter::ownStop()
{
  estimated_speed_sub.shutdown();
  trajectory_controller_speed_sub.shutdown();


}

/*Callbacks*/



/*
void TwistAdapter::estimatedSpeedCallback(const droneMsgsROS::droneSpeeds& message)
{


  twist_msg.linear.x = message.dx;
  twist_msg.linear.y = message.dy;
  twist_msg.linear.z = message.dz;
  twist_msg.angular.x = message.droll;
  twist_msg.angular.y = message.dpitch;
  twist_msg.angular.z = message.dyaw;


  geometric_speed_pub.publish(twist_msg);

}*/
void TwistAdapter::trajectoryControllerSpeedCallback(const droneMsgsROS::droneSpeeds& message)
{


  twist_msg.linear.x = message.dx;
  twist_msg.linear.y = message.dy;
  twist_msg.linear.z = message.dz;
  twist_msg.angular.x = message.droll;
  twist_msg.angular.y = message.dpitch;
  twist_msg.angular.z = message.dyaw;


  trajectory_controller_geometric_speed_pub.publish(twist_msg);

}
