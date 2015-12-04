#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch driverPixhawkROSModule driverPixhawkROSModule.launch --wait drone_id_int:="3" drone_id_namespace:="drone3"
