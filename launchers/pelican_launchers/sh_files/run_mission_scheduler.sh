#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneMissionScheduleProcessorROSModule droneMissionSheduleProcessorROSModule.launch  --wait drone_id_int:="0" drone_id_namespace:="drone0" drone_Estimated_Pose_Topic_Name:=ArucoSlam_EstimatedPose mission_config_file:=missionSchedule.xml
