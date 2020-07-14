#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DEBUG_MODE=$3

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

if [ -z $DEBUG_MODE ]
	then
		roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_100/launch_files/sdk_manifold.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch driverDjiMatriceROSModule driverDJIMatriceROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch sf30_node sf30.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} & --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} serial_port:="/dev/ttyUSB0" &
		roslaunch droneAltitudeFiltering droneAltitudeFiltering.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch droneRobotLocalizationROSModule droneRobotLocalizationROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_100/launch_files/EKF_ouster.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
                roslaunch ouster_ros os1.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
                roslaunch hdl_graph_slam hdl_graph_slam_501.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
		roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} &
	else
		gnome-terminal  \
			--tab --title "dji sdk ros"	--command "bash -c \"
		roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_100/launch_files/sdk_manifold.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\""  \
			--tab --title "Driver dji ros"	--command "bash -c \"
		roslaunch driverDjiMatriceROSModule driverDJIMatriceROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\""  \
			--tab --title "light ware node" --command "bash -c \"
		roslaunch sf30_node sf30.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} & --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} serial_port:="/dev/ttyUSB0";
								exec bash\""  \
                        --tab --title "Altitude Filtering" --command "bash -c \"
		roslaunch droneAltitudeFiltering droneAltitudeFiltering.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
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
		roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_100/launch_files/EKF_ouster.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\""  \
			--tab --title "Ouster node" --command "bash -c \"
		roslaunch ouster_ros os1.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\""  \
		--tab --title "Ouster node" --command "bash -c \"
		roslaunch hdl_graph_slam hdl_graph_slam_501.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\""  \
			 --tab --title "DroneSupervisor"	--command "bash -c \"
		roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
								exec bash\"" \ &
fi
