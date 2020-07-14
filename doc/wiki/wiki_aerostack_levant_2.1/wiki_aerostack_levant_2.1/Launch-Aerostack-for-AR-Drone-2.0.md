This section shows how to launch Aerostack for the aerial platform AR Drone 2.0. 

## Hardware Configuration

In this example we assume that the following hardware is used:

- An air vehicle Parrot AR Drone (other aerial platforms can be used with Aerostack).

- A computer with wifi connection.

[[Files/ARDrone.png]]

## Launch the system

To launch and start running the system, open a new terminal and, then, perform the following tasks:

1. Make sure the drone is on, and reset it if needed.

1. Connect the computer to the drone wifi (e.g., ardrone2_002410).

1. Execute the ROS master node:

        $ roscore

1. In a new terminal window, go to the directory which contains the launchers (it includes different pre-configured .sh files that launch the set of processes for different mission types):

        $ cd ${AEROSTACK_STACK}/launchers 

1. Execute the script to launch all processes:

        $ ./ardrone_basic.sh

Now, it is possible to operate the drone through the user interface controls (see [[Graphical User Interface]]).

[[Files/GUIEnvironmentViewer.png]]

To stop and terminate all program executions, it is necessary to perform the following steps in the terminal console:

        $ cd ${AEROSTACK_STACK}/launchers 
        $ ./stop.sh