#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/mikrokopter_launchers/launch_files/mikrocopter_driver_ros_module.launch --wait drone_id_int:="2" drone_id_namespace:="drone2" 
