/*!*******************************************************************************************
 *  \file       behavior_self_localize_and_map_with_lidar.cpp
 *  \brief      Behavior Self Localize and Map with Lidar implementation file.
 *  \details    This file implements the BehaviorSelfLocalizeAndMapWithLidar class.
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
#include "../include/behavior_self_localize_and_map_with_lidar.h"
#include <pluginlib/class_list_macros.h>

namespace navigation_with_lidar
{
BehaviorSelfLocalizeAndMapWithLidar::BehaviorSelfLocalizeAndMapWithLidar() : BehaviorExecutionController()
{
  hector_reset_msg.data = "reset";
  setName("self_localize_and_map_with_lidar"); 
  setExecutionGoal(ExecutionGoals::KEEP_RUNNING);
}

BehaviorSelfLocalizeAndMapWithLidar::~BehaviorSelfLocalizeAndMapWithLidar()
{
}

bool BehaviorSelfLocalizeAndMapWithLidar::checkSituation() 
{ 
 return true; 
}

void BehaviorSelfLocalizeAndMapWithLidar::checkProgress() 
{ 
 
}

void BehaviorSelfLocalizeAndMapWithLidar::checkProcesses() 
{ 
 
}

void BehaviorSelfLocalizeAndMapWithLidar::checkGoal() 
{ 

}
void BehaviorSelfLocalizeAndMapWithLidar::onConfigure(){

  ros::NodeHandle nh = getNodeHandle();
  nh.param<std::string>("hector_map_topic", hector_map_topic_str, "hector_map");
  nh.param<std::string>("output_map_topic", output_map_topic_str, "hector_map");

  is_stopped = false;
}


void BehaviorSelfLocalizeAndMapWithLidar::onActivate(){
  std::cout<<"start"<<std::endl;
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  //Subscribers
  hectorMapSub  = nh.subscribe("/" + nspace + "/" + hector_map_topic_str, 1000, &BehaviorSelfLocalizeAndMapWithLidar::hectorMapCallback, this);
  mapPub = nh.advertise<nav_msgs::OccupancyGrid>("/" + nspace + "/" + output_map_topic_str, 1000, true);
  std::cout<<"/" + nspace + "/" + "syscommand"<<std::endl;  
  hectorReset = nh.advertise<std_msgs::String>("/" + nspace + "/" + "syscommand", 1000, true);
  std::cout<<hector_reset_msg.data<<std::endl;
  is_stopped = false;
  // start processes is done automatically With the parent class
  hectorReset.publish(hector_reset_msg);
  std::cout<<"publish function"<<std::endl;
}


void BehaviorSelfLocalizeAndMapWithLidar::onDeactivate(){
  is_stopped = true;
  hectorMapSub.shutdown();
  mapPub.shutdown();
  // stop process to droneRobotLocalizationROS and ekf_localization is done automatically With the parent class
  hectorReset.publish(hector_reset_msg);
}

void BehaviorSelfLocalizeAndMapWithLidar::onExecute()
{
  
}

void BehaviorSelfLocalizeAndMapWithLidar::hectorMapCallback(const nav_msgs::OccupancyGrid &msg) {
  std::cout<<"hector callback"<<std::endl;
  if( !is_stopped ){
    mapPub.publish(msg);
  }
}
}
PLUGINLIB_EXPORT_CLASS(navigation_with_lidar::BehaviorSelfLocalizeAndMapWithLidar, nodelet::Nodelet)
