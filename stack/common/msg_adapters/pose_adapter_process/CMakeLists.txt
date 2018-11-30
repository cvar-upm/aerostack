cmake_minimum_required(VERSION 2.8.3)
project(pose_adapter_process)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directories definition
set(POSE_ADAPTER_PROCESS_SOURCE_DIR
  src/source
)

set(POSE_ADAPTER_PROCESS_INCLUDE_DIR
  src/include
)
set(POSE_ADAPTER_PROCESS_TEST_DIR
  src/test
)


# Files declaration
set(POSE_ADAPTER_PROCESS_SOURCE_FILES
  ${POSE_ADAPTER_PROCESS_SOURCE_DIR}/pose_adapter_process.cpp
  ${POSE_ADAPTER_PROCESS_SOURCE_DIR}/pose_adapter_process_main.cpp
)

set(POSE_ADAPTER_PROCESS_HEADER_FILES
  ${POSE_ADAPTER_PROCESS_INCLUDE_DIR}/pose_adapter_process.h
)

### Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  drone_process
  droneMsgsROS
 rviz roscpp image_transport  cv_bridge   angles lib_pugixml
)

###################################
## catkin specific configuration ##
###################################
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ${POSE_ADAPTER_PROCESS_INCLUDE_DIR}
  CATKIN_DEPENDS
  roscpp
  std_msgs
  geometry_msgs
  drone_process
  droneMsgsROS
  angles lib_pugixml DEPENDS yaml-cpp
)

###########
## Build ##
###########
include_directories(
  ${POSE_ADAPTER_PROCESS_INCLUDE_DIR}
  ${POSE_ADAPTER_PROCESS_SOURCE_DIR}
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(pose_adapter_process_lib ${POSE_ADAPTER_PROCESS_SOURCE_FILES} ${POSE_ADAPTER_PROCESS_HEADER_FILES})
add_dependencies(pose_adapter_process_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(pose_adapter_process_lib ${catkin_LIBRARIES})

add_executable(pose_adapter_process ${POSE_ADAPTER_PROCESS_SOURCE_DIR}/pose_adapter_process_main.cpp)
add_dependencies(pose_adapter_process ${catkin_EXPORTED_TARGETS})
target_link_libraries(pose_adapter_process pose_adapter_process_lib)
target_link_libraries(pose_adapter_process ${catkin_LIBRARIES})

#############
## Testing ##
#############
if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(pose_adapter_process_test ${POSE_ADAPTER_PROCESS_TEST_DIR}/pose_adapter_test.cpp)
  target_link_libraries(pose_adapter_process_test pose_adapter_process_lib)
  target_link_libraries(pose_adapter_process_test ${catkin_LIBRARIES})

endif()
