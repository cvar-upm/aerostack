#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh mastermind
roslaunch ${DRONE_STACK}/launchers/pelican_launchers/launch_files/droneInterface_jp_ROSModule.launch --wait drone_id_int:="0" drone_id_namespace:="drone0" 

