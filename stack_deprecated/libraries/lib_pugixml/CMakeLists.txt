cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_pugixml)
project(${PROJECT_NAME})

#add_definitions(-std=c++11)
#add_definitions(-std=c++0x)
add_definitions(-std=c++03)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
#add_definitions(-std=c++11)
# add_definitions(-std=c++0x)



# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

	
	
set(XML_LIBRARY_SOURCE_DIR
	src/sources
)

set(XML_LIBRARY_SOURCE_FILES
	src/sources/pugixml.cpp
)
	
set(XML_LIBRARY_HEADER_DIR
	src/include
)

set(XML_LIBRARY_HEADER_FILES
	src/include/pugiconfig.hpp
	src/include/pugixml.hpp
)


find_package(catkin REQUIRED)

catkin_package(
    INCLUDE_DIRS ${XML_LIBRARY_HEADER_DIR}
    LIBRARIES lib_pugixml
  )



include_directories(${XML_LIBRARY_HEADER_DIR})
include_directories(${catkin_INCLUDE_DIRS})


add_library(lib_pugixml ${XML_LIBRARY_SOURCE_FILES} ${XML_LIBRARY_HEADER_FILES})
add_dependencies(lib_pugixml ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_pugixml ${catkin_LIBRARIES})

