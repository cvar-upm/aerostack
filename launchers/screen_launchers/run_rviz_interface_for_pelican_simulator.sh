#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/screen_launchers/rviz_visualizations_jp.launch --wait
