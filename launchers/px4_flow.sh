#!/bin/bash

# rosmake px4flow_node 
# sudo chmod 777 /dev/ttyACM0 # check /dev/ttyACM0 and px4flow_node/launch/px4flow_parameters.yaml
# sudo chmod 777 /dev/ttyUSB0 # check /dev/ttyUSB0 and px4flow_node/launch/px4flow_parameters.yaml

echo " ### plotting optical flow sensor outputs !!! ###"

gnome-terminal  \
	--tab --title "PX4 Flow Sensor"		--command "bash -c \"
roslaunch px4flow_node px4flow.launch --wait;
						exec bash\""  \
	--tab --title "rqt_plot" 		--command "bash -c \"
rqt_plot $1/px4flow/opt_flow/velocity_x:velocity_y:ground_distance -b 10;
						exec bash\""  &
						




