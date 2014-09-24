#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/dronePelicanSimulatorROSModule/launch/dronePelicanSimulatorROSModule.launch --wait drone_sim_config_filename:="pelican_like_model.xml"
