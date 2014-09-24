# [IARC14_experimental_flight_final]
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 7 nodos
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
# px4flow_sensor
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh
# 3 nodos
screen -S pelican -X screen -t multicam_robot_tracker ${DRONE_STACK}/launchers/screen_launchers/run_multicamera_robot_tracker_simulator_iRobotCV.sh
screen -S pelican -X screen -t iarc14_brain        ${DRONE_STACK}/launchers/screen_launchers/run_iarc14_brain.sh
screen -S pelican -X screen -t mission_scheduler  ${DRONE_STACK}/launchers/screen_launchers/run_mission_scheduler.sh
# 10 nodos
# grids
screen -S pelican -X screen -t sim_grid_back      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_back.sh
screen -S pelican -X screen -t sim_grid_bottom    ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_bottom.sh
screen -S pelican -X screen -t sim_grid_left      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_left.sh
screen -S pelican -X screen -t sim_grid_front     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_front.sh
screen -S pelican -X screen -t sim_grid_right     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_right.sh
# iRobot
screen -S pelican -X screen -t sim_iRobotCV_back      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_back.sh
screen -S pelican -X screen -t sim_iRobotCV_bottom    ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_bottom.sh
screen -S pelican -X screen -t sim_iRobotCV_left      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_left.sh
screen -S pelican -X screen -t sim_iRobotCV_front     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_front.sh
screen -S pelican -X screen -t sim_iRobotCV_right     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_right.sh
# 2 nodos - Visualization + sim iRobots
# visualization
screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
# robot simulator
screen -S pelican -X screen -t sim_iRobots        ${DRONE_STACK}/launchers/screen_launchers/run_robot_simulator.sh
# total: 22 nodos
