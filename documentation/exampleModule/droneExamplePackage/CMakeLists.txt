cmake_minimum_required(VERSION 2.4.6)

set(PROJECT_NAME droneExamplePackage)
project(${PROJECT_NAME})

#include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

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
#set(ROS_BUILD_TYPE RelWithDebInfo)

#rosbuild_init()

#set the default path for built executables to the "bin" directory
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

set(DRONE_EXAMPLE_PACKAGE_SOURCE_DIR
    src/source)

set(DRONE_EXAMPLE_PACKAGE_INCLUDE_DIR
    src/include
)

set(DRONE_EXAMPLE_PACKAGE_HEADER_FILES
    ${DRONE_EXAMPLE_PACKAGE_INCLUDE_DIR}/droneExamplePackageHeader.h

)

set(DRONE_EXAMPLE_PACKAGE_SOURCE_FILES
    ${DRONE_EXAMPLE_PACKAGE_SOURCE_DIR}/droneExamplePackageSource.cpp
    


)



find_package(catkin REQUIRED
#		COMPONENTS lib_pugixml
)

#if OpenCV
#find_package(OpenCV REQUIRED)


catkin_package(
        INCLUDE_DIRS ${DRONE_EXAMPLE_PACKAGE_INCLUDE_DIR}
        LIBRARIES droneExamplePackage
#	CATKIN_DEPENDS lib_pugixml
  )


include_directories(${catkin_INCLUDE_DIRS})




#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})







include_directories(
    ${DRONE_EXAMPLE_PACKAGE_INCLUDE_DIR}

)
add_library(droneExamplePackage ${DRONE_EXAMPLE_PACKAGE_SOURCE_FILES} ${DRONE_EXAMPLE_PACKAGE_HEADER_FILES})


#target_link_libraries(droneExamplePackage ${OpenCV_LIBS})

target_link_libraries(droneExamplePackage ${catkin_LIBRARIES})



set(OTHER_FILES
        package.xml
)
add_custom_target(other_files SOURCES ${OTHER_FILES})

