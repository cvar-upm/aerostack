#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DRONE_IP=$3
DRONE_WCHANNEL=$4
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
    NUMID_DRONE=0   	
fi
echo "-Setting droneId = $NUMID_DRONE"
if [ -z $DRONE_IP ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 3 is empty
  	DRONE_IP=192.168.1.1  	
fi
echo "-Setting droneIp = $DRONE_IP"
if [ -z $DRONE_WCHANNEL ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 4 is empty
    DRONE_WCHANNEL=6
fi
echo "-Setting droneChannel = $DRONE_WCHANNEL"



  

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "MSF Localization"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/msf_localization/msf_localization_ros.launch --wait \
      drone_id_namespace:=drone$NUMID_DRONE \
      drone_id_int:=$NUMID_DRONE \
      my_stack_directory:=${AEROSTACK_STACK};
    exec bash\"" &
						

