#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_int:="2" drone_id_namespace:="drone2"
