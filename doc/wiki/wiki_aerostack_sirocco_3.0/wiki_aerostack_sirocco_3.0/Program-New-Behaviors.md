
Aerostack includes a behavior-based execution system that simplifies the configuration of robot mission plans. Each behavior is implemented as a [nodelet](http://wiki.ros.org/nodelet) inside a behavior system that groups behaviors with common uses. Those behaviors are also a subclass of BehaviorExecutionController class.

## Steps to create a new behavior

#### Step 1. Create a new package for the behavior system and change the directory structure
The name of the package should be  the name of the behavior system. As an example, the system  for the behavior `TAKE_OFF`, and therefore the package,  is called ` basic_quadrotor_behaviors`.

Then, the structure of the package created has to be like the following lines:
```
basic_cuadrotor_behaviors/             -- Name of the package
      CMakeLists.txt                   -- CMakeLists.txt file
      package.xml                      -- Package manifest
      basic_quadrotor_behaviors.xml    -- File to define the nodelets as a plugin
      launch/
        basic_quadrotor_behaviors.launch   -- Launcher
      src/
        include/
          behavior_take_off.h          -- Header file
        source/
          behavior_take_off.cpp        -- C++ file

```
#### Step 2. Edit the files CMakeLists and package.xml

In order to develop a new behavior, the class `BehaviorExecutionController` must be inherited, as well as the `Nodelet` class  . To inherit the class in C++, the file `CMakeLists.txt` and `package.xml` must have the following lines:

**File** ***CMakeLists.txt***
```
find_package(catkin REQUIRED
COMPONENTS
roscpp
behavior_execution_controller
nodelet
aerostack_msgs
geometry_msgs
std_msgs
)

catkin_package(
INCLUDE_DIRS ${BEHAVIOR_TAKE_OFF_INCLUDE_DIR}
CATKIN_DEPENDS
roscpp
behavior_execution_controller
nodelet
aerostack_msgs
geometry_msgs
std_msgs
)
```

**File** ***package.xml***
```xml
<build_depend>roscpp</build_depend>
<build_depend>behavior_execution_controller</build_depend>
<build_depend>nodelet</build_depend>
<build_depend>aerostack_msgs</build_depend>
<build_depend>geometry_msgs</build_depend>
<build_depend>std_msgs</build_depend>

<run_depend>roscpp</run_depend>
<run_depend>behavior_execution_controller</run_depend>
<run_depend>nodelet</run_depend>
<run_depend>aerostack_msgs</run_depend>
<run_depend>geometry_msgs</run_depend>
<run_depend>std_msgs</run_depend>
```
It is also important to include the <export> tag to specify the xml file used to export the nodelets:
```xml
<export>

<nodelet  plugin="${prefix}/basic_quadrotor_behaviors.xml"  />

</export>
```
You can find an example of the ```package.xml``` and ```CMakeLists.txt``` files at the end of the tutorial.

#### Step 3. Edit the <package_name>.launch file

As you can see, there is a directory called `launch` which contains a file with the definition of topics names or other parameters. It is important to include the following line  in each behavior system to launch its nodelet manager:

```xml
<node  pkg="nodelet"  type="nodelet"  args="manager"  name="basic_quadrotor_behaviors_manager"  output="screen" />
```
And also include a line like the following one for each behavior in the behavior system:

```xml
<node  pkg="nodelet"  type="nodelet"  args="load basic_quadrotor_behaviors/BehaviorTakeOff basic_quadrotor_behaviors_manager" name="behavior_take_off"  output="screen"/>
```
You can find an example of the ```basic_quadrotor_behaviors.launch``` file at the end of the tutorial.

#### Step 4.  Edit the <package_name>.xml file

Now we have to edit  the <package_name>.xml file to correctly define the nodelet as a plugin. To do so, in the first line indicate the library to which the plugin will be exported:
```xml
<library  path="lib/libbasic_quadrotor_behaviors">
```
Then include a <class> tag  with the following format for each behavior included in the system :
```xml
<class  name="basic_quadrotor_behaviors/BehaviorTakeOff"  type="basic_quadrotor_behaviors::BehaviorTakeOff"
base_class_type="nodelet::Nodelet">
    <description>
      BehaviorTakeOff.
    </description>
</class>
```

#### Step 5. Create the header and implementation files

To use the class BehaviorExecutionController the header file needs to have the following structure, using as namespace the name of the behavior system:

```c++
#include <behavior_execution_controller.h>
namespace  basic_quadrotor_behaviors
{
class  BehaviorTakeOff : public  BehaviorExecutionController
{
(...)
};
}
```
Then, the following functions should be implemented:

```c++
private:
// BehaviorExecutionController
void  onConfigure();
void  onActivate();
void  onDeactivate();
void  onExecute();
bool  checkSituation();
void  checkGoal();
void  checkProgress();
void  checkProcesses();
```
These functions give a behavior the ability to:

- Prepare the execution (onConfigure)
- Start the execution (onActivate)
- Stop the execution (onDeactivate)
- Develop the execution (onExecute)
- Verify if the behavior can be executed in that situation (checkSituation)
- Verify if the behavior has achieved its goal (checkGoal)
- Supervise the progress of the  execution (checkProgress)
- Supervise the state of the  necessary processes (checkProcesses)

The implementation file must include the following line to export the class to the nodelet manager:
```c++
PLUGINLIB_EXPORT_CLASS(basic_quadrotor_behaviors::BehaviorTakeOff, nodelet::Nodelet)
```

#### Step 6. Include the behavior in the catalog

The behavior catalog is the file`behavior_catalog.yaml`. The catalog includes information about each behavior to describe how to use it. This information includes the allowable arguments of each behavior, the compatibility with other behaviors, etc.

It is important to include the the information of a new behavior in the catalog in order to be able to check its format and to coordinate its execution with the execution of other behaviors.

There are some important aspects to consider in this file:

- NO tabs should be used. Spaces are used instead (two spaces).
- The `default_values` tag indicates values to be used when no explicit specification for the parameter is found.
- There are two categories of behaviors: goal_based and recurrent.
- Incompatibilities represent inconsistencies among behaviors.
- Precedences  represent behaviors that a requirement to carry out the activation.
- It is necessary to indicate the behavior system each behavior belongs to.
- It is possible to specify a timeout for the execution of the  behavior.
- If a behavior is specified as default, it will continuously be intended to be activated with low priority

Here there is an example of  behavior catalog: 

```yaml
#------------------------------------------------------
# Default values for behavior attributes.
#------------------------------------------------------
default_values:
  category: goal_based
  default: no
  timeout: 15
#------------------------------------------------------
# LIST OF BEHAVIOR DESCRIPTORS
#------------------------------------------------------
behavior_descriptors:
#------------------------------------------------------
# LOCALIZE_WITH_ODOMETRY
#------------------------------------------------------
- behavior: LOCALIZE_WITH_ODOMETRY
   category: recurrent
   default: yes
   system: basic_quadrotor_behaviors
#------------------------------------------------------
# TAKE_OFF
#------------------------------------------------------
- behavior: TAKE_OFF
    system: basic_quadrotor_behaviors
#------------------------------------------------------
# LAND
#------------------------------------------------------
- behavior: LAND
    system: basic_quadrotor_behaviors
#------------------------------------------------------
# PRECEDENCE CONSTRAINTS
#------------------------------------------------------
precedence_constraints:
- active:
  - LOCALIZE_WITH_ODOMETRY
  before:
  - TAKE_OFF
  - LAND
#------------------------------------------------------
# EXCLUSIVITY CONSTRAINTS
#------------------------------------------------------
exclusivity_constraints:
#------------------------------------------------------
# Motion behaviors are mutually exclusive
#------------------------------------------------------
- mutually_exclusive:
  - TAKE_OFF
  - LAND
```
#### Step 7. Launch the behavior within Aerostack
After the behavior is included  in the catalog file, you just need to add the  created behavior system  inside the launcher script. In your launcher include (following the example with `basic_quadrotor_behaviors`) the next lines:
```bash
`#---------------------------------------------------------------------------------------------` \
`# Basic Quadrotor Behaviors                                                                   ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Basic Quadrotor Behaviors" --command "bash -c \"
roslaunch basic_quadrotor_behaviors basic_quadrotor_behaviors.launch --wait \
  namespace:=drone$NUMID_DRONE \
  my_stack_directory:=${AEROSTACK_STACK};
exec bash\""\
```

When Aerostack is loaded, if you want to start the behavior created, just call the ROS service `request_behavior_activation` with the name of the behavior. An example can be found below these lines.
```bash
rosservice call /drone1/request_behavior_activation "behavior:            
name: 'TAKE_OFF'   
arguments: ''  
priority: 2"   
```

## Example 

As an example, we include all the  files  necessary for the execution of the  behavior `TAKE_OFF`: 

- behavior_take_off.h:
```c++

#ifndef TAKE_OFF_H
#define TAKE_OFF_H

// System
#include <string>
#include <thread>
#include <tuple>
// ROS
#include "std_srvs/Empty.h"
#include <geometry_msgs/Vector3Stamped.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>

// Aerostack msgs
#include <aerostack_msgs/BehaviorActivationFinished.h>
#include <droneMsgsROS/ConsultBelief.h>
#include <droneMsgsROS/droneCommand.h>
#include <droneMsgsROS/setInitDroneYaw_srv_type.h>
#include <geometry_msgs/PoseStamped.h>
// Aerostack libraries
#include <behavior_execution_controller.h>

namespace basic_quadrotor_behaviors
{
class BehaviorTakeOff : public BehaviorExecutionController
{
  // Constructor
public:
  BehaviorTakeOff();
  ~BehaviorTakeOff();

private:
  // ros::NodeHandle node_handle;

  // Congfig variables
  std::string estimated_pose_str;
  std::string controllers_str;
  std::string rotation_angles_str;
  std::string initialize_yaw_str;
  std::string execute_query_srv;

  // Communication variables
  ros::Subscriber estimated_pose_sub;
  ros::Subscriber rotation_angles_sub;
  ros::Publisher controllers_pub;
  ros::ServiceClient initialize_yaw_cli;
  ros::ServiceClient query_client;

  // Messages
  geometry_msgs::PoseStamped estimated_pose_msg;
  geometry_msgs::Vector3Stamped rotation_angles_msg;

  // Timer staticity_timer;
  bool first_position;

private:
  // BehaviorExecutionController
  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();



public: // Callbacks
  void estimatedPoseCallBack(const geometry_msgs::PoseStamped &);
  void rotationAnglesCallback(const geometry_msgs::Vector3Stamped &);
};
}

#endif
```
 - behavior_take_off.cpp:
```c++

#include "../include/behavior_take_off.h"
#include <pluginlib/class_list_macros.h>

namespace basic_quadrotor_behaviors
{
BehaviorTakeOff::BehaviorTakeOff() : BehaviorExecutionController() 
{ 
  setName("take_off"); 
}

BehaviorTakeOff::~BehaviorTakeOff() {}

void BehaviorTakeOff::onConfigure()
{ 
  ros::NodeHandle nh = getNodeHandle();
  nh.param<std::string>("estimated_pose_topic", estimated_pose_str, "self_localization/pose");
  nh.param<std::string>("controllers_topic", controllers_str, "command/high_level");
  nh.param<std::string>("rotation_angles_topic", rotation_angles_str, "rotation_angles");
  nh.param<std::string>("initialize_yaw_srv", initialize_yaw_str,
                                 "droneOdometryStateEstimator/setInitDroneYaw");
  nh.param<std::string>("consult_belief", execute_query_srv, "consult_belief");
  query_client = nh.serviceClient<droneMsgsROS::ConsultBelief>(execute_query_srv);
}

void BehaviorTakeOff::onActivate()
{
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace(); 
  // Activate communications
  estimated_pose_sub = nh.subscribe("/" + nspace + "/" + estimated_pose_str, 1000,
                                             &BehaviorTakeOff::estimatedPoseCallBack, this);
  rotation_angles_sub = nh.subscribe("/" + nspace + "/" + rotation_angles_str, 1000,
                                              &BehaviorTakeOff::rotationAnglesCallback, this);
  initialize_yaw_cli =
      nh.serviceClient<droneMsgsROS::setInitDroneYaw_srv_type>("/" + nspace + "/" + initialize_yaw_str);
  controllers_pub = nh.advertise<droneMsgsROS::droneCommand>("/" + nspace + "/" + controllers_str, 1, true);

  // Behavior implementation
  std_msgs::Header header;
  header.frame_id = "behavior_take_off";

  droneMsgsROS::droneCommand msg;
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::TAKE_OFF;
  controllers_pub.publish(msg);
  estimated_pose_msg.pose.position.z = 0;
  first_position = false;
}

void BehaviorTakeOff::onDeactivate()
{
  std_msgs::Header header;
  header.frame_id = "behavior_take_off";

  droneMsgsROS::droneCommand msg;
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::HOVER;

  controllers_pub.publish(msg);

  estimated_pose_sub.shutdown();
  rotation_angles_sub.shutdown();
  controllers_pub.shutdown();
  initialize_yaw_cli.shutdown();
}

void BehaviorTakeOff::onExecute()
{
  
}

bool BehaviorTakeOff::checkSituation()
{
  droneMsgsROS::ConsultBelief query_service;
  std::ostringstream capturador;
  capturador << "battery_level(self,LOW)";
  std::string query(capturador.str());
  query_service.request.query = query;
  query_client.call(query_service);
  if (query_service.response.success)
  {
    setErrorMessage("Error: Battery low, unable to perform action");
    return false;
  }
  std::ostringstream capturador2;
  capturador2 << "flight_state(self,FLYING)";
  std::string query2(capturador2.str());
  query_service.request.query = query2;
  query_client.call(query_service);
  if (query_service.response.success)
  {
    setErrorMessage("Error: Already flying");
    return false;
  }

  return true;
}

void BehaviorTakeOff::checkGoal()
{
  double precision_take_off = 0.1;
  // Check achievement
  if (std::abs(std::abs(estimated_pose_msg.pose.position.z) - 0.7) < precision_take_off)
  {
    BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::GOAL_ACHIEVED);
    droneMsgsROS::setInitDroneYaw_srv_type init_yaw_msg;
    init_yaw_msg.request.yaw_droneLMrT_telemetry_rad = (rotation_angles_msg.vector.z) * (M_PI / 180.0);
    initialize_yaw_cli.call(init_yaw_msg);

    droneMsgsROS::droneCommand msg;
    msg.command = droneMsgsROS::droneCommand::HOVER;
    controllers_pub.publish(msg);

  }

}

void BehaviorTakeOff::checkProgress() 
{ 
 
}


void BehaviorTakeOff::checkProcesses() 
{ 
 
}

// Custom topic Callbacks
void BehaviorTakeOff::estimatedPoseCallBack(const geometry_msgs::PoseStamped &message)
{
  if (!first_position)

    estimated_pose_msg = message;
}

void BehaviorTakeOff::rotationAnglesCallback(const geometry_msgs::Vector3Stamped &message)
{
  rotation_angles_msg = message;
}
}
PLUGINLIB_EXPORT_CLASS(basic_quadrotor_behaviors::BehaviorTakeOff, nodelet::Nodelet)
```
 - package.xml:
```xml
<?xml  version="1.0"?>
<package>
<name>basic_quadrotor_behaviors</name>
<version>0.1.0</version>
<description>Basic quadrotor system of behaviors</description>
<maintainer  email="abraham.carreragrob@alumnos.upm.es">Abraham Carrera Groba</maintainer>

<license>BSD-3</license>

<buildtool_depend>catkin</buildtool_depend>
<build_depend>roscpp</build_depend>
<build_depend>nodelet</build_depend>
<build_depend>std_msgs</build_depend>
<build_depend>drone_process</build_depend>
<build_depend>yaml-cpp</build_depend>
<build_depend>behavior_execution_controller</build_depend>
<build_depend>droneMsgsROS</build_depend>
<build_depend>geometry_msgs</build_depend>
<build_depend>aerostack_msgs</build_depend>

<run_depend>roscpp</run_depend>
<run_depend>nodelet</run_depend>
<run_depend>std_msgs</run_depend>
<run_depend>drone_process</run_depend>
<run_depend>behavior_execution_controller</run_depend>
<run_depend>droneMsgsROS</run_depend>
<run_depend>geometry_msgs</run_depend>
<run_depend>yaml-cpp</run_depend>
<run_depend>aerostack_msgs</run_depend>

<export>
<nodelet  plugin="${prefix}/basic_quadrotor_behaviors.xml"  />

</export>
</package>
```

 - CMakeLists.txt:
```
cmake_minimum_required(VERSION 2.8.3)
project(basic_quadrotor_behaviors)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directories definition
set(BASIC_QUADROTOR_BEHAVIORS_SOURCE_DIR
  src/source
)

set(BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR
  src/include
)

set(BASIC_QUADROTOR_BEHAVIORS_HEADER_FILES
        ${BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR}/behavior_take_off.h
        ${BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR}/behavior_localize_with_odometry.h
        ${BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR}/behavior_land.h
        ${BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR}/behavior_wait.h
)

set(BASIC_QUADROTOR_BEHAVIORS_SOURCE_FILES
        ${BASIC_QUADROTOR_BEHAVIORS_SOURCE_DIR}/behavior_take_off.cpp
        ${BASIC_QUADROTOR_BEHAVIORS_SOURCE_DIR}/behavior_localize_with_odometry.cpp
        ${BASIC_QUADROTOR_BEHAVIORS_SOURCE_DIR}/behavior_land.cpp
        ${BASIC_QUADROTOR_BEHAVIORS_SOURCE_DIR}/behavior_wait.cpp
)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  nodelet
  std_msgs
  behavior_execution_controller
  droneMsgsROS
  geometry_msgs
  aerostack_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ${BASIC_QUADROTOR_BEHAVIORS_INCLUDE_DIR}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS 
  roscpp 
  nodelet
  std_msgs
  drone_process
  behavior_execution_controller
  droneMsgsROS
  geometry_msgs
  aerostack_msgs
  DEPENDS yaml-cpp
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(basic_quadrotor_behaviors
  src/source/behavior_take_off.cpp
  src/source/behavior_localize_with_odometry.cpp
  src/source/behavior_land.cpp
  src/source/behavior_wait.cpp
)
target_link_libraries(basic_quadrotor_behaviors ${catkin_LIBRARIES})
target_link_libraries(basic_quadrotor_behaviors yaml-cpp)
if(catkin_EXPORTED_LIBRARIES)
  add_dependencies(basic_quadrotor_behaviors ${catkin_EXPORTED_LIBRARIES})
endif()
```
 - basic_quadrotor_behaviors.xml:
```xml

<library path="lib/libbasic_quadrotor_behaviors">
	<class name="basic_quadrotor_behaviors/BehaviorTakeOff" type="basic_quadrotor_behaviors::BehaviorTakeOff"
		base_class_type="nodelet::Nodelet">
		<description>
			BehaviorTakeOff.
		</description>
	</class>
        <class name="basic_quadrotor_behaviors/BehaviorLocalizeWithOdometry" type="basic_quadrotor_behaviors::BehaviorLocalizeWithOdometry"
		base_class_type="nodelet::Nodelet">
		<description>
			BehaviorLocalizeWithOdometry.
		</description>
	</class>
        <class name="basic_quadrotor_behaviors/BehaviorLand" type="basic_quadrotor_behaviors::BehaviorLand"
		base_class_type="nodelet::Nodelet">
		<description>
			BehaviorLand.
		</description>
	</class>
        <class name="basic_quadrotor_behaviors/BehaviorWait" type="basic_quadrotor_behaviors::BehaviorWait"
		base_class_type="nodelet::Nodelet">
		<description>
			BehaviorWait.
		</description>
	</class>
</library>

```
 - basic_quadrotor_behaviors.launch:
```xml
<launch>
    <arg name="namespace"                          default="drone1" />
    <arg name="activate_behavior_srv"              default="activate_behavior" />
    <arg name="deactivate_behavior_srv"            default="deactivate_behavior" />
    <arg name="check_activation_conditions_srv"    default="check_activation_conditions" />
    <arg name="activation_finished_topic"          default="behavior_activation_finished" />
    <arg name="estimated_pose_topic"               default="self_localization/pose" />
    <arg name="controllers_topic"                  default="command/high_level" />
    <arg name="rotation_angles_topic"              default="rotation_angles" />
    <arg name="initialize_yaw_srv"                 default="droneOdometryStateEstimator/setInitDroneYaw" />
    <arg name="consult_belief"                     default="consult_belief" />
    <arg name="behavior_system"                    default="basic_quadrotor_behaviors" />
    <arg name="odometry_str"                       default="change_self_localization_mode_to_odometry" />
   <group ns="$(arg namespace)/$(arg behavior_system)">
	     <param name="~namespace"                           value="$(arg namespace)"                          type="str" />
             <param name="~activate_behavior_srv"               value="$(arg activate_behavior_srv)"              type="str" />
             <param name="~deactivate_behavior_srv"             value="$(arg deactivate_behavior_srv)"            type="str" />
             <param name="~check_activation_conditions_srv"     value="$(arg check_activation_conditions_srv)"    type="str" />
	     <param name="~estimated_pose_topic"                value="$(arg estimated_pose_topic)"               type="str" />
             <param name="~controllers_topic"                   value="$(arg controllers_topic)"                  type="str" />
             <param name="~rotation_angles_topic"               value="$(arg rotation_angles_topic)"              type="str" />
             <param name="~initialize_yaw_srv"                  value="$(arg initialize_yaw_srv)"                 type="str" />
             <param name="~consult_belief"                      value="$(arg consult_belief)"                     type="str" />
             <param name="~behavior_system"                     value="$(arg behavior_system)"                    type="str" />
             <param name="~odometry_str"                        value="$(arg odometry_str)"                       type="str" /> 
            
       <node pkg="nodelet" type="nodelet" args="manager" name="basic_quadrotor_behaviors_manager" output="screen" />
       <node pkg="nodelet" type="nodelet" args="load basic_quadrotor_behaviors/BehaviorTakeOff basic_quadrotor_behaviors_manager"
        name="behavior_take_off" output="screen"/>
       <node pkg="nodelet" type="nodelet" args="load basic_quadrotor_behaviors/BehaviorLocalizeWithOdometry basic_quadrotor_behaviors_manager"
        name="behavior_localize_with_odometry" output="screen"/>
       <node pkg="nodelet" type="nodelet" args="load basic_quadrotor_behaviors/BehaviorLand basic_quadrotor_behaviors_manager"
        name="behavior_land" output="screen"/>
       <node pkg="nodelet" type="nodelet" args="load basic_quadrotor_behaviors/BehaviorWait basic_quadrotor_behaviors_manager"
        name="behavior_wait" output="screen"/>
              
  </group>
</launch>
```