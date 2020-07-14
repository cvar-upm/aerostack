screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore                     ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/start_roscore.sh
screen -S pelican -X screen -t pelican_node                ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_pelican_node.sh
screen -S pelican -X screen -t pelican_driver_node         ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t px4flow_sensor              ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface           ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_interface_lidar.sh
screen -S pelican -X screen -t midlevel_node               ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t ekf_odometry                ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_controller       ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_trajectory_controller.sh
screen -S pelican -X screen -t ibvs_controller             ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_IBVS_controller.sh
screen -S pelican -X screen -t ueycam		                   ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_cvg_ueye_02_front.sh
screen -S pelican -X screen -t Supervisor                  ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_supervisor_node.sh

screen -S pelican -X screen -t lider_lite                  ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_laser_altimeter.sh

screen -S pelican -X screen -t drone_interface             ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_interface_node.sh

screen -S pelican -X screen -t Opentld_node	               ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_opentld_node.sh

screen -S pelican -X screen -t logger                      ${AEROSTACK_STACK}/launchers/pelican_launchers/sh_files/run_logger.sh


