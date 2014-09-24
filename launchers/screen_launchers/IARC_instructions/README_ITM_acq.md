
	1) Conectarse a la wifi "pelican" (comprobar que esta encendido el led azul del pelican, que indica que la wifi esta funcionando; sino conectar el teclado usb y darle a enter)

		-> Hacer "ping 10.0.157.10" (IP del pelican: 10.0.157.10)    		

	2) Conexion por ssh: "ssh asctec@10.0.157.10 [-X]"
     	
		-> Usuario: asctec    Password: asctec     (igual que ssh)

	3) Seguir los pasos "tentative steps using screen" dentro del terminal de ssh del pelican


Camera order:
-------------
	ueye_id: 1	position: back
	ueye_id: 2	position: bottom
	ueye_id: 3	position: left


# ************ BEGIN: tentative steps using screen ************

# *** BEGIN: Start-up steps ***

# [ 0] update date and time on the Pelican
~/cvg_ros_workspace/screen_launchers/Pelican_date_update.sh

# [ 1] start ssh connection:
ssh asctec@10.0.157.10     	# Wifi
ssh asctec@192.168.0.135  	# Ethernet

# [ 2] start screen
screen -AmdS pelican -t terminal bash

# [ 3] start roscore
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh

# [ 4] start everything except for the logger
screen -S pelican -X screen -t pelican_nodelets  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_nodelets.sh
screen -S pelican -X screen -t pelican_driver    ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t px4flow_interface ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t px4flow_sensor    ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t cvg_ueye_1_back   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_back.sh
screen -S pelican -X screen -t cvg_ueye_2_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_02_bottom.sh
screen -S pelican -X screen -t cvg_ueye_3_left   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_03_left.sh
screen -S pelican -X screen -t cvg_ueye_4_front  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_04_front.sh
screen -S pelican -X screen -t cvg_ueye_5_right  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_05_right.sh

# [ 5] start the logger
screen -S pelican -X screen -t drone_logger     ${DRONE_STACK}/launchers/screen_launchers/run_droneLogger_node.sh

# [ 4b] Optional launchers, joypad, etc
# screen + roscore start
screen -AmdS pelican -t terminal bash
screen -S pelican -X screen -t roscore ${DRONE_STACK}/launchers/screen_launchers/start_roscore.sh
# test AutoPilotNodelet
screen -S pelican -X screen -t pelican_nodelets  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_nodelets.sh
screen -S pelican -X screen -t joy_node	        ${DRONE_STACK}/launchers/screen_launchers/run_joy_converter_pelican_command_node_js0.sh
# test driverPelicanROSModule
screen -S pelican -X screen -t pelican_nodelets  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_nodelets.sh
screen -S pelican -X screen -t pelican_driver    ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t joy_node	         ${DRONE_STACK}/launchers/screen_launchers/run_joy_converter_driver_pelican_command_node_js0.sh
# testing cameras rostopic hz
screen -S pelican -X screen -t cvg_ueye_1_hz  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_rostopic_hz.sh
screen -S pelican -X screen -t cvg_ueye_2_hz  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_02_rostopic_hz.sh
screen -S pelican -X screen -t cvg_ueye_3_hz  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_03_rostopic_hz.sh
screen -S pelican -X screen -t cvg_ueye_4_hz  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_04_rostopic_hz.sh
screen -S pelican -X screen -t cvg_ueye_5_hz  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_05_rostopic_hz.sh
# drone one image logger, for testing
screen -S pelican -X screen -t drone_logger     ${DRONE_STACK}/launchers/screen_launchers/run_droneOneImageLogger_node.sh
# pruebas joy_node + pelican_simulador
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
screen -S pelican -X screen -t px4flow_interface ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t rviz_interface  ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
screen -S pelican -X screen -t joy_node	        ${DRONE_STACK}/launchers/screen_launchers/run_joy_converter_pelican_command_node_js0.sh
# pruebas joy_node + cvg_driver_pelican + pelican_simulador
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
screen -S pelican -X screen -t joy_node	          ${DRONE_STACK}/launchers/screen_launchers/run_joy_converter_driver_pelican_command_node_js1.sh
# pruebas joy_node + cvg_driver_pelican + pelican_simulator + midlevel_autopilot + interface
screen -S pelican -X screen -t pelican_simulator  ${DRONE_STACK}/launchers/screen_launchers/run_pelican_simulator.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t rviz_interface     ${DRONE_STACK}/launchers/screen_launchers/run_rviz_interface_for_pelican_simulator.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t joy_node	          ${DRONE_STACK}/launchers/screen_launchers/run_joy_converter_midlevelautopilot_test_js1.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
# experimental tests: asctec_driver + px4flow_sensor + cvg_driver_pelican  + midlevel_autopilot + interface
screen -S pelican -X screen -t pelican_nodelets   ${DRONE_STACK}/launchers/screen_launchers/run_pelican_nodelets.sh
screen -S pelican -X screen -t px4flow_sensor     ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_node.sh
screen -S pelican -X screen -t px4flow_interface  ${DRONE_STACK}/launchers/screen_launchers/run_px4flow_interface.sh
screen -S pelican -X screen -t pelican_driver     ${DRONE_STACK}/launchers/screen_launchers/run_driverPelicanROSModule.sh
screen -S pelican -X screen -t midlevel_autopilot ${DRONE_STACK}/launchers/screen_launchers/run_midlevelautopilot_node.sh
screen -S pelican -X screen -t drone_interface    ${DRONE_STACK}/launchers/screen_launchers/run_interface_node.sh
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
# Brain
screen -S pelican -X screen -t iarc14_brain       ${DRONE_STACK}/launchers/screen_launchers/run_iarc14_brain.sh
# Mission Scheduler
screen -S pelican -X screen -t mission_scheduler  ${DRONE_STACK}/launchers/screen_launchers/run_mission_scheduler.sh

screen -S pelican -X screen -t cvg_ueye_1_back    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_01_back.sh
screen -S pelican -X screen -t cvg_ueye_2_bottom  ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_02_bottom.sh
screen -S pelican -X screen -t cvg_ueye_3_left    ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_03_left.sh
screen -S pelican -X screen -t cvg_ueye_4_front   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_04_front.sh
screen -S pelican -X screen -t cvg_ueye_5_right   ${DRONE_STACK}/launchers/screen_launchers/run_cvg_ueye_05_right.sh
screen -S pelican -X screen -t gridpoints_back    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_back_cam.sh
screen -S pelican -X screen -t gridpoints_bottom  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_bottom_cam.sh
screen -S pelican -X screen -t gridpoints_left    ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_left_cam.sh
screen -S pelican -X screen -t gridpoints_front   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_front_cam.sh
screen -S pelican -X screen -t gridpoints_right   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_keypoints_right_cam.sh
screen -S pelican -X screen -t groundrobots_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_bottom_cam.sh
screen -S pelican -X screen -t groundrobots_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_left_cam.sh
screen -S pelican -X screen -t groundrobots_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_front_cam.sh
screen -S pelican -X screen -t groundrobots_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_iarc14_ground_robots_right_cam.sh
screen -S pelican -X screen -t groundrobots_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_back_cam.sh
screen -S pelican -X screen -t groundrobots_3D_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_bottom_cam.sh
screen -S pelican -X screen -t groundrobots_3D_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_left_cam.sh
screen -S pelican -X screen -t groundrobots_3D_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_front_cam.sh
screen -S pelican -X screen -t groundrobots_3D_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_ground_robots_right_cam.sh
screen -S pelican -X screen -t keypoints_3D_back   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_back_cam.sh
screen -S pelican -X screen -t keypoints_3D_bottom ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_bottom_cam.sh
screen -S pelican -X screen -t keypoints_3D_left   ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_left_cam.sh
screen -S pelican -X screen -t keypoints_3D_front  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_front_cam.sh
screen -S pelican -X screen -t keypoints_3D_right  ${DRONE_STACK}/launchers/screen_launchers/run_cv_2d_to_3d_keypoints_right_cam.sh


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

