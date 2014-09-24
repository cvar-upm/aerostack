# [IARC14_experimental_flight_final]
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 8 nodos
screen -S pelican -X screen -t pelican_node       ${DRONE_STACK}/launchers/screen_launchers/run_pelican_node.sh
screen -S pelican -X screen -t px4flow_sensor     ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh
# 3 nodos
screen -S pelican -X screen -t multicam_robot_tracker ${DRONE_STACK}/launchers/screen_launchers/run_multicamera_robot_tracker_simulator_iRobotCV.sh
screen -S pelican -X screen -t iarc14_brain       ${DRONE_STACK}/launchers/screen_launchers/run_iarc14_brain.sh
screen -S pelican -X screen -t mission_scheduler  ${DRONE_STACK}/launchers/screen_launchers/run_mission_scheduler.sh
# 25 nodos
screen -S pelican -X screen -t cvg_ueye_1_back    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_back.sh
screen -S pelican -X screen -t cvg_ueye_2_bottom  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_02_bottom.sh
screen -S pelican -X screen -t cvg_ueye_3_left    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_03_left.sh
screen -S pelican -X screen -t cvg_ueye_4_front   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_04_front.sh
screen -S pelican -X screen -t cvg_ueye_5_right   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_05_right.sh
screen -S pelican -X screen -t gridpoints_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_back_cam.sh
screen -S pelican -X screen -t gridpoints_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_bottom_cam.sh
screen -S pelican -X screen -t gridpoints_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_left_cam.sh
screen -S pelican -X screen -t gridpoints_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_front_cam.sh
screen -S pelican -X screen -t gridpoints_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_right_cam.sh
screen -S pelican -X screen -t groundrobots_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_bottom_cam.sh
screen -S pelican -X screen -t groundrobots_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_left_cam.sh
screen -S pelican -X screen -t groundrobots_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_front_cam.sh
screen -S pelican -X screen -t groundrobots_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_right_cam.sh
screen -S pelican -X screen -t groundrobots_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_3D_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_bottom_cam.sh
screen -S pelican -X screen -t groundrobots_3D_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_left_cam.sh
screen -S pelican -X screen -t groundrobots_3D_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_front_cam.sh
screen -S pelican -X screen -t groundrobots_3D_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_right_cam.sh
screen -S pelican -X screen -t keypoints_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_back_cam.sh
screen -S pelican -X screen -t keypoints_3D_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_bottom_cam.sh
screen -S pelican -X screen -t keypoints_3D_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_left_cam.sh
screen -S pelican -X screen -t keypoints_3D_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_front_cam.sh
screen -S pelican -X screen -t keypoints_3D_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_right_cam.sh
# total: 36 nodos
# 1 nodos - visualization
cd $DRONE_STACK; source setup.sh mastermind; ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
