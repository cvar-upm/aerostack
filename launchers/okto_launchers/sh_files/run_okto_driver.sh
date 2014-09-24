#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch okto_driver okto_driver_launcher.launch --wait drone_id_int:="2" drone_id_namespace:="drone2" comm_port:="/dev/ttyUSB0"

