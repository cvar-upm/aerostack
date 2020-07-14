#!/bin/bash

NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DRONE_IP=$3
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
    	echo "-Setting droneId = 3"
    	NUMID_DRONE=3
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

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "Mavros"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/px4.launch --wait drone_id_int:=$NUMID_DRONE drone_id_namespace:=drone$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} fcu_url:="/dev/ttyACM0";
						exec bash\""  \
	--tab --title "Driver Pixhawk"	--command "bash -c \"
roslaunch driverPixhawkROSModule driverPixhawkROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "light ware node" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/lightware_altitude_node.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} serial_port:="/dev/ttyUSB1";
						exec bash\""  \
	--tab --title "Midlevel Controller"	--command "bash -c \"
roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "Trajectory Controller" --command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "RobotLocalizationROSModule" --command "bash -c \"
roslaunch droneRobotLocalizationROSModule droneRobotLocalizationROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Robot localization" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/Ekf.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "Hokuyo Node" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/hokuyo_node.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} serial_port:="/dev/ttyACM1";
						exec bash\""  \
	--tab --title "Hector Slam" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/hector_slam.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "Navigation Stack" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/move_base.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Navigation Stack Interface" --command "bash -c \"
roslaunch navigation_stack_ros_module droneNavigationStackROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "UeyeDriver" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/ueye_cvg_front.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "DroneManagerofActions" --command "bash -c \"
roslaunch droneManagerOfActionsROSModule droneManagerOfActionsROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "DroneSubMissionPlanner" --command "bash -c \"
roslaunch droneSubMissionPlannerROSModule droneSubMissionPlannerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} drone_Estimated_Pose_Topic_Name:=ArucoSlam_EstimatedPose;
						exec bash\"" \
	--tab --title "ShapeColor_ObjectDetection" --command "bash -c \"
roslaunch ShapeColor_ObjectDetection shapecolor_objectdetectionROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
	--tab --title "DroneSupervisor"	--command "bash -c \"
roslaunch  process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\"" \ &
#	--tab --title "UeyeDriver" --command "bash -c \"
#roslaunch ${AEROSTACK_STACK}/launchers/pixhawk_launchers/launch_files/ueye_front.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
#						exec bash\""  \

