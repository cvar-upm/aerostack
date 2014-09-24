#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneTrajectoryPlannerROSModule droneTrajectoryPlanner2dROSModule.launch --wait drone_id_namespace:=drone0 drone_id_int:=0 my_stack_directory:=${DRONE_STACK};


