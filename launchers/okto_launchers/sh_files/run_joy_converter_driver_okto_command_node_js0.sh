#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/driverOktoROSModule/launch/joyConverterToDrvOktoCmdNode.launch --wait drone_id_int:="2" drone_id_namespace:="drone2" joy_device_name:="/dev/input/js0"

