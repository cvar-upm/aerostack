#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
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

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "Pelican Simulator"    --command "bash -c \"
roslaunch dronePelicanSimulatorROSModule dronePelicanSimulatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Pelican Interface"	--command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/screen_launchers/driverPelicanROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "px4flow Interface"	--command "bash -c \"
roslaunch ${DRONE_STACK}/launchers/screen_launchers/driver_px4flow_interface_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "droneMidLevelAutopilot"	--command "bash -c \"
roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone State Estimator"	--command "bash -c \"
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Drone Trajectory Controller"	--command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Eye Simulator" --command "bash -c \"
roslaunch droneVisualMarkersEyeSimulatorROSModule droneVisualMarkersEyeSimulatorROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
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
	--tab --title "DroneInterface"	--command "bash -c \"
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneBrain" --command "bash -c \"
roslaunch droneBrainROSModule droneBrainROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  &

