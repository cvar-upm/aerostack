cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME task_based_mission_planner_process)
project(${PROJECT_NAME})

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)
#add_definitions(-std=c++0x)
#add_definitions(-std=c++03)


# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries




set(PARROT_MISSION_PLANNER_SOURCE_DIR
	src/sources)
	
set(PARROT_MISSION_PLANNER_INCLUDE_DIR
	src/include
	)

set(PARROT_MISSION_PLANNER_SOURCE_FILES

	#General
        ${PARROT_MISSION_PLANNER_SOURCE_DIR}/task_based_mission_planner_process.cpp	
        ${PARROT_MISSION_PLANNER_SOURCE_DIR}/task_based_mission_planner_process_main.cpp
	)
	
set(PARROT_MISSION_PLANNER_HEADER_FILES

	#General
        ${PARROT_MISSION_PLANNER_INCLUDE_DIR}/task_based_mission_planner_process.h	
	)
	
find_package(catkin REQUIRED
                COMPONENTS roscpp std_srvs droneMsgsROS droneModuleROS task_based_mission_planner droneTrajectoryPlanner droneVisualMarkersLocalizer drone_process)


catkin_package(
        CATKIN_DEPENDS roscpp std_srvs droneMsgsROS droneModuleROS task_based_mission_planner drone_process
  )

include_directories(${PARROT_MISSION_PLANNER_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})

add_library(task_based_mission_planner_process_lib ${PARROT_MISSION_PLANNER_SOURCE_FILES} ${PARROT_MISSION_PLANNER_HEADER_FILES})
add_dependencies(task_based_mission_planner_process_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(task_based_mission_planner_process_lib ${catkin_LIBRARIES})


add_executable(task_based_mission_planner_process_main ${PARROT_MISSION_PLANNER_SOURCE_DIR}/task_based_mission_planner_process_main.cpp)
add_dependencies(task_based_mission_planner_process_main ${catkin_EXPORTED_TARGETS})
target_link_libraries(task_based_mission_planner_process_main task_based_mission_planner_process_lib)
target_link_libraries(task_based_mission_planner_process_main ${catkin_LIBRARIES})
