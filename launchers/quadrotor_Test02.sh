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
    	echo "-Setting droneId = 0"
    	NUMID_DRONE=0
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


{
echo ./set_IP_Ch.sh $DRONE_IP $DRONE_WCHANNEL
echo exit
} | telnet 192.168.1.1

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "Ardrone_Autonomy"	--command "bash -c \"
roslaunch ./ardrone_launch/ardrone_indoors.launch --wait drone_id_namespace:=drone$NUMID_DRONE;
						exec bash\""  \
	--tab --title "Driver Parrot"	--command "bash -c \"
roslaunch driverParrotARDroneROSModule driverParrotARDroneROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone Logger"	--command "bash -c \"
roslaunch droneLoggerROSModule droneLoggerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone State Estimator"	--command "bash -c \"
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone Trajectory Controller"	--command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "ArucoEye" --command "bash -c \"
roslaunch droneArucoEyeROSModule droneArucoEyeROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "VisualMarkerLocalizer" --command "bash -c \"
roslaunch droneVisualMarkersLocalizerROSModule droneVisualMarkersLocalizerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "ObstacleProcessor" --command "bash -c \"
roslaunch droneObstacleProcessorVisualMarksROSModule droneObstacleProcessor2dVisualMarksROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""   \
	--tab --title "TrajectoryPlanner" --command "bash -c \"
roslaunch droneTrajectoryPlannerROSModule droneTrajectoryPlanner2dROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "YawCommander" --command "bash -c \"
roslaunch droneYawCommanderROSModule droneYawCommanderROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "MissionPlanner" --command "bash -c \"
roslaunch droneMissionPlannerROSModule droneMissionPlannerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneBrain" --command "bash -c \"
roslaunch droneBrainROSModule droneBrainROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  &
						
gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  &


# rosrun ardrone_autonomy ardrone_driver;
# gnome-terminal  --window --full-screen  \ # window part opens an unused tab

#						env sleep 13s ;
#						rosrun parrotController parrotController _droneId:=1; 
# ./ardrone_launchfiles/ardrone_indoors.launch
# ./+ardrone_launchfiles/ardrone_indoors_maclock.launch
