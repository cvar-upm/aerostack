cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME task_based_mission_planner)
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



set(TASKBASEDMISSIONPLANNER_SOURCE_DIR
	src/sources
	)
	
set(TASKBASEDMISSIONPLANNER_INCLUDE_DIR
	src/include
	)

set(TASKBASEDMISSIONPLANNER_SOURCE_FILES
	src/sources/Mission.cpp
	src/sources/ErrorHandler.cpp
	src/sources/Task.cpp
	src/sources/Action.cpp
	src/sources/Event.cpp
	src/sources/Condition.cpp
	src/sources/EventHandler.cpp
	src/sources/Parser.cpp
	)
	
set(TASKBASEDMISSIONPLANNER_HEADER_FILES
	src/include/Mission.h
	src/include/TreeNode.h
    src/include/Task.h
    src/include/Action.h
	src/include/Event.h
	src/include/Condition.h
	src/include/Definitions.h
	src/include/ErrorHandler.h
	src/include/Parser.h
	)	
	
find_package(catkin REQUIRED
		COMPONENTS lib_pugixml
	)

catkin_package(
        INCLUDE_DIRS ${TASKBASEDMISSIONPLANNER_INCLUDE_DIR}
        LIBRARIES task_based_mission_planner
        CATKIN_DEPENDS lib_pugixml
  )

include_directories(${TASKBASEDMISSIONPLANNER_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})

add_library(task_based_mission_planner ${TASKBASEDMISSIONPLANNER_SOURCE_FILES} ${TASKBASEDMISSIONPLANNER_HEADER_FILES})
add_dependencies(task_based_mission_planner ${catkin_EXPORTED_TARGETS})
target_link_libraries(task_based_mission_planner ${catkin_LIBRARIES})
