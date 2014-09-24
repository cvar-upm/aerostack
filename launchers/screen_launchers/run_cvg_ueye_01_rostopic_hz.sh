#! /bin/bash

cd $DRONE_STACK
source setup.sh
rostopic hz /drone0/camera/back/image_raw

