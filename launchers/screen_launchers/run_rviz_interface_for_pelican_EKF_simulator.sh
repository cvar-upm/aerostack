#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/droneEkfSimulatorRvizROSModule/launch/EKFSimulatorRvizROSModule.launch --wait
