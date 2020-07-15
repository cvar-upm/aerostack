cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME droneMsgsROS)
project(${PROJECT_NAME})

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
#add_definitions(-std=c++11)
#add_definitions(-std=c++0x)
add_definitions(-std=c++03)


# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)



set(DRONEMSGS_SOURCE_DIR
	src/sources)

set(DRONEMSGS_INCLUDE_DIR
	src/include
	)

set(DRONEMSGS_SOURCE_FILES

	)

set(DRONEMSGS_HEADER_FILES

	#General
        src/include/nodes_definition.h
        src/include/communication_definition.h
	)


find_package(catkin REQUIRED
                COMPONENTS message_generation std_msgs sensor_msgs geometry_msgs std_srvs opencv_apps)



add_message_files(
    DIRECTORY
        msg
    FILES
        #driver msgs
        battery.msg
        droneAltitude.msg
        droneStatus.msg
        monoMeasureStamped.msg #never used
        vector2.msg
        vector2Stamped.msg
		robotPose.msg
        dronePitchRollCmd.msg
        droneDYawCmd.msg
        droneDAltitudeCmd.msg
        droneCommand.msg

        droneAutopilotCommand.msg

        #other
	droneAltitudeCmd.msg
        droneGoTask.msg
        droneHLCommandAck.msg
        droneHLCommand.msg
	droneMissionPlannerCommand.msg
	droneManagerStatus.msg
        droneInfo.msg
        droneMissionInfo.msg
        droneNavCommand.msg #obsolete
        droneNavData.msg #obsolete
        dronePose.msg
        dronePoseStamped.msg
        dronePositionRefCommand.msg
        dronePositionRefCommandStamped.msg
        dronePositionTrajectoryRefCommand.msg
        droneRefCommand.msg
        droneSensorData.msg
        droneSpeeds.msg
        droneSpeedsStamped.msg
        droneTrajectoryRefCommand.msg
        droneYawRefCommand.msg
        imageFeaturesIBVS.msg
        imageFeaturesFeedbackIBVS.msg
        Landmark3D.msg
        landmarkVector.msg
        Observation3D.msg
        obstaclesTwoDim.msg
        obstacleTwoDimPole.msg
        obstacleTwoDimWall.msg
        obsVector.msg
        societyPose.msg
        droneTrajectoryControllerControlMode.msg
        FlightAnimation.msg
  	windowClosed.msg
        windowOpened.msg

        vectorPoints2D.msg
        vector2i.msg
        vectorPoints2DInt.msg

	robotPoseStamped.msg
        robotPoseStampedVector.msg

        targetInImage.msg
        vectorTargetsInImageStamped.msg

        vector3f.msg
        points3DStamped.msg

	robotPoseStamped.msg

	robotPoseVector.msg
	robotPoseStampedVector.msg

        # trajectories for EuRoC
        CommandTrajectoryPath.msg
        CommandTrajectoryWaypoint.msg

        #Opentld
        BoundingBox.msg
        Target.msg
        VectorROIs.msg

        #new process supervisor
        AliveSignal.msg
        ProcessState.msg
        ProcessError.msg
        ErrorType.msg
        ProcessDescriptorList.msg
        ProcessDescriptor.msg
        ProcessState.msg

	distanceToObstacle.msg
	distancesToObstacles.msg

	#Global Mission Planner
	droneTask.msg
	droneMission.msg
        visualObjectRecognized.msg
        vectorVisualObjectsRecognized.msg
        dronePerceptionManagerMissionRequest.msg
        dronePerceptionManagerMissionState.msg

	actionArguments.msg
	actionData.msg
	CompletedAction.msg
	PublicEvent.msg
	SkillDescriptor.msg
	SkillsList.msg
	SkillState.msg
	Event.msg
	AllBeliefs.msg
	BeliefStatement.msg
	CompletedMission.msg
	missionState.msg

	# Executive Layer
	BehaviorCommand.msg
	BehaviorEvent.msg
	Capability.msg
	ListOfCapabilities.msg
	ListOfProcesses.msg
	ListOfBehaviors.msg

  QRInterpretation.msg
	segmento.msg
	seg.msg

  PathWithID.msg

)


add_service_files(
    DIRECTORY
        srv
    FILES
        setControlMode.srv
        setInitDroneYaw_srv_type.srv
        askForModule.srv
        getFlightAnim.srv
        missionName.srv
        openMissionFile.srv
        skillRequest.srv
	perceptionManagerUpdateMissionStateSrv.srv
        classifyImage.srv
        ConsultBelief.srv
        AddBelief.srv
        RemoveBelief.srv
        CheckBeliefFormat.srv
        configurationFolder.srv

	#Executive Layer
	BehaviorSrv.srv
        StartBehavior.srv
	QueryResources.srv
	ResourcesSrv.srv
	CheckSituation.srv
	ConsultDefaultBehaviorValues.srv
	CheckBehaviorGroupConsistency.srv
	CheckCapabilitiesConsistency.srv
	InitiateBehaviors.srv
	StopBehavior.srv
	CheckReactiveActivation.srv
	RecordReactiveBehaviors.srv
	ConsultAvailableBehaviors.srv
	InhibitBehavior.srv
	RequestBehavior.srv
	ConsultIncompatibleBehaviors.srv
	RequestResources.srv
	CheckBehaviorFormat.srv
	RequestProcesses.srv

	#BeliefManager
  GenerateID.srv
  QueryLastGeneratedID.srv

    # Path Planner
    GeneratePath.srv
)


generate_messages(DEPENDENCIES std_msgs sensor_msgs geometry_msgs std_srvs opencv_apps)




catkin_package(
        INCLUDE_DIRS ${DRONEMSGS_INCLUDE_DIR}
        CATKIN_DEPENDS message_runtime std_msgs sensor_msgs geometry_msgs std_srvs opencv_apps
	)



include_directories(${DRONEMSGS_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})


add_custom_target(${PROJECT_NAME}
            SOURCES ${DRONEMSGS_HEADER_FILES}
            )
