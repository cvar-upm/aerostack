#! /bin/bash

cd ~/cvg_ros_workspace
source setup.bash
rostopic hz /drone0/camera/bottom/image_raw

