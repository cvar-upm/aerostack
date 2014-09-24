#!/bin/bash

#Setup
. ${DRONE_STACK}/setup.sh


NUMID_DRONE=$1
NETWORK_ROSCORE=$2
DRONE_IP=$3
DRONE_WCHANNEL=$4
# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument
if [ -z $NUMID_DRONE ] # Check if NUMID_DRONE is NULL
  then
    echo "Argument 1 is empty, setting droneId to 0..."
    NUMID_DRONE=0
  else
    echo "droneId assigned to argument 1:$1"
fi
if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
    echo "Argument 2 is empty, setting roscore to localhost..."
    export ROS_MASTER_URI=http://localhost:11311
    OPEN_ROSCORE=1
  else
    echo "setting roscore to argument 2"
    export ROS_MASTER_URI=http://$NETWORK_ROSCORE:11311
fi
if [ -z $DRONE_WCHANNEL ] # Check if NUMID_DRONE is NULL
  then
    echo "Argument 4 is empty, setting drone channel to 6"
    DRONE_WCHANNEL=6
  else
    echo "droneId assigned to argument 4:$4"
fi
if [ -z $DRONE_IP ] # Check if NUMID_DRONE is NULL
  then
    echo "Argument 3 is empty, setting droneIp to 192.168.1.1"
    DRONE_IP=192.168.1.1
  else
    echo "droneId assigned to argument 3:$3"
fi

{
echo ./set_IP_Ch.sh $DRONE_IP $DRONE_WCHANNEL
echo exit
} | telnet 192.168.1.1

#gnome-terminal  --full-screen  \
gnome-terminal  \
	--tab --title "ardrone_driver"	--command "bash -c \"
	roslaunch ./ardrone_launch/ardrone_indoors_ip_w_maclock_ROS_10.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_ip:=$DRONE_IP;
						exec bash\""  \
	--tab --title "droneLogger"	--command "bash -c \"
	roslaunch ./IMAV2013_launchfiles/parrotLogger.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK}; 
						exec bash\""  \
	--tab --title "EKF"	--command "bash -c \"
	roslaunch ./IMAV2013_launchfiles/parrotStateEstimator.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "Controller"	--command "bash -c \" 
	roslaunch ./IMAV2013_launchfiles/parrotController.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK}; 
						exec bash\""  \
	--tab --title "TrajectoryPlanner" --command "bash -c \"
roslaunch droneTrajectoryPlannerROSModule droneTrajectoryPlanner2dROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "ArucoEye" --command "bash -c \"
roslaunch droneArucoEyeROSModule droneArucoEyeROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "VisualMarkerLocalizer" --command "bash -c \"
roslaunch droneVisualMarkersLocalizerROSModule droneVisualMarkersLocalizerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "ObstacleProcessor" --command "bash -c \"
roslaunch droneObstacleProcessorVisualMarksROSModule droneObstacleProcessor2dVisualMarksROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "DroneYawPlanner" --command "bash -c \"
roslaunch ./IMAV2013_launchfiles/parrotYawPlanner.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  \
	--tab --title "DroneMissionPlanner" --command "bash -c \"
roslaunch ./IMAV2013_launchfiles/parrotMissionPlanner.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" \
	--tab --title "DroneBrain" --command "bash -c \"
roslaunch ./IMAV2013_launchfiles/parrotArchitectureBrain.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\"" &

gnome-terminal  \
	--tab --title "brainInterface"	--command "bash -c \"
	roslaunch ./IMAV2013_launchfiles/parrotBrainInterface.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${DRONE_STACK};
						exec bash\""  &


# rosrun ardrone_autonomy ardrone_driver;
# gnome-terminal  --window --full-screen  \ # window part opens an unused tab

#						env sleep 13s ;
#						rosrun parrotController parrotController _droneId:=1; 
# ./ardrone_launchfiles/ardrone_indoors.launch
# ./+ardrone_launchfiles/ardrone_indoors_maclock.launch
