cmake_minimum_required(VERSION 2.8.3)
project(twist_adapter_process)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directories definition
set(TWIST_ADAPTER_PROCESS_SOURCE_DIR
  src/source
)

set(TWIST_ADAPTER_PROCESS_INCLUDE_DIR
  src/include
)

set(TWIST_ADAPTER_PROCESS_TEST_DIR
  src/test
)


# Files declaration
set(TWIST_ADAPTER_PROCESS_SOURCE_FILES
  ${TWIST_ADAPTER_PROCESS_SOURCE_DIR}/twist_adapter_process.cpp
  ${TWIST_ADAPTER_PROCESS_SOURCE_DIR}/twist_adapter_process_main.cpp
)

set(TWIST_ADAPTER_PROCESS_HEADER_FILES
  ${TWIST_ADAPTER_PROCESS_INCLUDE_DIR}/twist_adapter_process.h
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
)

###################################
## catkin specific configuration ##
###################################
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ${TWIST_ADAPTER_PROCESS_INCLUDE_DIR}
  CATKIN_DEPENDS
  roscpp
  std_msgs
  geometry_msgs
  drone_process
  droneMsgsROS
)

###########
## Build ##
###########
include_directories(
  ${TWIST_ADAPTER_PROCESS_INCLUDE_DIR}
  ${TWIST_ADAPTER_PROCESS_SOURCE_DIR}
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(twist_adapter_process_lib ${TWIST_ADAPTER_PROCESS_SOURCE_FILES} ${TWIST_ADAPTER_PROCESS_HEADER_FILES})
add_dependencies(twist_adapter_process_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(twist_adapter_process_lib ${catkin_LIBRARIES})

add_executable(twist_adapter_process ${TWIST_ADAPTER_PROCESS_SOURCE_DIR}/twist_adapter_process_main.cpp)
add_dependencies(twist_adapter_process ${catkin_EXPORTED_TARGETS})
target_link_libraries(twist_adapter_process twist_adapter_process_lib)
target_link_libraries(twist_adapter_process ${catkin_LIBRARIES})

#############
## Testing ##
#############
if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(twist_adapter_process_test ${TWIST_ADAPTER_PROCESS_TEST_DIR}/twist_adapter_test.cpp)
  target_link_libraries(twist_adapter_process_test twist_adapter_process_lib)
  target_link_libraries(twist_adapter_process_test ${catkin_LIBRARIES})

endif()
