The alphanumeric interface is an efficient process that presents information about the robot behavior and can be used to teleoperate the robot. 

This user interface is presented in a window terminal (with the tab called *Shell User Interface*) after launching Aerostack. You can see several parameters that give  information about the situation of the drone and its state.

![Shell User Interface ](Files/ShellUserInterface.png)

The operator can send different commands using the following keys:

| Key |  Command|
|--|--|
|**t**  | *take off*: take off |
|**y**  | *land*: hover > land > stop controller |
|**space bar**  | *emergency stop:* emergency stop > stop controller |
| **h** | *hover*: hover > stop controller |
| **m**|  *move*: move (set flying mode) |
| **s** | *set commands to zero*: [open loop] hover, [closed loop] (non internal - with controller) hover |
| **q** | *move upwards*: [open loop] upwards speed command; [speed, position control] move altitude reference upwards  |
| **a** | *move downwards*: same as before but downwards |
| **z** | *(yaw) turn counter-clockwise*: [open loop] turn with speed command; [any controller] move yaw reference counter-clockwise  |
| **x** | *(yaw) turn clockwise*: same as before but clockwise |
|**\\**| *set yaw reference to 0* (look parallel to x-axis)  |
| **right arrow**|   *move right, or to[+]y_axis:* [open loop] or [speed command] or [position command], ignored during trayectory control|
| **left arrow**| *move left: [open loop] or [speed command] or [position command]*, ignored during trayectory control  |
| **up arrow** | *move frontwards; [open loop] or [speed command] or [position command]*, ignored during trayectory control  |
| **down arrow**|  *move backwards: [open loop] or [speed command] or [position command]*, ignored during trayectory control |
| **j**| *reset EKF*: stop controller > reset EKF |
| **k**| *stop  EKF:* stop controller > stop EKF |
| **l**| *start EKF*: start EKF and setInitDroneYaw |
| **u**|  *reset controller*  |
| **i**| *stop  controller*: stop controller > drone_hover  |
| **o**|*start controller*: start EKF > start controller  |
| **7**|  *start speed controller*: if controller started > drone_move > start controller (speed) |
| **8**|*start position controller*: if controller started > drone_move > start controller (position)  |
| **9**| *start trajectory controller* (3D quadrilateral) using rel_trajectory_ref channel |
