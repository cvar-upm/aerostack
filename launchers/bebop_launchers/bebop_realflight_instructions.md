screen -AmdS bebop -t terminal bash
screen -S    bebop -X screen -t roscore              ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
screen -S    bebop -X screen -t Bebop_Autonomy       ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_bebop_autonomy.sh
screen -S    bebop -X screen -t Driver_Bebop         ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_driver_bebop.sh
screen -S    bebop -X screen -t EKF		     ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_ekf_odometry.sh
screen -S    bebop -X screen -t trajectory_ctrl      ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_trajectory_controller.sh
screen -S    bebop -X screen -t supervisor	     ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_supervisor_node.sh
screen -S    bebop -X screen -t Opentld_node	     ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_opentld_node.sh
screen -S    bebop -X screen -t IBVS_Controller      ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_IBVS_controller.sh
screen -S    bebop -X screen -t drone_interface      ${DRONE_STACK}/launchers/bebop_launchers/sh_files/run_interface_node.sh
