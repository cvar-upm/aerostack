/*!*******************************************************************************************
*  \file       behavior_self_localize_and_map_with_lidar.h
*  \brief      behavior self localize and map with lidar definition file.
*  \authors    Raul Cruz
*  \maintainer Raul Cruz
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
* THIS SOFTWARE IS PROVIDED With THE COPYRIGHT HOLDERS AND CONTRIBUTORS
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
#ifndef behavior_self_localize_and_map_with_lidar_H
#define behavior_self_localize_and_map_with_lidar_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>

// ROS
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <droneMsgsROS/dronePose.h>
#include <aerostack_msgs/RequestProcesses.h>
#include <behavior_execution_controller.h>


namespace navigation_with_lidar
{
class BehaviorSelfLocalizeAndMapWithLidar : public BehaviorExecutionController
{
public:
  BehaviorSelfLocalizeAndMapWithLidar();
  ~BehaviorSelfLocalizeAndMapWithLidar();

private:
 

  ros::Subscriber hectorMapSub;
  ros::Publisher mapPub;
  
  ros::Publisher hectorReset;
  std_msgs::String hector_reset_msg;

  void hectorMapCallback(const nav_msgs::OccupancyGrid& msg);

  //Congfig variables

  std::string hector_map_topic_str;
  std::string output_map_topic_str;

  bool is_stopped;

  // BehaviorExecutionController
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();

  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();

};
}
#endif
