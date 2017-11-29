/*!*******************************************************************************************
 *  \file       camera_overlay_process.cpp
 *  \brief      CameraOverlay implementation file.
 *  \details    This file implements the CameraOverlay class.
 *  \authors    Daniel Rabasco García.
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

#include "../include/camera_overlay_process.h"

CameraOverlay::CameraOverlay(): it_(nh_)
{
  drone_publishing = false;
}

CameraOverlay::~CameraOverlay()
{

}


void CameraOverlay::ownSetUp()
{


  ros::NodeHandle private_nh("~");

  //private_nh.param<std::string>("drone_id", drone_id, "1");
  private_nh.param<std::string>("drone_id_namespace", drone_id_namespace,"drone1");

  //private_nh.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);




}

void CameraOverlay::ownStart()
{
    // Subscribe to input video feed and other feeds and publish output video feeds
    pose_sub_ = nh_.subscribe("/"+drone_id_namespace+"/EstimatedPose_droneGMR_wrt_GFF", 1000, &CameraOverlay::poseCallback,this);
    spd_sub_ = nh_.subscribe("/"+drone_id_namespace+"/EstimatedSpeed_droneGMR_wrt_GFF", 1000, &CameraOverlay::spdCallback,this);
    batt_sub_ = nh_.subscribe("/"+drone_id_namespace+"/battery", 1000, &CameraOverlay::battCallback,this);
    image_sub_ = it_.subscribe("/"+drone_id_namespace+VIDEO_STREAM_INPUT, 1000, &CameraOverlay::imageCallback, this);
    image_pub_big_ = it_.advertise("/"+drone_id_namespace+"/camera/overlay/image_raw/big", 1000);
    image_pub_small_ = it_.advertise("/"+drone_id_namespace+"/camera/overlay/image_raw/small", 1000);
}

void CameraOverlay::ownStop()
{
    pose_sub_.shutdown();
    spd_sub_.shutdown();
    batt_sub_.shutdown();
    image_sub_.shutdown();
}

void CameraOverlay::ownRun()
{
 // if(!drone_publishing)
  image_converter.imageOverlayCbBlack(image_pub_small_, image_pub_big_);
}

void CameraOverlay::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{ 
  drone_publishing = true;
  image_converter.imageOverlayCb(msg, image_pub_small_, image_pub_big_);
}

void CameraOverlay::poseCallback(const droneMsgsROS::dronePose::ConstPtr& msg)
{
  image_converter.poseInfoCb(msg);
}

void CameraOverlay::spdCallback(const droneMsgsROS::droneSpeeds::ConstPtr& msg)
{
  image_converter.spdInfoCb(msg);
}

void CameraOverlay::battCallback(const droneMsgsROS::battery::ConstPtr& msg)
{
  image_converter.battInfoCb(msg);
}

bool CameraOverlay::getDronePublishing(){
  return drone_publishing;
}

void CameraOverlay::setDronePublishing(bool publishing){
  drone_publishing = publishing;
}
