#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait
