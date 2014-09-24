#! /bin/bash

cd $DRONE_STACK
source setup.sh
rostopic hz /drone0/camera/left/image_raw

