screen -AmdS ardrone -t terminal bash
screen -S    ardrone -X screen -t roscore              ${AEROSTACK_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S    ardrone -X screen -t Ardrone_Autonomy     ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_ardrone_autonomy.sh
screen -S    ardrone -X screen -t Driver_Parrot        ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_driver_parrot.sh

screen -S    ardrone -X screen -t ekf_odometry         ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_ekf_odometry.sh
screen -S    ardrone -X screen -t trajectory_ctrl      ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_trajectory_controller.sh

screen -S    ardrone -X screen -t Opentld_node	       ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_opentld_node.sh
screen -S    ardrone -X screen -t IBVS_Controller      ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_IBVS_controller.sh
screen -S    ardrone -X screen -t supervisor           ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_supervisor_node.sh

screen -S    ardrone -X screen -t drone_interface      ${AEROSTACK_STACK}/launchers/ardrone_launch/sh_files/run_interface_node.sh
