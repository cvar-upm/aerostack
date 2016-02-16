#!/bin/bash

NUMID_DRONE=$5
NETWORK_ROSCORE=$2
DRONE_IP=$3
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
    	echo "-Setting droneId = 5"
    	NUMID_DRONE=5
  else
    	echo "-Setting droneId = $5"
fi
if [ -z $DRONE_IP ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 3 is empty
    	echo "-Setting droneIp = 192.168.1.1"
    	DRONE_IP=192.168.1.1
  else
    	echo "-Setting droneIp = $5"
fi

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "Mavros Simulation"	--command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/launch_files/px4_SITL.launch  --wait drone_id_int:=$NUMID_DRONE drone_id_namespace:=drone$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Driver Pixhawk"	--command "bash -c \"
roslaunch driverPixhawkROSModule driverPixhawkROSModuleSim.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
