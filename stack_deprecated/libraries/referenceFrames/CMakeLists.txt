cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME referenceFrames)
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
#set(ROS_BUILD_TYPE RelWithDebInfo)
#SET(CMAKE_BUILD_TYPE Release) # Release, RelWithDebInfo




set(REFERENCEFRAMES_SOURCE_DIR
	src/sources)
	
set(REFERENCEFRAMES_INCLUDE_DIR
	src/include
	)

set(REFERENCEFRAMES_SOURCE_FILES

	#General
	src/sources/referenceFrames.cpp
	)
	
set(REFERENCEFRAMES_HEADER_FILES

	#General
	src/include/referenceFrames.h

	)



find_package(catkin REQUIRED
		)

find_package(OpenCV REQUIRED)


catkin_package(
        INCLUDE_DIRS ${REFERENCEFRAMES_INCLUDE_DIR}
        LIBRARIES referenceFrames
        DEPENDS OpenCV
  )



include_directories(${REFERENCEFRAMES_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})



add_library(referenceFrames ${REFERENCEFRAMES_SOURCE_FILES} ${REFERENCEFRAMES_HEADER_FILES})
add_dependencies(referenceFrames ${catkin_EXPORTED_TARGETS})
target_link_libraries(referenceFrames ${OpenCV_LIBS})
target_link_libraries(referenceFrames ${catkin_LIBRARIES})

