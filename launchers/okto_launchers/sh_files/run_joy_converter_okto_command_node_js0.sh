#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/droneOktoSimulatorROSModule/launch/joyConverterToOktoCmdNode.launch --wait joy_device_name:="/dev/input/js0" drone_id_int:="2" drone_id_namespace:="drone2"

