#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait drone_id_int:="3" drone_id_namespace:="drone3"
