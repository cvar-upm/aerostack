#ifndef COMMUNICATION_DEFINITION_H
#define COMMUNICATION_DEFINITION_H

#include <string>

#define TEST_WITHOUT_AURCOSLAM
//#define TEST_WITH_AURCOSLAM


#include "nodes_definition.h"


///////////// driverParrotARDroneROSModule
const std::string DRONE_DRIVER_SENSOR_IMU               =  "imu";
const std::string DRONE_DRIVER_SENSOR_TEMPERATURE       =  "temperature";
const std::string DRONE_DRIVER_SENSOR_MAGNETOMETER      =  "magnetometer";
const std::string DRONE_DRIVER_SENSOR_BATTERY           =  "battery";
const std::string DRONE_DRIVER_SENSOR_ALTITUDE          =  "altitude";
const std::string DRONE_DRIVER_SENSOR_ROTATION_ANGLES   =  "rotation_angles";
const std::string DRONE_DRIVER_SENSOR_GROUND_SPEED      =  "ground_speed";
const std::string DRONE_DRIVER_SENSOR_PRESSURE          =  "pressure";
const std::string DRONE_DRIVER_SENSOR_STATUS            =  "status";
const std::string DRONE_DRIVER_SENSOR_BOTTOM_CAMERA =  "camera/bottom/image_raw";
const std::string DRONE_DRIVER_SENSOR_FRONT_CAMERA  =  "camera/front/image_raw";
const std::string DRONE_DRIVER_COMMAND_DRONE_COMMAND_PITCH_ROLL  = "command/pitch_roll";
const std::string DRONE_DRIVER_COMMAND_DRONE_COMMAND_DALTITUDE   = "command/dAltitude";
const std::string DRONE_DRIVER_COMMAND_DRONE_COMMAND_DYAW        = "command/dYaw";
const std::string DRONE_DRIVER_COMMAND_DRONE_HL_COMMAND          = "command/high_level";
const std::string DRONE_DRIVER_COMMAND_DRONE_LL_AUTOPILOT_COMMAND= "command/low_level";

///////////// droneSimulatorROSModule
const std::string DRONE_SIMULATOR_SENSOR_IMU               =  "imu";
const std::string DRONE_SIMULATOR_SENSOR_TEMPERATURE       =  "temperature";
const std::string DRONE_SIMULATOR_SENSOR_MAGNETOMETER      =  "magnetometer";
const std::string DRONE_SIMULATOR_SENSOR_BATTERY           =  "battery";
const std::string DRONE_SIMULATOR_SENSOR_ALTITUDE          =  "altitude";
const std::string DRONE_SIMULATOR_SENSOR_ROTATION_ANGLES   =  "rotation_angles";
const std::string DRONE_SIMULATOR_SENSOR_GROUND_SPEED      =  "ground_speed";
const std::string DRONE_SIMULATOR_SENSOR_PRESSURE          =  "pressure";
const std::string DRONE_SIMULATOR_SENSOR_STATUS            =  "status";
const std::string DRONE_SIMULATOR_COMMAND_DRONE_COMMAND_PITCH_ROLL = "command/pitch_roll";
const std::string DRONE_SIMULATOR_COMMAND_DRONE_COMMAND_DALTITUDE  = "command/dAltitude";
const std::string DRONE_SIMULATOR_COMMAND_DRONE_COMMAND_DYAW       = "command/dYaw";
const std::string DRONE_SIMULATOR_COMMAND_DRONE_HL_COMMAND         = "command/high_level";
const std::string DRONE_SIMULATOR_INTERNAL_POSE             = "simulator/dronePose";

///////////// PelicanLikeSimulatorROSModule
const std::string DRONE_PELICAN_LIKE_SIMULATOR_GROUND_SPEED_SENSOR_PUBLISHER = "px4flow/opt_flow";
const std::string DRONE_PELICAN_LIKE_SIMULATOR_LOW_LEVEL_STATUS_PUBLISHER    = "asctec/LL_STATUS";
const std::string DRONE_PELICAN_LIKE_SIMULATOR_IMU_CALCDATA_PUBLISHER        = "asctec/IMU_CALCDATA";
const std::string DRONE_PELICAN_LIKE_SIMULATOR_CONTROL_INPUT_SUBSCRIBER      = "asctec/CTRL_INPUT";
const std::string DRONE_PELICAN_LIKE_SIMULATOR_DRONEPOSE_PUBLISHER           = DRONE_SIMULATOR_INTERNAL_POSE;

///////////// OktoLikeSimulatorROSModule
const std::string DRONE_OKTO_LIKE_SIMULATOR_GROUND_SPEED_SENSOR_PUBLISHER = "px4flow/opt_flow";
const std::string DRONE_OKTO_LIKE_SIMULATOR_OKTO_SENSOR_DATA_PUBLISHER    = "okto_sensor_data";
const std::string DRONE_OKTO_LIKE_SIMULATOR_OKTO_COMMANDS_SUBSCRIBER      = "okto_commands";
const std::string DRONE_OKTO_LIKE_SIMULATOR_DRONEPOSE_PUBLISHER           = DRONE_SIMULATOR_INTERNAL_POSE;

/////////////// droneVisualMarksEyeSimulatorROSModule
const std::string DRONE_VISUAL_MARKS_EYE_SIMULATOR_INTERNAL_POSE         = "simulator/dronePose";
const std::string DRONE_VISUAL_MARKS_EYE_SIMULATOR_OBSERVATION_VEC_LIST = "arucoObservation";


// droneArucoEye -> Not used anymore
//const std::string DRONE_ARUCO_EYE_FRONT_IMAGE_RAW   =  "camera/front/image_raw";
//const std::string DRONE_ARUCO_EYE_OBSERVATIONVEC_LIST = "arucoObservation";


// droneLocalizer -> Not used anymore!
//const std::string DRONE_LOCALIZER_POSE_SUBSCRIPTION                    = "EstimatedPose_droneGMR_wrt_GFF";
//const std::string DRONE_LOCALIZER_ARUCO_OBSERVATIONVEC_LIST            = "arucoObservation";
//const std::string DRONE_LOCALIZER_POSE_PUBLICATION                     = "ArucoSlam_EstimatedPose";
//const std::string DRONE_LOCALIZER_SPEEDS_PUBLICATION                   = "ArucoSlam_EstimatedSpeeds";
//const std::string DRONE_LOCALIZER_POSE_PUBLICATION_2ND_YPR_CONVENTION  = "ArucoSlam_EstimatedPose_v2"; // Unused
//const std::string DRONE_LOCALIZER_LANDMARK_LIST                        = "ArucoSlam_LandarmkList";


// droneObstacleProcessor -> Not used anymore!
//const std::string DRONE_OBSTACLE_PROCESSOR_LANDMARK_LIST = "ArucoSlam_LandarmkList";
//const std::string DRONE_OBSTACLE_PROCESSOR_OBSTACLE_LIST = "obstacles";  // TODO_JL


// droneTrajectoryPlanner -> Not used anymore!
//const std::string DRONE_TRAJECTORY_PLANNER_TRAJ_REF_COM   =    "droneTrajectoryAbsRefCommand";
//const std::string DRONE_TRAJECTORY_PLANNER_MISSION_POINT_REF = "droneMissionPoint";
//const std::string DRONE_TRAJECTORY_PLANNER_OBSTACLE_LIST   =   "obstacles";
//const std::string DRONE_TRAJECTORY_PLANNER_SOCIETY_POSE   =    "societyPose";
//#ifdef TEST_WITHOUT_AURCOSLAM
//const std::string DRONE_TRAJECTORY_PLANNER_POSE_SUBSCRIPTION = "EstimatedPose_droneGMR_wrt_GFF";
//#endif // TEST_WITHOUT_AURCOSLAM
//#ifdef TEST_WITH_AURCOSLAM
//const std::string DRONE_TRAJECTORY_PLANNER_POSE_SUBSCRIPTION = "ArucoSlam_EstimatedPose";
//#endif // TEST_WITH_AURCOSLAM


// droneYawCommander -> Not used anymore!
//#ifdef TEST_WITHOUT_AURCOSLAM
//const std::string DRONE_YAW_PLANNER_POSE_SUBS		  =	"EstimatedPose_droneGMR_wrt_GFF";
//#endif // TEST_WITHOUT_AURCOSLAM
//#ifdef TEST_WITH_AURCOSLAM
//const std::string DRONE_YAW_PLANNER_POSE_SUBS		  =	"ArucoSlam_EstimatedPose";
//#endif // TEST_WITH_AURCOSLAM
//const std::string DRONE_YAW_PLANNER_POINT_TO_LOOK_SUB =	"dronePointToLook";
//const std::string DRONE_YAW_PLANNER_YAW_TO_LOOK_SUB	  =	"droneYawToLook";
//const std::string DRONE_YAW_PLANNER_YAW_REF_CMD_PUB   =	"droneControllerYawRefCommand";


// droneMissionPlanner -> Legacy
#ifdef TEST_WITHOUT_AURCOSLAM
const std::string DRONE_MISSION_PLANNER_POSE_SUBSCRIPTION =	"EstimatedPose_droneGMR_wrt_GFF";
#endif // TEST_WITHOUT_AURCOSLAM
#ifdef TEST_WITH_AURCOSLAM
const std::string DRONE_MISSION_PLANNER_POSE_SUBSCRIPTION =	"ArucoSlam_EstimatedPose";
#endif // TEST_WITH_AURCOSLAM
const std::string DRONE_MISSION_PLANNER_HL_COMMAND     =   "droneMissionHLCommand";
const std::string DRONE_MISSION_PLANNER_HL_COMMAND_ACK =	"droneMissionHLCommandAck";
const std::string DRONE_MISSION_PLANNER_MISSION_POINT_REF = "droneMissionPoint";
const std::string DRONE_MISSION_YAW_REF_CMD_SUBS       =    "droneControllerYawRefCommand";
const std::string DRONE_MISSION_PLANNER_POINT_TO_LOOK_PUB	=	"dronePointToLook";
const std::string DRONE_MISSION_PLANNER_YAW_TO_LOOK_PUB	=	"droneYawToLook";
const std::string DRONE_MISSION_INFO_PUB       =    	"droneMissionInfo";
const std::string DRONE_MISSION_GO_TASK_SUBS    =       	"droneGoTask";
const std::string DRONE_MISSION_PLANNER_MISSION_SPEED_REF = "droneMissionSpeed";
const std::string DRONE_MISSION_PLANNER_SPEEDS_SUBSCRIPTION = "ground_speed";

// droneStateEstimator -> Not used anymore!
//const std::string DRONE_STATE_ESTIMATOR_SENSOR_ALTITUDE          =  "altitude";
//const std::string DRONE_STATE_ESTIMATOR_SENSOR_ROTATION_ANGLES   =  "rotation_angles";
//const std::string DRONE_STATE_ESTIMATOR_SENSOR_GROUND_SPEED      =  "ground_speed";
//const std::string DRONE_STATE_ESTIMATOR_COMMAND_DRONE_COMMAND_PITCH_ROLL = "command/pitch_roll";
//const std::string DRONE_STATE_ESTIMATOR_COMMAND_DRONE_COMMAND_DALTITUDE  = "command/dAltitude";
//const std::string DRONE_STATE_ESTIMATOR_COMMAND_DRONE_COMMAND_DYAW       = "command/dYaw";
//const std::string DRONE_STATE_ESTIMATOR_POSE_PUBLICATION_LMrT    = "SOEstimatedPose";
//const std::string DRONE_STATE_ESTIMATOR_SPEEDS_PUBLICATION_LMrT  = "SOEstimatedSpeeds";
//const std::string DRONE_STATE_ESTIMATOR_POSE_PUBLICATION_GMR     = "EstimatedPose_droneGMR_wrt_GFF";
//const std::string DRONE_STATE_ESTIMATOR_SPEEDS_PUBLICATION_GMR   = "EstimatedSpeed_droneGMR_wrt_GFF";


// droneController -> Not used anymore!
//const std::string  DRONE_TRAJECTORY_CONTROLLER_DRONE_COMMAND_PITCH_ROLL      = "command/pitch_roll";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_DRONE_COMMAND_DALTITUDE       = "command/dAltitude";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_DRONE_COMMAND_DYAW            = "command/dYaw";
//#ifdef TEST_WITHOUT_AURCOSLAM
//const std::string  DRONE_TRAJECTORY_CONTROLLER_POSE_SUBSCRIPTION_GMR         = "EstimatedPose_droneGMR_wrt_GFF";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_SPEEDS_SUBSCRIPTION_GMR       = "EstimatedSpeed_droneGMR_wrt_GFF";
//#endif // TEST_WITHOUT_AURCOSLAM
//#ifdef TEST_WITH_AURCOSLAM
//const std::string  DRONE_TRAJECTORY_CONTROLLER_POSE_SUBSCRIPTION_GMR         = "ArucoSlam_EstimatedPose";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_SPEEDS_SUBSCRIPTION_GMR       = "ArucoSlam_EstimatedSpeeds";
//#endif // TEST_WITH_AURCOSLAM
//const std::string  DRONE_TRAJECTORY_CONTROLLER_TARGET_PBVS_ALTITUDE_SUBSCRIPTION_GMR     = "command_PBVS/Altitude";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_TARGET_GROUND_ROBOT_POSE_SUBSCRIPTION_GMR = "EstimatedPose_iRobotGMR_wrt_droneGMR";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_POSITION_REF_SUBSCRIPTION     = "dronePositionRefs";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_SPEED_REF_SUBSCRIPTION        = "droneSpeedsRefs";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_ABS_TRAJ_REF_CMD_SUBSCRIPTION = "droneTrajectoryAbsRefCommand";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_REL_TRAJ_REF_CMD_SUBSCRIPTION = "droneTrajectoryRefCommand";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_YAW_REF_CMD_SUBSCRIPTION      = "droneControllerYawRefCommand";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_POSITION_REF_REBROADCAST_PUBLICATION    = "trajectoryControllerPositionReferencesRebroadcast";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_SPEED_REF_REBROADCAST_PUBLICATION       = "trajectoryControllerSpeedReferencesRebroadcast";
//const std::string  DRONE_TRAJECTORY_CONTROLLER_TRAJECTORY_REF_REBROADCAST_PUBLICATION  = "trajectoryControllerTrajectoryReferencesRebroadcast";


// DroneInterfaceROSModule
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_IMU             = "imu";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_TEMPERATURE     = "temperature";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_MAGNETOMETER    = "magnetometer";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_BATTERY         = "battery";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_ALTITUDE        = "altitude";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_ROTATION_ANGLES = "rotation_angles";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_GROUND_SPEED    = "ground_speed";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_PRESSURE        = "pressure";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_STATUS          = "status";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_BOTTOM_CAMERA = "camera/bottom/image_raw";
const std::string DRONE_CONSOLE_INTERFACE_SENSOR_FRONT_CAMERA  = "camera/front/image_raw";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_PITCH_ROLL_PUBLICATION = "command/pitch_roll";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_DALTITUDE_PUBLICATION  = "command/dAltitude";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_DYAW_PUBLICATION       = "command/dYaw";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_HL_COMMAND_PUBLICATION         = "command/high_level";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_PITCH_ROLL_SUBSCRIPTION = "command/pitch_roll";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_DALTITUDE_SUBSCRIPTION  = "command/dAltitude";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_COMMAND_DYAW_SUBSCRIPTION       = "command/dYaw";
const std::string DRONE_CONSOLE_INTERFACE_COMMAND_DRONE_HL_COMMAND_SUBSCRIPTION         = "command/high_level";


// DroneModuleInterfaceROS
  // DroneEKFStateEstimatorInterface
const std::string DRONE_STATE_ESTIMATOR_INTERFACE_POSE_SUBSCRIPTION_LMrT   = "SOEstimatedPose";
const std::string DRONE_STATE_ESTIMATOR_INTERFACE_SPEEDS_SUBSCRIPTION_LMrT = "SOEstimatedSpeeds";
const std::string DRONE_STATE_ESTIMATOR_INTERFACE_POSE_SUBSCRIPTION_GMR    = "EstimatedPose_droneGMR_wrt_GFF";
const std::string DRONE_STATE_ESTIMATOR_INTERFACE_SPEEDS_SUBSCRIPTION_GMR  = "EstimatedSpeed_droneGMR_wrt_GFF";
  // DroneTrajectoryControllerInterface
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_POSITION_REF_PUBLICATION     = "dronePositionRefs";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_SPEED_REF_PUBLICATION        = "droneSpeedsRefs";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_ABS_TRAJ_REF_CMD_PUBLICATION = "droneTrajectoryAbsRefCommand";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_REL_TRAJ_REF_CMD_PUBLICATION = "droneTrajectoryRefCommand";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_YAW_REF_CMD_PUBLICATION      = "droneControllerYawRefCommand";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_POSITION_REF_REBROADCAST_SUBSCRIPTION    = "trajectoryControllerPositionReferencesRebroadcast";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_SPEED_REF_REBROADCAST_SUBSCRIPTION       = "trajectoryControllerSpeedReferencesRebroadcast";
const std::string DRONE_TRAJECTORY_CONTROLLER_INTERFACE_TRAJECTORY_REF_REBROADCAST_SUBSCRIPTION  = "trajectoryControllerTrajectoryReferencesRebroadcast";
  //
const std::string DRONE_LOCALIZER_INTERFACE_POSE_PUBLICATION   = "ArucoSlam_EstimatedPose";
const std::string DRONE_LOCALIZER_INTERFACE_SPEEDS_PUBLICATION = "ArucoSlam_EstimatedSpeeds";

// droneBrain -> Legacy
  // droneArchitectureBrain
const std::string DRONE_ARCHITECTURE_BRAIN_IS_IN_THE_SYSTEM  = "isInTheSystem";
const std::string DRONE_ARCHITECTURE_BRAIN_SOCIETY_BROADCAST = "/societyBroadcast";
const std::string DRONE_ARCHITECTURE_BRAIN_SOCIETY_POSE      = "societyPose";
  // BrainStateMachine
const std::string DRONE_BRAIN_PLANNER_HL_COMMAND     = "droneMissionHLCommand";
const std::string DRONE_BRAIN_PLANNER_HL_COMMAND_ACK = "droneMissionHLCommandAck";
const std::string DRONE_BRAIN_INFO_PUB               = "droneMissionInfo";
const std::string DRONE_BRAIN_GO_TASK_SUBS           = "droneGoTask";
const std::string DRONE_BRAIN_POSITION_REF_PUBLICATION = "dronePositionRefs";
const std::string DRONE_BRAIN_YAW_REF_PUBLICATION      = "droneControllerYawRefCommand";
  // ThisSwarmAgentInterface
const std::string DRONE_BRAIN_SENSOR_ROTATION_ANGLES =  "rotation_angles";
const std::string DRONE_BRAIN_SENSOR_ALTITUDE        =  "altitude";
const std::string DRONE_BRAIN_SENSOR_GROUND_SPEED    =  "ground_speed";
const std::string DRONE_BRAIN_SENSOR_BATTERY         =  "battery";
const std::string DRONE_BRAIN_SENSOR_STATUS          =  "status";
// ThisSwarmAgentInterface & OtherSwarmAgentListener
const std::string DRONE_ARCHITECTURE_BRAIN_IS_IN_THE_SYSTEM_SUBSCRIBER  = "isInTheSystem";
#ifdef TEST_WITHOUT_AURCOSLAM
const std::string DRONE_BRAIN_POSE_SUBSCRIBER  = "EstimatedPose_droneGMR_wrt_GFF";
#endif // TEST_WITHOUT_AURCOSLAM
#ifdef TEST_WITH_AURCOSLAM
const std::string DRONE_BRAIN_POSE_SUBSCRIBER  = "ArucoSlam_EstimatedPose";
#endif // TEST_WITH_AURCOSLAM


// droneGraphInterface -> Legacy
//const std::string  DRONE_GRAPH_INTERFACE_POSE_SUBS = "ArucoSlam_EstimatedPose";
//const std::string  DRONE_GRAPH_INTERFACE_TRAJECTORY_SUBS = "droneTrajectoryAbsRefCommand";
//const std::string  DRONE_GRAPH_INTERFACE_MISSION_POINT_SUBS = "droneMissionPoint";
//const std::string  DRONE_GRAPH_INTERFACE_SOCIETY_POSE_SUBS = "societyPose";
//const std::string  DRONE_GRAPH_INTERFACE_OBSTACLES_SUBS = "obstacles";


// droneLogger stuff
  // DroneLoggerROSPublisher
const int DRONE_LOGGER_EVENTSTRING_QUEUE_LENGTH =  50;
const std::string  DRONE_LOGGER_EVENTSTRING_PUBL       = "eventString";
const std::string  DRONE_LOGGER_EVENTSTRING_SUBS       = "eventString";
const std::string  DRONE_LOGGER_EVENTSTRING_SRV_CLIENT = "eventString_srv";
const std::string  DRONE_LOGGER_EVENTSTRING_SRV_SERVER = "eventString_srv";
  // DroneLoggerROSModule
    //droneController
const std::string DRONE_LOGGER_POSITION_REF_REBROADCAST_SUBSCRIPTION    = "trajectoryControllerPositionReferencesRebroadcast";
const std::string DRONE_LOGGER_SPEED_REF_REBROADCAST_SUBSCRIPTION       = "trajectoryControllerSpeedReferencesRebroadcast";
const std::string DRONE_LOGGER_TRAJECTORY_REF_REBROADCAST_SUBSCRIPTION  = "trajectoryControllerTrajectoryReferencesRebroadcast";
    //driverParrotARDrone
const std::string DRONE_LOGGER_SENSOR_BATTERY           =  "battery";
const std::string DRONE_LOGGER_SENSOR_ALTITUDE          =  "altitude";
const std::string DRONE_LOGGER_SENSOR_ROTATION_ANGLES   =  "rotation_angles";
const std::string DRONE_LOGGER_SENSOR_GROUND_SPEED      =  "ground_speed";
const std::string DRONE_LOGGER_SENSOR_STATUS            =  "status";
    //Asctec Autopilot/Pelican Low-Level Telemetry
const std::string DRONE_PELICAN_LOGGER_LLSTATUS_SUBSCRIBER    = "asctec/LL_STATUS";
const std::string DRONE_PELICAN_LOGGER_IMUCALCDATA_SUBSCRIBER = "asctec/IMU_CALCDATA";
const std::string DRONE_PELICAN_LOGGER_RCDATA_SUBSCRIBER      = "asctec/RC_DATA";
const std::string DRONE_PELICAN_LOGGER_CTRLINPUT_SUBSCRIBER   = "asctec/CTRL_INPUT";
const std::string DRONE_LOGGER_COMMAND_DRONE_COMMAND_PITCH_ROLL = "command/pitch_roll";
const std::string DRONE_LOGGER_COMMAND_DRONE_COMMAND_DALTITUDE  = "command/dAltitude";
const std::string DRONE_LOGGER_COMMAND_DRONE_COMMAND_DYAW       = "command/dYaw";
const std::string DRONE_LOGGER_COMMAND_DRONE_HL_COMMAND         = "command/high_level";
const std::string DRONE_LOGGER_SENSOR_FRONT_CAMERA      =  "camera/front/image_raw";
const std::string DRONE_LOGGER_SENSOR_BOTTOM_CAMERA     =  "camera/bottom/image_raw";
    //droneStateEstimator
const std::string DRONE_LOGGER_POSE_SUBSCRIPTION_LMrT   = "SOEstimatedPose";
const std::string DRONE_LOGGER_SPEEDS_SUBSCRIPTION_LMrT = "SOEstimatedSpeeds";
const std::string DRONE_LOGGER_POSE_SUBSCRIPTION_GMR    = "EstimatedPose_droneGMR_wrt_GFF";
const std::string DRONE_LOGGER_SPEEDS_SUBSCRIPTION_GMR  = "EstimatedSpeed_droneGMR_wrt_GFF";
    //droneLocalizer
const std::string DRONE_LOGGER_LOCALIZER_POSE_SUBSCRIPTION_GMR    = "ArucoSlam_EstimatedPose";
const std::string DRONE_LOGGER_LOCALIZER_SPEEDS_SUBSCRIPTION_GMR  = "ArucoSlam_EstimatedSpeeds";
const std::string DRONE_LOGGER_LOCALIZER_LANDMARK_LIST =  "ArucoSlam_LandarmkList";
    //droneTrajectoryPlanner
const std::string DRONE_LOGGER_TRAJECTORY_COMMAND = "droneTrajectoryAbsRefCommand";
    //droneArucoEye
const std::string DRONE_LOGGER_ARUCO_EYE_OBSERVATIONVEC_LIST = "arucoObservation";
    //droneMissionPlanner
const std::string DRONE_LOGGER_MISSION_POINT_SUBS = "droneMissionPoint";
const std::string DRONE_LOGGER_POINT_TO_LOOK_PUB	=	"dronePointToLook";
const std::string DRONE_LOGGER_YAW_TO_LOOK_PUB	=	"droneYawToLook";
const std::string DRONE_LOGGER_MISSION_INFO_PUB       =    	"droneMissionInfo";
const std::string DRONE_LOGGER_MISSION_HL_COMMAND     =   "droneMissionHLCommand";
    //droneBrain
const std::string DRONE_LOGGER_SOCIETY_POSE_SUBS = "societyPose";
const std::string DRONE_BRAIN_MISSION_HL_COMMAND_ACK =	"droneMissionHLCommandAck";
    //droneObstacleProcessor
const std::string DRONE_LOGGER_OBSTACLES_SUBS = "obstacles";
    //droneYawCommander
const std::string DRONE_LOGGER_YAW_REF_CMD   =	"droneControllerYawRefCommand";
    //Cameras
const std::string DRONE_LOGGER_SENSOR_RIGHT_CAMERA    =  "camera/right/image_raw";
const std::string DRONE_LOGGER_SENSOR_LEFT_CAMERA     =  "camera/left/image_raw";
const std::string DRONE_LOGGER_SENSOR_BACK_CAMERA     =  "camera/back/image_raw";


// DroneArchitectureRvizInterfaceROSModule
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_SOCIETY_BROADCAST_SUBSCRIPTION = "/societyBroadcast";
    // SwarmAgentInterface
#ifdef TEST_WITHOUT_AURCOSLAM
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_POSE_SUBSCRIPTION = "EstimatedPose_droneGMR_wrt_GFF";
#endif // TEST_WITHOUT_AURCOSLAM
#ifdef TEST_WITH_AURCOSLAM
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_POSE_SUBSCRIPTION = "ArucoSlam_EstimatedPose";
#endif // TEST_WITH_AURCOSLAM
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_MISSION_POINT_SUBSCRIPTION = "droneMissionPoint";
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_TRAJECTORY_ABS_REF_CMD_SUBSCRIPTION = "trajectoryControllerTrajectoryReferencesRebroadcast"; //"droneTrajectoryAbsRefCommand";
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_OBSTACLE_LIST_SUBSCRIPTION = "obstacles";
const std::string DRONE_ARCHITECTURE_RVIZ_INTERFACE_SOCIETY_POSE_SUBSCRIPTION = "societyPose";


// IARC14, other stuff                               perception/back/gridIntersections
const std::string GRID_INTERSECTIONS_TOPIC_BACK   = "perception/back/gridIntersections";
const std::string GRID_INTERSECTIONS_TOPIC_BOTTOM = "perception/bottom/gridIntersections";
const std::string GRID_INTERSECTIONS_TOPIC_LEFT   = "perception/left/gridIntersections";
const std::string GRID_INTERSECTIONS_TOPIC_FRONT  = "perception/front/gridIntersections";
const std::string GRID_INTERSECTIONS_TOPIC_RIGHT  = "perception/right/gridIntersections";
const std::string MULTICAMERA_IROBOT_TRACKER_FEEDBACK = "perception/multirobot_tracker/iRobot";





#endif // COMMUNICATION_DEFINITION_H

