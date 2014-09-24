#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait

