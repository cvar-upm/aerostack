#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneObstacleDistanceCalculatorROSModule droneObstacleDistanceCalculationROSModule.launch --wait drone_id_namespace:="drone0" drone_id_int:="0" sdrone_pose_topic_name:=ArucoSlam_EstimatedPose
						
