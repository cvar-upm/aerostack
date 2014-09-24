cmake_minimum_required(VERSION 2.4.6)

set(PROJECT_NAME droneExamplePackageROSModule)
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

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)

#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)

#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#http://answers.ros.org/question/11294/a-problem-of-linking-external-libraries/
#gcc -I/usr/xenomai/include -D_GNU_SOURCE -D_REENTRANT -D__XENO__ -Wall -pipe -lnative -L/usr/xenomai/lib -lxenomai -lpthread -lrtdk hellworld.c -o helloworld
#link_directories(/usr/xenomai/lib)
#rosbuild_add_executable(listener src/listener.cpp)
#include_directories(/usr/xenomai/include)
#add_definitions(-D_GNU_SOURCE -D_REENTRANT -D__XENO__)
#rosbuild_add_compile_flags(listener -Wall -pipe)
#target_link_libraries(listener native xenomai pthread rtdk)






set(DRONE_EXAMPLE_PACKAGE_ROS_MODULE_SOURCE_DIR
	src/sources)
	
set(DRONE_EXAMPLE_PACKAGE_ROS_MODULE_INCLUDE_DIR
	src/include
	)

set(DRONE_EXAMPLE_PACKAGE_ROS_MODULE_SOURCE_FILES

	#General
	${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_SOURCE_DIR}/droneExamplePackageROSModuleSource.cpp

	
	)
	
set(DRONE_EXAMPLE_PACKAGE_ROS_MODULE_HEADER_FILES

	#General
	${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_INCLUDE_DIR}/droneExamplePackageROSModuleHeader.h

	
	
	)
	

#Nodes
set(DRONE_EXAMPLE_PACKAGE_ROS_MODULE_NODE_SOURCE_FILES
    src/sources/droneExamplePackageROSModule_SourceNode.cpp
)
	


find_package(catkin REQUIRED
		COMPONENTS roscpp droneModuleROS droneExamplePackage
)

#if OpenCV
#find_package(OpenCV REQUIRED)


catkin_package(
        CATKIN_DEPENDS roscpp droneModuleROS droneExamplePackage
  )


include_directories(${catkin_INCLUDE_DIRS})



#NODES
include_directories(${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_INCLUDE_DIR})
add_executable(droneExamplePackageNode ${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_NODE_SOURCE_FILES} ${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_SOURCE_FILES} ${DRONE_EXAMPLE_PACKAGE_ROS_MODULE_HEADER_FILES})

#external libraries, like OpenCV
#target_link_libraries(droneExamplePackageNode ${OpenCV_LIBS})

target_link_libraries(droneExamplePackageNode ${catkin_LIBRARIES})



set(OTHER_FILES
        package.xml
)
add_custom_target(other_files SOURCES ${OTHER_FILES})


