#include "droneloggerrosmodule.h"

bool DroneLoggerROSModule::save_front_camera_images  = false;
bool DroneLoggerROSModule::save_bottom_camera_images = false;
bool DroneLoggerROSModule::save_right_camera_images  = false;
bool DroneLoggerROSModule::save_left_camera_images   = false;
bool DroneLoggerROSModule::save_back_camera_images   = false;

DroneLoggerROSModule::DroneLoggerROSModule( ros::NodeHandle n) :
    DroneLoggerROSBasicModule(n),
    // Drone Telemetry
    battery_subscriber(n,        "drone;battery", DRONE_LOGGER_SENSOR_BATTERY, &DroneLoggerROSModule::batteryCallback, init_rostime),
    altitude_subscriber(n,       "drone;altitude", DRONE_LOGGER_SENSOR_ALTITUDE, &DroneLoggerROSModule::droneAltitudeCallback, init_rostime),
    rotation_angles_subscriber(n,"drone;rotation_angles", DRONE_LOGGER_SENSOR_ROTATION_ANGLES, &DroneLoggerROSModule::vector3StampedCallback, init_rostime),
    ground_speed_subscriber(n,   "drone;ground_speed", DRONE_LOGGER_SENSOR_GROUND_SPEED, &DroneLoggerROSModule::vector2StampedCallback, init_rostime),
    status_subscriber(n,         "drone;status", DRONE_LOGGER_SENSOR_STATUS, &DroneLoggerROSModule::droneStatusCallback, init_rostime),
    // Drone driver commands (sent by the interface, the controller or other publishers)
    drone_command_pitch_roll_subscriber(n,"drone;command;PR", DRONE_LOGGER_COMMAND_DRONE_COMMAND_PITCH_ROLL, &DroneLoggerROSModule::dronePitchRollCmdCallback, init_rostime),
    drone_command_daltitude_subscriber(n, "drone;command;Dh", DRONE_LOGGER_COMMAND_DRONE_COMMAND_DALTITUDE, &DroneLoggerROSModule::droneDAltitudeCmdCallback, init_rostime),
    drone_command_dyaw_subscriber(n,      "drone;command;DY", DRONE_LOGGER_COMMAND_DRONE_COMMAND_DYAW, &DroneLoggerROSModule::droneDYawCmdCallback, init_rostime),
    drone_command_high_level_subscriber(n,"drone;command;high_level", DRONE_LOGGER_COMMAND_DRONE_HL_COMMAND, &DroneLoggerROSModule::droneCommandCallback, init_rostime),
    //Cameras
    front_camera_subscriber(n,"camera;front", DRONE_LOGGER_SENSOR_FRONT_CAMERA, &DroneLoggerROSModule::droneFrontCameraCallback, init_rostime),
    bottom_camera_subscriber(n,"camera;bottom", DRONE_LOGGER_SENSOR_BOTTOM_CAMERA, &DroneLoggerROSModule::droneBottomCameraCallback, init_rostime),
    right_camera_subscriber(n,"camera;right", DRONE_LOGGER_SENSOR_RIGHT_CAMERA, &DroneLoggerROSModule::droneRightCameraCallback, init_rostime),
    left_camera_subscriber(n,"camera;left", DRONE_LOGGER_SENSOR_LEFT_CAMERA, &DroneLoggerROSModule::droneLeftCameraCallback, init_rostime),
    back_camera_subscriber(n,"camera;back", DRONE_LOGGER_SENSOR_BACK_CAMERA, &DroneLoggerROSModule::droneBackCameraCallback, init_rostime),
    // EKF pose/speed estimates
    state_estimator_pose_LMrT_subscriber(n,  "state_estimator;pose_LMrT", DRONE_LOGGER_POSE_SUBSCRIPTION_LMrT, &DroneLoggerROSModule::dronePoseCallback, init_rostime),
    state_estimator_pose_GMR_subscriber(n,   "state_estimator;pose_GMR", DRONE_LOGGER_POSE_SUBSCRIPTION_GMR, &DroneLoggerROSModule::dronePoseCallback, init_rostime),
    state_estimator_speeds_LMrT_subscriber(n,"state_estimator;speeds_LMrT", DRONE_LOGGER_SPEEDS_SUBSCRIPTION_LMrT, &DroneLoggerROSModule::droneSpeedsCallback, init_rostime),
    state_estimator_speeds_GMR_subscriber(n, "state_estimator;speeds_GMR", DRONE_LOGGER_SPEEDS_SUBSCRIPTION_GMR, &DroneLoggerROSModule::droneSpeedsCallback, init_rostime),
    // droneLocalizer
    localizer_pose_GMR_subscriber(n,   "aruco_localizer;pose_GMR", DRONE_LOGGER_LOCALIZER_POSE_SUBSCRIPTION_GMR, &DroneLoggerROSModule::dronePoseCallback, init_rostime),
    localizer_speeds_GMR_subscriber(n, "aruco_localizer;speeds_GMR", DRONE_LOGGER_LOCALIZER_SPEEDS_SUBSCRIPTION_GMR, &DroneLoggerROSModule::droneSpeedsCallback, init_rostime),
    localizer_landmark_list_subscriber(n, "aruco_localizer;landmark_list", DRONE_LOGGER_LOCALIZER_LANDMARK_LIST, &DroneLoggerROSModule::landmarkVectorCallback, init_rostime),
    // Controller references (rebroadcasts): control mode and position, speed and trajectory references
    trajectory_controller_control_mode_subscriber(n,        "controller;control_mode", MODULE_NAME_TRAJECTORY_CONTROLLER+"/controlMode", &DroneLoggerROSModule::droneTrajectoryControllerControlModeCallback, init_rostime),
    trajectory_controller_position_reference_subscriber(n,  "controller;position_ref", DRONE_LOGGER_POSITION_REF_REBROADCAST_SUBSCRIPTION, &DroneLoggerROSModule::dronePoseCallback, init_rostime),
    trajectory_controller_speeds_reference_subscriber(n,    "controller;speeds_ref", DRONE_LOGGER_SPEED_REF_REBROADCAST_SUBSCRIPTION, &DroneLoggerROSModule::droneSpeedsCallback, init_rostime),
    trajectory_controller_trajectory_reference_subscriber(n,"controller;trajectory_ref", DRONE_LOGGER_TRAJECTORY_REF_REBROADCAST_SUBSCRIPTION, &DroneLoggerROSModule::dronePositionTrajectoryRefCommandCallback, init_rostime),
    //Trajectory planner
    trajectory_planner_drone_trajectory_subscriber(n,"trajectory_planner;droneTrajectory", DRONE_LOGGER_TRAJECTORY_COMMAND, &DroneLoggerROSModule::dronePositionTrajectoryRefCommandCallback, init_rostime),
    //Brain
    brain_society_pose_subscriber(n,"brain;societyPose", DRONE_LOGGER_SOCIETY_POSE_SUBS, &DroneLoggerROSModule::societyPoseCallback, init_rostime),
    brain_mission_hl_cmd_ack_subscriber(n,"brain;drone_hl_cmd_ack", DRONE_BRAIN_MISSION_HL_COMMAND_ACK, &DroneLoggerROSModule::droneHLCommandAckCallback, init_rostime),
    //Obstacles
    obstacles_two_dim(n,"obstacles_processor;obstacles", DRONE_LOGGER_OBSTACLES_SUBS, &DroneLoggerROSModule::obstaclesTwoDimCallback, init_rostime),
    //Aruco Eye
    aruco_eye_observation_list_subscriber(n,"aruco_eye;obs_arucos", DRONE_LOGGER_ARUCO_EYE_OBSERVATIONVEC_LIST, &DroneLoggerROSModule::obsVectorCallback, init_rostime),
    //Drone Mission planner
    drone_mission_point_subscriber(n,"mission_planner;drone_mission_point", DRONE_LOGGER_MISSION_POINT_SUBS, &DroneLoggerROSModule::dronePositionRefCommandCallback, init_rostime),
    drone_mission_point_to_look_subscriber(n,"mission_planner;drone_point_to_look", DRONE_LOGGER_POINT_TO_LOOK_PUB, &DroneLoggerROSModule::dronePositionRefCommandCallback, init_rostime),
    drone_mission_yaw_to_look_subscriber(n,"mission_planner;drone_yaw_to_look", DRONE_LOGGER_YAW_TO_LOOK_PUB, &DroneLoggerROSModule::droneYawRefCommandCallback, init_rostime),
    drone_mission_info_subscriber(n,"mission_planner;drone_mission_info", DRONE_LOGGER_MISSION_INFO_PUB, &DroneLoggerROSModule::droneMissionInfoCallback, init_rostime),
    drone_mission_hl_cmd_subscriber(n,"mission_planner;drone_hl_cmd", DRONE_LOGGER_MISSION_HL_COMMAND, &DroneLoggerROSModule::droneHLCommandCallback, init_rostime),
    //Yaw ref command
    yaw_ref_command_subscriber(n,"yaw_commander;drone_yaw_ref_command", DRONE_LOGGER_YAW_REF_CMD, &DroneLoggerROSModule::droneYawRefCommandCallback, init_rostime),
    // This boolean is added to perform the reading of configuration files outside of the constructors
    configuration_files_are_read(false)
{
    return;
}

DroneLoggerROSModule::~DroneLoggerROSModule()
{
    return;
}

std::string DroneLoggerROSModule::batteryCallback(const droneMsgsROS::battery::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "batteryPercent:" << msg->batteryPercent;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneAltitudeCallback(const droneMsgsROS::droneAltitude::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "altitude:" << msg->altitude;
    result_ss << " altitude_speed:" << msg->altitude_speed;
    return result_ss.str();
}

std::string DroneLoggerROSModule::vector3StampedCallback(const geometry_msgs::Vector3Stamped::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "z:" << msg->vector.z; //yaw
    result_ss << " y:" << msg->vector.y; //pitch
    result_ss << " x:" << msg->vector.x; //roll
    return result_ss.str();
}

std::string DroneLoggerROSModule::vector2StampedCallback(const droneMsgsROS::vector2Stamped::ConstPtr &msg) {
    std::stringstream result_ss;
    result_ss <<  "x:" << msg->vector.x;
    result_ss << " y:" << msg->vector.y;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneStatusCallback(const droneMsgsROS::droneStatus::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "status:";
    switch (msg->status) {
    case droneMsgsROS::droneStatus::INITED:
        result_ss << "INITED";
        break;
    case droneMsgsROS::droneStatus::LANDED:
        result_ss << "LANDED";
        break;
    case droneMsgsROS::droneStatus::FLYING:
        result_ss << "FLYING";
        break;
    case droneMsgsROS::droneStatus::HOVERING:
        result_ss << "HOVERING";
        break;
    case droneMsgsROS::droneStatus::TAKING_OFF:
        result_ss << "TAKING_OFF";
        break;
    case droneMsgsROS::droneStatus::LANDING:
        result_ss << "LANDING";
        break;
    case droneMsgsROS::droneStatus::LOOPING:
        result_ss << "LOOPING";
        break;
    case droneMsgsROS::droneStatus::UNKNOWN:
    default:
        result_ss << "UNKNOWN";
        break;
    }
    return result_ss.str();
}

std::string DroneLoggerROSModule::dronePitchRollCmdCallback(const droneMsgsROS::dronePitchRollCmd::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "pitchCmd:" << msg->pitchCmd;
    result_ss << " rollCmd:" << msg->rollCmd;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneDAltitudeCmdCallback(const droneMsgsROS::droneDAltitudeCmd::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "dAltitudeCmd:" << msg->dAltitudeCmd;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneDYawCmdCallback(const droneMsgsROS::droneDYawCmd::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "dYawCmd:" << msg->dYawCmd;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneCommandCallback(const droneMsgsROS::droneCommand::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "command:";
    switch (msg->command) {
    case droneMsgsROS::droneCommand::TAKE_OFF:
        result_ss << "TAKE_OFF";
        break;
    case droneMsgsROS::droneCommand::HOVER:
        result_ss << "HOVER";
        break;
    case droneMsgsROS::droneCommand::LAND:
        result_ss << "LAND";
        break;
    case droneMsgsROS::droneCommand::MOVE:
        result_ss << "MOVE";
        break;
    case droneMsgsROS::droneCommand::RESET:
        result_ss << "RESET";
        break;
    case droneMsgsROS::droneCommand::UNKNOWN:
    default:
        result_ss << "UNKNOWN";
        break;
    }

    return result_ss.str();
}

std::string DroneLoggerROSModule::dronePoseCallback(const droneMsgsROS::dronePose::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "x:" << msg->x;
    result_ss << " y:" << msg->y;
    result_ss << " z:" << msg->z;
    result_ss << " yaw:" << msg->yaw;
    result_ss << " pitch:" << msg->pitch;
    result_ss << " roll:" << msg->roll;
    return result_ss.str();
}

std::string DroneLoggerROSModule::dronePoseStampedCallback(const droneMsgsROS::dronePoseStamped::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "x:" << msg->pose.x;
    result_ss << " y:" << msg->pose.y;
    result_ss << " z:" << msg->pose.z;
    result_ss << " yaw:" << msg->pose.yaw;
    result_ss << " pitch:" << msg->pose.pitch;
    result_ss << " roll:" << msg->pose.roll;
    return result_ss.str();
}


std::string DroneLoggerROSModule::droneSpeedsCallback(const droneMsgsROS::droneSpeeds::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "dx:" << msg->dx;
    result_ss << " dy:" << msg->dy;
    result_ss << " dz:" << msg->dz;
    result_ss << " dyaw:" << msg->dyaw;
    result_ss << " dpitch:" << msg->dpitch;
    result_ss << " droll:" << msg->droll;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneSpeedsStampedCallback(const droneMsgsROS::droneSpeedsStamped::ConstPtr &msg)
{
    std::stringstream result_ss;
    result_ss <<  "dx:" << msg->speed.dx;
    result_ss << " dy:" << msg->speed.dy;
    result_ss << " dz:" << msg->speed.dz;
    result_ss << " dyaw:" << msg->speed.dyaw;
    result_ss << " dpitch:" << msg->speed.dpitch;
    result_ss << " droll:" << msg->speed.droll;
    return result_ss.str();
}

std::string DroneLoggerROSModule::droneTrajectoryControllerControlModeCallback(const droneMsgsROS::droneTrajectoryControllerControlMode::ConstPtr &msg)
{
    std::stringstream result_ss;
    switch (msg->command) {
    case droneMsgsROS::droneTrajectoryControllerControlMode::SPEED_CONTROL:
        result_ss << "command:" << "SPEED";
        break;
    case droneMsgsROS::droneTrajectoryControllerControlMode::POSITION_CONTROL:
        result_ss << "command:" << "POSITION";
        break;
    case droneMsgsROS::droneTrajectoryControllerControlMode::TRAJECTORY_CONTROL:
        result_ss << "command:" << "TRAJECTORY";
        break;
    case droneMsgsROS::droneTrajectoryControllerControlMode::UNKNOWN_CONTROL_MODE:
        result_ss << "command:" << "UNKNOWN";
    default:
        break;
    }
    return result_ss.str();
}

std::string DroneLoggerROSModule::dronePositionTrajectoryRefCommandCallback(const droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr &msg)
{
    std::ostringstream xmat_trajectoryLogMsgStrm; xmat_trajectoryLogMsgStrm.str(std::string());
    std::ostringstream ymat_trajectoryLogMsgStrm; ymat_trajectoryLogMsgStrm.str(std::string());
    std::ostringstream zmat_trajectoryLogMsgStrm; zmat_trajectoryLogMsgStrm.str(std::string());
    int num_checkpoints = msg->droneTrajectory.size();

    if ( num_checkpoints == 0) {
        xmat_trajectoryLogMsgStrm << "[]";
        ymat_trajectoryLogMsgStrm << "[]";
        zmat_trajectoryLogMsgStrm << "[]";
    } else {
        xmat_trajectoryLogMsgStrm << "[";
        ymat_trajectoryLogMsgStrm << "[";
        zmat_trajectoryLogMsgStrm << "[";

        for (int i=0; i<num_checkpoints; i++ ) {
            xmat_trajectoryLogMsgStrm << msg->droneTrajectory[i].x;
            ymat_trajectoryLogMsgStrm << msg->droneTrajectory[i].y;
            zmat_trajectoryLogMsgStrm << msg->droneTrajectory[i].z;
            if (i < num_checkpoints-1) {
                xmat_trajectoryLogMsgStrm << ";";
                ymat_trajectoryLogMsgStrm << ";";
                zmat_trajectoryLogMsgStrm << ";";
            } else {
                xmat_trajectoryLogMsgStrm << "]";
                ymat_trajectoryLogMsgStrm << "]";
                zmat_trajectoryLogMsgStrm << "]";
            }
        }
    }

    std::stringstream result_ss;
    result_ss <<  "x:" << xmat_trajectoryLogMsgStrm.str()
              << " y:" << ymat_trajectoryLogMsgStrm.str()
              << " z:" << zmat_trajectoryLogMsgStrm.str();
    result_ss << " is_periodic:" << (int)msg->is_periodic
              << " initial_checkpoint:" << msg->initial_checkpoint;
    return result_ss.str();
}


std::string DroneLoggerROSModule::obsVectorCallback(const droneMsgsROS::obsVector::ConstPtr &msg)
{
    std::stringstream result_ss;

    //result_ss<<" YPR_system:"<<msg->YPR_system;
    //result_ss<<" target_frame:"<<msg->target_frame;
    //result_ss<<" reference_frame:"<<msg->reference_frame;

    result_ss<< "obs_id:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].id<<";";
    }
    result_ss<<"]";

    result_ss<<" obs_x:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].x<<";";
    }
    result_ss<<"]";

    result_ss<<" obs_y:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].y<<";";
    }
    result_ss<<"]";

    result_ss<<" obs_z:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].z<<";";
    }
    result_ss<<"]";

    result_ss<<" obs_yaw:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].yaw<<";";
    }
    result_ss<<"]";

    result_ss<<" obs_pitch:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].pitch<<";";
    }
    result_ss<<"]";

    result_ss<<" roll:[";
    for(unsigned int i=0;i<msg->obs.size();i++)
    {
        result_ss<<msg->obs[i].roll<<";";
    }
    result_ss<<"]";

    return result_ss.str();
}


std::string DroneLoggerROSModule::landmarkVectorCallback(const droneMsgsROS::landmarkVector::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "id:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++)
    {
        result_ss<<msg->landmark_vector[i].id<<";";
    }
    result_ss<<"]";
    result_ss<<" x:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].x<<";";
    }
    result_ss<<"]";
    result_ss<<" y:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].y<<";";
    }
    result_ss<<"]";
    result_ss<<" z:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].z<<";";
    }
    result_ss<<"]";
    result_ss<<" yaw:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].yaw<<";";
    }
    result_ss<<"]";
    result_ss<<" pitch:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].pitch<<";";
    }
    result_ss<<"]";
    result_ss<<" roll:[";
    for (unsigned int i=0;i<msg->landmark_vector.size();i++) {
        result_ss<<msg->landmark_vector[i].roll<<";";
    }
    result_ss<<"]";


    return result_ss.str();
}


std::string DroneLoggerROSModule::obstaclesTwoDimCallback(const droneMsgsROS::obstaclesTwoDim::ConstPtr &msg)
{
    std::stringstream result_ss;


    //msg->walls
    result_ss<< "walls_id:[";
    for (unsigned int i=0; i<msg->walls.size(); i++) {
        result_ss<<msg->walls[i].id<<";";
    }
    result_ss<<"]";
    result_ss<<" walls_center:[";
    for (unsigned int i=0; i<msg->walls.size(); i++) {
        result_ss<<msg->walls[i].centerX<<",";
        result_ss<<msg->walls[i].centerY<<";";
    }
    result_ss<<"]";

    result_ss<<" walls_size:[";
    for (unsigned int i=0; i<msg->walls.size(); i++) {
        result_ss<<msg->walls[i].sizeX<<",";
        result_ss<<msg->walls[i].sizeY<<";";
    }
    result_ss<<"]";

    result_ss<<" walls_yaw:[";
    for (unsigned int i=0; i<msg->walls.size(); i++) {
        result_ss<<msg->walls[i].yawAngle<<";";
    }
    result_ss<<"]";

    // msg->poles
    result_ss<<" poles_id:[";
    for (unsigned int i=0; i<msg->poles.size(); i++) {
        result_ss<<msg->poles[i].id<<";";
    }
    result_ss<<"]";
    result_ss<<" poles_center:[";
    for (unsigned int i=0; i<msg->poles.size(); i++) {
        result_ss<<msg->poles[i].centerX<<",";
        result_ss<<msg->poles[i].centerY<<";";
    }
    result_ss<<"]";
    result_ss<<" poles_size:[";
    for (unsigned int i=0; i<msg->poles.size(); i++) {
        result_ss<<msg->poles[i].radiusX<<",";
        result_ss<<msg->poles[i].radiusY<<";";
    }
    result_ss<<"]";
    result_ss<<" poles_yaw:[";
    for (unsigned int i=0; i<msg->poles.size(); i++) {
        result_ss<<msg->poles[i].yawAngle<<";";
    }
    result_ss<<"]";


    return result_ss.str();
}

std::string DroneLoggerROSModule::societyPoseCallback(const droneMsgsROS::societyPose::ConstPtr &msg)
{
    std::stringstream result_ss;


    result_ss<< "societyDrone_id:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].id<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_x:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.x<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_y:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.y<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_z:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.z<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_yaw:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.yaw<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_pitch:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.pitch<<";";
    }
    result_ss<<"]";

    result_ss<<" societyDrone_pose_roll:[";
    for(unsigned int i=0;i<msg->societyDrone.size();i++)
    {
        result_ss<<msg->societyDrone[i].pose.roll<<";";
    }
    result_ss<<"]";

    return result_ss.str();
}


std::string DroneLoggerROSModule::dronePositionRefCommandCallback(const droneMsgsROS::dronePositionRefCommand::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "x:"<<msg->x;
    result_ss<<" y:"<<msg->y;
    result_ss<<" z:"<<msg->z;


    return result_ss.str();
}

std::string DroneLoggerROSModule::dronePositionRefCommandStampedCallback(const droneMsgsROS::dronePositionRefCommandStamped::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "position_command_x:"<<msg->position_command.x;
    result_ss<<" position_command_y:"<<msg->position_command.y;
    result_ss<<" position_command_z:"<<msg->position_command.z;


    return result_ss.str();
}

std::string DroneLoggerROSModule::droneYawRefCommandCallback(const droneMsgsROS::droneYawRefCommand::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "yaw:"<<msg->yaw;

    return result_ss.str();
}


std::string DroneLoggerROSModule::droneHLCommandCallback(const droneMsgsROS::droneHLCommand::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss << "hlCommand:";
    switch (msg->hlCommand)
    {
    case droneMsgsROS::droneHLCommand::TAKE_OFF:
        result_ss << "TAKE_OFF";
        break;
    case droneMsgsROS::droneHLCommand::HOVER:
        result_ss << "HOVER";
        break;
    case droneMsgsROS::droneHLCommand::LAND:
        result_ss << "LAND";
        break;
    case droneMsgsROS::droneHLCommand::MOVE_TRAJECTORY:
        result_ss << "MOVE_TRAJECTORY";
        break;
    case droneMsgsROS::droneHLCommand::SLEEP:
        result_ss << "SLEEP";
        break;
    case droneMsgsROS::droneHLCommand::UNKNOWN:
    default:
        result_ss << "UNKNOWN";
        break;
    }

    return result_ss.str();
}

std::string DroneLoggerROSModule::droneHLCommandAckCallback(const droneMsgsROS::droneHLCommandAck::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "ack:"<<static_cast<int>(msg->ack);

    return result_ss.str();
}

std::string DroneLoggerROSModule::droneMissionInfoCallback(const droneMsgsROS::droneMissionInfo::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "durationMission:"<<msg->durationMission.toSec();
    result_ss<<" durationSubmission:"<<msg->durationSubmission.toSec();
    result_ss<<" idSubmission:"<<msg->idSubmission;
    result_ss<<" loopSubmision:"<<static_cast<int>(msg->loopSubmission);
    result_ss<<" durationTask:"<<msg->durationTask.toSec();
    result_ss<<" idTask:"<<msg->idTask;
    result_ss<<" taskType:"<<msg->taskType;
    result_ss<<" taskState:";
    switch(msg->taskState)
    {
    case droneMsgsROS::droneMissionInfo::WAITING_BRAIN:
        result_ss<<"WAITING_BRAIN";
        break;
    case droneMsgsROS::droneMissionInfo::TASK_RUNNING:
        result_ss<<"TASK_RUNNING";
        break;
    default:
        result_ss<<"UNKNOWN";
        break;
    }

    return result_ss.str();
}

std::string DroneLoggerROSModule::droneGoTaskCallback(const droneMsgsROS::droneGoTask::ConstPtr &msg)
{
    std::stringstream result_ss;

    result_ss<< "submissionId:"<<msg->submissionId;
    result_ss<<" taskId:"<<msg->taskId;


    return result_ss.str();
}






//////// IMAGES
std::string DroneLoggerROSModule::droneFrontCameraCallback(const sensor_msgs::ImageConstPtr &msg)
{
    std::stringstream return_ss;
    std::stringstream image_ss;
    static int numImage=-1;

    numImage++;

    std::string pathToSave=DroneLoggerROSBasicModule::currentlog_path+"/frontImage/";
    image_ss  << "im_" << std::setfill('0') << std::setw(10) << numImage << ".png";
    return_ss << "image:" << image_ss.str();

    if (DroneLoggerROSModule::save_front_camera_images) {
        //Front image
        cv_bridge::CvImagePtr cvFrontImage;
        cv::Mat frontImage;

        try
        {
            cvFrontImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return return_ss.str();
        }

        frontImage=cvFrontImage->image;


        //Store in memory
        cv::imwrite( pathToSave+image_ss.str(), frontImage );
    }

    return return_ss.str();
}

std::string DroneLoggerROSModule::droneBottomCameraCallback(const sensor_msgs::ImageConstPtr &msg)
{
    std::stringstream return_ss;
    std::stringstream image_ss;
    static int numImage=-1;
    numImage++;

    std::string pathToSave=DroneLoggerROSBasicModule::currentlog_path+"/bottomImage/";
    image_ss  << "im_" << std::setfill('0') << std::setw(10) << numImage << ".png";
    return_ss << "image:" << image_ss.str();

    if (DroneLoggerROSModule::save_bottom_camera_images) {
        //Bottom image
        cv_bridge::CvImagePtr cvBottomImage;
        cv::Mat BottomImage;

        try
        {
            cvBottomImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return return_ss.str();
        }

        BottomImage=cvBottomImage->image;


        //Store in memory
        cv::imwrite( pathToSave+image_ss.str(), BottomImage );
    }

    return return_ss.str();
}

std::string DroneLoggerROSModule::droneRightCameraCallback(const sensor_msgs::ImageConstPtr &msg)
{
    std::stringstream return_ss;
    std::stringstream image_ss;
    static int numImage=-1;
    numImage++;

    std::string pathToSave=DroneLoggerROSBasicModule::currentlog_path+"/rightImage/";
    image_ss  << "im_" << std::setfill('0') << std::setw(10) << numImage << ".png";
    return_ss << "image:" << image_ss.str();

    if (DroneLoggerROSModule::save_right_camera_images) {
        //Right image
        cv_bridge::CvImagePtr cvRightImage;
        cv::Mat RightImage;

        try
        {
            cvRightImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return return_ss.str();
        }

        RightImage=cvRightImage->image;


        //Store in memory
        cv::imwrite( pathToSave+image_ss.str(), RightImage );
    }

    return return_ss.str();
}

std::string DroneLoggerROSModule::droneLeftCameraCallback(const sensor_msgs::ImageConstPtr &msg)
{
    std::stringstream return_ss;
    std::stringstream image_ss;
    static int numImage=-1;
    numImage++;

    std::string pathToSave=DroneLoggerROSBasicModule::currentlog_path+"/leftImage/";
    image_ss  << "im_" << std::setfill('0') << std::setw(10) << numImage << ".png";
    return_ss << "image:" << image_ss.str();

    if (DroneLoggerROSModule::save_left_camera_images) {
        //Left image
        cv_bridge::CvImagePtr cvLeftImage;
        cv::Mat LeftImage;

        try
        {
            cvLeftImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return return_ss.str();
        }

        LeftImage=cvLeftImage->image;


        //Store in memory
        cv::imwrite( pathToSave+image_ss.str(), LeftImage );
    }

    return return_ss.str();
}


std::string DroneLoggerROSModule::droneBackCameraCallback(const sensor_msgs::ImageConstPtr &msg)
{
    std::stringstream return_ss;
    std::stringstream image_ss;
    static int numImage=-1;
    numImage++;

    std::string pathToSave=DroneLoggerROSBasicModule::currentlog_path+"/backImage/";
    image_ss  << "im_" << std::setfill('0') << std::setw(10) << numImage << ".png";
    return_ss << "image:" << image_ss.str();

    if (DroneLoggerROSModule::save_back_camera_images) {
        //Back image
        cv_bridge::CvImagePtr cvBackImage;
        cv::Mat BackImage;

        try
        {
            cvBackImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return return_ss.str();
        }

        BackImage=cvBackImage->image;


        //Store in memory
        cv::imwrite( pathToSave+image_ss.str(), BackImage );
    }

    return return_ss.str();
}

bool DroneLoggerROSModule::read_configuration_files()
{
    try {
        XMLFileReader my_xml_reader(stackPath+"configs/drone"+ cvg_int_to_string(idDrone)+"/drone_logger_config.xml");
        DroneLoggerROSModule::save_front_camera_images  = (bool) my_xml_reader.readIntValue( "drone_logger_config:save_front_camera_images" );
        DroneLoggerROSModule::save_bottom_camera_images = (bool) my_xml_reader.readIntValue( "drone_logger_config:save_bottom_camera_images" );
        DroneLoggerROSModule::save_right_camera_images  = (bool) my_xml_reader.readIntValue( "drone_logger_config:save_right_camera_images" );
        DroneLoggerROSModule::save_left_camera_images = (bool) my_xml_reader.readIntValue( "drone_logger_config:save_left_camera_images" );
        DroneLoggerROSModule::save_back_camera_images  = (bool) my_xml_reader.readIntValue( "drone_logger_config:save_back_camera_images" );
    }
    catch ( cvg_XMLFileReader_exception &e)
    {
        throw cvg_XMLFileReader_exception(std::string("[cvg_XMLFileReader_exception! caller_function: ") + BOOST_CURRENT_FUNCTION + e.what() + "]\n");
        DroneLoggerROSModule::save_front_camera_images  = false;
        DroneLoggerROSModule::save_bottom_camera_images = false;
        DroneLoggerROSModule::save_right_camera_images  = false;
        DroneLoggerROSModule::save_left_camera_images = false;
        DroneLoggerROSModule::save_back_camera_images  = false;
    }

    return true;
}

bool DroneLoggerROSModule::run() {
    if (!configuration_files_are_read) {
        read_configuration_files();
        configuration_files_are_read = true;
    }

    if(!DroneLoggerROSBasicModule::run()) {
        return false;
    }

    return true;
}
