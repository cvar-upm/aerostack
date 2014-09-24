#!/bin/bash
#echo "Running setup.sh .."
echo "-Setting ROS workspace"
#http://stackoverflow.com/questions/16011245/source-files-in-a-bash-script
. ${DRONE_WORKSPACE}/setup.bash

NETWORK_ROSCORE=$1
# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument
if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
    echo "-Setting roscore in localhost"
    export ROS_MASTER_URI=http://localhost:11311
  else
    echo "-Setting roscore in $NETWORK_ROSCORE"
    export ROS_MASTER_URI=http://$NETWORK_ROSCORE:11311
fi
