#!/bin/bash

#source $AEROSTACK_STACK/setup.sh 
source $AEROSTACK_STACK/setup.sh hriday-Lenovo-G50-70


# TOPICS TO RECORD
TOPICS_TO_RECORD="";

for i in 3 4 5
do
TOPICS_TO_RECORD="$TOPICS_TO_RECORD
  /drone$i/ArucoSlam_EstimatedPose \
  /drone$i/ArucoSlam_EstimatedPose_v2 \
  /drone$i/ArucoSlam_EstimatedSpeeds \
  /drone$i/ArucoSlam_LandarmkList \
  /drone$i/EstimatedPose_droneGMR_wrt_GFF \
  /drone$i/EstimatedPose_iRobotGMR_wrt_droneGMR \
  /drone$i/EstimatedSpeed_droneGMR_wrt_GFF \
  /drone$i/SOEstimatedPose \
  /drone$i/SOEstimatedSpeeds \
  /drone$i/altitude \
  /drone$i/ardrone/imu \
  /drone$i/ardrone/land \
  /drone$i/ardrone/mag \
  /drone$i/ardrone/navdata \
  /drone$i/ardrone/reset \
  /drone$i/ardrone/takeoff \
  /drone$i/arucoObservation \
  /drone$i/aruco_eye/aruco_observation \
  /drone$i/battery \
  /drone$i/camera/front/camera_info \
  /drone$i/camera/front/image_raw \
  /drone$i/camera/front/image_raw/compressed \
  /drone$i/cmd_vel \
  /drone$i/collision_free_trajectory \
  /drone$i/command/dAltitude \
  /drone$i/command/dYaw \
  /drone$i/command/high_level \
  /drone$i/command/pitch_roll \
  /drone$i/command_PBVS/Altitude \
  /drone$i/controller_image_features \
  /drone$i/controller_image_features_feedback \
  /drone$i/distanceToObstacles \
  /drone$i/droneControllerYawRefCommand \
  /drone$i/droneGoTask \
  /drone$i/droneManagerStateDoContinue \
  /drone$i/droneManagerStatus \
  /drone$i/droneMissionHLCommandAck \
  /drone$i/droneMissionInfo \
  /drone$i/droneMissionPlannerCommand \
  /drone$i/droneMissionPoint \
  /drone$i/dronePointToLook \
  /drone$i/dronePositionRefs \
  /drone$i/droneSpeedsRefs \
  /drone$i/droneTrajectoryAbsRefCommand \
  /drone$i/droneTrajectoryController/controlMode \
  /drone$i/droneTrajectoryRefCommand \
  /drone$i/droneYawToLook \
  /drone$i/eventString \
  /drone$i/file_to_reproduce \
  /drone$i/get_bounding_box \
  /drone$i/ground_speed \
  /drone$i/imu \
  /drone$i/isInTheSystem \
  /drone$i/is_object_on_frame \
  /drone$i/magnetometer \
  /drone$i/message_to_say \
  /drone$i/missionState \
  /drone$i/obstacles \
  /drone$i/obstacles_visualization \
  /drone$i/pressure \
  /drone$i/process_alive_signal \
  /drone$i/process_error_unified_notification \
  /drone$i/processes_performance \
  /drone$i/robotsound \
  /drone$i/rotation_angles \
  /drone$i/self_detected_process_error \
  /drone$i/societyPose \
  /drone$i/status \
  /drone$i/temperature \
  /drone$i/tld_commands \
  /drone$i/tld_fps \
  /drone$i/tld_gui_bb \
  /drone$i/tld_gui_cmds \
  /drone$i/tld_tracked_object \
  /drone$i/tracking_object \
  /drone$i/trajectoryControllerPositionReferencesRebroadcast \
  /drone$i/trajectoryControllerSpeedReferencesRebroadcast \
  /drone$i/trajectoryControllerTrajectoryReferencesRebroadcast \
  /drone$i/wifiIsOk"
done

TOPICS_TO_RECORD="$TOPICS_TO_RECORD
  /rosout \
  /rosout_agg \
  /societyBroadcast \
  /tf \
  /tf_static" 

#echo $TOPICS_TO_RECORD


# RECORD
rosbag record -o session1 $TOPICS_TO_RECORD


