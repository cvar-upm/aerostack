#! /bin/bash

cd $DRONE_STACK
source setup.sh 
roslaunch performance_monitor performance_monitor.launch --wait drone_id_int:="1" drone_id_namespace:="drone1" 

