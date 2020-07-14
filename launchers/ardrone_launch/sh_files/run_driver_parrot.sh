#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch driverParrotARDroneROSModule driverParrotARDroneROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1"
