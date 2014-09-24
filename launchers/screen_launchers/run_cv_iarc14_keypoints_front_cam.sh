#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_Keypoints.launch --wait camera_name:="front" camera_calib_param:="front_camera_calibration.yaml" grid_param:="gridConfig_frontCameras.xml" camera_topic_name:="camera/front" keypoints_topic_name:="camera/front/cv/grid_detection" 

#  bot_param="botConfig_frontCameras.xml"

