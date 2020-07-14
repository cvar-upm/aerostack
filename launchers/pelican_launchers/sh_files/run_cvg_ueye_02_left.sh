#! /bin/bash

cd $AEROSTACK_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/pelican_launchers/launch_files/ueye_cvg_cam.launch --wait camera_id_num:=2 camera_name_str:="left" config_file:="small_camera_RGB24_HUB.ini"

