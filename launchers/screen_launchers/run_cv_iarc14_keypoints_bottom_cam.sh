#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_Keypoints.launch --wait camera_name:="bottom" camera_calib_param:="bottom_camera_calibration.yaml" grid_param:="gridConfig_bottomCamera.xml" camera_topic_name:="camera/bottom" keypoints_topic_name:="camera/bottom/cv/grid_detection"


