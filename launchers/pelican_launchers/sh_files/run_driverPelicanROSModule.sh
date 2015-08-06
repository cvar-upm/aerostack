#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/pelican_launchers/launch_files/driverPelicanROSModule.launch --wait  drone_id_int:="0" drone_id_namespace:="drone0"
 