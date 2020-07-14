Aerostack includes a behavior-based execution system that helps simplify the configuration of robots' mission plans. Each behavior is implemented as a separate process (see [[how to program a new process]]) that uses the class BehaviorProcess that, in its turn, is subclass of [[the class RobotProcess]].

## Steps to create a new behavior

#### Step 1. Create a new package and change the directory structure
The name of the package should be  `behavior_<name>`. As an example, the package for the behavior `TAKE_OFF` is called `behavior_take_off`.

Then, the structure of the package created has to be like the following lines:
```
behavior_take_off/                     -- Name of the package
      CMakeLists.txt                   -- CMakeLists.txt file
      package.xml                      -- Package manifest
      launch/
        my_process_process.launch      -- Launcher
      src/
        include/
          behavior_take_off.h          -- Header file
        source/
          behavior_take_off.cpp        -- C++ file
          behavior_take_off_main.cpp   -- C++ main file
```
As you can see, there is a directory called ```launch``` which contains a file with topics names or other parameters. You can find an example of this file at the end of this tutorial.

#### Step 2. Edit the files CMakeLists and package.xml

In order to develop a new behavior, the class `BehaviorProcess` must be inherited. To inherit the class in C++, the file `CMakeLists.txt` and `package.xml` must have the following lines:

**File** ***CMakeLists.txt***
```
find_package(catkin REQUIRED
COMPONENTS
roscpp
behavior_process
droneMsgsROS
)

catkin_package(
INCLUDE_DIRS ${BEHAVIOR_TAKE_OFF_INCLUDE_DIR}
CATKIN_DEPENDS
roscpp
behavior_process
droneMsgsROS
)
```

**File** ***package.xml***
```xml
<build_depend>behavior_process</build_depend>
<build_depend>droneMsgsROS</build_depend>

<run_depend>behavior_process</run_depend>
<run_depend>droneMsgsROS</run_depend>
```
You can find an example of the ```package.xml``` and ```CMakeLists.txt``` files at the end of the tutorial.

#### Step 3. Create the header and implementation files

To use the class BehaviorProcess the header file needs to have the following structure:

```c++
class BehaviorTakeOff : public BehaviorProcess
{
...
};
```

Then, the following functions should be implemented:

```c++
private: //BehaviorProcess
void ownSetUp();
void ownStart();
void ownRun();
void ownStop();
std::tuple<bool, std::string> ownCheckSituation();
```
These functions give a behavior the ability to:

- Prepare the execution (set up)

- Start the execution (start)

- Stop the execution (stop)

- Supervise the execution (run)

- Verify if the behavior can be executed in that situation (check situation)

#### Step 4. Include the behavior in the catalog

The behavior catalog is the file`behavior_catalog.yaml`. The catalog includes information about each behavior to describe how to use it. This information includes the allowable arguments of each behavior, the compatibility with other behaviors, etc.

It is important to include the the information of a new behavior in the catalog in order to be able to check its format and to coordinate its execution with the execution of other behaviors.

There are some important aspects to consider in this file:

- NO tabs should be used. Spaces are used instead (two spaces).

- Capabilities represent a group of processes that need to be activated before the behavior starts.

- Incompatibilities represent inconsistencies among behaviors.

Some examples of the behavior catalog: 
 
- An example of a behavior with no capabilities associated and no incompatibilities is written in the following lines:
```yaml
- behavior: TAKE_OFF
```
- An example of a behavior with no capabilities associated and some incompatibilities is written in the following lines:
```yaml
behavior_descriptors:
  - behavior: TAKE_OFF
    incompatibilities: motion

  - behavior: LAND
    incompatibilities: motion

behavior_lists:
  - name: motion
    behaviors:
      - TAKE_OFF
      - LAND
```

- An example of a behavior with capabilities associated and some incompatibilities is written in the following lines:
```yaml
behavior_descriptors:
  - behavior: TAKE_OFF
    incompatibilities: motion

  - behavior: LAND
    incompatibilities: motion

  - behavior: GO_TO_POINT
    capabilities: TRAJECTORY

behavior_lists:
  - name: motion
    behaviors:
      - TAKE_OFF
      - LAND

capability_descriptors:
  - capability: TRAJECTORY
    process_sequence: [droneTrajectoryController]
```
**NOTE:** Every process written inside the tag process_sequence should be the name of the service that starts the process. For example, for the process `droneTrajectoryController`, the service `/droneX/droneTrajectoryController/start` has to be called. So, inside the catalog you don't have to write the whole path.

#### Step 5. Launch the behavior within Aerostack
After the behavior is described inside the catalog file, you just need to add the behavior created inside the launcher script. For that reason, go to the launchers directory and edit the script ```simulated_quadrotor_basic.sh``` (if you want to use the simulation) or ```ardrone_basic.sh``` (if you want to fly the real drone) with the following lines:
```bash
`#---------------------------------------------------------------------------------------------` \
`# Behavior TakeOff                                                                            ` \
`#---------------------------------------------------------------------------------------------` \
--tab --title "Behavior TakeOff" --command "bash -c \"
roslaunch behavior_take_off behavior_take_off.launch --wait \
    drone_id_namespace:=drone$NUMID_DRONE \
    drone_id:=$NUMID_DRONE \
    my_stack_directory:=${AEROSTACK_STACK};
exec bash\"" \
```

When Aerostack is loaded, if you want to start the behavior created, just call the ROS service `activate_behavior` with the name of the behavior. An example can be found below these lines.
```bash
rosservice call /drone1/activate_behavior "behavior:            
name: 'TAKE_OFF'   
arguments: ''"   
```

One important point is the name of the behavior, it needs to be the same as the one written in the catalog and without the `behavior_`.

## Example behaviors

The following lines represents the definition file, the implementation file of a behavior, the package file and the CMakeLists file. 

header file:
```c++
#ifndef TAKE_OFF_H
#define TAKE_OFF_H

//System
#include <string>
#include <tuple>
// ROS
#include <ros/ros.h>
#include "std_srvs/Empty.h"
#include <geometry_msgs/Vector3Stamped.h>

// Aerostack msgs
#include <droneMsgsROS/BehaviorEvent.h>
#include <droneMsgsROS/dronePose.h>
#include <droneMsgsROS/droneCommand.h>
#include <droneMsgsROS/setInitDroneYaw_srv_type.h>
#include<droneMsgsROS/ConsultBelief.h>
//Aerostack libraries
#include <behavior_process.h>


class BehaviorTakeOff:public BehaviorProcess
{
  //Constructor
public:
  BehaviorTakeOff();
  ~BehaviorTakeOff();

private:
  ros::NodeHandle node_handle;

  //Congfig variables
  std::string drone_id;
  std::string drone_id_namespace;
  std::string my_stack_directory;
  std::string behavior_name_str;
  std::string estimated_pose_str;
  std::string controllers_str;
  std::string rotation_angles_str;
  std::string initialize_yaw_str;
  std::string execute_query_srv;

  //Subscriber---
  ros::Subscriber estimated_pose_sub;
  ros::Subscriber rotation_angles_sub;
  ros::Publisher controllers_pub;
  ros::ServiceClient initialize_yaw_cli;
  ros::ServiceClient query_client;
  //Message
  droneMsgsROS::dronePose estimated_pose_msg;
  droneMsgsROS::dronePose static_pose;
  geometry_msgs::Vector3Stamped rotation_angles_msg;
  //Timer staticity_timer;
  bool first_position;
  bool is_finished;

private: //BehaviorProcess
  void ownSetUp();
  void ownStart();
  void ownRun();
  void ownStop();
  std::tuple<bool, std::string> ownCheckSituation();

private:
  void endingImplementation();
  bool monitor();

public: //Callbacks
  void estimatedPoseCallBack(const droneMsgsROS::dronePose&);
  void rotationAnglesCallback(const geometry_msgs::Vector3Stamped&);
};


#endif
```


And for the implementation file:
```c++
#include "../include/behavior_take_off.h"

BehaviorTakeOff::BehaviorTakeOff() : BehaviorProcess()
{

}

BehaviorTakeOff::~BehaviorTakeOff()
{

}


void BehaviorTakeOff::ownSetUp()
{
  node_handle.param<std::string>("drone_id", drone_id, "1");
  node_handle.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);
  node_handle.param<std::string>("my_stack_directory", my_stack_directory,
             "~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack");

  estimated_pose_str = "estimated_pose";
  node_handle.param<std::string>("controllers_topic", controllers_str, "command/high_level");
  node_handle.param<std::string>("rotation_angles_topic", rotation_angles_str, "rotation_angles");
  node_handle.param<std::string>("initialize_yaw_srv", initialize_yaw_str, 
  "droneOdometryStateEstimator/setInitDroneYaw");
  node_handle.param<std::string>("consult_belief",execute_query_srv,"consult_belief");
}

void BehaviorTakeOff::ownStart()
{
  /*Initialize topics*/
  estimated_pose_sub = node_handle.subscribe(estimated_pose_str, 1000, &BehaviorTakeOff::estimatedPoseCallBack, this);
  rotation_angles_sub = node_handle.subscribe(rotation_angles_str, 1000, &BehaviorTakeOff::rotationAnglesCallback, this);
  controllers_pub = node_handle.advertise<droneMsgsROS::droneCommand>(controllers_str, 1, true);
  initialize_yaw_cli = node_handle.serviceClient<droneMsgsROS::setInitDroneYaw_srv_type>(initialize_yaw_str);
  query_client = node_handle.serviceClient <droneMsgsROS::ConsultBelief> (execute_query_srv);

/*behavior implementation*/
  std_msgs::Header header;
  header.frame_id = "behavior_take_off";

  droneMsgsROS::droneCommand msg;
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::TAKE_OFF;
  controllers_pub.publish(msg);
  estimated_pose_msg.z = 0;
  first_position = false;
  is_finished = false;
}

void BehaviorTakeOff::ownRun()
{
  if(!is_finished){
    monitor();
  }
}

//ownRun
void BehaviorTakeOff::ownStop()
{
  std::cout << "ownStop" << std::endl;
  std_msgs::Header header;
  header.frame_id = "behavior_land";

  droneMsgsROS::droneCommand msg;
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::HOVER;
  controllers_pub.publish(msg);

  estimated_pose_sub.shutdown();
  rotation_angles_sub.shutdown();
  controllers_pub.shutdown();
  initialize_yaw_cli.shutdown();
}

std::tuple<bool,std::string> BehaviorTakeOff::ownCheckSituation()
{
  droneMsgsROS::ConsultBelief query_service;
  std::ostringstream capturador;
  capturador << "battery_level(self,LOW)";
  std::string query(capturador.str());
  query_service.request.query = query;
  query_client.call(query_service);
  if(query_service.response.success)
  {
    return std::make_tuple(false,"Error: Battery low, unable to perform action");
  }
  std::ostringstream capturador2;
  capturador2<<"flight_state(self,FLYING)";
  std::string query2(capturador2.str());
  query_service.request.query = query2;
  query_client.call(query_service);
  if(query_service.response.success)
  {
    return std::make_tuple(false,"Error: Already flying");
  }

  return std::make_tuple(true,"");
}

//Private functions
bool BehaviorTakeOff::monitor()
{
  double precision_take_off = 0.1;

  //Check achievement
  if(std::abs(std::abs(estimated_pose_msg.z) - 0.7) < precision_take_off){
    BehaviorProcess::setFinishEvent(droneMsgsROS::BehaviorEvent::GOAL_ACHIEVED);
    BehaviorProcess::setFinishConditionSatisfied(true);
    endingImplementation();
    is_finished = true;
    return true;
  }

  //Check timeout
  if(timerIsFinished()){
    BehaviorProcess::setFinishEvent(droneMsgsROS::BehaviorEvent::TIME_OUT);
    BehaviorProcess::setFinishConditionSatisfied(true);
    endingImplementation();
    is_finished = true;
    return true;
  }
  return false;
}

void BehaviorTakeOff::endingImplementation()
{
  droneMsgsROS::setInitDroneYaw_srv_type init_yaw_msg;
  init_yaw_msg.request.yaw_droneLMrT_telemetry_rad = (rotation_angles_msg.vector.z)*(M_PI/180.0);
  initialize_yaw_cli.call(init_yaw_msg);

  droneMsgsROS::droneCommand msg;
  msg.command = droneMsgsROS::droneCommand::HOVER;
  controllers_pub.publish(msg);
}

//Custom topic Callbacks
  void BehaviorTakeOff::estimatedPoseCallBack(const droneMsgsROS::dronePose& message){
  if(!first_position)
    static_pose = message;
  estimated_pose_msg = message;
}

void BehaviorTakeOff::rotationAnglesCallback(const geometry_msgs::Vector3Stamped& message){
  rotation_angles_msg = message;
}
```
Finally, the main file should look like the one below:

```c++
#include "../include/behavior_take_off.h"

int main(int argc, char** argv){
  ros::init(argc, argv, ros::this_node::getName());

  std::cout << ros::this_node::getName() << std::endl;

  BehaviorTakeOff behavior;
  behavior.setUp();
  ros::Rate rate(10);
  while(ros::ok()){
    behavior.run();
    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}
```
In order to compile and to launch the program, the following file have to be inside the behavior created.

package.xml:
```xml
<?xml version="1.0"?>
<package>
  <name> behavior_take_off </name>
  <version>0.1.0</version>
  <description>The behavior_take_off package</description>

  <author email="test@test.com">Author</author>
  <maintainer email="test@test.com">Maintainer</maintainer>

  <license>GPLv3</license>

  <!-- The *_depend tags are used to specify dependencies -->
  <!-- Dependencies can be catkin packages or system dependencies -->
  <!-- Examples: -->
  <!-- Use build_depend for packages you need at compile time: -->
  <!--   <build_depend>message_generation</build_depend> -->
  <!-- Use buildtool_depend for build tool packages: -->
  <!--   <buildtool_depend>catkin</buildtool_depend> -->
  <!-- Use run_depend for packages you need at runtime: -->
  <!--   <run_depend>message_runtime</run_depend> -->
  <!-- Use test_depend for packages you need only for testing: -->
  <!--   <test_depend>gtest</test_depend> -->
  <buildtool_depend>catkin</buildtool_depend>
  <build_depend>roscpp</build_depend>
  <build_depend>std_msgs</build_depend>
  <build_depend>drone_process</build_depend>
  <build_depend>behavior_process</build_depend>
  <build_depend>droneMsgsROS</build_depend>
  <build_depend>geometry_msgs</build_depend>

  <run_depend>roscpp</run_depend>
  <run_depend>std_msgs</run_depend>
  <run_depend>drone_process</run_depend>
  <run_depend>behavior_process</run_depend>
  <run_depend>droneMsgsROS</run_depend>
  <run_depend>geometry_msgs</run_depend>

  <!-- The export tag contains other, unspecified, tags -->
  <export>
    <!-- Other tools can request additional information be placed here -->

  </export>
</package>
```

CMakeLists.txt:
```
cmake_minimum_required(VERSION 2.8.3)
project(behavior_take_off)

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
add_definitions(-std=c++11)

# Directories definition
set(BEHAVIOR_TAKE_OFF_SOURCE_DIR
  src/source
)
	
set(BEHAVIOR_TAKE_OFF_INCLUDE_DIR
  src/include
) 

# Files declaration
set(BEHAVIOR_TAKE_OFF_SOURCE_FILES
  ${BEHAVIOR_TAKE_OFF_SOURCE_DIR}/behavior_take_off.cpp
  ${BEHAVIOR_TAKE_OFF_SOURCE_DIR}/behavior_take_off_main.cpp
)

set(BEHAVIOR_TAKE_OFF_HEADER_FILES
  ${BEHAVIOR_TAKE_OFF_INCLUDE_DIR}/behavior_take_off.h
)

### Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  COMPONENTS 
  roscpp 
  std_msgs
  behavior_process
  droneMsgsROS
  geometry_msgs
)

###################################
## catkin specific configuration ##
###################################
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS ${BEHAVIOR_TAKE_OFF_INCLUDE_DIR}
  CATKIN_DEPENDS
  roscpp 
  std_msgs
  drone_process
  behavior_process
  droneMsgsROS
  geometry_msgs
)

###########
## Build ##
###########			       	     
include_directories(
  ${BEHAVIOR_TAKE_OFF_INCLUDE_DIR}
  ${BEHAVIOR_TAKE_OFF_SOURCE_DIR}
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(behavior_take_off_lib ${BEHAVIOR_TAKE_OFF_SOURCE_FILES} ${BEHAVIOR_TAKE_OFF_HEADER_FILES})
add_dependencies(behavior_take_off_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(behavior_take_off_lib ${catkin_LIBRARIES})

add_executable(behavior_take_off ${BEHAVIOR_TAKE_OFF_SOURCE_DIR}/behavior_take_off_main.cpp)
add_dependencies(behavior_take_off ${catkin_EXPORTED_TARGETS})
target_link_libraries(behavior_take_off behavior_take_off_lib)
target_link_libraries(behavior_take_off ${catkin_LIBRARIES})
```

behavior_take_off.launch:
```xml
<!-- Launches: behavior_take_off -->
<launch>

  <!-- Basic data -->
  <arg name="drone_id_namespace"                    default="drone1" />
  <arg name="drone_id"                              default="1" />
  <arg name="my_stack_directory"                    default="$(env AEROSTACK_STACK)" />
  <arg name="behavior_name"                         default="TAKE_OFF" />
  <arg name="behavior_mode"                         default="" />

  <!-- Custom topics & services-->
  <arg name="estimated_pose_topic"               default="estimated_pose" />
  <arg name="controllers_topic"                     default="command/high_level" />
  <arg name="rotation_angles_topic"                 default="rotation_angles" />
  <arg name="initialize_yaw_srv"                    default="droneOdometryStateEstimator/setInitDroneYaw"/>
  <arg name="consult_belief"                         default="consult_belief"/>

  <group ns="$(arg drone_id_namespace)">

    <!-- Basic data -->
    <param name="~drone_id_namespace"                    value="$(arg drone_id_namespace)" type="str" />
    <param name="~drone_id"                              value="$(arg drone_id)" type="str" />
    <param name="~my_stack_directory"                    value="$(arg my_stack_directory)" type="str" />
    <param name="~behavior_name"                         value="$(arg behavior_name)" type="str" />
    <param name="~behavior_mode"                         value="$(arg behavior_mode)" type="str" />

    <!-- Custom topics & services -->
    <param name="~estimated_pose_topic"                  value="$(arg estimated_pose_topic)" type="str" />
    <param name="~controllers_topic"                     value="$(arg controllers_topic)" type="str" />
    <param name="~rotation_angles_topic"                 value="$(arg rotation_angles_topic)" type="str" />
    <param name="~initialize_yaw_srv"                    value="$(arg initialize_yaw_srv) " type="str"/>
    <param name="~consult_belief"                         value="$(arg consult_belief) " type="str"/>

    <node name="behavior_take_off" pkg="behavior_take_off" type="behavior_take_off" output="screen"/>

    <!--<test test-name="SequencerTest" pkg="behavior_take_off" type="SequencerTest"/>-->

  </group>

</launch>
```