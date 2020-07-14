#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DRONE_IP=$3
DRONE_WCHANNEL=$4
DRONE_WTYPE=$5

# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument

if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
  	#Argument 2 is empty
	. ${AEROSTACK_STACK}/setup.sh
    	OPEN_ROSCORE=1
  else
    	. ${AEROSTACK_STACK}/setup.sh $2
fi
if [ -z $NUMID_DRONE ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 1 empty
    	echo "-Setting droneId = 0"
    	NUMID_DRONE=4
  else
    	echo "-Setting droneId = $4"
fi
if [ -z $DRONE_IP ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 3 is empty
    	echo "-Setting droneIp = 192.168.1.1"
    	DRONE_IP=192.168.1.1
  else
    	echo "-Setting droneIp = $3"
fi
if [ -z $DRONE_WCHANNEL ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 4 is empty
    	echo "-Setting droneChannel = 5"
    	DRONE_WCHANNEL=5
  else
    	echo "-Setting droneChannel = $5"
fi
if [ -z $DRONE_WTYPE ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 5 is empty
    	echo "-Setting WifiSelectionType = 1"
    	DRONE_WTYPE=1
  else
    	echo "-Setting WifiSelectionType = $1"
fi



#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "Driver Parrot"	--command "bash -c \"
roslaunch droneSimulatorROSModule droneSimulatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "Drone State Estimator"	--command "bash -c \"
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
      --tab --title "Trajectory Controller "	--command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} drone_estimated_pose_topic_name:=ArucoSlam_EstimatedPose drone_estimated_speeds_topic_name:=ArucoSlam_EstimatedSpeeds;
						exec bash\""  \
      --tab --title "ArucoEye" --command "bash -c \"
roslaunch drone_aruco_eye_ros_module droneArucoEyeROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
                                                exec bash\""  \
      --tab --title "Visual Marker Localizer" --command "bash -c \"
roslaunch droneVisualMarkersLocalizerROSModule droneVisualMarkersLocalizerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\"" \
      --tab --title "Trajectory Planner" --command "bash -c \"
roslaunch droneTrajectoryPlannerROSModule droneTrajectoryPlanner2dROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} drone_pose_topic_name:=ArucoSlam_EstimatedPose;
						exec bash\""  \
      --tab --title "Yaw Commander" --command "bash -c \"
roslaunch droneYawCommanderROSModule droneYawCommanderROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} drone_pose_topic_name:=ArucoSlam_EstimatedPose;
						exec bash\""  \
       --tab --title "DroneManagerofActions" --command "bash -c \"
roslaunch droneManagerOfActionsROSModule droneManagerOfActionsROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
        --tab --title "DroneMissionScheduler" --command "bash -c \"
roslaunch droneMissionScheduleProcessorROSModule droneMissionSheduleProcessorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} drone_Estimated_Pose_Topic_Name:=ArucoSlam_EstimatedPose mission_config_file:=missionSchedule.xml;
						exec bash\"" \
	--tab --title "Supervisor" --command "bash -c \"
roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  &				
gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};					exec bash\"" &

