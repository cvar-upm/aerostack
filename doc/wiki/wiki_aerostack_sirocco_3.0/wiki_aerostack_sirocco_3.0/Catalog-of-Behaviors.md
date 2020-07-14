This catalog shows the available behaviors provided by Aerostack. They are presented according to different categories: 

- [Basic motion behaviors:](#basic-motion-behaviors)
  * [TAKE_OFF](#behavior-take_off)
  * [LAND](#behavior-land)   
  * [WAIT](#behavior-wait)  
- [Behaviors using motion controllers:](#behaviors-using-motion-controllers)
  * [KEEP_HOVERING_WITH_PID_CONTROL](#behavior-keep_hovering_with_pid_control)
  * [KEEP_MOVING_WITH_PID_CONTROL](#behavior-keep_moving_with_pid_control)
  * [ROTATE_WITH_PID_CONTROL](#behavior-rotate_with_pid_control)
  * [FOLLOW_PATH_WITH_PID_CONTROL](#behavior-follow_path_with_pid_control)
- [Navigation behaviors:](#navigation-behaviors)
  * [GENERATE_PATH_WITH_OCCUPANCY_GRID](#behavior-generate_path_with_occupancy_grid)
  * [GO_TO_POINT_WITH_OCCUPANCY_GRID](#behavior-go_to_point_with_occupancy_grid)
- [Behaviors for attention control:](#behaviors-for-attention-control)
  * [PAY_ATTENTION_TO_QR_CODE](#behavior-pay_attention_to_qr_code)
  * [PAY_ATTENTION_TO_ROBOT_MESSAGES](#behavior-pay_attention_to_robot_messages)
- [Behaviors for self localization:](#behaviors-for-self-localization)
  * [SELF_LOCALIZE_BY_ODOMETRY](#behavior-self_localize_by_odometry)
  * [SELF_LOCALIZE_AND_MAP_WITH_LIDAR](#behavior-self_localize_and_map_with_lidar)
- [Behaviors for communication:](#behaviors-for-communication)
  * [INFORM_OPERATOR](#behavior-inform_operator)
  * [INFORM_ROBOTS](#behavior-inform_robots)
  * [REQUEST_OPERATOR_ASSISTANCE](#behavior-request_operator_assistance)

It is important to note that there are two types of behaviors: 

- **Goal-based behaviors**. These behaviors are defined to reach a final state (attain a goal). For example, the behavior TAKE_OFF ends when the drone has reached a certain height. 

- **Recurrent behaviors**. These behaviors perform an activity recurrently or maintain a desired state (for example, the behavior PAY_ATTENTION_TO_QR_CODE).

You can consult the following link to know how to add your own behaviors:

- [[Program new behaviors]]

# **Basic motion behaviors**

## Behavior `TAKE_OFF`

**Description:** The robot takes off vertically from a static surface. This behavior ends when the robot reaches a default altitude.

**Type:** Goal-based behavior.

## Behavior `LAND`

**Description:** The robot lands vertically in the current position. This behavior assumes that the ground is static.

**Type:** Goal-based behavior.

## Behavior `WAIT`

**Description:** The robot waits until a certain condition is satisfied (e.g., duration). 

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| duration| number(seconds) | duration: 30 |			


# **Behaviors using motion controllers**

## Behavior `KEEP_HOVERING_WITH_PID_CONTROL`

**Description:** The robot keeps hovering. Hovering is a maneuver in which the robot is maintained in nearly motionless flight over a reference point at a constant altitude and on a constant heading. This behavior does not avoid moving obstacles. 

**Type:** Recurrent behavior.

## Behavior `KEEP_MOVING_WITH_PID_CONTROL`

**Description:** The robot keeps moving at a constant speed in some direction (forward, backward, left,right). If the speed value is not given a default value is considered. This behavior does not avoid obstacles. 

**Type:** Recurrent behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| direction |{FORWARD, BACKWARD, LEFT, RIGHT}|direction: FORWARD |			
| speed |number (m/sec)|speed: 12|

## Behavior `ROTATE_WITH_PID_CONTROL`

**Description:** The robot rotates left or right a certain number of degrees (angle) on the vertical axis (yaw). The number of degrees can be expressed as an absolute value (argument “angle”) or relative to the robot (argument “relative_angle”).

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|			
| angle |number (degrees)|angle: 90|
| relative_angle |number (degrees)|relative_angle: 90|

## Behavior `FOLLOW_PATH_WITH_PID_CONTROL`

**Description:** The robot tries to follow a path that is defined as a sequence of points. The robot assumes that there are not moving or unknown obstacles.

**Type:** Goal-based behavior. 	

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| path: |sequence of 3D points (x,y,z) in meters| path: [ [1.1,1.1,0.7], [2.2,2.2,0.7], [3.3,3.3,2.5] ]|


# **Navigation behaviors**

## Behavior `GENERATE_PATH_WITH_OCCUPANCY_GRID`

**Description:** This behavior generates a path free of obstacles between the current position of the robot and the given destination. This behavior uses a representation of the environment as an occupancy grid. The result of this task is stored in the belief memory in the predicates: object(X, path) and path(X, Y), where Y is a list of 3D points. For example: object(32, path), path(32, ((1.1,1.1,0.7), (2.2,2.2,0.7), (3.3,3.3,0.7))). Note that the height value of each point (z value) is a constant value because the path is planned on a horizontal surface.

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| destination | Tuple of 3 numbers x, y, z (meters)| destination: [3.3,3.3,3.3]|


**Note:** This behavior is especially useful when used in companion with the Behavior SELF_LOCALIZE_AND_MAP_WITH_LIDAR


## Behavior `GO_TO_POINT_WITH_OCCUPANCY_GRID`

**Description:** The robot goes to a destination point avoiding obstacles. The point can be expressed in absolute coordinates (argument “coordinates”) or coordinates relative to the robot (argument “relative coordinates”). To reach the target point, the robot vertically changes the altitude to be at the same altitude as the target point and, then, follows a two-dimensional (2D) movement in the horizontal plane avoiding existing obstacles. During the movement, the robot can dynamically change the planned path if a new obstacle (e.g., another robot) is detected.

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| coordinates |Tuple of 3 numbers x, y, z (meters)|coordinates: [1.23, 2, 0.5]|	
| relative_coordinates |Tuple of 3 numbers x, y, z (meters)|relative_coordinates: [1.23, 2, 0.5]|
 

# **Behaviors for attention control**

## Behavior `PAY_ATTENTION_TO_QR_CODE`

**Description:** The robot pays attention to QR codes. Each recognized code is stored as a belief with the following format: object(X, qr_code), code(X, Y), visible(X) where X is the object identifier (generated automatically) and Y is the recognized QR code (string). The predicate visible(X) is deleted when the QR code is not observed. We assume that the objects with QR codes are static (they don't move in the environment). We assume that there are not different objects with the same QR code.

**Type:** Recurrent behavior.

## Behavior `PAY_ATTENTION_TO_ROBOT_MESSAGES`

**Description**: This behavior pays attention to messages sent by other robots. When the name of the message's receiver is the name of the own robot, the message is added to the belief memory. Each message must be written as a logic predicate according to the format of the belief memory.

**Type:** Recurrent behavior

# **Behaviors for self localization**

## Behavior `SELF_LOCALIZE_BY_ODOMETRY`

**Description:** The robot self localizes using odometry. To obtain good trajectories with visual odometry it is necessary to fly in a controlled environment (e.g., good illumination without reflections and a non visually uniform ground). 

**Type:** Recurrent behavior.

## Behavior `SELF_LOCALIZE_AND_MAP_WITH_LIDAR`

**Description:** The robot self localizes and maps the environment using lidar. The resulting map is represented with an occupancy grid. 

**Type:** Recurrent behavior.

# **Behaviors for communication**

## Behavior `INFORM_OPERATOR`

**Description:** This behavior presents through a pop-up window a text message that the robot sends to the operator.

[[Files/MessageToOperator.png]]

**Type:** Goal-based behavior.

| Name    |   Format  |  Example |  
| :-----------| :---------| :--------|
| message |String with the message to show|message: "Sensors detect a low level of light intensity in the environment where the aerial robot is flying."|	


## Behavior `INFORM_ROBOTS`

**Description:** This behavior sends a text message to another robot. The other robot must have activated the behavior PAY_ATTENTION_TO_ROBOT_MESSAGES. The text message must be a logic predicate according to the format of the belief memory.

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example | 
| :-----------| :---------| :--------|
| source |String with the name of the sender | source: "drone1"|
| destination |String with the name of the receiver| destination: "drone2"|
| text | String with the text of the message as a logic predicate | text: "found(item07)"|

## Behavior `REQUEST_OPERATOR_ASSISTANCE`

**Description:** This behavior shows a pop-up window with a question for the operator and several options to be selected as the answer. The robot will save the selected answer in its belief memory.

[[Files/OperatorAssistanceRequest.png]]

**Type:** Goal-based behavior.

| Name    |   Format  |  Example |  
| :-----------| :---------| :--------|
| question |String with the question for the operator | question: "What is the level of light intensity in the environment where the aerial robot is flying?"|
| belief_predicate_name |String with the name of the predicate to be saved in the belief memory| belief_predicate_name: "light_intensity"|
| options | Array of strings with the possible answers to the question| options: ["Too low","Adequate","Too high"]|