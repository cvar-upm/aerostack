#!/bin/bash

mkdir -p ~/src 
cd ~/src
git clone https://alejodosr@bitbucket.org/alejodosr/pixhawk_sitl.git
cd pixhawk_sitl
git submodule update --init

. /opt/ros/kinetic/setup.bash
cd ~/src/pixhawk_sitl/sitl_gazebo
mkdir Build 
cd Build
cmake ..
cmake ..
make