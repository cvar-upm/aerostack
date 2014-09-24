#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch videoPublisherROSModule videoPublisherROSModule.launch --wait video_file:="/home/joselusl/Desktop/video.mp4" video_topic_name:="camera" module_rate:="30"

