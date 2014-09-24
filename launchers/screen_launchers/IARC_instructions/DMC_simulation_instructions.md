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
# 1 nodos - Visualization
# visualization
cd $DRONE_STACK; source setup.sh; rosrun rqt_plot rqt_plot

screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
# [ 5] start the logger
screen -S pelican -X screen -t drone_logger       ${DRONE_STACK}/launchers/screen_launchers/run_droneLogger_node.sh
rosrun rqt_plot rqt_plot

