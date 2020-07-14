#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_int:="5" drone_id_namespace:="drone5"
