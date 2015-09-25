screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore                      ${DRONE_STACK}/launchers/pelican_launchers/sh_files/start_roscore.sh
screen -S pelican -X screen -t pelican_node                 ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_pelican_node.sh
screen -S pelican -X screen -t pelican_driver_node          ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t px4flow_sensor               ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface            ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_px4flow_interface_okto.sh
screen -S pelican -X screen -t midlevel_node                ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t ekf_odometry                 ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_controller        ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_trajectory_controller.sh
screen -S pelican -X screen -t ueycam_front		              ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_cvg_ueye_03_front.sh
screen -S pelican -X screen -t localizer                    ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_localizer.sh
screen -S pelican -X screen -t obstacle_processor           ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_obstacle_processor.sh
screen -S pelican -X screen -t obstacle_distance_calculator ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_obstacle_distance_calculator.sh
screen -S pelican -X screen -t trajectory_planner           ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_trajectory_planner.sh
screen -S pelican -X screen -t yaw_commander                ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_yaw_commander.sh
screen -S pelican -X screen -t run_communication_manager    ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_communication_manager.sh
screen -S pelican -X screen -t run_manager                  ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_manager.sh
screen -S pelican -X screen -t run_mission_scheduler        ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_mission_scheduler.sh
screen -S pelican -X screen -t supervisor                   ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_supervisor_node.sh

screen -S pelican -X screen -t lider_lite                  ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_laser_altimeter.sh

screen -S pelican -X screen -t aruco_eye_front              ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_arucoeye_front.sh

screen -S pelican -X screen -t drone_interface             ${DRONE_STACK}/launchers/pelican_launchers/sh_files/run_interface_node.sh

