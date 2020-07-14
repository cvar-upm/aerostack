#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch droneObstacleProcessorVisualMarksROSModule droneObstacleProcessor2dVisualMarksROSModule.launch  --wait drone_id_int:="0" drone_id_namespace:="drone0"
