cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_cvgthread)
project(${PROJECT_NAME})

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
##add_definitions(-std=c++11)
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



set(CVGTHREADLIB_SOURCE_DIR
        src/source)

set(CVGTHREADLIB_INCLUDE_DIR
        src/include)

set(CVGTHREADLIB_HEADER_FILES
        ${CVGTHREADLIB_INCLUDE_DIR}/cvgException.h
        ${CVGTHREADLIB_INCLUDE_DIR}/cvgMutex.h
        ${CVGTHREADLIB_INCLUDE_DIR}/cvgThread.h
        ${CVGTHREADLIB_INCLUDE_DIR}/cvgCondition.h
        ${CVGTHREADLIB_INCLUDE_DIR}/cvgSemaphore.h
)

set(CVGTHREADLIB_SOURCE_FILES
        ${CVGTHREADLIB_SOURCE_DIR}/cvgException.cpp
        ${CVGTHREADLIB_SOURCE_DIR}/cvgMutex.cpp
        ${CVGTHREADLIB_SOURCE_DIR}/cvgThread.cpp
)


find_package(catkin REQUIRED)



catkin_package(
	INCLUDE_DIRS ${CVGTHREADLIB_INCLUDE_DIR}
        LIBRARIES lib_cvgthread
  )



include_directories(${CVGTHREADLIB_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})



add_library(lib_cvgthread ${CVGTHREADLIB_SOURCE_FILES} ${CVGTHREADLIB_HEADER_FILES})
add_dependencies(lib_cvgthread ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_cvgthread ${catkin_LIBRARIES})
