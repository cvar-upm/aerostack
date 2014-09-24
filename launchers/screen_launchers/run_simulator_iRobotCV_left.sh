#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneSimulatoriRobotCVROSModule droneSimulatoriRobotCVROSModule.launch --wait camera_name:="left" sensor_configuration:="simulator_grid_config_left.xml" drone_pose_topic_name:="simulator/dronePose" detected_irobots_topic_name:="perception/left/iRobot"

