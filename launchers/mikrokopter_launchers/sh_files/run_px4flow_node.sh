#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/okto_launchers/launch_files/px4flow.launch --wait drone_id_int:="2" drone_id_namespace:="drone2" 


