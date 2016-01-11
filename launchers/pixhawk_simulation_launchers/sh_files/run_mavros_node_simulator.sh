#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/launch_files/px4_SITL.launch  --wait drone_id_int:="5" drone_id_namespace:="drone5"
