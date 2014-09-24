#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneCV2DTo3DROSModule droneCV2DTo3D_GroundRobots.launch --wait camera_name:="right" camera_topic_name:="camera/right" camera_calib_param:="right_camera_calibration.yaml" camera_pose_wrt_drone:="camera_right_posewrtdrone.yaml" drone_pose_topic_name:="EstimatedPose_droneGMR_wrt_GFF" drone_rotation_angles_topic_name:="rotation_angles" ground_robots_2d_topic_name:="camera/right/cv/ground_robots" ground_robots_3d_topic_name:="perception/right/robots_detection"

