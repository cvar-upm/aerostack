#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/bebop_launchers/launch_files/opentld_for_IBVSController.launch --wait drone_id_int:="4" drone_id_namespace:="drone4" &
roslaunch ${DRONE_STACK}/launchers/bebop_launchers/launch_files/opentld_gui_for_IBVSController.launch  --wait drone_id_int:="4" drone_id_namespace:="drone4" &
roslaunch droneOpenTLDTranslatorROS droneOpenTLDTranslatorROSModule.launch --wait drone_id_int:="4" drone_id_namespace:="drone4"
