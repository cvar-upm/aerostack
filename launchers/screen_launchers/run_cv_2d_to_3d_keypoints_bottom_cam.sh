#! /bin/bash

cd $DRONE_STACK
source setup.sh
roslaunch droneCV2DTo3DROSModule droneCV2DTo3D_Keypoints.launch --wait camera_name:="bottom" camera_topic_name:="camera/bottom" camera_calib_param:="bottom_camera_calibration.yaml" camera_pose_wrt_drone:="camera_bottom_posewrtdrone.yaml" drone_pose_topic_name:="EstimatedPose_droneGMR_wrt_GFF" drone_rotation_angles_topic_name:="rotation_angles" keypoints_2d_topic_name:="camera/bottom/cv/grid_detection" keypoints_3d_topic_name:="perception/bottom/gridIntersections"

