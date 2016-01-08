#!/bin/bash
echo "Configuring stack submodules .."


CONFIG_SUBMODULES_FILE=$1


#Reading configuration of which submodules include
. $CONFIG_SUBMODULES_FILE



#Adquire bitbucket info
echo "Acquiring bitbucket user info"
echo -n " -Bitbucket username: "
read bitbucketUsername

echo -n " -Bitbucket password: "
read -s bitbucketPassword
echo ""



#Loop for git submodule init
echo "Adding submodules"


#configs
MODULE_PATH=configs
REPO_URL=https://bitbucket.org/joselusl/quadrotor_stack_configs
REPO_BRANCH=master
./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
echo " -Added package in: $MODULE_PATH"

#mav_tools
if [[ ${mav_tools}  && $mav_tools = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverAsctecPelican/mav_tools
		REPO_URL=https://bitbucket.org/joselusl/mav_tools.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#asctec_drivers
if [[ ${asctec_drivers}  && $asctec_drivers = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverAsctecPelican/asctec_drivers
		REPO_URL=https://bitbucket.org/joselusl/asctec_drivers.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driverPelicanROSModule
if [[ ${driverPelicanROSModule}  && $driverPelicanROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverAsctecPelican/driverPelicanROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/driverpelicanrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#okto_driver
if [[ ${okto_driver}  && $okto_driver = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverMikrokopterOkto/okto_driver
		REPO_URL=https://bitbucket.org/Vision4UAV/okto_driver.git
		REPO_BRANCH=catkin
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driverOktoROSModule
if [[ ${driverOktoROSModule}  && $driverOktoROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverMikrokopterOkto/driverOktoROSModule
		REPO_URL=https://bitbucket.org/joselusl/driveroktorosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#mikrokopter_driver
if [[ ${mikrokopter_driver}  && $mikrokopter_driver = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverMikrokopterOkto/mikrokopter_driver
		REPO_URL=https://bitbucket.org/hridaybavle/mikrokopter_driver.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#mikrokopter_driver_ros_module
if [[ ${mikrokopter_driver_ros_module}  && $mikrokopter_driver_ros_module = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverMikrokopterOkto/mikrokopter_driver_ros_module
		REPO_URL=https://bitbucket.org/hridaybavle/mikrokopter_driver_ros_module.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#ardrone_autonomy
if [[ ${ardrone_autonomy}  && $ardrone_autonomy = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverParrotARDrone/ardrone_autonomy
		REPO_URL=https://github.com/AutonomyLab/ardrone_autonomy.git
		REPO_BRANCH=indigo-devel
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driverParrotARDroneROSModule
if [[ ${driverParrotARDroneROSModule}  && $driverParrotARDroneROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverParrotARDrone/driverParrotARDroneROSModule
		REPO_URL=https://bitbucket.org/joselusl/driverparrotardronerosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#mavros
if [[ ${mavros}  && $mavros = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverPixhawk/mavros
		REPO_URL=https://github.com/mavlink/mavros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driverPixhawkROSModule
if [[ ${driverPixhawkROSModule}  && $driverPixhawkROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversPlatforms/driverPixhawk/driverPixhawkROSModule
		REPO_URL=https://bitbucket.org/hridaybavle/driverpixhawkrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driver_camera_ueye
if [[ ${driver_camera_ueye}  && $driver_camera_ueye = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye
		REPO_URL=https://bitbucket.org/jespestana/driver_camera_ueye.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#driver_camera_ueye_ROSModule
if [[ ${driver_camera_ueye_ROSModule}  && $driver_camera_ueye_ROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_camera_ueye/driver_camera_ueye_ROSModule
		REPO_URL=https://bitbucket.org/jespestana/driver_camera_ueye_rosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"

fi

#px-ros-pkg
if [[ ${px_ros_pkg}  && $px_ros_pkg = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_px4flow/px-ros-pkg
		REPO_URL=https://github.com/cvg/px-ros-pkg.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driver_px4flow_interface_ROSModule
if [[ ${driver_px4flow_interface_ROSModule}  && $driver_px4flow_interface_ROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_px4flow/driver_px4flow_interface_ROSModule
		REPO_URL=https://bitbucket.org/jespestana/driver_px4flow_interface_rosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#driverLidarliteInterfaceROSModule
if [[ ${driverLidarliteInterfaceROSModule}  && $driverLidarliteInterfaceROSModule = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driverLidarlite/driverLidarliteInterfaceROSModule
		REPO_URL=https://bitbucket.org/hridaybavle/driverlidarliteinterfacerosmodule
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#rosserial driver
if [[ ${rosserial}  && $rosserial = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/utils/rosserial
		REPO_URL=https://github.com/ros-drivers/rosserial.git
		REPO_BRANCH=indigo-devel
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneObstacleProcessorVisualMarks
if [[ ${droneObstacleProcessorVisualMarks}  && $droneObstacleProcessorVisualMarks = true ]]
	then
		MODULE_PATH=stack/droneEnvironmentUnderstanding/droneObstacleProcessorVisualMarks/droneObstacleProcessorVisualMarks
		REPO_URL=https://bitbucket.org/joselusl/droneobstacleprocessorvisualmarks.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneObstacleProcessorVisualMarksROSModule
if [[ ${droneObstacleProcessorVisualMarksROSModule}  && $droneObstacleProcessorVisualMarksROSModule = true ]]
	then
		MODULE_PATH=stack/droneEnvironmentUnderstanding/droneObstacleProcessorVisualMarks/droneObstacleProcessorVisualMarksROSModule
		REPO_URL=https://bitbucket.org/joselusl/droneobstacleprocessorvisualmarksrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#robotLocalizationROSModule
if [[ ${robotLocalizationROSModule}  && $robotLocalizationROSModule = true ]]
	then
		MODULE_PATH=stack/droneEnvironmentUnderstanding/robotLocalizationROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/robotlocalizationrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneIBVSController
if [[ ${droneIBVSController}  && $droneIBVSController = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneIBVSControl/droneIBVSController
		REPO_URL=https://bitbucket.org/hridaybavle/droneibvscontroller.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneIBVSControllerROSModule
if [[ ${droneIBVSControllerROSModule}  && $droneIBVSControllerROSModule = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneIBVSControl/droneIBVSControllerROSModule
		REPO_URL=https://bitbucket.org/hridaybavle/droneibvscontrollerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrackerEyeROSModule
if [[ ${droneTrackerEyeROSModule}  && $droneTrackerEyeROSModule = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneIBVSControl/droneTrackerEyeROSModule
		REPO_URL=https://bitbucket.org/hridaybavle/dronetrackereyerosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#dronePBVSPositionMidLevelController
if [[ ${dronePBVSPositionMidLevelController}  && $dronePBVSPositionMidLevelController = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/dronePBVSPositionMidLevelController
		REPO_URL=https://bitbucket.org/jespestana/dronepbvspositionmidlevelcontroller.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSpeedPositionMidLevelController
if [[ ${droneSpeedPositionMidLevelController}  && $droneSpeedPositionMidLevelController = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneSpeedPositionMidLevelController
		REPO_URL=https://bitbucket.org/jespestana/dronespeedpositionmidlevelcontroller.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrajectoryController
if [[ ${droneTrajectoryController}  && $droneTrajectoryController = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneTrajectoryController
		REPO_URL=https://bitbucket.org/jespestana/dronetrajectorycontroller.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrajectoryControllerROSModule
if [[ ${droneTrajectoryControllerROSModule}  && $droneTrajectoryControllerROSModule = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneTrajectoryControllerROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronetrajectorycontrollerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrajectoryStateMachine
if [[ ${droneTrajectoryStateMachine}  && $droneTrajectoryStateMachine = true ]]
	then
		MODULE_PATH=stack/droneHighLevelControl/droneTrajectoryStateMachine
		REPO_URL=https://bitbucket.org/jespestana/dronetrajectorystatemachine.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneLoggerROSModule
if [[ ${droneLoggerROSModule}  && $droneLoggerROSModule = true ]]
	then
		MODULE_PATH=stack/droneLogging/droneLoggerROSModule
		REPO_URL=https://bitbucket.org/jespestana/droneloggerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#dronePelicanLoggerROSModule
if [[ ${dronePelicanLoggerROSModule}  && $dronePelicanLoggerROSModule = true ]]
	then
		MODULE_PATH=stack/droneLogging/dronePelicanLoggerROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronepelicanloggerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_cvglogger
if [[ ${lib_cvglogger}  && $lib_cvglogger = true ]]
	then
		MODULE_PATH=stack/droneLogging/lib_cvglogger
		REPO_URL=https://bitbucket.org/jespestana/lib_cvglogger.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_cvgloggerROS
if [[ ${lib_cvgloggerROS}  && $lib_cvgloggerROS = true ]]
	then
		MODULE_PATH=stack/droneLogging/lib_cvgloggerROS
		REPO_URL=https://bitbucket.org/jespestana/lib_cvgloggerros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMidLevelAutopilot
if [[ ${droneMidLevelAutopilot}  && $droneMidLevelAutopilot = true ]]
	then
		MODULE_PATH=stack/droneMidLevelControl/droneMidLevelAutopilot
		REPO_URL=https://bitbucket.org/jespestana/dronemidlevelautopilot.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMidLevelAutopilotROSModule
if [[ ${droneMidLevelAutopilotROSModule}  && $droneMidLevelAutopilotROSModule = true ]]
	then
		MODULE_PATH=stack/droneMidLevelControl/droneMidLevelAutopilotROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronemidlevelautopilotrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneIARC14MissionSchedulerROSModule
if [[ ${droneIARC14MissionSchedulerROSModule}  && $droneIARC14MissionSchedulerROSModule = true ]]
	then
		MODULE_PATH=stack/droneMissionPlanning/droneIARC14MissionSchedulerROSModule
		REPO_URL=https://bitbucket.org/jespestana/droneiarc14missionschedulerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMissionPlanner
if [[ ${droneMissionPlanner}  && $droneMissionPlanner = true ]]
	then
		MODULE_PATH=stack/droneMissionPlanning/droneMissionPlanner
		REPO_URL=https://bitbucket.org/joselusl/dronemissionplanner.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMissionPlannerROSModule
if [[ ${droneMissionPlannerROSModule}  && $droneMissionPlannerROSModule = true ]]
	then
		MODULE_PATH=stack/droneMissionPlanning/droneMissionPlannerROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronemissionplannerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMissionScheduleProcessor
if [[ ${droneMissionScheduleProcessor}  && $droneMissionScheduleProcessor = true ]]
	then
		MODULE_PATH=stack/droneMissionPlanning/droneMissionScheduleProcessor
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/dronemissionscheduleprocessor.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMissionScheduleProcessorROSModule
if [[ ${droneMissionScheduleProcessorROSModule}  && $droneMissionScheduleProcessorROSModule = true ]]
	then
		MODULE_PATH=stack/droneMissionPlanning/droneMissionScheduleProcessorROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/dronemissionscheduleprocessorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneOpenTLDTranslatorROS
if [[ ${droneOpenTLDTranslatorROS}  && $droneOpenTLDTranslatorROS = true ]]
	then
		MODULE_PATH=stack/dronePerception/openTLD/droneOpenTLDTranslatorROS
		REPO_URL=https://bitbucket.org/hridaybavle/droneopentldtranslatorros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#ros_opentld
if [[ ${ros_opentld}  && $ros_opentld = true ]]
	then
		MODULE_PATH=stack/dronePerception/openTLD/ros_opentld
		REPO_URL=https://github.com/Ronan0912/ros_opentld.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#arucoEye
if [[ ${arucoEye}  && $arucoEye = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneArucoEye/arucoEye
		REPO_URL=https://bitbucket.org/joselusl/arucoeye.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneArucoEye
if [[ ${droneArucoEye}  && $droneArucoEye = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneArucoEye/droneArucoEye
		REPO_URL=https://bitbucket.org/joselusl/dronearucoeye.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneArucoEyeROSModule
if [[ ${droneArucoEyeROSModule}  && $droneArucoEyeROSModule = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneArucoEye/droneArucoEyeROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronearucoeyerosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_aruco
if [[ ${lib_aruco}  && $lib_aruco = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneArucoEye/lib_aruco
		REPO_URL=https://bitbucket.org/joselusl/lib_aruco.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneComputerVisionIARC14
if [[ ${droneComputerVisionIARC14}  && $droneComputerVisionIARC14 = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneComputerVisionIARC14/droneComputerVisionIARC14
		REPO_URL=https://bitbucket.org/Vision4UAV/dronecomputervisioniarc14.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneComputerVisionIARC14ROSModule
if [[ ${droneComputerVisionIARC14ROSModule}  && $droneComputerVisionIARC14ROSModule = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneComputerVisionIARC14/droneComputerVisionIARC14ROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronecomputervisioniarc14rosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneCV2DTo3DROSModule
if [[ ${droneCV2DTo3DROSModule}  && $droneCV2DTo3DROSModule = true ]]
	then
		MODULE_PATH=stack/dronePerception/droneCV2DTo3DROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronecv2dto3drosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneEKFStateEstimator
if [[ ${droneEKFStateEstimator}  && $droneEKFStateEstimator = true ]]
	then
		MODULE_PATH=stack/droneSelfLocalization/droneOdometryPoseEstimator/droneEKFStateEstimator
		REPO_URL=https://bitbucket.org/jespestana/droneekfstateestimator.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneEKFStateEstimatorROSModule
if [[ ${droneEKFStateEstimatorROSModule}  && $droneEKFStateEstimatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSelfLocalization/droneOdometryPoseEstimator/droneEKFStateEstimatorROSModule
		REPO_URL=https://bitbucket.org/jespestana/droneekfstateestimatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneVisualMarkersLocalizer
if [[ ${droneVisualMarkersLocalizer}  && $droneVisualMarkersLocalizer = true ]]
	then
		MODULE_PATH=stack/droneSelfLocalization/droneVisualMarkersLocalizer/droneVisualMarkersLocalizer
		REPO_URL=https://bitbucket.org/joselusl/dronevisualmarkerslocalizer.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneVisualMarkersLocalizerROSModule
if [[ ${droneVisualMarkersLocalizerROSModule}  && $droneVisualMarkersLocalizerROSModule = true ]]
	then
		MODULE_PATH=stack/droneSelfLocalization/droneVisualMarkersLocalizer/droneVisualMarkersLocalizerROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronevisualmarkerslocalizerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#referenceFramesROS
if [[ ${referenceFramesROS}  && $referenceFramesROS = true ]]
	then
		MODULE_PATH=stack/droneSelfLocalization/droneVisualMarkersLocalizer/referenceFramesROS
		REPO_URL=https://bitbucket.org/joselusl/referenceframesros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneOktoSimulatorROSModule
if [[ ${droneOktoSimulatorROSModule}  && $droneOktoSimulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneSimulator/droneOktoSimulatorROSModule
		REPO_URL=https://bitbucket.org/jespestana/droneoktosimulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#dronePelicanSimulatorROSModule
if [[ ${dronePelicanSimulatorROSModule}  && $dronePelicanSimulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneSimulator/dronePelicanSimulatorROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronepelicansimulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSimulator
if [[ ${droneSimulator}  && $droneSimulator = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneSimulator/droneSimulator
		REPO_URL=https://bitbucket.org/jespestana/droneSimulator.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSimulatorROSModule
if [[ ${droneSimulatorROSModule}  && $droneSimulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneSimulator/droneSimulatorROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronesimulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMissionPlannerEmulatorROSModule
if [[ ${droneMissionPlannerEmulatorROSModule}  && $droneMissionPlannerEmulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneMissionPlanning/droneMissionPlannerEmulatorROSModule
		REPO_URL=https://bitbucket.org/csampedro/dronemissionplanneremulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneVisualMarkersEyeSimulator
if [[ ${droneVisualMarkersEyeSimulator}  && $droneVisualMarkersEyeSimulator = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneVisualMarkersEyeSimulator/droneVisualMarkersEyeSimulator
		REPO_URL=https://bitbucket.org/joselusl/dronevisualmarkerseyesimulator.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneVisualMarkersEyeSimulatorROSModule
if [[ ${droneVisualMarkersEyeSimulatorROSModule}  && $droneVisualMarkersEyeSimulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/droneVisualMarkersEyeSimulator/droneVisualMarkersEyeSimulatorROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronevisualmarkerseyesimulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSimulatorGridROSModule
if [[ ${droneSimulatorGridROSModule}  && $droneSimulatorGridROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/simulatorsIARC14/droneSimulatorGridROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronesimulatorgridrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSimulatoriRobotCVROSModule
if [[ ${droneSimulatoriRobotCVROSModule}  && $droneSimulatoriRobotCVROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/simulatorsIARC14/droneSimulatoriRobotCVROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronesimulatorirobotcvrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#robotSimulatorROSModule
if [[ ${robotSimulatorROSModule}  && $robotSimulatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSimulators/simulatorsIARC14/robotSimulatorROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/robotsimulatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneModuleInterfaceROS
if [[ ${droneModuleInterfaceROS}  && $droneModuleInterfaceROS = true ]]
	then
		MODULE_PATH=stack/droneStackBasics/droneModuleInterfaceROS
		REPO_URL=https://bitbucket.org/jespestana/dronemoduleinterfaceros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneModuleROS
if [[ ${droneModuleROS}  && $droneModuleROS = true ]]
	then
		MODULE_PATH=stack/droneStackBasics/droneModuleROS
		REPO_URL=https://bitbucket.org/joselusl/dronemoduleros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneMsgsROS
if [[ ${droneMsgsROS}  && $droneMsgsROS = true ]]
	then
		MODULE_PATH=stack/droneStackBasics/droneMsgsROS
		REPO_URL=https://bitbucket.org/joselusl/dronemsgsros.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneBrainROSModule
if [[ ${droneBrainROSModule}  && $droneBrainROSModule = true ]]
	then
		MODULE_PATH=stack/droneSupervising/droneBrainROSModule
		REPO_URL=https://bitbucket.org/jespestana/dronebrainrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneIARC14BrainROSModule
if [[ ${droneIARC14BrainROSModule}  && $droneIARC14BrainROSModule = true ]]
	then
		MODULE_PATH=stack/droneSupervising/droneIARC14BrainROSModule
		REPO_URL=https://bitbucket.org/jespestana/droneiarc14brainrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneManagerOfActions
if [[ ${droneManagerOfActions}  && $droneManagerOfActions = true ]]
	then
		MODULE_PATH=stack/droneActionsManaging/droneManagerOfActions
		REPO_URL=https://bitbucket.org/csampedro/dronemanagerofactions.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneManagerOfActionsROSModule
if [[ ${droneManagerOfActionsROSModule}  && $droneManagerOfActionsROSModule = true ]]
	then
		MODULE_PATH=stack/droneActionsManaging/droneManagerOfActionsROSModule
		REPO_URL=https://bitbucket.org/csampedro/dronemanagerofactionsrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSupervisorROSModule
if [[ ${droneSupervisorROSModule}  && $droneSupervisorROSModule = true ]]
	then
		MODULE_PATH=stack/droneSupervising/droneBasicSupervisor/droneSupervisorROSModule
		REPO_URL=https://bitbucket.org/csampedro/dronesupervisorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSupervisorROSModule_v2
if [[ ${droneSupervisorROSModule_v2}  && $droneSupervisorROSModule_v2 = true ]]
	then
		MODULE_PATH=stack/droneSupervising/droneBasicSupervisor/droneSupervisorROSModule_v2
		REPO_URL=https://bitbucket.org/csampedro/dronesupervisorrosmodule_v2.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrajectoryPlanner
if [[ ${droneTrajectoryPlanner}  && $droneTrajectoryPlanner = true ]]
	then
		MODULE_PATH=stack/droneTrajectoryPlanning/droneTrajectoryPlanner
		REPO_URL=https://bitbucket.org/joselusl/dronetrajectoryplanner.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneTrajectoryPlannerROSModule
if [[ ${droneTrajectoryPlannerROSModule}  && $droneTrajectoryPlannerROSModule = true ]]
	then
		MODULE_PATH=stack/droneTrajectoryPlanning/droneTrajectoryPlannerROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronetrajectoryplannerrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneYawCommanderROSModule
if [[ ${droneYawCommanderROSModule}  && $droneYawCommanderROSModule = true ]]
	then
		MODULE_PATH=stack/droneYawCommanding/droneYawCommanderROSModule
		REPO_URL=https://bitbucket.org/joselusl/droneyawcommanderrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneArchitectureRvizInterfaceROSModule
if [[ ${droneArchitectureRvizInterfaceROSModule}  && $droneArchitectureRvizInterfaceROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneArchitectureRvizInterfaceROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/dronearchitecturervizinterfacerosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneEkfSimulatorRvizROSModule
if [[ ${droneEkfSimulatorRvizROSModule}  && $droneEkfSimulatorRvizROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneEkfSimulatorRvizROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/droneekfsimulatorrvizrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneInterfaceROSModule
if [[ ${droneInterfaceROSModule}  && $droneInterfaceROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneInterfaceROSModule
		REPO_URL=https://bitbucket.org/joselusl/droneinterfacerosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSimulatorRvizROSModule
if [[ ${droneSimulatorRvizROSModule}  && $droneSimulatorRvizROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneSimulatorRvizROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/dronesimulatorrvizrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#robotSimulatorRvizROSModule
if [[ ${robotSimulatorRvizROSModule}  && $robotSimulatorRvizROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/IARC14/robotSimulatorRvizROSModule
		REPO_URL=https://bitbucket.org/ramon_suarez_fernandez/robotsimulatorrvizrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH $bitbucketUsername $bitbucketPassword > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_cvgekf
if [[ ${lib_cvgekf}  && $lib_cvgekf = true ]]
	then
		MODULE_PATH=stack/libraries/lib_cvgekf
		REPO_URL=https://bitbucket.org/joselusl/lib_cvgekf.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_cvgthread
if [[ ${lib_cvgthread}  && $lib_cvgthread = true ]]
	then
		MODULE_PATH=stack/libraries/lib_cvgthread
		REPO_URL=https://bitbucket.org/jespestana/lib_cvgthread.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_cvgutils
if [[ ${lib_cvgutils}  && $lib_cvgutils = true ]]
	then
		MODULE_PATH=stack/libraries/lib_cvgutils
		REPO_URL=https://bitbucket.org/jespestana/lib_cvgutils.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_newmat11
if [[ ${lib_newmat11}  && $lib_newmat11 = true ]]
	then
		MODULE_PATH=stack/libraries/lib_newmat11
		REPO_URL=https://bitbucket.org/joselusl/lib_newmat11.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_pose
if [[ ${lib_pose}  && $lib_pose = true ]]
	then
		MODULE_PATH=stack/libraries/lib_pose
		REPO_URL=https://bitbucket.org/joselusl/lib_pose.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_pugixml
if [[ ${lib_pugixml}  && $lib_pugixml = true ]]
	then
		MODULE_PATH=stack/libraries/lib_pugixml
		REPO_URL=https://bitbucket.org/joselusl/lib_pugixml.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#referenceFrames
if [[ ${referenceFrames}  && $referenceFrames = true ]]
	then
		MODULE_PATH=stack/libraries/referenceFrames
		REPO_URL=https://bitbucket.org/joselusl/referenceframes.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#videoPublisherROSModule
if [[ ${videoPublisherROSModule}  && $videoPublisherROSModule = true ]]
	then
		MODULE_PATH=stack/utils/videoPublisherROSModule
		REPO_URL=https://bitbucket.org/joselusl/videopublisherrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#mavlink
if [[ ${mavlink}  && $mavlink = true ]]
	then
		MODULE_PATH=stack/libraries/mavlink
		REPO_URL=https://github.com/mavlink/mavlink-gbp-release
		REPO_BRANCH=release/indigo/mavlink
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneCommunicationManagerROSModule
if [[ ${droneCommunicationManagerROSModule}  && $droneCommunicationManagerROSModule = true ]]
	then
		MODULE_PATH=stack/droneCommunication/droneCommunicationManagerROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronecommunicationmanagerrosmodule
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#droneLeapMotionDroneControlUserInterfaceROSModule
if [[ ${droneLeapMotionDroneControlUserInterfaceROSModule}  && $droneLeapMotionDroneControlUserInterfaceROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneLeapMotionDroneControlUserInterfaceROSModule
		REPO_URL=https://bitbucket.org/joselusl/droneleapmotiondronecontroluserinterfacerosmodule
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#leap_motion
if [[ ${leap_motion}  && $leap_motion = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_leapmotion/leap_motion
		REPO_URL=https://github.com/ros-drivers/leap_motion
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSpeechROSModule
if [[ ${droneSpeechROSModule}  && $droneSpeechROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneSpeechROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronespeechrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi


#audio_common
if [[ ${audio_common}  && $audio_common = true ]]
	then
		MODULE_PATH=stack/utils/audio_common
		REPO_URL=https://github.com/ros-drivers/audio_common
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#ueye_cam
if [[ ${ueye_cam}  && $ueye_cam = true ]]
	then
		MODULE_PATH=stack/droneDrivers/driversSensors/driver_camera_ueye/ueye_cam
		REPO_URL=https://github.com/anqixu/ueye_cam
		REPO_BRANCH=master
		./installation/gitSubmoduleAddPublRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#supervision_system
if [[ ${supervision_system}  && $supervision_system = true ]]
	then
		MODULE_PATH=stack/supervision_system
		REPO_URL=https://bitbucket.org/Ortinson/supervision_system.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#lib_levmar-2.6
if [[ ${lib_levmar_2_6}  && $lib_levmar_2_6 = true ]]
	then
		MODULE_PATH=stack/libraries/lib_levmar-2.6
		REPO_URL=https://bitbucket.org/joselusl/lib_levmar-2.6
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneObstacleDistanceCalculatorROSModule
if [[ ${droneObstacleDistanceCalculatorROSModule}  && $droneObstacleDistanceCalculatorROSModule = true ]]
	then
		MODULE_PATH=stack/droneEnvironmentUnderstanding/droneObstacleDistanceCalculation/droneObstacleDistanceCalculatorROSModule
		REPO_URL=https://bitbucket.org/joselusl/droneobstacledistancecalculatorrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

#droneSoundROSModule
if [[ ${droneSoundROSModule}  && $droneSoundROSModule = true ]]
	then
		MODULE_PATH=stack/HMI/droneSoundROSModule
		REPO_URL=https://bitbucket.org/joselusl/dronesoundrosmodule.git
		REPO_BRANCH=master
		./installation/gitSubmoduleAddBitbucketPrivRepo.sh $REPO_BRANCH $REPO_URL $MODULE_PATH > /dev/null
		echo " -Added package in: $MODULE_PATH"
fi

