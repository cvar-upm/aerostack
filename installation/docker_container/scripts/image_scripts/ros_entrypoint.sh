#!/bin/bash

shell=${SHELL:-"/bin/bash"}
shell=`basename $shell`
# setup ros environment
source "/opt/ros/$ROS_DISTRO/setup.$shell"
unset $shell
set +e
exec "$@"
