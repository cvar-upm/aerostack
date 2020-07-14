## Previous requirements

To install Aerostack, you need to meet these requirements:

- A non-ARM architecture computer.
- 2 GB of free disk space.
- (Good) internet connection.
- Linux operating system **Ubuntu 16.04** (64 bit) installed. Aerostack should also work on any other mainstream Linux distributions. The code requires a compiler that is compatible with the C++11 standard.
- **Robot Operating System** (ROS), **Kinetic** distribution installed. You can get ROS Kinetic following [these instructions](http://wiki.ros.org/kinetic/Installation/Ubuntu).

## License agreement

Before the installation, you must read and accept the conditions defined by the software [license](https://github.com/Vision4UAV/Aerostack/wiki/License). 

## Installation process

Open a terminal window and write the commands below corresponding to the following steps:

1. Download the installation script file from our GitHub repository:

        $ git clone https://github.com/Vision4UAV/Aerostack_installer ~/temp

1. Run the installation script file (this process will take a few minutes, wait until the whole project is compiled and installed):

        $ ~/temp/installation_script.sh

1. Re-open the terminal and Aerostack is ready to be used.
 
## Verify correct installation

To verify that Aerostack is correctly installed, you can execute a simulated mission by doing the following tasks:

- [[Launch Aerostack with Drone Simulator]]
- [[Teleoperate a simulated drone]]

## Update Aerostack

If you have an old version of Aerostack and you want to update it to the latest release open a terminal window and enter the commands bellow.

1. Go to the  Aerostack workspace folder already pointed by the variable $AEROSTACK_STACK:

         $ cd $AEROSTACK_STACK
	 
1. Update the stack:

         $ git pull origin master

1. Update  all submodules recursively:

         $ git submodule update --init --recursive

Sometimes, you will need to install new dependencies or update the old dependencies what is done by executing the following command:

         $ $AEROSTACK_STACK/installation/installation_dep_script.sh

> NOTE: Be sure that you are connected to Internet when you compile Aerostack. This is because certain packages (e.g., opentld) need to be updated from remote repositories.

## Common installation problems

| Problem | Solution |
|--|--|
| The program 'git' is currently not installed | Execute $sudo apt install git |
| Unable to access 'https://github.com/Vision4UAV/Aerostack_installer/'|Check your internet connection |
| Catkin_make: command not found|Install ROS kinetic before installing Aerostack |
|Could not find a package configuration file| Look for dependencies (using "sudo apt install") or execute: $AEROSTACK_STACK/installation/installation_dep_script.sh |

## Example video

In the following video you can see the complete installation process.

  [ ![Install tutorial](https://img.youtube.com/vi/iOfNoWsvxS0/0.jpg)](https://youtu.be/iOfNoWsvxS0)