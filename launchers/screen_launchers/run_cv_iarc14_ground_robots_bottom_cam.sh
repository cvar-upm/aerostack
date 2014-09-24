#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_GroundRobots.launch --wait camera_name:="bottom" camera_calib_param:="bottom_camera_calibration.yaml" bot_param:="botConfig_bottomCamera.xml" camera_topic_name:="camera/bottom" ground_robots_topic_name:="camera/bottom/cv/ground_robots" viola_jones_model:="[BOTTOM]_mixed_300714_17stages.xml" svm_model:="csvm_YUV_model_nocv.xml" svm_scale_values:="csvm_YUV_scaleValues_nocv.xml"

