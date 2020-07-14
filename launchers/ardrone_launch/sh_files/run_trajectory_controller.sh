#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1"
