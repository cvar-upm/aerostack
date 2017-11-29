cmake_minimum_required(VERSION 2.8.3)
project(camera_overlay_process)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directories definition
set(CAMERA_OVERLAY_PROCESS_SOURCE_DIR
  src/source
)
	
set(CAMERA_OVERLAY_PROCESS_INCLUDE_DIR
  src/include
)

# Files declaration
set(CAMERA_OVERLAY_PROCESS_SOURCE_FILES
  ${CAMERA_OVERLAY_PROCESS_SOURCE_DIR}/camera_overlay_process.cpp
  ${CAMERA_OVERLAY_PROCESS_SOURCE_DIR}/camera_overlay_process_main.cpp
)

set(CAMERA_OVERLAY_PROCESS_HEADER_FILES
  ${CAMERA_OVERLAY_PROCESS_INCLUDE_DIR}/camera_overlay_process.h
)

### Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  COMPONENTS 
  roscpp 
  std_msgs
  robot_process
  camera_overlay
)

###################################
## catkin specific configuration ##
###################################
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ${CAMERA_OVERLAY_PROCESS_INCLUDE_DIR}
  CATKIN_DEPENDS
  roscpp 
  std_msgs
  robot_process
  camera_overlay
)

###########
## Build ##
###########			       	     
include_directories(
  ${CAMERA_OVERLAY_PROCESS_INCLUDE_DIR}
  ${CAMERA_OVERLAY_PROCESS_SOURCE_DIR}
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(camera_overlay_process_lib ${CAMERA_OVERLAY_PROCESS_SOURCE_FILES} ${CAMERA_OVERLAY_PROCESS_HEADER_FILES})
add_dependencies(camera_overlay_process_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(camera_overlay_process_lib ${catkin_LIBRARIES})


add_executable(camera_overlay_process ${CAMERA_OVERLAY_PROCESS_SOURCE_DIR}/camera_overlay_process_main.cpp)
add_dependencies(camera_overlay_process ${catkin_EXPORTED_TARGETS})
target_link_libraries(camera_overlay_process camera_overlay_process_lib)
target_link_libraries(camera_overlay_process ${catkin_LIBRARIES})

#############
## Testing ##
#############
#if (CATKIN_ENABLE_TESTING)  
#  catkin_add_gtest(BehaviorManagerTest ${BEHAVIOR_DESCRIPTOR_TEST_DIR}/behavior_manager_test.cpp)
#  target_link_libraries(BehaviorManagerTest camera_overlay_process_lib)
#  target_link_libraries(BehaviorManagerTest ${catkin_LIBRARIES})
  
  #find_package(rostest REQUIRED)
  #add_rostest(launch/lau.test)
#endif()
