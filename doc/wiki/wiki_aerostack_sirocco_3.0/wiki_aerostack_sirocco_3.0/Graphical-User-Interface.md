# Graphical user interface

This page describes the graphical user interface (GUI) of Aerostack. The GUI is used by the operator to (1) supervise the behavior of the aerial robot from the ground station and (2) configure details of the mission to be executed by the robot. The GUI presents user-friendly graphical views and visual aids to facilitate the realization of these tasks.

The GUI of Aerostack is provided as a collection of individual applications for different tasks. Each of these applications is implemented as a separate ROS node that can be launched individually. This separation is useful, for example, to minimize the computational consumption during the execution of a mission, because only the different parts of the GUI are launched by the user when they are needed.

The following sections present these interface applications separated into three groups:

1. Individual viewers
1. Mission control windows
1. Integrated viewer
1. Graphical editors

Besides the GUI, Aerostack also provides an [alphanumeric user interface](https://github.com/Vision4UAV/Aerostack/wiki/Alphanumeric-User-Interface) to monitor basic parameters and to send commands to the robot using the keyboard.

# 1. Individual viewers

This section shows the list of individual viewers, i.e., applications that present a window to monitor certain features of the robot behavior. Each application may be launched using the ROS command:

     $ roslaunch <package-name> <launch-filename> --wait [args]


## Vehicle dynamics viewer

This window is used to consult the values of the pose and speed parameters.

To launch the vehicle dynamics viewer (for example, for the robot namespace `drone7`), the command is:

     $ roslaunch vehicle_dynamics_viewer vehicle_dynamics_viewer.launch --wait robot_namespace:=drone7

[[Files/GUIDynamicsViewer.png]]
	 
## Execution viewer

This window shows two kinds of components: the memory of beliefs, and a list of the behaviors currently executing accompanied by the arguments that have been passed as a parameter at the time of defining the mission. It also offers the option of modifying the existing beliefs and behaviors by right-clicking on them.

To launch the execution viewer (for example, for the robot namespace `drone7`), the command is:

     $ roslaunch execution_viewer execution_viewer.launch --wait robot_namespace:=drone7

[[Files/GUIExecutionViewer.png]]

## Environment Viewer

2D representation of the elements in the scene of the mission (obstacles, poles, visual markers...) and the drone, showing its trajectory updated in real time. To clean up the path followed by the vehicle press the button clear.

To launch the environment viewer (for example, for the robot namespace `drone1`), the command is:

     $ roslaunch environment_viewer environment_viewer.launch --wait robot_namespace:=drone1 robot_config_path:=$AEROSTACK_STACK/configs/drone1

[[Files/GUIEnvironmentViewer.png]]
	 
## First Person Viewer

Head-up visualization of the images captured by the frontal camera, with some dynamic parameters over it. You can press the button in the upper left corner to switch to extended mode.

To launch the first person viewer (for example, for the robot namespace `drone7`), the commands are:

     $ roslaunch first_view_process first_view.launch --wait robot_namespace:=drone7 
     $ roslaunch first_person_view_process first_person_view.launch --wait robot_namespace:=drone7 

[[Files/GUIFirstPersonViewer.png]]
	    
## Parameters Viewer

Through this component, the user can monitor those variables that s/he has previously selected in its side menu. They are shown in the form of a line chart updated in real time. It also shows the value of the complete set of parameters. To make it easier to read, it uses a legend in which a different color is automatically assigned to each of the variables. It allows the operator to stop the representation as well as export the graphic built up to that moment in different formats. It is very useful to verify that the course of the mission is happening as planned.

To launch the parameters viewer (for example, for the robot namespace `drone7`), the command is:

     $ roslaunch parameters_viewer parameters_viewer.launch --wait robot_namespace:=drone7

[[Files/GUIParametersViewer.png]]
	   
## Camera Viewer

This widget shows images and videos captured by all the cameras installed in the vehicle. We can visualize different cameras at the same time by using one of the display options in the upper left part. We can also save these images in a file.

To launch the camera viewer (for example, for the robot namespace `drone7`), the command is:

     $ roslaunch camera_viewer camera_viewer.launch --wait robot_namespace:=drone7

[[Files/GUICameraViewer.png]]

# 2. Mission control windows

## Teleoperation control window

Window to control the operation of the vehicle using the keyboard. The behavior of the robot is fully controlled by the keys pressed by the user.

To launch the teleoperation control window (for example, for the robot namespace `drone1`), the command is:

     $ roslaunch teleoperation_control_window teleoperation_control_window.launch --wait robot_namespace:=drone1 

[[Files/GUIGraphicalTeleoperationWindow.png]]

## Behavior tree control window

Aerostack presents graphically the behavior tree using a hierarchy browser. To execute the behavior tree, the interpreter loads the yaml file with the mission plan and it follows its structure to generate a sequence of activations and deactivations of robot behaviors. During the execution, the control window shows graphically the dynamic evolution of the execution. The control window also presents the current values of variables used by the behavior tree. The interpreter also facilitates preemptive interaction between the user and the robot, i.e., the user can interrupt the mission at any point and continue the execution in another node of the behavior tree. 

To launch the window to control a mission plan written as behavior trees (for example, for the robot namespace `drone7` and the mission configuration folder $AEROSTACK_STACK/projects/configs/mission), the command is:

     $ roslaunch behavior_tree_interpreter behavior_tree_interpreter.launch --wait robot_namespace:=drone7 mission_configuration_folder:=$AEROSTACK_STACK/projects/configs/mission

[[Files/GUIBehaviorTreeControlWindow.png]]

# 3. Integrated viewer

The integrated viewer may be used to show layouts that present prefixed groups of windows. The integrated viewer is launched with the following ROS command:

     $ roslaunch integrated_viewer integrated_viewer.launch 

Then, a screen background is presented with a menu bar in the upper part.

[[Files/GUIMenuBarAerostack.png]]

The option **View** shows a menu to launch the different layouts that are described below.

## Graphical teleoperation

Layout oriented to control the operation of the vehicle using the keyboard. The behavior of the robot is fully controlled by the keys pressed by the user while the Graphical Teleoperation **window is active**. Besides that dialog, this layout also includes the Vehicle Dynamics Viewer, the Execution Viewer, the Environment Viewer and the First Person Viewer.
	 
[[Files/GUILayoutGraphicalTeleoperation.png]]
	  
## Alphanumeric interface

As we have mentioned before, the [Alphanumeric Interface](https://github.com/Vision4UAV/Aerostack/wiki/Alphanumeric-User-Interface) is integrated inside the Graphical User Interface as a prefixed layout. It shows the console and the Environment Viewer. The console accepts commands through the keyboard and sends them to the actuators of the aerial robot.

[[Files/GUILayoutAlphanumericInterface.png]]

## Behavior tree mission

The user executes the behavior tree previously charged using Edit Behavior Tree. This widget also captures commands through the keyboard but their use **stops the execution of the mission**.  The mission can be started from any node right-clicking on the desired one. It is composed of the Behavior Tree Control, the Environment Viewer, the Execution Viewer and the Vehicle Dynamics. For more information visit the [Behavior Tree Control section](https://bitbucket.org/Vision4UAV/aerostack/wiki/Behavior%20Tree%20Control).

[[Files/GUILayoutBehaviorTreeControl.png]]
	  
## Python mission

With this layout, the operator starts and controls the execution of the selected Python Mission. He can also use the keyboard interrupting the execution of the mission. It shows the Python Mission Control, the Pỳthon Based Mission Interpreter (feedback of the mission), the Environment Viewer, the Execution Viewer and the Vehicle Dynamics Viewer.

[[Files/GUILayoutPythonMissionControl.png]]
	 
# 4. Graphical editors

The editors may be used by the operator to change the configuration of the mission. 

## Environment map editor

The user can use this editor to design a new map or import and change an existing one.

To launch the environment map editor (for example, for the robot namespace `drone1`), the command is:

     $ roslaunch environment_editor environment_editor.launch --wait  robot_namespace:=drone1 robot_config_path:=$AEROSTACK_STACK/configs/drone1

[[Files/GUIEnvironmentEditor.png]]

See more details in the following page:

- [[Configure the Environment Map]]
 
## Behavior tree editor

The operator can use this editor to create or import and change a mission plan represented as a behavior tree. 
 
[[Files/GUIBehaviorTreeEditor.png]]