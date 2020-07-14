#!/bin/bash

DEBUG_MODE=$1
NUMID_DRONE=$2
NETWORK_ROSCORE=$3

SESSION=$USER

# http://stackoverflow.com/questions/6482377/bash-shell-script-check-input-argument
if [ -z $NETWORK_ROSCORE ] # Check if NETWORK_ROSCORE is NULL
  then
  	#Argument 2 is empty
	. ${AEROSTACK_STACK}/setup.sh
    	OPEN_ROSCORE=1
  else
    	. ${AEROSTACK_STACK}/setup.sh $3
fi
if [ -z $NUMID_DRONE ] # Check if NUMID_DRONE is NULL
  then
  	#Argument 1 empty
    	echo "-Setting droneId = 1"
    	NUMID_DRONE=6
  else
    	echo "-Setting droneId = $2"
fi
if [ -z $DEBUG_MODE ]
	then
		# Kill any previous session
		tmux kill-session -t $SESSION
		tmux kill-session -a

		# Create new session
		tmux -2 new-session -d -s $SESSION

		# Create roscore
		tmux send-keys -t $SESSION:0 "roscore" C-m

		# Create one window per roslaunch
		tmux new-window -t $SESSION:1 -n 'sdk'
		tmux send-keys "roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_210/launch_files/sdk_mbzirc.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

		tmux new-window -t $SESSION:2 -n 'driverDJIMatrice210ROSModule'
		tmux send-keys "roslaunch driverDjiMatrice210ROSModule driverDJIMatrice210ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} use_mpc_mode:='false' use_mpc_zvelocity_mode:='true'" C-m

		tmux new-window -t $SESSION:3 -n 'ethz_msf'
                tmux send-keys "roslaunch msf_updates  pose_position_velocity_altitude_sensor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

		tmux new-window -t $SESSION:4 -n 'ethz_msf_process'
                tmux send-keys "roslaunch ethz_msf_process ethz_msf_process_outdoors_sim.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

		tmux new-window -t $SESSION:5 -n 'droneMidLevelAutopilotROSModule'
		tmux send-keys "roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

		tmux new-window -t $SESSION:6 -n 'droneTrajectoryControllerROSModule'
		tmux send-keys "roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

  		tmux new-window -t $SESSION:7 -n 'process_monitor'
		tmux send-keys "roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK}" C-m

		tmux new-window -t $SESSION:8 -n 'LinearMPC'
	    	tmux send-keys "roslaunch mav_linear_mpc mav_linear_mpc_msf.launch mav_name:=m210_sim_msf --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE" C-m

                tmux new-window -t $SESSION:9 -n 'MotionController'
                tmux send-keys "roslaunch motion_controller_process motion_controller.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE" C-m

                tmux new-window -t $SESSION:10 -n 'TrajectoryPlanner'
                tmux send-keys "roslaunch Fast_Traj_Planner Fast_Traj_Planner_outdoor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE" C-m
	else
		gnome-terminal  \
  --tab --title "dji sdk ros"	--command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_210/launch_files/sdk.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Driver dji ros"	--command "bash -c \"
roslaunch driverDjiMatrice210ROSModule driverDJIMatrice210ROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK} use_mpc_mode:='false' use_mpc_mode:='true';
						exec bash\""  \
  --tab --title "Midlevel Controller"	--command "bash -c \"
roslaunch droneMidLevelAutopilotROSModule droneMidLevelAutopilotROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "Trajectory Controller" --command "bash -c \"
roslaunch droneTrajectoryControllerROSModule droneTrajectoryControllerROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
   --tab --title "Robot localizationROSModule" --command "bash -c \"
roslaunch droneRobotLocalizationROSModule droneRobotLocalizationROSModule.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
   --tab --title "Robot localization" --command "bash -c \"
roslaunch ${AEROSTACK_STACK}/launchers/dji_launchers/matrice_210/launch_files/EKF_ouster.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\""  \
  --tab --title "DroneSupervisor"	--command "bash -c \"
roslaunch process_monitor_process process_monitor.launch --wait drone_id_namespace:=drone$NUMID_DRONE drone_id_int:=$NUMID_DRONE my_stack_directory:=${AEROSTACK_STACK};
						exec bash\"" \ &
fi
