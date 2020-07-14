#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch driverPixhawkROSModule joyConverterToDrvPixhawkCmdNode.launch --wait drone_id_int:="3" drone_id_namespace:="drone3" joy_device_name:="/dev/input/js0"
