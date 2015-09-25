#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneArucoEyeROSModule droneArucoEyeROSModule.launch --wait drone_aruco_eye_ros_module_name:="droneArucoEyeROSModuleLeftCam" camera_calibration_file:="left.yaml" drone_image_topic_name:="camera/left/image_raw" camera_number:="1"

