#ifndef DRONELOGGERROSMODULE_H
#define DRONELOGGERROSMODULE_H

#include <ros/ros.h>
#include "droneloggerrosbasicmodule.h"
#include "droneloggerrostopicsubscriber.h"

#include "communication_definition.h"

// Drone Telemetry
//Magnetometer and RotationAngles
#include "geometry_msgs/Vector3Stamped.h"
//Battery
#include "droneMsgsROS/battery.h"
//Altitude
#include "droneMsgsROS/droneAltitude.h"
//Ground Speed
#include "droneMsgsROS/vector2Stamped.h"
//Drone Status
#include "droneMsgsROS/droneStatus.h"
// BottomCamera and FrontCamera
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include "xmlfilereader.h"

// Drone driver commands
#include "droneMsgsROS/dronePitchRollCmd.h"
#include "droneMsgsROS/droneDYawCmd.h"
#include "droneMsgsROS/droneDAltitudeCmd.h"
#include "droneMsgsROS/droneCommand.h"
// EKF pose/speed estimates
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/dronePoseStamped.h"
#include "droneMsgsROS/droneSpeeds.h"
#include "droneMsgsROS/droneSpeedsStamped.h"
// Controller control mode and references
#include "droneMsgsROS/droneTrajectoryControllerControlMode.h"
#include "droneMsgsROS/dronePositionTrajectoryRefCommand.h"

#include "droneMsgsROS/obsVector.h"

#include "droneMsgsROS/landmarkVector.h"
#include "droneMsgsROS/obstaclesTwoDim.h"

#include "droneMsgsROS/societyPose.h"

#include "droneMsgsROS/dronePositionRefCommand.h"
#include "droneMsgsROS/dronePositionRefCommandStamped.h"
#include "droneMsgsROS/droneYawRefCommand.h"

#include "droneMsgsROS/droneHLCommand.h"
#include "droneMsgsROS/droneHLCommandAck.h"
#include "droneMsgsROS/droneMissionInfo.h"
#include "droneMsgsROS/droneGoTask.h"


#include <string>
#include <sstream>

class DroneLoggerROSModule : public DroneLoggerROSBasicModule {
public:
    DroneLoggerROSModule( ros::NodeHandle n);
    ~DroneLoggerROSModule();

private:
    //// Callbacks for each msg type
    static std::string batteryCallback(const droneMsgsROS::battery::ConstPtr &msg);
    static std::string droneAltitudeCallback(const droneMsgsROS::droneAltitude::ConstPtr &msg);
    static std::string vector3StampedCallback(const geometry_msgs::Vector3Stamped::ConstPtr &msg);
    static std::string vector2StampedCallback(const droneMsgsROS::vector2Stamped::ConstPtr &msg);
    static std::string droneStatusCallback(const droneMsgsROS::droneStatus::ConstPtr &msg);

    static std::string dronePitchRollCmdCallback(const droneMsgsROS::dronePitchRollCmd::ConstPtr &msg);
    static std::string droneDAltitudeCmdCallback(const droneMsgsROS::droneDAltitudeCmd::ConstPtr &msg);
    static std::string droneDYawCmdCallback(const droneMsgsROS::droneDYawCmd::ConstPtr &msg);
    static std::string droneCommandCallback(const droneMsgsROS::droneCommand::ConstPtr &msg);

    static std::string dronePoseCallback(const droneMsgsROS::dronePose::ConstPtr &msg);
    static std::string dronePoseStampedCallback(const droneMsgsROS::dronePoseStamped::ConstPtr &msg);
    static std::string droneSpeedsCallback(const droneMsgsROS::droneSpeeds::ConstPtr &msg);
    static std::string droneSpeedsStampedCallback(const droneMsgsROS::droneSpeedsStamped::ConstPtr &msg);

    static std::string droneTrajectoryControllerControlModeCallback(const droneMsgsROS::droneTrajectoryControllerControlMode::ConstPtr &msg);
    static std::string dronePositionTrajectoryRefCommandCallback(const droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr &msg);

    static std::string landmarkVectorCallback(const droneMsgsROS::landmarkVector::ConstPtr &msg);
    static std::string obstaclesTwoDimCallback(const droneMsgsROS::obstaclesTwoDim::ConstPtr &msg);

    static std::string obsVectorCallback(const droneMsgsROS::obsVector::ConstPtr &msg);

    static std::string societyPoseCallback(const droneMsgsROS::societyPose::ConstPtr &msg);

    static std::string dronePositionRefCommandCallback(const droneMsgsROS::dronePositionRefCommand::ConstPtr &msg);
    static std::string dronePositionRefCommandStampedCallback(const droneMsgsROS::dronePositionRefCommandStamped::ConstPtr &msg);
    static std::string droneYawRefCommandCallback(const droneMsgsROS::droneYawRefCommand::ConstPtr &msg);

    static std::string droneHLCommandCallback(const droneMsgsROS::droneHLCommand::ConstPtr &msg);
    static std::string droneHLCommandAckCallback(const droneMsgsROS::droneHLCommandAck::ConstPtr &msg);
    static std::string droneMissionInfoCallback(const droneMsgsROS::droneMissionInfo::ConstPtr &msg);
    static std::string droneGoTaskCallback(const droneMsgsROS::droneGoTask::ConstPtr &msg);



    //Images
    //Front
    static bool save_front_camera_images;
    static std::string droneFrontCameraCallback(const sensor_msgs::ImageConstPtr &msg);
    //Bottom
    static bool save_bottom_camera_images;
    static std::string droneBottomCameraCallback(const sensor_msgs::ImageConstPtr &msg);
    //Right
    static bool save_right_camera_images;
    static std::string droneRightCameraCallback(const sensor_msgs::ImageConstPtr &msg);
    //Left
    static bool save_left_camera_images;
    static std::string droneLeftCameraCallback(const sensor_msgs::ImageConstPtr &msg);
    //Back
    static bool save_back_camera_images;
    static std::string droneBackCameraCallback(const sensor_msgs::ImageConstPtr &msg);




    ///// Subscribers
    // Drone Telemetry
    DroneLoggerROSTopicSubscriber<droneMsgsROS::battery::ConstPtr> battery_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneAltitude::ConstPtr> altitude_subscriber;
    DroneLoggerROSTopicSubscriber<geometry_msgs::Vector3Stamped::ConstPtr> rotation_angles_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::vector2Stamped::ConstPtr> ground_speed_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneStatus::ConstPtr> status_subscriber;

    // Drone driver commands
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePitchRollCmd::ConstPtr> drone_command_pitch_roll_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneDAltitudeCmd::ConstPtr> drone_command_daltitude_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneDYawCmd::ConstPtr> drone_command_dyaw_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneCommand::ConstPtr> drone_command_high_level_subscriber;


    //Cameras
    DroneLoggerROSTopicSubscriber_MsgWithHeader<sensor_msgs::ImageConstPtr> front_camera_subscriber;
    DroneLoggerROSTopicSubscriber_MsgWithHeader<sensor_msgs::ImageConstPtr> bottom_camera_subscriber;
    DroneLoggerROSTopicSubscriber_MsgWithHeader<sensor_msgs::ImageConstPtr> right_camera_subscriber;
    DroneLoggerROSTopicSubscriber_MsgWithHeader<sensor_msgs::ImageConstPtr> left_camera_subscriber;
    DroneLoggerROSTopicSubscriber_MsgWithHeader<sensor_msgs::ImageConstPtr> back_camera_subscriber;



    // EKF pose/speed estimates
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePose::ConstPtr> state_estimator_pose_LMrT_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePose::ConstPtr> state_estimator_pose_GMR_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneSpeeds::ConstPtr> state_estimator_speeds_LMrT_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneSpeeds::ConstPtr> state_estimator_speeds_GMR_subscriber;

    // droneLocalizer
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePose::ConstPtr> localizer_pose_GMR_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneSpeeds::ConstPtr> localizer_speeds_GMR_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::landmarkVector::ConstPtr> localizer_landmark_list_subscriber;


    // Controller references (rebroadcasts): control mode and position, speed and trajectory references.
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneTrajectoryControllerControlMode::ConstPtr> trajectory_controller_control_mode_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePose::ConstPtr> trajectory_controller_position_reference_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneSpeeds::ConstPtr> trajectory_controller_speeds_reference_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr> trajectory_controller_trajectory_reference_subscriber;

    // Trajectory planner
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr> trajectory_planner_drone_trajectory_subscriber;

    // Brain
    DroneLoggerROSTopicSubscriber<droneMsgsROS::societyPose::ConstPtr> brain_society_pose_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneHLCommandAck::ConstPtr> brain_mission_hl_cmd_ack_subscriber;

    //Obstacles
    DroneLoggerROSTopicSubscriber<droneMsgsROS::obstaclesTwoDim::ConstPtr> obstacles_two_dim;


    // DroneArucoEye
    DroneLoggerROSTopicSubscriber<droneMsgsROS::obsVector::ConstPtr> aruco_eye_observation_list_subscriber;

    //Mission planner
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePositionRefCommand::ConstPtr> drone_mission_point_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::dronePositionRefCommand::ConstPtr> drone_mission_point_to_look_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneYawRefCommand::ConstPtr> drone_mission_yaw_to_look_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneMissionInfo::ConstPtr> drone_mission_info_subscriber;
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneHLCommand::ConstPtr> drone_mission_hl_cmd_subscriber;

    //Yaw commander
    DroneLoggerROSTopicSubscriber<droneMsgsROS::droneYawRefCommand::ConstPtr> yaw_ref_command_subscriber;

    // This boolean is added to perform the reading of configuration files outside of the constructors
private:
    bool configuration_files_are_read;
    bool read_configuration_files();
public:
    bool run();
};

#endif // DRONELOGGERROSMODULE_H
