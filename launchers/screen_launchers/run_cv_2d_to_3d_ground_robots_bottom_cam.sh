#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneCV2DTo3DROSModule droneCV2DTo3D_GroundRobots.launch --wait camera_name:="bottom" camera_topic_name:="camera/bottom" camera_calib_param:="bottom_camera_calibration.yaml" camera_pose_wrt_drone:="camera_bottom_posewrtdrone.yaml" drone_pose_topic_name:="EstimatedPose_droneGMR_wrt_GFF" drone_rotation_angles_topic_name:="rotation_angles" ground_robots_2d_topic_name:="camera/bottom/cv/ground_robots" ground_robots_3d_topic_name:="perception/bottom/robots_detection"

