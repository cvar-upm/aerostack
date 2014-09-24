# [IARC14_experimental_flight_final]
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S pelican -X screen -t pelican_node       ${DRONE_STACK}/launchers/screen_launchers/run_pelican_node.sh
screen -S pelican -X screen -t px4flow_sensor     ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh

screen -S pelican -X screen -t cvg_ueye_1_back    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_back.sh
screen -S pelican -X screen -t gridpoints_back    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_back_cam.sh
screen -S pelican -X screen -t groundrobots_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_back_cam.sh
screen -S pelican -X screen -t keypoints_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_back_cam.sh

cd ${DRONE_STACK}; source setup.sh; rosrun rviz rviz
rostopic echo /drone0/camera/back/cv/grid_detection
rostopic echo /drone0/perception/back/gridIntersections
rostopic echo /drone0/camera/back/cv/robots_detection
rostopic echo /drone0/perception/back/robots_detection

