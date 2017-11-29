/*!*********************************************************************************
 *  \file       behavior_specialist_process.h
 *  \brief      CameraOverlay definition file.
 *  \details    This file contains the CameraOverlay declaration.
 *              To obtain more information about it's definition consult
 *              the behavior_specialist_process.cpp file.
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

#ifndef CAMERA_OVERLAY_PROCESS_H
#define CAMERA_OVERLAY_PROCESS_H


#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include "image_converter.h"
#include <camera_info_manager/camera_info_manager.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <boost/assign/list_of.hpp>

#include <robot_process.h>

static std::string VIDEO_STREAM_INPUT=/*"/videofile/image_raw";*/"/camera/front/image_raw";//name of the receiving topic


class CameraOverlay : public RobotProcess
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
  CameraOverlay();
  ~CameraOverlay();

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