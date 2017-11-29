/*!*******************************************************************************************
 *  \file       first_view_process.cpp
 *  \brief      FirstView implementation file.
 *  \details    This file implements the FirstView class.
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

#include "../include/first_view_process.h"

FirstView::FirstView(): it_(nh_)
{
  drone_publishing = false;
}

FirstView::~FirstView()
{

}


void FirstView::ownSetUp()
{


  ros::NodeHandle private_nh("~");

  //private_nh.param<std::string>("drone_id", drone_id, "1");
  private_nh.param<std::string>("drone_id_namespace", drone_id_namespace,"drone1");

  //private_nh.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);




}

void FirstView::ownStart()
{
    // Subscribe to input video feed and other feeds and publish output video feeds
    pose_sub_ = nh_.subscribe("/"+drone_id_namespace+"/EstimatedPose_droneGMR_wrt_GFF", 1000, &FirstView::poseCallback,this);
    spd_sub_ = nh_.subscribe("/"+drone_id_namespace+"/EstimatedSpeed_droneGMR_wrt_GFF", 1000, &FirstView::spdCallback,this);
    batt_sub_ = nh_.subscribe("/"+drone_id_namespace+"/battery", 1000, &FirstView::battCallback,this);
    image_sub_ = it_.subscribe("/"+drone_id_namespace+VIDEO_STREAM_INPUT, 1000, &FirstView::imageCallback, this);
    image_pub_big_ = it_.advertise("/"+drone_id_namespace+"/camera/overlay/image_raw/big", 1000);
    image_pub_small_ = it_.advertise("/"+drone_id_namespace+"/camera/overlay/image_raw/small", 1000);
}

void FirstView::ownStop()
{
    pose_sub_.shutdown();
    spd_sub_.shutdown();
    batt_sub_.shutdown();
    image_sub_.shutdown();
}

void FirstView::ownRun()
{
 // if(!drone_publishing)
  image_converter.imageOverlayCbBlack(image_pub_small_, image_pub_big_);
}

void FirstView::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{ 
  drone_publishing = true;
  image_converter.imageOverlayCb(msg, image_pub_small_, image_pub_big_);
}

void FirstView::poseCallback(const droneMsgsROS::dronePose::ConstPtr& msg)
{
  image_converter.poseInfoCb(msg);
}

void FirstView::spdCallback(const droneMsgsROS::droneSpeeds::ConstPtr& msg)
{
  image_converter.spdInfoCb(msg);
}

void FirstView::battCallback(const droneMsgsROS::battery::ConstPtr& msg)
{
  image_converter.battInfoCb(msg);
}

bool FirstView::getDronePublishing(){
  return drone_publishing;
}

void FirstView::setDronePublishing(bool publishing){
  drone_publishing = publishing;
}
