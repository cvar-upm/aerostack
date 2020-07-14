#!/bin/bash


echo " ### Launching AEROSTACK DX plots ###"

#gnome-terminal  \
#  --tab --title "rqt_plot dx" 		--command "bash -c \"
#rqt_plot $1/drone3/EstimatedSpeed_droneGMR_wrt_GFF/dx, /drone3/droneSpeedsRefs/dx -b 10;
#						exec bash\""  \  &
gnome-terminal  \
  --tab --title "rqt_plot x" 		--command "bash -c \"
rqt_plot $1/drone3/EstimatedPose_droneGMR_wrt_GFF/x, /drone3/dronePositionRefs/position_command/x -b 10;
						exec bash\""  \  &
