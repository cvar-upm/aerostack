This page describes how the operator can interact with UAV platforms using the human machine interface (HMI). The HMI allows the interaction with the drone, observing states and dynamics. The HMI also presents graphical views and images to help the user to understand both the external and internal behavior of the drone.

The Human Machine Interface (HMI) offers to the drone operators a bi-directional communication with each aerial robotic agent. Both communication directions are equally important because:

- The communication from the robotic agent to the operator is needed to monitor its state and the performance of the requested mission. This will allow the operator to actuate in case of a need to redefine or abort the mission. A good user graphical interface simplifies this task.

- The communication from the operator to the robotic agent is needed if a non-rigid behavior is required to accomplish the goal, making it possible to redefine the mission and also to start, stop, abort the mission or repair certain unexpected malfunctions that may occur during the mission execution.
 
In general, the operator can use a graphical user interface to perform the following types of tasks:
 
- Specify the vehicle’s behavior in advance (vehicle set up). Before a mission starts, the operator can specify what kind of behavior the drone must follow by selecting an operation mode (teleoperated, guided by mission plan), configure active capabilities and select a mission to be done.

- Monitor the vehicle’s behavior during a complex mission. The operator can monitor the state and the performance of a requested mission. Here, a non-rigid behavior is required, making it possible to redefine the mission and also to start, stop, abort the mission or repair certain unexpected malfunctions that may occur during the mission execution. A good graphical user interface simplifies this task.

- Operate manually with simple movements. The operator can operate manually the vehicle using the mouse and the keyboard to send basic motion commands (move forwards, backwards, etc.) and emergency actions (land, stop, reset, etc.).

- Collect data for later use. The operator can also use the GUI to collect relevant data to be used later. This includes, for example, images (photographs, videos) or data from other types of sensors (lidar, temperature, etc.).

The HMI includes some procedures used in most of the standard user interfaces to operate with aerial vehicles. The HMI also includes other specific features. For example, when an operator monitors the vehicle’s behavior during a mission, it is possible to distinguish between different levels of descriptions:
 
- *Mission level*. This level corresponds to the language used to describe the mission goals. Here the operator and the vehicle use the concepts such as the following: mission, name of the mission; task, a particular step of the mission (e.g., go to the building); skill, a capability of the vehicle (e.g., avoid certain types of obstacles, or interpret visual markers); action, an elementary task that can be performed (e.g., go to a certain point), and event, a situation that can require special attention.

- *Operation level*. This level corresponds to observed facts or derived facts by the vehicle during its operation. Here the operator uses the following concepts: internal states, (e.g., battery state, armed or disarmed, flying or landed, state of wifi connection, etc.), parameters measured by sensors or computed by specific algorithms (pose, yaw, pitch, roll, etc.), and images obtained from cameras.

- *Software level*. This corresponds to the internal behavior of the vehicle, related to the execution of running processes and internal error messages.

The HMI presents information at the different levels. This requires the corresponding translation procedures and specific data structures. For example, the HMI keeps a relation between each skill (at mission level) and the corresponding set of running processes (at software level). Operators who are not familiar with software architectures can consult information at mission level, which is more abstract, avoiding specific details of software execution. On the other hand, operators who are interested in software debugging and maintenance can use the software level to get more details about the mission execution.

## 1. Windows Layout

The figure below shows a sample screen of the user interface with the windows layout with main parts: the control panel on the upper left side of the image, the dynamics viewer on the lower left side, the windows for detailed content on the right hand side of the screen with  different tabs (parameters, the camera viewer or the performance monitor). At the top, there are drop-down menus (file, view, settings, etc.) to perform additional tasks related to standard procedures such as load and save files, help about user commands, etc. For example, in the settings menu the user can establish the connection between the GUI and the vehicle.

<p align="center">[[images/HMIGeneral.png]]</p>

## 2. The Control Panel

The control panel shows the general state of the UAV and the main control commands. This panel provides a summary of information considered critical that needs to be permanently present on the screen to be easily available to the operator.
 
The control panel is divided into three main areas: general state of the vehicle, operation mode and operation commands. The general state of the vehicle shows information such as wireless connection (connected, disconnected), battery charge (percentage of remaining battery charge), flight time (total time the vehicle has been flying), current status (landing, taking off, , etc.), action (name of the current action) and detected errors (the number of detected errors detected during the mission).
 
In the central area, the operator can change the operation mode: keyboard teleoperation (the user controls the movements using the keyboard) or guided by mission planner (the mission planner takes the control of the movements). 

If the operation mode is keyboard teleoperation, the area for operation commands shows buttons for different actions: take off, land and stabilize (reset the vehicle position with zero values for rotation angles).

<p align="center">[[images/HMIControlPanelKeyboard.png]]</p>

Besides these actions, the operator can control the movements using the following keys (this guide can be shown by clicking at the top of the screen, in the help menu):

<p align="center">[[images/HMIKeyboardGuide.png]]</p>

If the operation mode is guided by the mission planner, the area for operation commands shows a button to start the mission and the mission name.

<p align="center">[[images/HMIControlPanelStartMission.png]]</p>

Once the operator starts the mission, this area of the window changes with a button that helps to abort the mission (and hover) or land the vehicle. This area also shows the current task in the mission.

<p align="center">[[images/HMIControlPanelAbortMission.png]]</p>


## 3. The Parameter Viewer

In order to monitor the vehicle’s behavior in detail during a mission, the operator can observe the values of numerical parameters. The operator can display multiple plots of the parameters selected in real time to analyze and compare their values.

<p align="center">[[images/HMIParameterView.png]]</p>
 
This type of view is useful to verify the right operation of certain quantitative sensors. The view is also useful during the development of a particular vehicle configuration to select appropriate components and algorithms. For example, this window can be used to analyze the quality of different perception algorithms that estimate the vehicle’s position.
 
The window displays a plot for each parameter, identified by distinguishable colors. The graphic shows the evolution in a determined time interval, moving as time goes by from right to left. The vertical axis has been designed in a configurable way due to diversity of the parameters and the range of values. The maximum value can be set by a selector or directly zooming on the canvas.
 
As an additional feature, the window gives the possibility of saving the graphic plots for later use in various file formats (e.g., pdf, postscript).

## 4. The Camera Viewer

The camera viewer shows pictures and/or video images captured by the aerial vehicle during flight. The camera viewer displays a video streaming of the camera images.
 
Since the vehicle can use several cameras, the operator can select different display options to visualize the images. For example, the operator can select an option that displays only one camera (e.g., the frontal camera), an option that displays all cameras at the same time, or an option that displays a selected group of cameras.

<p align="center">[[images/HMICameraViewer.png]]</p>

## 5. The Process Monitor

The process monitor helps the user to supervise the current state of the software system (processes and error messages).

<p align="center">[[images/HMIProcessMonitor.png]]</p>

The process viewer (in the performance monitor window) helps the operator to monitor details of the internal behavior of the vehicle at software level. For example, the window displays a list of the existing processes and, for each one, the window shows its state (started, not started, etc.). 

The process monitor also presents error messages with a temporal identifier or timestamp. The system uses this window to centralize and present in a uniform way to the operator all kind of software errors (invalid input data, time out, division by zero, etc.) This is very important to help operators who are familiar with the system architecture to diagnose and debug software errors for software development and maintenance tasks.

## 6. The Viewer of Requested Skills

The operator can use the viewer of requested skills to consult and request the activation of specific skills. The GUI shows a list of available skills for the vehicle and indicates for each one its state.

For example, the operator can request a particular skills to be active (e.g., interpret Aruco visual markers) for a vehicle and can request another skills to be inactive (outloud speech the current task). The GUI translates each skill to the corresponding running processes.

<p align="center">[[images/HMIRequestedSkills.png]]</p>

## 7. The Mission Reporter

The HMI includes a mission reporter. Using this window, the operator can see the sequence of tasks and actions followed by the vehicle during the execution of a mission.

<p align="center">[[images/HMIMissionReporter.png]]</p>

## 8. The Dynamics of the Vehicle

The GUI includes a viewer that shows the dynamics of the vehicle. This can be used by the operator, for example, to better guide the vehicle during manual operations of the vehicle with the keyboard. The window presents the real time values of the position (x, y, z) and the angles corresponding to roll, pitch and yaw.

<p align="center">[[images/HMIVehicleDynamics.png]]</p>