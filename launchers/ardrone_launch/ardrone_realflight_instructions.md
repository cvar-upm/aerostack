screen -AmdS ardrone -t terminal bash
screen -S    ardrone -X screen -t roscore              ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh


screen -S    ardrone -X screen -t Ardrone_Autonomy     ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_ardrone_autonomy.sh
screen -S    ardrone -X screen -t Driver_Parrot        ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_driver_parrot.sh

screen -S    ardrone -X screen -t ekf_odometry         ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_ekf_odometry.sh
screen -S    ardrone -X screen -t trajectory_ctrl      ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_trajectory_controller.sh


screen -S    ardrone -X screen -t Opentld_node	       ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_opentld_node.sh
screen -S    ardrone -X screen -t IBVS_Controller      ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_IBVS_controller.sh

screen -S    ardrone -X screen -t drone_interface      ${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_interface_node.sh
