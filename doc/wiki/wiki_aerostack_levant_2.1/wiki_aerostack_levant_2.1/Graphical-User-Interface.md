
This page describes the graphical user interface (GUI) of Aerostack. The GUI allows an operator to operate with an aerial robot from a ground station, observing states and dynamics. The GUI presents graphical views and images to help the operator to understand both the external and internal behavior of the robot.

Besides the GUI, Aerostack also includes an [[alphanumeric user interface]] to monitor basic parameters and to send commands to the robot using the keyboard.

## Windows layout

The figure below shows a sample screen of the user interface with the windows layout with main parts: the **control panel** on the upper left side of the image, the **dynamics viewer** on the lower left side, the windows for detailed content on the right hand side of the screen with  different tabs (environment, parameters, the camera viewer or the execution viewer). At the top, there are drop-down menus to perform additional tasks related to standard procedures. 

[[Files/GUIWindowsLayout.png]]

The **control panel** shows the general state of the UAV and the main control commands. This panel provides a summary of information considered critical that needs to be permanently present on the screen to be easily available to the operator.

The control panel shows general state of the vehicle with information such as wireless connection (connected, disconnected), battery charge (percentage of remaining battery charge) and the flight time (total time the vehicle has been flying).

In the central area, the operator can change the operation mode: keyboard teleoperation (the user controls the movements using the keyboard) or guided by a mission plan with three alternative options: Python mission (a mission file written in Python language), guided by TML mission (written in TML language), and guided by behavior trees (a behavior tree specifies the mission).

## Keyboard teleoperation

When the operation mode is set with the value keyboard teleoperation, the operator can control the movements of the robot with the keyboard. In the control panel, the available operation command is take off.

[[Files/GUIControlPanelKeyboardFirst.png]]

After pressing the take off button, the robot takes off and the layout changes showing two commands: land and reset (reset the vehicle position with zero values for rotation angles).

[[Files/GUIControlPanelKeyboardSecond.png]]

Besides these actions, the operator can control the movements using the following keys (this guide can be shown by clicking at the top of the screen, in the help menu):

[[Files/GUIKeyboardTeleoperationGuide.png]]

The operator can select the **first person view** in the vehicle dynamics to see a window with the front camera image together with dynamic parameters. Please, note that if you activate the first-person view, the efficiency of execution may decrease. To deactivate the first person viewer set the value **"No"** in the field **"First person view enabled"** of the control panel. The first person view shows a window like the following:

[[Files/GUIFirstPersonViewSmall.png]]

The operator can separate this window from its frame in order to have a bigger view and see additional information (e.g., horizon line):

[[Files/GUIFirstPersonViewBig.png]]



## Operation guided by a mission plan

The operation can be guided by a mission plan. A mission plan can be specified using one of the following options: 

- [[TML Language]]. TML is a mission specification language designed specifically for Aerostack using a task-based approach. 
- [[Behavior Tree]]. A mission plan can be specified graphically using a behavior tree.
- [[Python Language]]. It is also possible to use Python (with a specialized library) to formulate mission plans.

For example, the next figure shows that the operation is set to be guided by a Python mission:

[[Files/GUIControlPanelStartMission.png]]

In this case, the operator can import a text file with the mission plan specified in Python and, then, start the mission execution. Once the operator starts the mission, the control panel shows other buttons. 

[[Files/GUIControlPanelAbortMission.png]]

The operator can choose to perform an emergency land by pressing the "Emergency land" button or to stop the execution of the mission by pressing the "Abort mission" button but keep in mind this action will not land the robot. Pressing either one of these buttons will allow the user to select another Python mission file or to re-start the current mission.

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

- [[Configure the environment map]]

This window may also show information about behavior trees. This is presented when the operation mode (in the control panel) is set with the value 'guided by behavior trees'. 

## The execution viewer

The execution viewer shows the current state of the execution in two windows:

- The behavior viewer shows the list of active behaviors. The list is updated each time a behavior is started or stopped.

- The belief viewer shows the content of the memory of beliefs. This list is updated each time a belief is added, modified or removed.

If you right-click on the components of these windows, you can remove or add dynamically behaviors or beliefs.

[[Files/GUIBehaviorViewer.png]]

[[Files/GUIBeliefViewer.png]]