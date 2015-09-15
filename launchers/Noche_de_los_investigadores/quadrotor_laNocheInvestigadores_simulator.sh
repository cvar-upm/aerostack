#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DRONE_IP=$3
DRONE_WCHANNEL=$4
# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument
if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
  	#Argument 2 is empty
	. ${DRONE_STACK}/setup.sh
    	OPEN_ROSCORE=1
  else
    	. ${DRONE_STACK}/setup.sh $2
fi
if [ -z $NUMID_DRONE ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 1 empty
    	echo "-Setting droneId = 1"
    	NUMID_DRONE=1
  else
    	echo "-Setting droneId = $1"
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
    	echo "-Setting droneChannel = 6"
    	DRONE_WCHANNEL=6
  else
    	echo "-Setting droneChannel = $4"
fi


#{
#echo ./set_IP_Ch.sh $DRONE_IP $DRONE_WCHANNEL
#echo exit
#} | telnet 192.168.1.1
#	--tab --title "Ardrone_Autonomy"	--command "bash -c \"
#roslaunch ./ardrone_launch/ardrone_indoors.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_ip:=$DRONE_IP;
#						exec bash\""  \

  

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "ROSCORE"	--command "bash -c \"
roscore;
						exec bash\""  \
	--tab --title "Driver Parrot"	--command "bash -c \"
roslaunch droneSimulatorROSModule droneSimulatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone State Estimator"	--command "bash -c \"
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone Trajectory Controller"	--command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} drone_estimated_pose_topic_name:=ArucoSlam_EstimatedPose drone_estimated_speeds_topic_name:=ArucoSlam_EstimatedSpeeds;
						exec bash\""  \
	--tab --title "Drone IBVS Controller"	--command "bash -c \"
roslaunch droneIBVSControllerROSModule DroneIBVSControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Eye Simulator" --command "bash -c \"
roslaunch droneVisualMarkersEyeSimulatorROSModule droneVisualMarkersEyeSimulatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Visual Marker Localizer" --command "bash -c \"
roslaunch droneVisualMarkersLocalizerROSModule droneVisualMarkersLocalizerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "Obstacle Processor" --command "bash -c \"
roslaunch droneObstacleProcessorVisualMarksROSModule droneObstacleProcessor2dVisualMarksROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""   \
	--tab --title "Obstacle Distance Calculator" --command "bash -c \"
roslaunch droneObstacleDistanceCalculatorROSModule droneObstacleDistanceCalculationROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} drone_pose_topic_name:=ArucoSlam_EstimatedPose;
						exec bash\""   \
	--tab --title "Trajectory Planner" --command "bash -c \"
roslaunch droneTrajectoryPlannerROSModule droneTrajectoryPlanner2dROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} drone_pose_topic_name:=ArucoSlam_EstimatedPose;
						exec bash\""  \
	--tab --title "Yaw Commander" --command "bash -c \"
roslaunch droneYawCommanderROSModule droneYawCommanderROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} drone_pose_topic_name:=ArucoSlam_EstimatedPose;
						exec bash\""  \
	--tab --title "openTLD translator"	--command "bash -c \"
roslaunch droneOpenTLDTranslatorROS droneOpenTLDTranslatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneCommunicationManager" --command "bash -c \"
roslaunch droneCommunicationManagerROSModule droneCommunicationManagerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "sound_play" --command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/sound_play.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneSpeechModule" --command "bash -c \"
roslaunch droneSpeechROSModule droneSpeechROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} voice:=voice_rab_diphone;
						exec bash\""  \
	--tab --title "DroneSupervisor"	--command "bash -c \"
roslaunch performance_monitor performance_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "DroneManagerofActions" --command "bash -c \"
roslaunch droneManagerOfActionsROSModule droneManagerOfActionsROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneMissionScheduler" --command "bash -c \"
roslaunch droneMissionScheduleProcessorROSModule droneMissionSheduleProcessorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} drone_Estimated_Pose_Topic_Name:=ArucoSlam_EstimatedPose mission_config_file:=missionSchedule.xml;
						exec bash\"" &
						

gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  &



#	--tab --title "tracker Eye"	--command "bash -c \"
#roslaunch droneTrackerEyeROSModule droneTrackerEyeROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
#						exec bash\""  \
# rosrun ardrone_autonomy ardrone_driver;
# gnome-terminal  --window --full-screen  \ # window part opens an unused tab

#						env sleep 13s ;
#						rosrun parrotController parrotController _droneId:=1; 
# ./ardrone_launchfiles/ardrone_indoors.launch
# ./+ardrone_launchfiles/ardrone_indoors_maclock.launch
