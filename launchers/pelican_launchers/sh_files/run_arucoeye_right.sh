#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneArucoEyeROSModule droneArucoEyeROSModule.launch --wait drone_aruco_eye_ros_module_name:="droneArucoEyeROSModuleRightCam" camera_calibration_file:="right.yaml" drone_image_topic_name:="camera/right/image_raw" camera_number:="2"

