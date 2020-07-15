cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME droneModuleInterfaceROS)
project(${PROJECT_NAME})

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)



# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)



set(DRONEMODULE_SOURCE_DIR
        src/source
)
	
set(DRONEMODULE_INCLUDE_DIR
	src/include
	)

set(DRONEMODULE_SOURCE_FILES

	#General

        ${DRONEMODULE_SOURCE_DIR}/dronemoduleinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/droneekfstateestimatorinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/dronetrajectorycontrollerinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/dronecontrollerinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/droneIBVScontrollerinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/dronelocalizerinterface.cpp
        ${DRONEMODULE_SOURCE_DIR}/drone_iarc14_brain_interface.cpp
	${DRONEMODULE_SOURCE_DIR}/droneModuleInterfaceList.cpp
	)
	
set(DRONEMODULE_HEADER_FILES

	#General

        ${DRONEMODULE_INCLUDE_DIR}/dronemoduleinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/droneekfstateestimatorinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/dronetrajectorycontrollerinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/dronecontrollerinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/droneIBVScontrollerinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/dronelocalizerinterface.h
        ${DRONEMODULE_INCLUDE_DIR}/drone_iarc14_brain_interface.h
	${DRONEMODULE_INCLUDE_DIR}/droneModuleInterfaceList.h
	)



find_package(catkin REQUIRED
    COMPONENTS roscpp std_msgs std_srvs lib_cvgutils droneMsgsROS cv_bridge)

find_package(OpenCV REQUIRED)

catkin_package(
	INCLUDE_DIRS ${DRONEMODULE_INCLUDE_DIR}
        LIBRARIES droneModuleInterfaceROS
        CATKIN_DEPENDS roscpp std_msgs std_srvs lib_cvgutils droneMsgsROS cv_bridge
        DEPENDS OpenCV
  )


include_directories(${DRONEMODULE_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(droneModuleInterfaceROS ${DRONEMODULE_SOURCE_FILES} ${DRONEMODULE_HEADER_FILES})
add_dependencies(droneModuleInterfaceROS ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneModuleInterfaceROS ${catkin_LIBRARIES})
target_link_libraries(droneModuleInterfaceROS ${OpenCV_LIBS})
