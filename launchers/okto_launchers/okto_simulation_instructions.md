# *** prueba ***: joy_node + okto_simulador
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 
screen -S    okto -X screen -t okto_simulator    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_simulator.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t rviz_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_rviz_interface_for_okto_simulator.sh
screen -S    okto -X screen -t joy_node_js1	 ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_joy_converter_okto_command_node_js1.sh

# *** prueba ***: joy_node + driverOktoROSmodule + okto_simulador
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 
screen -S    okto -X screen -t okto_simulator    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_simulator.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t driverOktoROSmodule ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_driverOktoROSModule.sh
screen -S    okto -X screen -t rviz_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_rviz_interface_for_okto_simulator.sh
screen -S    okto -X screen -t joy_node_js1	 ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_joy_converter_driver_okto_command_node_js1.sh

# *** prueba ***: joy_node + mid_level_autopilot + driverOktoROSmodule + okto_simulador
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 
screen -S    okto -X screen -t okto_simulator    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_simulator.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t driverOktoROSmodule ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_driverOktoROSModule.sh
screen -S    okto -X screen -t midlevel_autopilot  ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S    okto -X screen -t rviz_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_rviz_interface_for_okto_simulator.sh
screen -S    okto -X screen -t joy_node	          ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_joy_converter_midlevelautopilot_test_js1.sh
screen -S    okto -X screen -t drone_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_interface_node.sh

# *** prueba ***: trj_ctrl + ekf + mid_level_autopilot + driverOktoROSmodule + okto_simulador
screen -AmdS okto -t terminal bash
screen -S    okto -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# 
screen -S    okto -X screen -t okto_simulator    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_okto_simulator.sh
screen -S    okto -X screen -t px4flow_interface ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_px4flow_interface.sh
screen -S    okto -X screen -t driverOktoROSmodule ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_driverOktoROSModule.sh
screen -S    okto -X screen -t midlevel_autopilot  ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S    okto -X screen -t rviz_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_rviz_interface_for_okto_simulator.sh
screen -S    okto -X screen -t drone_interface    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_interface_node.sh
screen -S    okto -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_ekf_odometry.sh
screen -S    okto -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/okto_launchers/sh_files/run_trajectory_controller.sh
