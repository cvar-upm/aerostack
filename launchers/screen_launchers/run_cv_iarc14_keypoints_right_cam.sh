#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_Keypoints.launch --wait camera_name:="right" camera_calib_param:="right_camera_calibration.yaml" grid_param:="gridConfig_frontCameras.xml" camera_topic_name:="camera/right" keypoints_topic_name:="camera/right/cv/grid_detection"


