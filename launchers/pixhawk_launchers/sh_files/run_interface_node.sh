#! /bin/bash

cd $DRONE_STACK
source setup.sh odroid
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait drone_id_int:="3" drone_id_namespace:="drone3" 

