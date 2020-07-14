#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh 
roslaunch performance_monitor performance_monitor.launch --wait drone_id_int:="5" drone_id_namespace:="drone5" 

