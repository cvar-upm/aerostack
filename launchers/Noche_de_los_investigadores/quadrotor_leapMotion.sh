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
	--tab --title "ArDrone Autonomy"	--command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/ardrone_launch/ardrone_indoors.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK} owner_mac:=84:A6:C8:4E:DE:3C;
						exec bash\""  \
	--tab --title "Driver Parrot"	--command "bash -c \"
roslaunch driverParrotARDroneROSModule driverParrotARDroneROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Leap Motion"	--command "bash -c \"
roslaunch $DRONE_STACK/launchers/leap_motion.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Leap Motion Drone Control Interface "	--command "bash -c \"
roslaunch droneLeapMotionDroneControlUserInterfaceROSModule droneLeapMotionDroneControlUserInterfaceROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneCommunicationManager" --command "bash -c \"
roslaunch droneCommunicationManagerROSModule droneCommunicationManagerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneSupervisor"	--command "bash -c \"
roslaunch performance_monitor performance_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "DroneManagerofActions" --command "bash -c \"
roslaunch droneManagerOfActionsROSModule droneManagerOfActionsROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""   &
						

gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" &


# rosrun ardrone_autonomy ardrone_driver;
# gnome-terminal  --window --full-screen  \ # window part opens an unused tab

#						env sleep 13s ;
#						rosrun parrotController parrotController _droneId:=1; 
# ./ardrone_launchfiles/ardrone_indoors.launch
# ./+ardrone_launchfiles/ardrone_indoors_maclock.launch
