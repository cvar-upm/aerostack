cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME droneLoggerROSModule)
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



set(DRONELOGGERROSMODULE_SOURCE_DIR
        src/source)

set(DRONELOGGERROSMODULE_INCLUDE_DIR
        src/include)

set(DRONELOGGERROSMODULE_HEADER_FILES
        ${DRONELOGGERROSMODULE_INCLUDE_DIR}/droneloggerrosmodule.h
)

set(DRONELOGGERROSMODULE_SOURCE_FILES
        ${DRONELOGGERROSMODULE_SOURCE_DIR}/droneloggerrosmodule.cpp

)

find_package(catkin REQUIRED
                COMPONENTS roscpp std_msgs geometry_msgs sensor_msgs image_transport cv_bridge droneModuleROS droneMsgsROS lib_cvglogger lib_cvgloggerROS)

find_package(OpenCV REQUIRED)


catkin_package(
        DEPENDS OpenCV
        CATKIN_DEPENDS roscpp std_msgs geometry_msgs sensor_msgs image_transport cv_bridge droneModuleROS droneMsgsROS lib_cvglogger lib_cvgloggerROS
  )


include_directories(${DRONELOGGERROSMODULE_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})



add_library(droneLoggerROSModule ${DRONELOGGERROSMODULE_SOURCE_FILES} ${DRONELOGGERROSMODULE_HEADER_FILES})
add_dependencies(droneLoggerROSModule ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneLoggerROSModule ${OpenCV_LIBS})
target_link_libraries(droneLoggerROSModule ${catkin_LIBRARIES})


add_executable(droneLoggerROSModuleNode ${DRONELOGGERROSMODULE_SOURCE_DIR}/droneLoggerROSModuleNode.cpp)
add_dependencies(droneLoggerROSModuleNode ${catkin_EXPORTED_TARGETS})
target_link_libraries(droneLoggerROSModuleNode droneLoggerROSModule)
target_link_libraries(droneLoggerROSModuleNode ${OpenCV_LIBS})
target_link_libraries(droneLoggerROSModuleNode ${catkin_LIBRARIES})


