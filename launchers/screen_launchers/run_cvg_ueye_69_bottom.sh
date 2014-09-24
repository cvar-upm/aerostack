#! /bin/bash

cd ~/cvg_ros_workspace
source setup.bash
roslaunch ${DRONE_STACK}/launchers/screen_launchers/ueye_cvg_cam.launch --wait camera_id_num:=69 camera_name_str:="bottom" config_file:="USB3_camera_RGB24_HUB.ini"

