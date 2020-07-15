cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME droneVisualMarkersEyeSimulator)
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




set(DRONE_VISUAL_MARKERS_SIMULATOR_SOURCE_DIR
	src/sources)
	
set(DRONE_VISUAL_MARKERS_SIMULATOR_INCLUDE_DIR
	src/include
	)

set(DRONE_VISUAL_MARKERS_SIMULATOR_SOURCE_FILES

	#General
	${DRONE_VISUAL_MARKERS_SIMULATOR_SOURCE_DIR}/droneVisualMarkersEyeSimulator.cpp
	
	)
	
set(DRONE_VISUAL_MARKERS_SIMULATOR_HEADER_FILES

	#General
	${DRONE_VISUAL_MARKERS_SIMULATOR_INCLUDE_DIR}/droneVisualMarkersEyeSimulator.h
	
	)
	

find_package(catkin REQUIRED
                COMPONENTS lib_cvgutils lib_pugixml referenceFrames)


catkin_package(
        INCLUDE_DIRS ${DRONE_VISUAL_MARKERS_SIMULATOR_INCLUDE_DIR}
        LIBRARIES droneVisualMarkersEyeSimulator
        CATKIN_DEPENDS lib_cvgutils lib_pugixml referenceFrames
  )


include_directories(${DRONE_VISUAL_MARKERS_SIMULATOR_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})



add_library(droneVisualMarkersEyeSimulator ${DRONE_VISUAL_MARKERS_SIMULATOR_SOURCE_FILES} ${DRONE_VISUAL_MARKERS_SIMULATOR_HEADER_FILES})
add_dependencies(droneVisualMarkersEyeSimulator ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneVisualMarkersEyeSimulator ${catkin_LIBRARIES})


