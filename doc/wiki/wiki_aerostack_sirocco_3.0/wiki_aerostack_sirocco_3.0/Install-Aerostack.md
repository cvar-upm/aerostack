## Hardware and software requirements

To install Aerostack, you need to meet these requirements:

- A non-ARM architecture computer.
- 2 GB of free disk space.
- (Good) internet connection.
- Linux Ubuntu 18.04 with ROS Melodic or Linux Ubuntu 16.04 with ROS Kinetic. 
- The code requires a compiler that is compatible with the C++11 standard.

## License agreement

Before the installation, you must [read and accept the conditions defined by the software license](https://github.com/Vision4UAV/Aerostack/wiki/License)

## Installation method of a specific project

This installation method is appropriate to install a project developed using Aerostack. This method only installs the set of modules of Aerostack that are needed for the project. During the installation, the user has to provide the name of the project. Please, consult the following link to know the available example projects:

* [[Example projects]]

To install the project, perform the following steps: 

1. Download the installation files:

        $ git clone https://github.com/Vision4UAV/aerostack_installer.git ~/temp

1. Run the following installation script to install the project called `teleoperation_drone_simulator`, which is located in the folder `projects` (you can install any other available project of [[example projects]]):

        $ ~/temp/install_project.sh projects/teleoperation_drone_simulator

### Update the project

In order to update the modules of a project, execute the following script:

        $ ./$AEROSTACK_STACK/update_project_modules.sh

## Installation method (full version)

This method downloads and builds all the components of Aerostack.

1. Download the installation script file: 

        $ git clone https://github.com/Vision4UAV/aerostack_installer.git ~/temp

2. Execute the installation script:
      
        $ ~/temp/install_full_aerostack.sh

3. Re-open the Terminal and the Aerostack is ready to be used.

### Update Aerostack

In order to update Aerostack, execute the following commands:

        $ cd $AEROSTACK_STACK
        $ git pull origin master 
        $ git submodule sync
        $ git submodule update --init
        $ cd $AEROSTACK_STACK/installation && ./install_dependencies.sh