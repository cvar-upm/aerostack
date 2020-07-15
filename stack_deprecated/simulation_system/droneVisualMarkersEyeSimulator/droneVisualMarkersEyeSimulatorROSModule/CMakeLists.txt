cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME droneVisualMarkersEyeSimulatorROSModule)
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




set(DRONE_VISUAL_MARKERS_EYE_SIMULATOR_SOURCE_DIR
	src/sources)
	
set(DRONE_VISUAL_MARKERS_EYE_SIMULATOR_INCLUDE_DIR
	src/include
	)

set(DRONE_VISUAL_MARKERS_EYE_SIMULATOR_SOURCE_FILES

	#General
	${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_SOURCE_DIR}/droneVisualMarkersEyeSimulatorROSModule.cpp
	
	#General
	
	
	)
	
set(DRONE_VISUAL_MARKERS_EYE_SIMULATOR_HEADER_FILES

	#General
	
	${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_INCLUDE_DIR}/droneVisualMarkersEyeSimulatorROSModule.h
	
	)
	
	
	
find_package(catkin REQUIRED
                COMPONENTS roscpp droneModuleROS droneMsgsROS droneVisualMarkersEyeSimulator)


catkin_package(
        CATKIN_DEPENDS roscpp droneModuleROS droneMsgsROS droneVisualMarkersEyeSimulator
  )


include_directories(${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})



add_library(droneVisualMarkersEyeSimulatorROSModule ${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_SOURCE_FILES} ${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_HEADER_FILES})
add_dependencies(droneVisualMarkersEyeSimulatorROSModule ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneVisualMarkersEyeSimulatorROSModule ${catkin_LIBRARIES})



add_executable(droneVisualMarkersEyeSimulatorROSModuleNode ${DRONE_VISUAL_MARKERS_EYE_SIMULATOR_SOURCE_DIR}/droneVisualMarkersEyeSimulatorROSModuleNode.cpp)
add_dependencies(droneVisualMarkersEyeSimulatorROSModuleNode ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneVisualMarkersEyeSimulatorROSModuleNode droneVisualMarkersEyeSimulatorROSModule)
target_link_libraries(droneVisualMarkersEyeSimulatorROSModuleNode ${catkin_LIBRARIES})


