cmake_minimum_required(VERSION 2.8.3)
project(planning_msgs)

find_package(catkin REQUIRED COMPONENTS geometry_msgs sensor_msgs message_generation mav_msgs_rotors trajectory_msgs cmake_modules)
find_package(Eigen REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${Eigen_INCLUDE_DIRS})

add_message_files(
  FILES
  PointCloudWithPose.msg
  PolynomialSegment4D.msg
  PolynomialTrajectory4D.msg
)

add_service_files(
  FILES
  PlannerService.srv
)

generate_messages(
  DEPENDENCIES geometry_msgs sensor_msgs mav_msgs_rotors trajectory_msgs
)

catkin_package(
  INCLUDE_DIRS include ${Eigen_INCLUDE_DIRS}
  CATKIN_DEPENDS message_runtime geometry_msgs sensor_msgs mav_msgs_rotors trajectory_msgs
)
