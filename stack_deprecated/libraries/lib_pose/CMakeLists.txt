cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_pose)
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



#LIB_POSE LIB
set(LIB_POSE_SOURCE_DIR
	src/sources) 
	
set(LIB_POSE_INCLUDE_DIR
	src/include)

set(LIB_POSE_SOURCE_FILES	
	${LIB_POSE_SOURCE_DIR}/pose.cpp   
	${LIB_POSE_SOURCE_DIR}/poseOperations.cpp   

)
 
set(LIB_POSE_HEADER_FILES
	
	${LIB_POSE_INCLUDE_DIR}/pose.h  
	${LIB_POSE_INCLUDE_DIR}/poseOperations.h  
)


find_package(catkin REQUIRED)

find_package(OpenCV REQUIRED)



catkin_package(
	INCLUDE_DIRS ${LIB_POSE_INCLUDE_DIR}
        LIBRARIES lib_pose
	DEPENDS OpenCV
  )


include_directories(${LIB_POSE_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})

 
#common commands for building c++ executables and libraries


add_library(lib_pose ${LIB_POSE_SOURCE_FILES} ${LIB_POSE_HEADER_FILES})
add_dependencies(lib_pose ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_pose ${OpenCV_LIBS})
target_link_libraries(lib_pose ${catkin_LIBRARIES})


