cmake_minimum_required(VERSION 2.8.3)
project(camera_overlay)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directory definitions
set(CAMERA_OVERLAY_SOURCE_DIR
  src/source
)
  
set(CAMERA_OVERLAY_INCLUDE_DIR
  src/include
) 

# Files declaration
set(CAMERA_OVERLAY_SOURCE_FILES
  ${CAMERA_OVERLAY_SOURCE_DIR}/image_converter.cpp 
)

set(CAMERA_OVERLAY_HEADER_FILES
  ${CAMERA_OVERLAY_INCLUDE_DIR}/image_converter.h
)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  sensor_msgs 
  cv_bridge
  roscpp 
  std_msgs 
  image_transport 
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
  INCLUDE_DIRS ${CAMERA_OVERLAY_INCLUDE_DIR}
  LIBRARIES camera_overlay
  CATKIN_DEPENDS sensor_msgs cv_bridge roscpp std_msgs image_transport droneMsgsROS
  DEPENDS yaml-cpp
)
         
###########
## Build ##
###########

find_package(OpenCV)

include_directories(
  ${CAMERA_OVERLAY_INCLUDE_DIR}
  ${CAMERA_OVERLAY_SOURCE_DIR}
)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ Library
add_library(camera_overlay ${CAMERA_OVERLAY_SOURCE_FILES} ${CAMERA_OVERLAY_HEADER_FILES})
add_dependencies(camera_overlay ${catkin_EXPORTED_TARGETS})
target_link_libraries(camera_overlay ${catkin_LIBRARIES})
target_link_libraries(camera_overlay ${OpenCV_LIBS} )
target_link_libraries(camera_overlay ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
#target_link_libraries(camera_overlay yaml-cpp)

#add_executable(behavior_manager_process ${CAMERA_OVERLAY_SOURCE_DIR}/behavior_manager_main.cpp)
#add_dependencies(behavior_manager_process ${catkin_EXPORTED_TARGETS})
#target_link_libraries(behavior_manager_process behavior_manager_process_lib)
#target_link_libraries(behavior_manager_process ${catkin_LIBRARIES})


#############
## Testing ##
#############
#if (CATKIN_ENABLE_TESTING)  
#  catkin_add_gtest(BehaviorManagerTest ${BEHAVIOR_DESCRIPTOR_TEST_DIR}/behavior_manager_test.cpp)
#  target_link_libraries(BehaviorManagerTest behavior_manager_process_lib)
#  target_link_libraries(BehaviorManagerTest ${catkin_LIBRARIES})
  
  #find_package(rostest REQUIRED)
  #add_rostest(launch/lau.test)
#endif()































