cmake_minimum_required(VERSION 2.8.3)
project(parrot_arsdk)

find_package(catkin REQUIRED)

catkin_package(
  CFG_EXTRAS parrot_arsdk.cmake
)

###########
## Build ##
###########

# use the build space for downloading/building the package
# we populate the results to devel/install spaces after the build
set(ARDRONESDK3_DEVEL_PATH ${CMAKE_CURRENT_BINARY_DIR}/arsdk)
set(ARDRONESDK3_PATH ${ARDRONESDK3_DEVEL_PATH}/src/ARSDKBuildUtils/out/arsdk-native/staging/usr)

# 3.12.6 patch 1
set(ARSDK_ARCHIVE arsdk_3_12_6_p1_stripped.tgz)
set(ARSDK_ARCHIVE_MD5 134b533513045235e55134b47d1ba8d4)

# Determine the architecure of the host in a robust way
execute_process(COMMAND python ${PROJECT_SOURCE_DIR}/script/get_arch.py OUTPUT_VARIABLE BUILD_HOST_ARCH)
message(STATUS "Host architecure: ${BUILD_HOST_ARCH}")

add_custom_target(ARSDK_MKDIR
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ARDRONESDK3_DEVEL_PATH})

include(ExternalProject)
ExternalProject_Add(ARSDKBuildUtils
    DEPENDS ARSDK_MKDIR
    URL ${PROJECT_SOURCE_DIR}/sdk/${ARSDK_ARCHIVE}
    URL_MD5 ${ARSDK_ARCHIVE_MD5}
    PREFIX ${ARDRONESDK3_DEVEL_PATH}
    CONFIGURE_COMMAND echo "No configure"
    # Setting TARGET_OS_FLAVOUR is experimental. The idea is to trick the build script to always pass the correct arch flags to all of underlying build scripts. This is useful when building the sdk for i386 targets inside a docker container which is running on a x86_64 host.
    BUILD_COMMAND TARGET_OS_FLAVOUR=native-chroot TARGET_ARCH=${BUILD_HOST_ARCH} ./build.sh -p arsdk-native -t build-sdk -j --no-color
    INSTALL_COMMAND echo "No SDK install command"
    BUILD_IN_SOURCE 1
)

add_custom_target(ARSDKPopulate ALL
  COMMENT "Populating ARDroneSDK to devel space: ${ARDRONESDK3_DEVEL_PATH}"
  WORKING_DIRECTORY ${ARDRONESDK3_DEVEL_PATH}/src/ARSDKBuildUtils
  # Populate the build results into the devel space
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  COMMAND cp -rp ./out/arsdk-native/staging/usr/include/* ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME}
  COMMAND cp -rp ./out/arsdk-native/staging/usr/lib/* ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_SHARE_DESTINATION}/${PROJECT_NAME}
  COMMAND cp -rp ./out/arsdk-native/staging/usr/share/* ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_SHARE_DESTINATION}/${PROJECT_NAME}
  #COMMAND ${CMAKE_COMMAND} -E make_directory ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/${PROJECT_NAME}
  #COMMAND cp -rp ./out/Unix-base/staging/usr/bin/* ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/${PROJECT_NAME}
)
add_dependencies(ARSDKPopulate ARSDKBuildUtils)

#############
## Install ##
#############

#install(DIRECTORY ${ARDRONESDK3_PATH}/bin/
#  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#  USE_SOURCE_PERMISSIONS
#)

install(DIRECTORY ${ARDRONESDK3_PATH}/include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY ${ARDRONESDK3_PATH}/lib/
  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}/parrot_arsdk
)

install(DIRECTORY ${ARDRONESDK3_PATH}/share/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY ${ARDRONESDK3_PATH}/../etc/
  DESTINATION ${CATKIN_PACKAGE_ETC_DESTINATION}
)
