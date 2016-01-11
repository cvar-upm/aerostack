screen -AmdS ardrone -t terminal bash
screen -S    ardrone -X screen -t roscore              ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S    ardrone -X screen -t Ardrone_Autonomy     ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_bebop_autonomy.sh
screen -S    ardrone -X screen -t Driver_Parrot        ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_driver_bebop.sh

screen -S ardrone -X screen -t ekf			${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_ekf_odometry.sh

screen -S    ardrone -X screen -t trajectory_ctrl      ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_trajectory_controller.sh

screen -S ardrone -X screen -t supervisor		${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_supervisor_node.sh

screen -S    ardrone -X screen -t drone_interface      ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_interface_node.sh



