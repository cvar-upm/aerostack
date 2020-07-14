#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/bebop_launchers/launch_files/bebop_node.launch --wait drone_id_int:="4" drone_id_namespace:="drone4"
