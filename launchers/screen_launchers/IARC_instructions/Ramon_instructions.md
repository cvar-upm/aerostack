# screen + roscore
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# simulator + state_estimator + traj_controller
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh
# grids
screen -S pelican -X screen -t sim_grid_back      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_back.sh
screen -S pelican -X screen -t sim_grid_bottom    ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_bottom.sh
screen -S pelican -X screen -t sim_grid_left      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_left.sh
screen -S pelican -X screen -t sim_grid_front     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_front.sh
screen -S pelican -X screen -t sim_grid_right     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_grid_right.sh
# iRobot
screen -S pelican -X screen -t sim_iRobotCV_back      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_back.sh
screen -S pelican -X screen -t sim_iRobotCV_bottom    ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_bottom.sh
screen -S pelican -X screen -t sim_iRobotCV_left      ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_left.sh
screen -S pelican -X screen -t sim_iRobotCV_front     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_front.sh
screen -S pelican -X screen -t sim_iRobotCV_right     ${DRONE_STACK}/launchers/screen_launchers/run_simulator_iRobotCV_right.sh
screen -S pelican -X screen -t multicam_robot_tracker ${DRONE_STACK}/launchers/screen_launchers/run_multicamera_robot_tracker_simulator_iRobotCV.sh
# Brain
screen -S pelican -X screen -t iarc14_brain       ${DRONE_STACK}/launchers/screen_launchers/run_iarc14_brain.sh
# Mission Scheduler
screen -S pelican -X screen -t mission_scheduler  ${DRONE_STACK}/launchers/screen_launchers/run_mission_scheduler.sh
# visualization
screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
# robot simulator
screen -S pelican -X screen -t sim_iRobots        ${DRONE_STACK}/launchers/screen_launchers/run_robot_simulator.sh


# [IARC14_simulation] experimental tests: asctec_simulator + mavwork + interfaz + ekf
## T0: First, compile the stack with 
### ${DRONE_STACK}/droneMsgsROS/src/include/communication_definition.h
#### //#define TEST_WITHOUT_AURCOSLAM
#### #define TEST_WITH_AURCOSLAM
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh

screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh


# [IARC14_flight] experimental tests: asctec_driver + mavwork + ekf
screen -S pelican -X screen -t pelican_node       ${DRONE_STACK}/launchers/screen_launchers/run_pelican_node.sh
screen -S pelican -X screen -t px4flow_sensor     ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh
# [IARC14_flight] interfaz en remoto
cd $DRONE_STACK; source setup.sh mastermind; roslaunch ${DRONE_STACK}/launchers/screen_launchers/rviz_visualizations_jp.launch --wait

roslaunch ${DRONE_STACK}/launchers/screen_launchers/rviz_visualizations_jp.launch --wait drone_id_namespace:=drone1 drone_id_int:=1 my_stack_directory:=${DRONE_STACK};

# [IMAV13_simulation]
## T0: First, compile the stack with 
### ${DRONE_STACK}/droneMsgsROS/src/include/communication_definition.h
#### //#define TEST_WITHOUT_AURCOSLAM
#### #define TEST_WITH_AURCOSLAM
cd ${DRONE_STACK}; source setup.sh; cd launchers; ./IMAV13_with_Pelican_rosmake_01.sh
## T1: Init a roscore
cd ${DRONE_STACK}; source setup.sh; roscore
## T2: Init rviz interface
${DRONE_STACK}/launchers/rvizInterface_Test.sh 1 localhost
## T3: start IMAV13 simulation with the Pelican
${DRONE_STACK}/launchers/IMAV13_with_Pelican_CVGStack_quadrotor_Testsim01.sh 1 localhost

# [IARC14_experimental_flight_final]
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

screen -S pelican -X screen -t pelican_node       ${DRONE_STACK}/launchers/screen_launchers/run_pelican_node.sh
screen -S pelican -X screen -t px4flow_sensor     ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
screen -S pelican -X screen -t ekf_odometry       ${DRONE_STACK}/launchers/screen_launchers/run_ekf_odometry.sh
screen -S pelican -X screen -t trajectory_ctrl    ${DRONE_STACK}/launchers/screen_launchers/run_trajectory_controller.sh
screen -S pelican -X screen -t cvg_ueye_1_back    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_back.sh
screen -S pelican -X screen -t cvg_ueye_2_bottom  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_02_bottom.sh
screen -S pelican -X screen -t cvg_ueye_3_left    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_03_left.sh
screen -S pelican -X screen -t cvg_ueye_4_front   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_04_front.sh
screen -S pelican -X screen -t cvg_ueye_5_right   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_05_right.sh
screen -S pelican -X screen -t gridpoints_back    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_back_cam.sh
#screen -S pelican -X screen -t gridpoints_bottom    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_bottom_cam.sh
screen -S pelican -X screen -t gridpoints_left    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_left_cam.sh
screen -S pelican -X screen -t gridpoints_front   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_front_cam.sh
screen -S pelican -X screen -t gridpoints_right   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_right_cam.sh
screen -S pelican -X screen -t groundrobots_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_bottom_cam.sh
screen -S pelican -X screen -t groundrobots_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_left_cam.sh
screen -S pelican -X screen -t groundrobots_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_front_cam.sh
screen -S pelican -X screen -t groundrobots_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_right_cam.sh
# [IARC14_experimental_flight_final]
cd $DRONE_STACK; source setup.sh mastermind; roslaunch ${DRONE_STACK}/launchers/screen_launchers/rviz_visualizations_jp.launch --wait


# rqt_plot to mastermind
# export ROS_MASTER_URI=http://mastermind:11311
cd $DRONE_STACK
source setup.sh mastermind 
rqt_plot


# [ 6] correr rviz para visualizar las imagenes en ROS
# Esto solo se puede hacer con la microSD en un laptop o en un sobremesa
# abrir terminal nuevo en interfaz grafica de ubuntu, y ejecutar los siguientes comandos:
cd ~/cvg_ros_workspace
source setup.bash
rosrun rviz rviz

# [ 7] tutoriales de screen
# many links: http://aperiodic.net/screen/other_links
# tutorials:  http://www.rackaid.com/blog/linux-screen-tutorial-and-how-to/
# tutorials:  http://aperiodic.net/screen/quick_reference
# tutorials:  http://archive09.linux.com/articles/113657
# tutorials:  http://www.jerri.de/blog/archives/2006/05/02/scripting_screen_for_fun_and_profit/
# manual:     http://www.gnu.org/software/screen/manual/screen.html
# Una vez iniciado screen, en el terminal de ssh del pelican ejecutar
screen -x pelican
# presionar 'control+a', despues '?' para instrucciones
# presionar 'control+a', despues '"' para ver que subventanas hay abiertas en screen y navegar entre ellas


# *** END:   Start-up steps ***

# [F1] Shutdown the pelican
sudo shutdown now -h 0

# ------------ END:   tentative steps using screen ------------

cd $DRONE_STACK
source setup.sh
rostopic hz /drone0/camera/back/image_raw   --window=15
rostopic hz /drone0/camera/bottom/image_raw --window=15
rostopic hz /drone0/camera/left/image_raw   --window=15
rostopic hz /drone0/camera/front/image_raw  --window=15
rostopic hz /drone0/camera/right/image_raw  --window=15

