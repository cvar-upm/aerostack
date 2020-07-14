#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh mastermind
roslaunch droneArucoEyeROSModule droneArucoEyeROSModule.launch --wait drone_aruco_eye_ros_module_name:="droneArucoEyeROSModule" camera_calibration_file:="front.yaml" drone_image_topic_name:="camera/front/image" camera_number:="0"

