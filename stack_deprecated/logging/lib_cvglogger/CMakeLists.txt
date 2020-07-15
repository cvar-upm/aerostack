cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_cvglogger)
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


set(CVGLOGGERLIB_SOURCE_DIR
        src/source)

set(CVGLOGGERLIB_INCLUDE_DIR
        src/include)

set(CVGLOGGERLIB_HEADER_FILES
        ${CVGLOGGERLIB_INCLUDE_DIR}/debugstringstacker.h
        ${CVGLOGGERLIB_INCLUDE_DIR}/dronelogfileswritter.h
        ${CVGLOGGERLIB_INCLUDE_DIR}/stringstacker.h
)

set(CVGLOGGERLIB_SOURCE_FILES
        ${CVGLOGGERLIB_SOURCE_DIR}/debugstringstacker.cpp
        ${CVGLOGGERLIB_SOURCE_DIR}/dronelogfileswritter.cpp
        ${CVGLOGGERLIB_SOURCE_DIR}/stringstacker.cpp
)

find_package(catkin REQUIRED
                COMPONENTS lib_cvgutils)


catkin_package(
        INCLUDE_DIRS ${CVGLOGGERLIB_INCLUDE_DIR}
        LIBRARIES lib_cvglogger
        CATKIN_DEPENDS lib_cvgutils
  )


include_directories(${CVGLOGGERLIB_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})



add_library(lib_cvglogger ${CVGLOGGERLIB_SOURCE_FILES} ${CVGLOGGERLIB_HEADER_FILES})
add_dependencies(lib_cvglogger ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_cvglogger ${catkin_LIBRARIES})


add_executable(${PROJECT_NAME}_code_tests ${CVGLOGGERLIB_SOURCE_DIR}/code_tests.cpp)
add_dependencies(${PROJECT_NAME}_code_tests ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests lib_cvglogger)
target_link_libraries(${PROJECT_NAME}_code_tests ${catkin_LIBRARIES})

