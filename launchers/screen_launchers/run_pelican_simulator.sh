#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch dronePelicanSimulatorROSModule dronePelicanSimulatorROSModule.launch --wait drone_sim_config_filename:="pelican_like_model.xml"
