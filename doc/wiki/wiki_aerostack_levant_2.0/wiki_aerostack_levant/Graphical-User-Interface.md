
This page describes the graphical user interface (GUI) of Aerostack 2.0 (Levant distribution). The GUI allows an operator to operate with an aerial robot from a ground station, observing states and dynamics. The GUI presents graphical views and images to help the operator to understand both the external and internal behavior of the robot.

The GUI offers to the robot operators a bi-directional communication with each aerial robot system. Both communication directions are equally important because:

- The communication from the robotic agent to the operator is needed to monitor its state and the performance of the requested mission. This will allow the operator to actuate in case of a need to redefine or abort the mission. A good user graphical interface simplifies this task.

- The communication from the operator to the robotic agent is needed if a non-rigid behavior is required to accomplish the goal, making it possible to redefine the mission and also to start, stop, abort the mission or repair certain unexpected malfunctions that may occur during the mission execution.

In general, the operator can use a graphical user interface to perform the following types of tasks:

- Specify the robot’s behavior in advance (robot set up). Before a mission starts, the operator can specify what kind of behavior the robot must follow by selecting an operation mode (teleoperated, guided by python mission plan or guided by behavior trees), selecting this way a mission to be done.

- Monitor the robot’s behavior during a complex mission. The operator can monitor the state and the performance of a requested mission. Here, a non-rigid behavior is required, making it possible to redefine the mission and also to start, stop, abort the mission or repair certain unexpected malfunctions that may occur during the mission execution. A good graphical user interface simplifies this task.

- Operate manually with simple movements. The operator can operate manually the robot using the keyboard to send basic motion commands (move forwards, backwards, etc.) and emergency actions (land, stop, reset, etc.).

- Collect data for later use. The operator can also use the GUI to collect relevant data to be used later. This includes, for example, images (photographs, videos) or data from other types of sensors (lidar, temperature, etc.).

The GUI includes some procedures used in most of the standard user interfaces to operate with aerial vehicles. The GUI also includes other specific features. For example, when an operator monitors the robot’s behavior during a mission, it is possible to distinguish between different levels of descriptions:

- *Mission level*. This level corresponds to the language used to describe the mission goals. Here the operator and the vehicle use concepts such as the following: mission, task, behavior, task or belief.

- *Operation level*. This level corresponds to observed facts or derived facts by the vehicle during its operation. Here the operator uses the following concepts: internal states, (e.g., battery state, armed or disarmed, flying or landed, state of wifi connection, etc.), parameters measured by sensors or computed by specific algorithms (pose, yaw, pitch, roll, etc.), and images obtained from cameras.

- *Software level*. This corresponds to the internal behavior of the vehicle, related to the execution of running processes and internal error messages.

The GUI presents information at the different levels. This requires the corresponding translation procedures and specific data structures. For example, the GUI keeps a relation between each capability (at mission level) and the corresponding set of running processes (at software level). Operators who are not familiar with software architectures can consult information at mission level, which is more abstract, avoiding specific details of software execution. On the other hand, operators who are interested in software debugging and maintenance can use the software level to get more details about the mission execution.

## Windows layout

The figure below shows a sample screen of the user interface with the windows layout with main parts: the control panel on the upper left side of the image, the dynamics viewer on the lower left side, the windows for detailed content on the right hand side of the screen with  different tabs (environment, parameters, the camera viewer or the execution viewer). At the top, there are drop-down menus to perform additional tasks related to standard procedures such as load and save files, help about user commands, etc. 

[[Files/GUIWindowsLayout.png]]

## The control panel

The control panel shows the general state of the UAV and the main control commands. This panel provides a summary of information considered critical that needs to be permanently present on the screen to be easily available to the operator.

The control panel is divided into three main areas: general state of the vehicle, operation mode and operation commands. The general state of the vehicle shows information such as wireless connection (connected, disconnected), battery charge (percentage of remaining battery charge) and the flight time (total time the vehicle has been flying).

In the central area, the operator can change the operation mode: keyboard teleoperation (the user controls the movements using the keyboard), guided by Python mission (a mission file written in Python specifies the mission to be followed), guided by TML mission (a mission file written in TML language specifies the mission to be followed), and guided by behavior trees (a behavior tree created by the user specifies the mission the drone will follow).

### Keyboard teleoperation

When the operation mode is set with the value keyboard teleoperation, the operator can control the movements of the robot with the keyboard. In the control panel, the available operation command is take off.

[[Files/GUIControlPanelKeyboardFirst.png]]

After pressing the take off button, the robot takes off and the layout changes showing two commands: land and reset (reset the vehicle position with zero values for rotation angles).

[[Files/GUIControlPanelKeyboardSecond.png]]

Besides these actions, the operator can control the movements using the following keys (this guide can be shown by clicking at the top of the screen, in the help menu):

[[Files/GUIKeyboardTeleoperationGuide.png]]

### Operation guided by Python mission

If the operation mode is guided by a Python mission, the area for operation commands shows a button to start the mission and a button to select the mission file.  

[[Files/HMIControlPanelStartMission.png]]

The operator can select a text file with the mission plan specified in [[Python Language]] (consult the previous link to know how to specify a mission plan in this language).

Once the operator starts the mission, the control panel shows the available commands. The operator can choose to perform an emergency land by pressing the "Emergency land" button or to stop the execution of the mission by pressing the "Abort mission" button but keep in mind this action will not land the robot. Pressing either one of these buttons will allow the user to select another Python mission file or to re-start the current mission.

[[Files/HMIControlPanelAbortMission.png]]

### Operation guided by TML mission

The operator can use the TML language to guide the mission execution. TML is a mission specification language designed specifically for Aerostack using a task-based approach. See the following link to know how to specify a mission in this language:

- [[TML Language]]

Follow these steps to specify the tasks of a mission:

- The task-based mission of the robot is specified in a XML file called `mission_specification_file.xml` (this is the default name, as it is established in the .launch file located within the `launch` directory in the repository `task_based_mission_planner_process`). This file must be located in `$AEROSTACK_STACK/configs/` within a folder selected by the operator called `drone{Id}` (`{Id}` = 00, 01, 02, ...).

- To check if the file has syntax errors, launch the mission planner executing the following command:
        
    $ roslaunch task_based_mission_planner_process task_based_mission_planner_process.launch

- If the xml file does not have any errors, the following message is presented:

    File loaded without errors! Waiting to start ...

To use the TML language for a mission, the operator sets the operation mode in the control panel to the value guided by TML mission. The TML mission can only be edited and loaded via the mission_specification_file.xml located in the correct '$AEROSTACK/configs' folder. 

[[Files/GUIControlPanelTMLStart.png]]

When the mission is started, control panel shows the current task being executed and the name of the mission. The control panel also presents buttons to abort the mission or execute an emergency land: 

[[Files/GUIControlPanelTMLAbort.png]]

### Operation guided by behavior trees

If the operation mode is guided by behavior trees, the area for operation commands shows a button to start the mission.

[[Files/GUIControlPanelBTStart.png]]

When this button is pressed, it will change itself to a "Emergency land" button which will land the robot and stop the execution of the Behavior Tree and a "Abort mission" button which will end the execution and show the "Start mission" button again.  

[[Files/GUIControlPanelBTExecuting.png]]

The operator can specify a mission as a [[Behavior Tree]] (consult the previous link to know how to specify a mission plan with a behavior tree).

## The parameter viewer

In order to monitor the vehicle’s behavior in detail during a mission, the operator can observe the values of numerical parameters. The operator can display multiple plots of the parameters selected in real time to analyze and compare their values.

[[Files/GUIParameterView.png]]

This type of view is useful to verify the right operation of certain quantitative sensors. The view is also useful during the development of a particular vehicle configuration to select appropriate components and algorithms. For example, this window can be used to analyze the quality of different perception algorithms that estimate the vehicle’s position.

The window displays a plot for each parameter, identified by distinguishable colors. The graphic shows the evolution in a determined time interval, moving as time goes by from right to left. The vertical axis has been designed in a configurable way due to diversity of the parameters and the range of values. The maximum value can be set by a selector or directly zooming on the canvas.

As an additional feature, the window gives the possibility of saving the graphic plots for later use in various file formats (e.g., pdf, postscript).

## The camera viewer

The camera viewer shows pictures and/or video images captured by the aerial vehicle during flight. The camera viewer displays a video streaming of the camera images.

Since the vehicle can use several cameras, the operator can select different display options to visualize the images. For example, the operator can select an option that displays only one camera (e.g., the frontal camera), an option that displays all cameras at the same time, or an option that displays a selected group of cameras.

[[Files/GUICameraViewer.png]]

## The environment viewer

The environment viewer provides a 2D graphical representation of the environment. It gives dynamic information about the position of the robot and the obstacles as well.

[[Files/GUIEnvironmentViewer.png]]

The operator can edit the environment map by pressing the 'Edit' button. To consult more details about how to edit an environment map, please read the following page:

- [[How to create an environment map]]

This window may also show information about behavior trees. This is presented when the operation mode (in the control panel) is set with the value 'guided by behavior trees'. 

## The execution viewer

The execution viewer shows the current state of the execution in two windows:

- The behavior viewer shows the list of active behaviors. The list is updated each time a behavior is started or stopped.

- The belief viewer shows the content of the memory of beliefs. This list is updated each time a belief is added, modified or removed. 

[[Files/GUIBehaviorViewer.png]]

[[Files/GUIBeliefViewer.png]]