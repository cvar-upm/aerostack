This catalog shows the available behaviors provided by Aerostack. They are presented according to different categories: 

- [Motion behaviors:](#motion-behaviors)
  * [TAKE_OFF](#behavior-take_off)
  * [LAND](#behavior-land)    
  * [KEEP_HOVERING](#behavior-keep_hovering)
  * [KEEP_MOVING](#behavior-keep_moving)
  * [ROTATE](#behavior-rotate)
  * [WAIT](#behavior-wait)
  * [FOLLOW_OBJECT_IMAGE](#behavior-follow_object_image)
  * [GO_TO_POINT](#behavior-go_to_point)
- [Behaviors for environment understanding:](#behaviors-for-environment-understanding)
  * [PAY_ATTENTION_TO_VISUAL_MARKERS](#behavior-pay_attention_to_visual_markers)
  * [SELF_LOCALIZE_BY_ODOMETRY](#behavior-self_localize_by_odometry)
  * [SELF_LOCALIZE_BY_VISUAL_MARKERS](#behavior-self_localize_by_visual_markers)
- [Behaviors for communication:](#behaviors-for-communication)
  * [REQUEST_OPERATOR_ASSISTANCE](#behavior-request_operator_assistance)

It is important to note that there are two types of behaviors: 

- **Goal-based behaviors**. These behaviors are defined to reach a final state (attain a goal). For example, the behavior TAKE_OFF ends when the drone has reached a certain height. 

- **Recurrent behaviors**. These behaviors perform an activity recurrently or maintain a desired state (for example, the behavior PAY_ATTENTION_TO_VISUAL_MARKERS).

You can consult the following link to know how to add your own behaviors:

- [[Program new behaviors]]

# **Motion behaviors**

## Behavior `TAKE_OFF`

**Description:** The robot takes off vertically from a static surface. This behavior ends when the robot reaches a default altitude.

**Type:** Goal-based behavior.

## Behavior `LAND`

**Description:** The robot lands vertically in the current position. This behavior assumes that the ground is static.

**Type:** Goal-based behavior.

## Behavior `KEEP_HOVERING`

**Description:** The robot keeps hovering. Hovering is a maneuver in which the robot is maintained in nearly motionless flight over a reference point at a constant altitude and on a constant heading. This behavior does not avoid moving obstacles. 

**Type:** Recurrent behavior.

## Behavior `KEEP_MOVING`

**Description:** The robot keeps moving at a constant speed in some direction (forward, backward, left,right). If the speed value is not given a default value is considered. This behavior does not avoid obstacles. 

**Type:** Recurrent behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| direction |{FORWARD, BACKWARD, LEFT, RIGHT}|direction: FORWARD |			
| speed |number (m/sec)|speed: 12|

## Behavior `ROTATE`

**Description:** The robot rotates left or right a certain number of degrees (angle) on the vertical axis (yaw). The number of degrees can be expressed as an absolute value (argument “angle”) or relative to the robot (argument “relative_angle”).

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|			
| angle |number (degrees)|angle: 90|
| relative_angle |number (degrees)|relative_angle: 90|

## Behavior `WAIT`

**Description:** The robot waits until a certain condition is satisfied (e.g., timeout or a certain visual marker is observed). 

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| timeout| number(seconds) | timeout: 30 |			
| until_observed_visual_marker | number (visual marker id)|until_observed_visual_marker: 1|

## Behavior `FOLLOW_OBJECT_IMAGE`

**Description:** The robot follows the image of a moving object, keeping a certain constant distance between the robot and the object. The operator selects the image to follow through the user interface. To select the object image to follow using the user interface (the OpenTLD GUI) the operator has to press the F5 button to refresh the image on the screen, select the image to follow and then press and hold (just for few seconds) the ENTER key. Then the robot will start following the selected image.

**Type:** Recurrent behavior. 

## Behavior `GO_TO_POINT`

**Description:** The robot goes to a destination point avoiding obstacles. The point can be expressed in absolute coordinates (argument “coordinates”) or coordinates relative to the robot (argument “relative coordinates”). To reach the target point, the robot vertically changes the altitude to be at the same altitude as the target point and, then, follows a two-dimensional (2D) movement in the horizontal plane avoiding existing obstacles. During the movement, the robot can dynamically change the planned path if a new obstacle (e.g., another robot) is detected.

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| coordinates |Tuple of 3 numbers x, y, z (meters)|coordinates: [1.23, 2, 0.5]|	
| relative_coordinates |Tuple of 3 numbers x, y, z (meters)|relative_coordinates: [1.23, 2, 0.5]|			 

# **Behaviors for environment understanding**

## Behavior `PAY_ATTENTION_TO_VISUAL_MARKERS`

**Description:** The robot pays attention to visual markers (ArUco markers). The recognized markers are stored as beliefs.

**Type:** Recurrent behavior.

## Behavior `SELF_LOCALIZE_BY_ODOMETRY`

**Description:** The robot self localizes using odometry. To obtain good trajectories with visual odometry it is necessary to fly in a controlled environment (e.g., good illumination without reflections and a non visually uniform ground). 

**Type:** Recurrent behavior.

## Behavior `SELF_LOCALIZE_BY_VISUAL_MARKERS`

**Description:** The robot self localizes using visual markers (ArUco markers).

**Type:** Recurrent behavior.

# **Behaviors for communication**

## Behavior `REQUEST_OPERATOR_ASSISTANCE`

**Description:** This behavior presents through a pop-up window a text message and a list of options to select. The operator selects one of the options and the selection is written in the belief memory. When this behavior is activated, the robot stops its current movement and hovers. Once the operator provides an answer, the robot continues the previous movement.

**Type:** Goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| message |text| message: "The light intensity is very low"|
| options |list of texts| options: ["Turn on light","Land"]|