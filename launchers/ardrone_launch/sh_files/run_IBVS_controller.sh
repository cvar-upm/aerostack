#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneIBVSControllerROSModule DroneIBVSControllerROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1"&
roslaunch droneTrackerEyeROSModule droneTrackerEyeROSModule.launch --wait drone_id_int:="1" drone_id_namespace:="drone1"
