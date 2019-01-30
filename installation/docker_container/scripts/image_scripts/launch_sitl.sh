#!/usr/bin/zsh

if [[ "$#" -lt 1 ]]; then
  echo "Usage launch_sitl.sh <world>"
  exit 0
fi

GAZEBO_WORLD=${1:-""}
GAZEBO_LOCATION=${GAZEBO_LOCATION:-"$HOME/src/pixhawk_sitl"}
ROS_DISTRO=${ROS_DISTRO:-"kinetic"}
LOG_DIR="$HOME/sitl_log"

if [[ "$GAZEBO_WORLD" == "" ]]; then
  echo "Unable to get world"
  exit 1
fi

if [[ -d $LOG_DIR ]]; then
  rm -rf $LOG_DIR
fi

mkdir -p $LOG_DIR

[[ "$GAZEBO_WORLD" =~ ".*\.world" ]] || GAZEBO_WORLD=$GAZEBO_WORLD.world

source /opt/ros/$ROS_DISTRO/setup.zsh

echo "- Launching roscore"
cd $GAZEBO_LOCATION/Firmware
roscore &>$LOG_DIR/roscore.log &

sleep 0.5

echo "- Launching posix_sitl"
cd $GAZEBO_LOCATION/Firmware
no_sim=1 make posix_sitl_default gazebo &>$LOG_DIR/pixhawk_sitl.log &
while [[ $(tail -33 $LOG_DIR/pixhawk_sitl.log | head -1) != d* ]]; do
  sleep 0.5
done

echo "- Launching gazebo_ros"
cd $GAZEBO_LOCATION/sitl_gazebo/worlds
rosrun gazebo_ros gazebo $GAZEBO_WORLD --verbose &>$LOG_DIR/gazebo_ros.log &


