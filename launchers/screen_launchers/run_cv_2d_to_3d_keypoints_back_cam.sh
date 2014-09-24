#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneCV2DTo3DROSModule droneCV2DTo3D_Keypoints.launch --wait camera_name:="back" camera_topic_name:="camera/back" camera_calib_param:="back_camera_calibration.yaml" camera_pose_wrt_drone:="camera_back_posewrtdrone.yaml" drone_pose_topic_name:="EstimatedPose_droneGMR_wrt_GFF" drone_rotation_angles_topic_name:="rotation_angles" keypoints_2d_topic_name:="camera/back/cv/grid_detection" keypoints_3d_topic_name:="perception/back/gridIntersections"

