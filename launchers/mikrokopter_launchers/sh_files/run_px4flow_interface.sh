#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/mikrokopter_launchers/launch_files/driver_px4flow_interface_ROSModule.launch --wait drone_id_int:="2" drone_id_namespace:="drone2"

