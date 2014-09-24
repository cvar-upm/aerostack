#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneComputerVisionIARC14ROSModule droneCVIARC14_GroundRobots.launch --wait camera_name:="back" camera_calib_param:="back_camera_calibration.yaml" bot_param:="botConfig_frontCameras.xml" camera_topic_name:="camera/back" ground_robots_topic_name:="camera/back/cv/ground_robots" viola_jones_model:="[SIDE]LBP_110714_30stages.xml" svm_model:="csvm_YUV_model_nocv.xml" svm_scale_values:="csvm_YUV_scaleValues_nocv.xml"

