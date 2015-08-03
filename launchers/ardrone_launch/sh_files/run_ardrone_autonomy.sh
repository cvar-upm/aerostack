#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/ardrone_launch/ardrone_indoors.launch  --wait drone_id_int:="1" drone_id_namespace:="drone1"
