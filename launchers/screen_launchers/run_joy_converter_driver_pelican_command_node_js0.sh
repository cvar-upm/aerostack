#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/driverPelicanROSModule/launch/joyConverterToDrvPelicanCmdNode.launch --wait joy_device_name:="/dev/input/js0"

