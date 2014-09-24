#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneSimulatorGridROSModule droneSimulatorGrid.launch --wait camera_name:="back" sensor_configuration:="simulator_grid_config_back.xml" drone_pose_topic_name:="simulator/dronePose" grid_intersections_topic_name:="perception/back/gridIntersections"

