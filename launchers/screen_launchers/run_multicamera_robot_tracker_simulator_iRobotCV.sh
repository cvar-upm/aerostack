#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneSimulatoriRobotCVROSModule MulticameraRobotTrackeriRobotCVROSModule.launch --wait

