This section shows with a simple example how to install Aerostack and control manually the flight of a drone. 

## 1. Hardware Configuration

In this example we assume that the following hardware is used:

- An air vehicle Parrot AR Drone (other aerial platforms can be used with Aerostack).

- A computer with wifi connection.

[[images/ARDrone.png]]

## 2. Software Installation

Aerostack has been tested in a computer with the following software:

- Linux operating system Ubuntu 14.04 (64 bit).

- Robot Operating System (ROS), Jade distribution.

However Aerostack should also work on any other mainstream Linux distributions. The code requires a compiler that is compatible with the C++11 standard. 

Aerostack requires additional libraries like: boost and ncurses (among others). Aerostack has ROS packages dependencies like: ardrone_autonomy, opencv2, roscpp, image_transport, sensor_msgs and std_srvs (among others).
All the dependencies are automatically installed during the installation process.

The installation follows the same steps needed usually to compile a self-contained ROS stack:

1. Before the installation, you must read and accept the conditions defined by the software [[License]].

1. Download the installation script file:

        $ git clone https://github.com/Vision4UAV/Aerostack_installer ~/temp

1. Run it in a non-ARM architecture computer: 

        $ ~/temp/installation_script.sh

1. Re-open the terminal and Aerostack is ready to be used.

If you need to update the software:

1. Go to the Aerostack folder:

        $ cd $AEROSTACK_STACK

1. Update the stack:

        $ git pull origin master

1. Update submodules: 

        $ git submodule update --init --recursive

Sometimes, you will need to install new dependencies or update the old dependencies what is done by executing the following command:

        $ $AEROSTACK_STACK/installation/installation_dep_script.sh

> NOTE: Be sure that you are connected to Internet when you compile Aerostack. This is because certain packages (e.g., opentld) need to be updated from remote repositories.

## 3. A First Flight

To launch and start running the system, the user has to open a new terminal and, then, perform the following tasks:

1. Make sure the drone is on, and reset it if needed.

1. Connect the computer to the drone wifi (e.g., ardrone2_002410).

1. Execute the ROS master node:

        $ roscore

1. In a new terminal window, go to the directory which contains the launchers:

        $ cd ${AEROSTACK_STACK}/launchers 

1. Execute the script to launch all processes and the Human Machine Interface:

        $ ./ardrone_basic.sh

Now, the installation is complete and it is possible to operate with the drone through the user interface controls (see details about the operation control in the chapter about the human machine interface).

[[images/HMIGeneral.png]]

To stop and terminate all program executions, it is necessary to perform the following steps in the terminal console:

        $ cd ${AEROSTACK_STACK}/launchers 
        $ ./stop.sh