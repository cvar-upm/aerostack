screen -AmdS pixhawk -t terminal bash
screen -S  pixhawk -X screen -t roscore          ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S  pixhawk -X screen -t mavros           ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_mavros_node_simulator.sh
screen -S  pixhawk -X screen -t driver_Pixhawk   ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_driver_pixhawk.sh
screen -S  pixhawk -X screen -t midlevel_node    ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S  pixhawk -X screen -t supervisor       ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_supervisor_node.sh
screen -S  pixhawk -X screen -t ekf_odometry     ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_ekf_odometry.sh
screen -S  pixhawk -X screen -t trajectory_ctrl  ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_trajectory_controller.sh

screen -S  pixhawk -X screen -t drone_interface  ${DRONE_STACK}/launchers/pixhawk_simulation_launchers/sh_files/run_interface_node.sh
