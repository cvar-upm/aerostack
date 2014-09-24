#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneEKFStateEstimatorROSModule droneEKFStateEstimatorROSModule.launch --wait
