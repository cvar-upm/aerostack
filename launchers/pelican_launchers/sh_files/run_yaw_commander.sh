#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch droneYawCommanderROSModule droneYawCommanderROSModule.launch  --wait drone_id_int:="0" drone_id_namespace:="drone0" drone_pose_topic_name:=ArucoSlam_EstimatedPose
