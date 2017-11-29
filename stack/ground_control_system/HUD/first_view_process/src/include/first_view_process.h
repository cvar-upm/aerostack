/*!*********************************************************************************
 *  \file       first_view_process.h
 *  \brief      FirstView definition file.
 *  \details    This file contains the FirstView declaration.
 *              To obtain more information about it's definition consult
 *              the behavior_specialist_process.cpp file.
 *  \authors    Daniel Rabasco.
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

#ifndef FIRST_VIEW_PROCESS_H
#define FIRST_VIEW_PROCESS_H


#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include "image_converter.h"


#include <robot_process.h>

static std::string VIDEO_STREAM_INPUT="/camera/front/image_raw";//name of the receiving topic


class FirstView : public RobotProcess
{
private:
  ros::NodeHandle nh_;

  std::string drone_id_namespace;//The drone name

  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_big_,image_pub_small_;
  ros::Subscriber pose_sub_,batt_sub_,spd_sub_;

  ImageConverter image_converter;

  bool drone_publishing;


public:
  FirstView();
  ~FirstView();

private://DroneProcess
  void ownSetUp();
  void ownStart();
  void ownRun();
  void ownStop();

public:

  void imageCallback(const sensor_msgs::ImageConstPtr& msg);
  void poseCallback(const droneMsgsROS::dronePose::ConstPtr& msg);
  void spdCallback(const droneMsgsROS::droneSpeeds::ConstPtr& msg);
  void battCallback(const droneMsgsROS::battery::ConstPtr& msg);
  bool getDronePublishing();
  void setDronePublishing(bool drone_publishing);

};
#endif