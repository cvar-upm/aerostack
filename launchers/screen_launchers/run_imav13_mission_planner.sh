#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneMissionPlannerROSModule droneMissionPlannerROSModule.launch --wait drone_id_namespace:=drone0 drone_id_int:=0 my_stack_directory:=${DRONE_STACK};


