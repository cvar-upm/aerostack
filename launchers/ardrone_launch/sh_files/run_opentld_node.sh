#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch ${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_for_IBVSController.launch --wait drone_id_int:="1" drone_id_namespace:="drone1" &
roslaunch ${AEROSTACK_STACK}/launchers/ardrone_launch/launch_files/opentld_gui_for_IBVSController.launch  --wait drone_id_int:="1" drone_id_namespace:="drone1" &
roslaunch droneOpenTLDTranslatorROS droneOpenTLDTranslatorROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1"
