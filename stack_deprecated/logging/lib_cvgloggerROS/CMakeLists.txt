cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_cvgloggerROS)
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




set(CVGLOGGERROSLIB_SOURCE_DIR
        src/source)

set(CVGLOGGERROSLIB_INCLUDE_DIR
        src/include)

set(CVGLOGGERROSLIB_HEADER_FILES
        ${CVGLOGGERROSLIB_INCLUDE_DIR}/droneloggerrospublisher.h
        ${CVGLOGGERROSLIB_INCLUDE_DIR}/droneloggerrostopicsubscriber.h
        ${CVGLOGGERROSLIB_INCLUDE_DIR}/droneloggerrosbasicmodule.h
)

set(CVGLOGGERROSLIB_SOURCE_FILES
        ${CVGLOGGERROSLIB_SOURCE_DIR}/droneloggerrospublisher.cpp
        ${CVGLOGGERROSLIB_SOURCE_DIR}/droneloggerrostopicsubscriber.cpp
        ${CVGLOGGERROSLIB_SOURCE_DIR}/droneloggerrosbasicmodule.cpp
)


find_package(catkin REQUIRED
		COMPONENTS message_generation roscpp droneModuleROS std_msgs lib_cvglogger lib_cvgutils droneMsgsROS)


add_service_files(
    DIRECTORY
        srv
    FILES
        logThisString.srv
)

generate_messages()


catkin_package(
        INCLUDE_DIRS ${CVGLOGGERROSLIB_INCLUDE_DIR}
        LIBRARIES lib_cvgloggerROS
        CATKIN_DEPENDS message_runtime roscpp droneModuleROS std_msgs lib_cvglogger lib_cvgutils droneMsgsROS
  )


include_directories(${CVGLOGGERROSLIB_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})





add_library(lib_cvgloggerROS ${CVGLOGGERROSLIB_SOURCE_FILES} ${CVGLOGGERROSLIB_HEADER_FILES})
add_dependencies(lib_cvgloggerROS ${catkin_EXPORTED_TARGETS})
add_dependencies(lib_cvgloggerROS lib_cvgloggerROS_generate_messages_cpp)
target_link_libraries(lib_cvgloggerROS ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests.cpp)
add_dependencies(${PROJECT_NAME}_code_tests ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests2 ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests2.cpp)
add_dependencies(${PROJECT_NAME}_code_tests2 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests2 lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests2 ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests3 ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests3.cpp)
add_dependencies(${PROJECT_NAME}_code_tests3 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests3 lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests3 ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests4 ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests4.cpp)
add_dependencies(${PROJECT_NAME}_code_tests4 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests4 lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests4 ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests5 ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests5.cpp)
add_dependencies(${PROJECT_NAME}_code_tests5 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests5 lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests5 ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests6 ${CVGLOGGERROSLIB_SOURCE_DIR}/code_tests6.cpp)
add_dependencies(${PROJECT_NAME}_code_tests6 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests6 lib_cvgloggerROS)
target_link_libraries(${PROJECT_NAME}_code_tests6 ${catkin_LIBRARIES})

