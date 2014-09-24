#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneSimulatoriRobotCVROSModule droneSimulatoriRobotCVROSModule.launch --wait camera_name:="bottom" sensor_configuration:="simulator_grid_config_bottom.xml" drone_pose_topic_name:="simulator/dronePose" detected_irobots_topic_name:="perception/bottom/iRobot"

