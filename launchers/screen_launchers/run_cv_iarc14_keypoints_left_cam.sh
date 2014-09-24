#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_Keypoints.launch --wait camera_name:="left" camera_calib_param:="left_camera_calibration.yaml" grid_param:="gridConfig_frontCameras.xml" camera_topic_name:="camera/left" keypoints_topic_name:="camera/left/cv/grid_detection"


