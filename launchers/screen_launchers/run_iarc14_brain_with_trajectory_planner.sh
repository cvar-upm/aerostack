#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneIARC14BrainROSModule droneIARC14BrainROSModule_with_traj_planner.launch --wait

