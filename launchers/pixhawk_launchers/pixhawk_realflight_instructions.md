screen -AmdS pixhawk -t terminal bash
screen -S  pixhawk -X screen -t roscore              ${AEROSTACK_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S  pixhawk -X screen -t mavros               ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_mavros_node.sh
screen -S  pixhawk -X screen -t driver_Pixhawk       ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_driver_pixhawk.sh
screen -S  pixhawk -X screen -t px4flow_sensor       ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_px4flow_node.sh
screen -S  pixhawk -X screen -t px4flow_interface    ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_px4flow_interface.sh
screen -S  pixhawk -X screen -t midlevel_node        ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S  pixhawk -X screen -t supervisor           ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_supervisor_node.sh
screen -S  pixhawk -X screen -t ekf_odometry         ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_ekf_odometry.sh
screen -S  pixhawk -X screen -t trajectory_ctrl      ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_trajectory_controller.sh
screen -S  pixhawk -X screen -t joy_node             ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_joy_node.sh

screen -S    pixhawk -X screen -t drone_interface    ${AEROSTACK_STACK}/launchers/pixhawk_launchers/sh_files/run_interface_node.sh
