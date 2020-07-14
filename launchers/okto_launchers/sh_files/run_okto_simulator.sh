#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/droneOktoSimulatorROSModule/launch/droneOktoSimulatorROSModule.launch --wait drone_sim_config_filename:="okto_like_model.xml" drone_id_int:="2" drone_id_namespace:="drone2"
