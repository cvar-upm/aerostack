
This catalog shows the available behaviors provided by Aerostack. They are presented according to the following categories: motion behaviors, behaviors for environment understanding, and behaviors for communication.

It is important to note that there are two types of behaviors: 

- **Goal-based behaviors**. These behaviors are defined to reach a final state (attain a goal). For example, the behavior TAKE_OFF ends when the drone has reached a certain height. 

- **Recurrent behaviors**. These behaviors perform an activity recurrently or maintain a desired state (for example, the behavior PAY_ATTENTION_TO_VISUAL_MARKERS).

You can consult the following link to know how to add your own behaviors:

- [[How to program a new behavior]]

## Motion behaviors

**Behavior** `TAKE_OFF`

The robot takes off vertically from the surface to the normal altitude. If the altitude argument is not given, the robot reaches a default altitude. **Type:** goal-based behavior.

**Behavior** `LAND`

The robot lands vertically in the current position. This behavior assumes that the floor is static. **Type:** goal-based behavior.

**Behavior** `KEEP_HOVERING`

The robot keeps hovering. Hovering is a maneuver in which the robot is maintained in nearly motionless flight over a reference point at a constant altitude and on a constant heading. This behavior does not avoid moving obstacles. **Type:** recurrent behavior.

**Behavior** `KEEP_MOVING`

The robot keeps moving at a constant speed in some direction (forward, backward, left,right). If the speed value is not given a default value is considered. This behavior does not avoid obstacles. **Type:** recurrent behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| direction |{FORWARD, BACKWARD, LEFT, RIGHT}|direction: FORWARD |			
| speed |number (m/sec)|speed: 12|

**Behavior** `ROTATE`

The robot rotates some degrees in a certain axis (yaw). **Type:** goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|			
| angle |number (degrees)|angle: 90|
| relative_angle |number (degrees)|relative_angle: 90|

**Behavior** `WAIT`

The robot keeps doing the action while waiting for timeout or seeing a certain visual marker or both. **Type:** goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| timeout| number(seconds) | timeout: 30 |			
| until_observed_visual_marker | number (visual marker id)|until_observed_visual_marker: 1|

**Behavior** `FOLLOW_OBJECT_IMAGE`

The robot follows the image of a moving object, keeping a certain constant distance between the robot and the object. The operator selects the image to follow through the user interface. **Type:** recurrent behavior.

**Action** `GO_TO_POINT`

The vehicle goes to a given poin avoiding obstacles. The trajectory follows horizontal movements in two dimensions (2D). The point can be expressed using absolute coordinates (argument “coordinates”) or coordinates relative to the vehicle (argument “relative coordinates”). **Type:** goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| coordinates |Tuple of 3 numbers x, y, z (meters)|coordinates: [1.23, 2, 0.5]|	
| relative_coordinates |Tuple of 3 numbers x, y, z (meters)|relative_coordinates: [1.23, 2, 0.5]|			 


## Behaviors for environment understanding


**Behavior** `PAY_ATTENTION_TO_VISUAL_MARKERS`

The robot pays attention to visual markers. **Type:** recurrent behavior.

**Behavior** `SELF_LOCALIZE_BY_ODOMETRY`

The robot self localizes using odometry. **Type:** recurrent behavior.

**Behavior** `SELF_LOCALIZE_BY_VISUAL_MARKERS`

The robot self localizes using visual markers (ArUco markers). **Type:** recurrent behavior.

**Behavior** `RECOGNIZE_SURFACE_IMPERFECTION`

The robot recognizes imperfections (holes and fissures) in a surface observed by the camera. **Type:** recurrent behavior.

**Behavior** `VERIFY`

The robot checks if a condition is satisfied. The result is true if the condition is satisfied. Otherwise, the result is false. **Type:** deliberative behavior.

| Arguments    |   Format  |  Example |  Comments | 
| :-----------| :---------| :--------|:--------|
| marker_is_observed |integer| marker_is_observed: 3||			
| hovering |Boolean (TRUE/FALSE)|hovering: TRUE| Not implemented yet|			 
| obstacle_distance |number|obstacle_distance: 0.5| Not implemented yet|	
| voice_command |text|voice_command: "land"| Not implemented yet|

## Behaviors for communication

**Behavior** `REQUEST_OPERATOR_ASSISTANCE`

This behavior presents (e.g., through a pop-up window) a text message and a list of options to select. The operator selects one of the options and the selection is written in the belief memory. **Type:** goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| MESSAGE |text| MESSAGE: "The light intensity is very low"|
| OPTIONS |list of texts| OPTIONS: ["Turn on light","Land"]|

**Behavior** `REQUEST_OPERATOR_CONFIRM_RECOGNITION`

This behavior presents (e.g., through a pop-up window) a text message related to the uncertain recognition of an object. The window presents two options to the operator: confirm or reject. The operator selects one of the options and the selection is written in the belief memory. **Type:** goal-based behavior.

| Arguments    |   Format  |  Example |  
| :-----------| :---------| :--------|
| MESSAGE |text| MESSAGE: "The image of the front camera has been classified into the category 'hole'"|



