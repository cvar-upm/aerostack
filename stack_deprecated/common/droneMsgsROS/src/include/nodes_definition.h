#ifndef NODES_DEFINITION_H
#define NODES_DEFINITION_H



#include <string>




// ***** BEGIN: MODULE NAMES *****
const std::string MODULE_NAME_ODOMETRY_STATE_ESTIMATOR   = "droneOdometryStateEstimator";
const std::string MODULE_NAME_TRAJECTORY_CONTROLLER      = "droneTrajectoryController";
const std::string MODULE_NAME_CONTROLLER                 = "flight_motion_controller_process";
const std::string MODULE_NAME_IBVS_CONTROLLER            = "droneIBVSController";
const std::string MODUlE_NAME_OPENTLD_TRANSLATOR         = "open_tld_translator";
const std::string MODULE_NAME_TRACKER_EYE                = "trackerEye";
const std::string MODULE_NAME_HOGSVM                     = "hogsvm_sample";
const std::string MODULE_NAME_ARUCO_EYE                  = "droneArucoEyeROSModule";
const std::string MODULE_NAME_LOCALIZER                  = "droneLocalizer";
const std::string MODULE_NAME_OBSTACLE_PROCESSOR         = "droneObstacleProcessor";
const std::string MODULE_NAME_TRAJECTORY_PLANNER         = "droneTrajectoryPlanner";
const std::string MODULE_NAME_MISSION_PLANNER            = "droneMissionPlanner";
const std::string MODULE_NAME_MISSION_SCHEDULER          = "droneMissionScheduler";
const std::string MODULE_NAME_YAW_PLANNER	             = "droneYawPlanner";
const std::string MODULE_NAME_ARCHITECTURE_BRAIN         = "droneArchitectureBrain";
const std::string MODULE_NAME_DRONE_LOGGER               = "droneLogger";

const std::string MODULE_NAME_DRONE_CONSOLE_INTERFACE    = "droneInterface";

const std::string MODULE_NAME_DRIVER_PARROT_ALTITUDE        = "droneAltitude";
const std::string MODULE_NAME_DRIVER_PARROT_STATUS          = "droneStatusARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_BATTERY         = "droneBattery";
const std::string MODULE_NAME_DRIVER_PARROT_GROUND_SPEED    = "droneGroundSpeed";
const std::string MODULE_NAME_DRIVER_PARROT_IMU             = "imuARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_MAGNETOMETER    = "magnetometerARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_PRESSURE        = "pressureARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_ROTATION_ANGLES = "droneRotationAngles";
const std::string MODULE_NAME_DRIVER_PARROT_TEMPERATURE     = "temperatureARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_FRONT_CAMERA    = "frontCameraARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_BOTTOM_CAMERA   = "bottomCameraARDroneROSModule";
const std::string MODULE_NAME_DRIVER_PARROT_DRONE_COMMAND   = "droneCommand";

const std::string MODULE_NAME_DRIVER_PELICAN_ALTITUDE        = "droneAltitude";
const std::string MODULE_NAME_DRIVER_PELICAN_BATTERY         = "droneBattery";
const std::string MODULE_NAME_DRIVER_PELICAN_GROUND_SPEED    = "droneGroundSpeed";
const std::string MODULE_NAME_DRIVER_PELICAN_ROTATION_ANGLES = "droneRotationAngles";
const std::string MODULE_NAME_DRIVER_PELICAN_DRONE_COMMAND   = "droneCommand";
const std::string MODULE_NAME_DRONE_MIDLEVEL_AUTOPILOT       = "droneMidLevelAutopilot";

const std::string MODULE_NAME_UEYE_CAMERA  = "cvg_ueye_camid_pos";

const std::string MODULE_NAME_DRONE_SIMULATOR                    = "droneSimulator";
const std::string MODULE_NAME_DRONE_VISUAL_MARKERS_EYE_SIMULATOR = "droneArucoEyeROSModule";
const std::string MODULE_NAME_PELICAN_LIKE_SIMULATOR             = "dronePelicanLikeSimulator";

const std::string MODULE_NAME_DRONE_ARCHITECTURE_RVIZ_INTERFACE    = "droneArchitectureRvizInterface";

const std::string MODULE_NAME_DRONE_SPEECH_ROS_MODULE = "droneSpeechROSModule";
const std::string MODULE_NAME_DRONE_SOUND_ROS_MODULE = "droneSoundROSModule";

const std::string MODULE_NAME_OBSTACLE_DISTANCE_CALCULATION = "droneObstacleDistanceCalculator";

const std::string MODULE_NAME_DRONE_KEYPOINTS_GRID_DETECTOR  = "droneComputerVisionIARC14Keypoints_id";
const std::string MODULE_NAME_DRONE_GROUND_ROBOTS            = "droneComputerVisionIARC14GroundRobots_id";

const std::string MODULE_NAME_DRONE_SIMULATOR_GRID_DETECTOR  = "droneSimulatorGrid_id";
const std::string MODULE_NAME_DRONE_MULTICAMERAIROBOTTRACKER = "droneMulticameraIRobotTracker";

const std::string MODULE_NAME_DRONE_CV_GROUND_ROBOTS_2D_TO_3D  = "droneCVGroundRobots2DTo3D";
const std::string MODULE_NAME_DRONE_CV_KEYPOINTS_2D_TO_3D  = "droneCVKeypoints2DTo3D";

const std::string MODULE_NAME_ROBOT_LOCALIZATION = "droneRobotLocalizationROSModuleNode";
const std::string MODULE_NAME_NAVIGATION_STACK = "droneNavigationStackROSModuleNode";
const std::string MODULE_NAME_IBVS_CONTROLLER_FROM_TOP = "droneVSFollowingFromTop";
const std::string MODULE_NAME_RL_IBVS_CONTROLLER_FROM_TOP = "RlEnvironmentGazeboRos";
const std::string MODULE_NAME_AUTONOMOUS_LANDING = "droneLandingROSModule";

const std::string MODULE_NAME_VEHICLE_DYNAMICS = "droneVehicleDynamicsROSModule";
const std::string MODULE_NAME_PARAMETERS_VIEWER = "parametersViewerROSModule";
const std::string MODULE_NAME_EDIT_ENVIRONMENT = "editEnvironmentROSModule";
const std::string MODULE_NAME_ENVIRONMENT_VIEWER = "environmentViewerROSModule";
const std::string MODULE_NAME_EXECUTION_VIEWER = "executionViewerROSModule";


namespace ModuleNames {
    enum name { ODOMETRY_STATE_ESTIMATOR = 1,
                TRAJECTORY_CONTROLLER,
                ARUCO_EYE,
                LOCALIZER,
                OBSTACLE_PROCESSOR,
                TRAJECTORY_PLANNER,
                MISSION_PLANNER,
                YAW_PLANNER,
                ARCHITECTURE_BRAIN,
                MULTICAMERA_IROBOT_TRACKER,
                FLIGHT_MOTION_CONTROLLER
              };
}
// ***** END:   MODULE NAMES *****







#endif
