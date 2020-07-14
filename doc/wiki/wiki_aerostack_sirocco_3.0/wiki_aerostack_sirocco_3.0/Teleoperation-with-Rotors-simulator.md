Rotors is a computer program (based on the simulator Gazebo) that simulates the dynamics of a quadrotor. With this project, you can launch Aerostack with Rotors and teleoperate the drone using the keyboard. After installing this project, perform the following steps:

1. Execute the ROS master node:

        $ roscore

1. Open another terminal and change your current directory to the folder that contains the launcher of this project:

         $ cd $AEROSTACK_STACK/projects/teleoperation_rotors_simulation

1. Execute the script that launches Gazebo for this project:

        $ ./launcher_gazebo.sh

    A Gazebo window is presented with a simulated drone.

    [[Files/ProjectTRSGazebo.png]]

1. Execute the script that launches the Aerostack components for this project:

        $ ./main_launcher.sh

    A set of terminals with different tabs is presented. Select the tab corresponding to the drone interface:

    [[Files/ProjectTRSAlphanumericInterface.png]]

Aerostack now is ready to operate the simulated drone. Teleoperate the drone with the alphanumeric interface using the appropriate keys. Here you can see how to use the keyboard:

- [Alphanumeric drone interface](https://github.com/Vision4UAV/Aerostack/wiki/Alphanumeric-User-Interface)

Here there is a video that shows the execution of this project:

[ ![Python Mission](https://img.youtube.com/vi/vIi-TN3Wq5w/0.jpg)](https://youtu.be/vIi-TN3Wq5w)