/*!*********************************************************************************
 *  \file       twist_adapter_process.h
 *  \brief      TwistAdapter definition file.
 *  \details    This file contains the TwistAdapter declaration.
 *              To obtain more information about it's definition consult
 *              the twist_adapter_process.cpp file.
 *  \authors    Abraham Carrera.
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

#ifndef TWIST_ADAPTER_PROCESS_H
#define TWIST_ADAPTER_PROCESS_H

/*System*/
#include <string>
#include <ros/ros.h>

/*Messages*/
#include <droneMsgsROS/droneSpeeds.h>
/*Aerostack*/
#include <drone_process.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>


/*Class definition*/
class TwistAdapter : public DroneProcess
{
public:
  TwistAdapter();
  ~TwistAdapter();

private:
  ros::NodeHandle node_handle;


  std::string drone_id;
  std::string drone_id_namespace;
  std::string estimated_speed_str;
  std::string geometric_speed_str;
  std::string trajectory_controller_speed_str;
  std::string trajectory_controller_geometric_speed_str;

  geometry_msgs::Twist twist_msg;
  geometry_msgs::Twist new_trajectory_controller_twist_msg;

  ros::Subscriber estimated_speed_sub;
  ros::Publisher geometric_speed_pub;
  ros::Publisher  trajectory_controller_geometric_speed_pub;
  ros::Subscriber trajectory_controller_speed_sub;


private:
  void ownSetUp();
  void ownStart();
  void ownRun();
  void ownStop();

  /*Callbacks*/
private:

  void estimatedSpeedCallback(const droneMsgsROS::droneSpeeds&);
  void trajectoryControllerSpeedCallback(const droneMsgsROS::droneSpeeds&);



};

#endif
