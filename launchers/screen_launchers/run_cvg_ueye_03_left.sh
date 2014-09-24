#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch ${DRONE_STACK}/launchers/screen_launchers/ueye_cvg_cam.launch --wait camera_id_num:=3 camera_name_str:="left" config_file:="small_camera_RGB24_OTHER.ini"

