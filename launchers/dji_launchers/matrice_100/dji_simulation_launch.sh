#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2

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
    	echo "-Setting droneId = 1"
    	NUMID_DRONE=6
  else
    	echo "-Setting droneId = $1"
fi

#gnome-terminal  --full-screen  \
gnome-terminal  \
  --tab --title "dji sdk ros"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/launch_files/sdk_manifold.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Driver dji ros"	--command "bash -c \"
roslaunch driverDjiMatriceROSModule driverDJIMatriceROSModuleSim.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
		--tab --title "dji ros client"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/launch_files/dji_sdk_client.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	  --tab --title "guidance node ros"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/launch_files/guidance_node.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Midlevel Controller"	--command "bash -c \"
roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Trajectory Controller" --command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
   --tab --title "Robot localizationROSModule" --command "bash -c \"
roslaunch droneRobotLocalizationROSModule droneRobotLocalizationROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
   --tab --title "Robot localization" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/launch_files/EKF_sim.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
   --tab --title "DroneSupervisor"	--command "bash -c \"
roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\"" \ &
						
gnome-terminal  \
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\"" &
