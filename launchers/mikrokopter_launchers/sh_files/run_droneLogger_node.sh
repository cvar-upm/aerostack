#! /bin/bash

cd $DRONE_STACK
source setup.sh mastermind
roslaunch ${DRONE_STACK}/launchers/mikrokopter_launchers/launch_files/droneLoggerROSModule.launch --wait drone_id_int:="0" drone_id_namespace:="drone0"

