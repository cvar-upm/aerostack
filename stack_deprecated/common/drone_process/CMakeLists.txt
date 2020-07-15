cmake_minimum_required(VERSION 2.8.3)
project(drone_process)
add_definitions(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  droneMsgsROS
  std_srvs
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES drone_process
  CATKIN_DEPENDS roscpp std_msgs droneMsgsROS std_srvs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
)
include_directories(
  include
  source
  test
)

## Declare a cpp library
add_library(drone_process source/drone_process.cpp include/drone_process.h)
add_dependencies(drone_process ${catkin_EXPORTED_TARGETS})
target_link_libraries(drone_process ${catkin_LIBRARIES})