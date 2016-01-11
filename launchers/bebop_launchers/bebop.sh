#!/bin/bash

NUMID_DRONE=$4
NETWORK_ROSCORE=$2
DRONE_IP=$3
DRONE_WCHANNEL=$5
DRONE_WTYPE=$1

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
	--tab --title "roscore"	--command "bash -c \"
roscore
						exec bash\""  \
	--tab --title "Bebop Autonomy"	--command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/bebop_launchers/launch_files/bebop_node.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} wifi_selection_type:=${DRONE_WTYPE};
						exec bash\""  \
	--tab --title "Driver Bebop"	--command "bash -c \"
roslaunch driverBebopROSModule driverBebopROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "EKF Odometry"	--command "bash -c \"
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Trajectory Controller "	--command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Supervisor" --command "bash -c \"
roslaunch performance_monitor performance_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \   &
						

gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" &


