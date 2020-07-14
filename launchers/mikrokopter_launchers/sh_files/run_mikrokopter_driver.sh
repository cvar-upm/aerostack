#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch mikrokopter_driver mikrokopter_driver_launcher.launch --wait drone_id_int:="2" drone_id_namespace:="drone2" comm_port:="/dev/ttyUSB0"

