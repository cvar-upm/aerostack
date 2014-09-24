# [IARC14_experimental_flight_final]
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
# px4flow_sensor
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh

# IMAV Trajectory Planner
screen -S pelican -X screen -t trajectory_planner  ${DRONE_STACK}/launchers/screen_launchers/run_imav13_trajectory_planner.sh
# IARC2014 Brain
screen -S pelican -X screen -t iarc14_brain        ${DRONE_STACK}/launchers/screen_launchers/run_iarc14_brain_with_trajectory_planner.sh
# IMAV Mission Planner
screen -S pelican -X screen -t IMAV_MissionPlanner ${DRONE_STACK}/launchers/screen_launchers/run_imav13_mission_planner.sh 

# Visualization
cd ${DRONE_STACK}; source setup.sh; roslaunch ${DRONE_STACK}/launchers/screen_launchers/rviz_visualizations_jp.launch --wait

