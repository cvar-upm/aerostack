#!/bin/bash

NETWORK_ROSCORE=$1

shell=${SHELL:-"/bin/bash"}
shell=`basename $shell`

#echo "Running setup.sh .."
echo "-Setting ROS workspace"
#http://stackoverflow.com/questions/16011245/source-files-in-a-bash-script
. ${AEROSTACK_WORKSPACE}/devel/setup.$shell


# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument
if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
    echo "-Setting roscore in localhost"
    host_name=`cat /etc/hostname`
    export ROS_MASTER_URI=http://$host_name:11311
    export ROS_IP=$host_name
    export ROS_HOSTNAME=$host_name
  else
    echo "-Setting roscore in $NETWORK_ROSCORE"
    export ROS_MASTER_URI=http://$NETWORK_ROSCORE:11311
    OWN_IP=$(ifconfig | grep -Eo "[0-9]{3}\.[0-9]{2,3}\.[0-9]{1,3}\.[0-9]{1,3}" | head -n1)
    echo "-My IP in network (please check!)="$OWN_IP
    export ROS_IP=$OWN_IP
    export ROS_HOSTNAME=$OWN_IP
fi
