#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneInterfaceROSModule droneInterface_jp_ROSModule.launch --wait

