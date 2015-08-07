screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore                     ${DRONE_STACK}/launchers/pelican_launchers/sh_files/start_roscore.sh
screen -S pelican -X screen -t pelican_node                ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_pelican_node.sh
screen -S pelican -X screen -t pelican_driver_node         ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t px4flow_sensor              ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface           ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_interface_okto.sh
screen -S pelican -X screen -t midlevel_node               ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t ekf_odometry                ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_controller       ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_trajectory_controller.sh

screen -S pelican -X screen -t lider_lite                  ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_laser_altimeter.sh

screen -S pelican -X screen -t drone_interface             ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_interface_node.sh


