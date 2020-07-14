#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh 
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1" 

