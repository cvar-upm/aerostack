# *** prueba ***: joy_node + okto_driver + okto_real
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 
screen -S    okto -X screen -t okto_driver       ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_driver.sh
screen -S    okto -X screen -t px4flow_sensor    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_node.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t joy_node_js0	 ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_joy_converter_okto_command_node_js0.sh

# *** prueba ***: trj_ctrl + ekf + mid_level_autopilot + driverOktoROSmodule + okto_driver + okto_real
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 8
screen -S    okto -X screen -t okto_driver       ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_driver.sh
screen -S    okto -X screen -t px4flow_sensor    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_node.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t driverOktoROSmodule ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_driverOktoROSModule.sh
screen -S    okto -X screen -t midlevel_autopilot  ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S    okto -X screen -t drone_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_interface_node.sh
screen -S    okto -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_ekf_odometry.sh
screen -S    okto -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_trajectory_controller.sh

