#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneIARC14MissionSchedulerROSModule droneIARC14MissionSchedulerROSModule.launch --wait

