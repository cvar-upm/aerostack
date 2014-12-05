#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch dronePelicanSimulatorROSModule dronePelicanSimulatorROSModule.launch --wait drone_sim_config_filename:="$DRONE_STACK/stack/droneSimulators/droneSimulator/droneSimulator/configs/pelican_like_model.xml"
