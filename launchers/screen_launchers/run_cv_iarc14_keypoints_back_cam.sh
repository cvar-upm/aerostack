#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_Keypoints.launch --wait camera_name:="back" camera_calib_param:="back_camera_calibration.yaml" grid_param:="gridConfig_frontCameras.xml" camera_topic_name:="camera/back" keypoints_topic_name:="camera/back/cv/grid_detection"


