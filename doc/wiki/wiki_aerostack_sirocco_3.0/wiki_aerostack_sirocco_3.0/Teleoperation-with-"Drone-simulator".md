##  Teleoperation with Drone-simulator

Drone-simulator is a program that simulates the dynamics of a quadrotor. With this project, you can launch Aerostack with Drone-simulator and teleoperate the drone using the keyboard. After installing this project, perform the following steps:

1. Execute the ROS master node:

        $ roscore

1. Open another terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/teleoperation_drone_simulator 

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    An ArViz window will pop up showing a 3D image with a drone.

    [[Files/ProjectTDSArVizDroneSimulator.png]]

    A set of terminals with different tabs is presented. Select the tab corresponding to the drone interface:

    [[Files/ProjectTDSDroneAlphanumericInterface.png]]

Aerostack now is ready to operate the simulated drone. Teleoperate the drone with the alphanumeric interface using the appropriate keys. Here you can see how to use the keyboard:

- [Alphanumeric drone interface](https://github.com/Vision4UAV/Aerostack/wiki/Alphanumeric-User-Interface)

Here there is a video that shows the execution of this project:

[ ![Teleoperation with Drone simulator](https://img.youtube.com/vi/8rGHGJ7X4eg/0.jpg)](https://www.youtube.com/watch?v=8rGHGJ7X4eg)