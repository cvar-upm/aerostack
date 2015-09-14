#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneIBVSControllerROSModule DroneIBVSControllerROSModule.launch --wait drone_id_int:="0" drone_id_namespace:="drone0" &
roslaunch droneTrackerEyeROSModule droneTrackerEyeROSModule.launch --wait drone_id_int:="0" drone_id_namespace:="drone0"