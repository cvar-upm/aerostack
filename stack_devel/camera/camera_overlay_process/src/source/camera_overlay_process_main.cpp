/*!*********************************************************************************
 *  \file       camera_overlay_process_main.cpp
 *  \brief      CameraOverlay main file.
 *  \details    This file implements the main function of the CameraOverlay.
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

#include "../include/camera_overlay_process.h"
#include <thread>




int main(int argc, char** argv){
  ros::init(argc, argv, ros::this_node::getName());

  std::cout << ros::this_node::getName() << std::endl;

  CameraOverlay camera_overlay;
  camera_overlay.setUp();
  ros::Rate rate(6);

  try{
    camera_overlay.start();
  }catch(std::exception &exception){
    camera_overlay.notifyError(camera_overlay.SafeguardRecoverableError, 0, "ownStart()", exception.what());
    camera_overlay.stop();
  }

  while(ros::ok()) 
  {
       ros::spinOnce();
       if(!camera_overlay.getDronePublishing())
         camera_overlay.run();
       else
         camera_overlay.setDronePublishing(false); 


       rate.sleep();
  }

    return 1;
}