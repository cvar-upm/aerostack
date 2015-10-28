## Safety Warning and Disclaimer

You are using this software at your own risk. The authors decline any responsibility for personal injuries and/or property damage.

Some drones supported by this framework ARE NOT TOYS. Even operation by expert users might cause SERIOUS INJURIES to people around. So, please consider flying in a properly screened or isolated flight area.

## cvg_quadrotor_swarm stack


NOT UPDATED. FOR INSTALATION GO TO installation/installation_instructions.txt

We present a cost-effective framework for the prototyping of vision-based quadrotor multi-robot systems, which core characteristics are: modularity, compatibility with different platforms and being flight-proven. The framework is fully operative and based on [ROS](http://ros.org/ "Robot Operating System"). It works in simulation and in real flight tests of up to 5 drones, and was demonstrated during our participation in the 2013 International Micro Air Vehicle Indoor Flight Competition [IMAV2013](http://www.imav2013.org/ "2013 International Micro Air Vehicle Indoor Flight Competition") (Toulouse, France).

The current distribution supports only the usage of the AR Drone 1.0 & 2.0. The architecture has been modified to be able to handle other platforms such as the: UASTech LinkQuad, Mikrokopter Oktokopter and the Asctec Pelican. Suitable driver modules for these quadrotors are currently in development.

The connectivity between modules of the stack is specified in:
`${DRONE_STACK}/documentation/system_module_architecture.png` . Where ${DRONE_STACK} refers to the folder where this software stack was downloaded. 

The functionality of the modules and the full AeroStack is explained in the following papers, please, refer to them in your work:
- J. L. Sanchez-Lopez, J. Pestana, P. de la Puente, P. Campoy. "A Reliable Open-Source System Architecture for the Fast Designing and Prototyping of Autonomous Multi-UAV Systems: Simulation and Experimentation". Journal of Intelligent and Robotic Systems. Online: Oct. 2015. Springer Netherlands. Online ISSN: 0921-0296. DOI: 10.1007/s10846-015-0288-x.
- J. L. Sanchez-Lopez, J. Pestana, P. de la Puente, R. Suarez-Fernandez, P. Campoy. "A System for the Design and Development of Vision-based Multi-robot Quadrotor Swarms". 2014 International Conference on Unmanned Aircraft Systems (ICUAS’14). Orlando (FL, USA). May 27-30, 2014. Pp: 640-648. DOI: 10.1109/ICUAS.2014.6842308.

Other related papers (selection):
- J. L. Sanchez-Lopez, J. Pestana, J.-F. Collumeau, R. Suarez-Fernandez, P. Campoy, M. Molina. "A Vision Based Aerial Robot solution for the Mission 7 of the International Aerial Robotics Competition". Unmanned Aircraft Systems (ICUAS), 2015 International Conference on. Denver, (CO, USA). 9-12 June 2015. Pp: 1391 – 1400. Print ISBN: 978-1-4799-6009-5. DOI: 10.1109/ICUAS.2015.7152435
- J. Pestana, J. L. Sanchez-Lopez, P. de la Puente, A. Carrio, P. Campoy. "A Vision-based Quadrotor Swarm for the participation in the 2013 International Micro Air Vehicle Competition". 2014 International Conference on Unmanned Aircraft Systems (ICUAS’14). Orlando (FL, USA). May 27-30, 2014. Pp: 617-622. DOI: 10.1109/ICUAS.2014.6842305.
- J. L. Sanchez-Lopez, J. Pestana, P. de la Puente, A. Carrio, P. Campoy. "Visual Quadrotor Swarm for the IMAV 2013 Indoor Competition". Robot 2013: First Iberian Robotics Conference (ROBOT 2013). Madrid (Spain). Nov. 28-29, 2013. Book title: Robot 2013: First Iberian Robotics Conference. Book subtitle: Advances in intelligent Systems and Computing. Vol. 253. Published year: 2014. Pp: 55-63. DOI: 10.1007/978-3-319-03653-3_5. Print ISBN: 978-3-319-03652-6. Online ISBN: 978-3-319-03653-3. Publisher: Springer International Publishing.

The functionality of the modules and the full AeroStack is explained in the following webpages:
- [http://www.vision4uav.eu/?q=quadrotor_stack](http://www.vision4uav.eu/?q=quadrotor_stack "http://www.vision4uav.eu")
- [http://www.vision4uav.eu/?q=swarm](http://www.vision4uav.eu/?q=swarm "http://www.vision4uav.eu")
- [http://www.vision4uav.eu/?q=imav13](http://www.vision4uav.eu/?q=imav13 "http://www.vision4uav.eu")

## Table of Contents

- [Installation](#installation)
	- [Pre-requirements](#pre-requirements)
	- [Installation Steps](#installation-steps)
- [Network setup](#Network-setup)
- [Launch scripts](#Launch-scripts)
- [Coordinate Frames](#Coordinate-Frames)
- [How to Run](#how-to-run)
	- [Navigation with console UI](#Navigation-with-console UI)
	- [Complete mission execution](#Complete-mission-execution)
- [Other README files](#Other-README-files)
- [License](#license)
- [Contributors](#Contributors)
- [Contact Information](#Contact-Information)

## Installation
### Pre-requirements 

This driver has been tested on Linux machines running Ubuntu 12.10 (64 bit). However it should also work on any other mainstream Linux distributions. The driver has been tested on ROS "groovy". The code requires a compiler that is compatible with the C++11 standard. Additional required libraries are: boost and ncurses. The ROS package depends on these ROS packages: `ardrone_autonomy`, `opencv2`, `roscpp`, `image_transport`, `sensor_msgs` and `std_srvs`.

### Installation Steps

The installation follows the same steps needed usually to compile a self-contained ROS stack.

NOT UPDATED!!!!!!! FOR INSTALATION GO TO installation/installation_instructions.txt

* Install ncurses and the boost libraries in your system.

        sudo apt-get install libncurses5
        sudo apt-get install ncurses-bin
        sudo apt-get install ncurses-dev
        sudo apt-get install libboost1.49-dev


* Create a ROS_WORKSPACE to install the stack and the required external ROS packages and stacks. For example, A ROS_WORKSPACE can be configured in the folder. `~/workspace/ros/quadrotor`. The following steps are advised:

        # create the ~/workspace/ros/quadrotor folder
        cd ~
        mkdir workspace
        cd workspace
        mkdir ros
        cd ros
        mkdir quadrotor
        cd quadrotor
        # initialize ROS workspace using ROS groovy
        rosws init ./ /opt/ros/groovy


* Download the required ROS packages using git or rosws:

        # create folder where external ROS stacks are downloaded
        rosws set ./extStack
        # set folder to download the ardrone_autonomy ROS package
        rosws set ./extStack/ardrone_autonomy --git https://github.com/AutonomyLab/ardrone_autonomy.git --version=fuerte
        # set folder to download the cvg_quadrotor_swarm ROS package
        rosws set ./stack --git https://bitbucket.org/joselusl/quadrotor_swarm.git
        # set folder to download the Mikrokopter Oktokopter driver 
        rosws set ./extStack/okto_driver --git https://bitbucket.org/Vision4UAV/okto_driver.git
        # set folder to download the AscTec Quadrotor drivers
        rosws set ./extStack/asctec_drivers --git https://github.com/ccny-ros-pkg/asctec_drivers --version=fuerte
        # set folder to download the Px4Flow drivers
        rosws set ./extStack/px-ros-pkg --git https://github.com/cvg/px-ros-pkg --version=rosbuild
        # set folder to download the ROS Micro Air Vehicle tools
        rosws set ./extStack/mav_tools --git https://github.com/ccny-ros-pkg/mav_tools --version=fuerte
        # set folder to download the OpenTLD tracker
        rosws set ./extStack/ros_opentld --git https://github.com/Ronan0912/ros_opentld
        # download latest version of all packages using git, through the rosws command
        rosws update


* Set up the `DRONE_STACK` and `DRONE_WORKSPACE` environment variables. 

        ./stack/documentation/installation/installers/installWS.sh
        cd stack
        ./documentation/installation/installers/installStack.sh

        

* Each time the cvg_quadrotor_swarm is going to be used, do the following (note that the ROS_WORKSPACE and other ROS environment variables should not be loaded in the .bashrc file or other ubuntu terminal startup files):

        cd ${DRONE_STACK}
        source setup.sh

        
* Final steps installation instructions:

        cd ${DRONE_STACK}
        source setup.sh
        rospack profile
        rosdep update
        # Compile external ROS packages: ardrone_autonomy
        cd ../extStack/ardrone_autonomy/
        roscd ardrone_autonomy
        ./build_sdk.sh

        
* Compile the stack:

        cd ${DRONE_STACK}/launchers/
        ./rosmake_01.sh
        ./rosmake_sim_01.sh

        
## Network setup

First: checkout the related ROS tutorial `http://wiki.ros.org/ROS/NetworkSetup` .

Then, follow these steps:

1. Configure a LAN network connection to communicate this ground stations with the rest using ROS. The configuration that we have used during testing is shown in the image (in this folder): `${DRONE_STACK}/documentation/network_configuration/ROS_NETWORK_config.png` (from now called ROS_NETWORK).

2. Edit the hosts file, all the computers in the network have to be included in it. The IPs have to be the same that is specified in the configuration of each computer's ROS_NETWORK configuration.

	- to edit the hosts file, run: sudo gedit /etc/hosts
	- an example of it is shown in the file (in this folder): `${DRONE_STACK}/documentation/network_configuration/hosts`

3. Restart your network for the configuration changes to take place.

## Coordinate Frames

There are several coordinate frames, which location is briefly documented in `${DRONE_STACK}/documentation/Coordinate_Frames/Coordinate_Frames_documentation.tex/pdf`. Please, refer to this documentation to understand the coordinate frames involved in running the software stack.

### Multirotor coordinate frame

In the documentation located in `${DRONE_STACK}/documentation/Coordinate_Frames/Coordinate_Frames_documentation.tex/pdf`, this reference frame is called F_{drone_LMrT}.

The reference frame that is used to reference the multirotor's telemetry, broadcasted by the multirotor's ROS driver, is:

	[Fm] the mobile reference frame is centered on the drone, with:
	 [xm] horizontal and pointing forward (same direction as the optical axis of the frontal camera
	 [ym] horizontal and pointing rightwards from the center of the drone
	 [zm] vertical and pointing downwards
	
	[F] the fixed reference frame:
	 [x] horizontal and pointing "North" (where the magnetometer reading finds the North)
	 [y] horizontal and pointing "East"
	 [z] vertical and pointing downwards (the z coordinate of the drone is, thus, always negative)
	
	[yaw (mobile to fixed)] increases when the drones rotate in clock-wise direction

The sign convention for the commands, received by the multirotor's ROS driver, is the following:

	[paraphrased] The yaw, pitch, roll angles commands are related to the above mentioned [Fm] reference frame (thus setting their sign convention). The dz/"gaz" command is such that the AR Drone is commanded to go higher (increased altitude) when dz/"gaz" is positive. It can be thought of as the dz/"gaz" command setting a higher thrust on the propellers. 

	[comment] the following phrases are understood from the point of view of a person sitting on the drone looking forward (looking in the same direction as the frontal camera), under no external wind conditions.
	[pitch][+] move backwards
	[pitch][-] move forward
	[roll][+] move rightwards
	[roll][-] move leftwards
	[dyaw][+][speed command] rotate clockwise (as seen from above), or N > E > S > W > N > ...
	[dyaw][-][speed command] rotate counter-clockwise (as seen from above), or N > W > S > E > N > ...
	[dz][+][speed command] increase altitude, move upwards
	[dz][-][speed command] decrease altitude, move downwards


## Launch scripts

In order to compile the stack, the following scripts are provided (please take a look at them to understand how to modify them for your own purposes):

- `${DRONE_STACK}/launchers/rosmake_sim_01.sh` : for simulated flights.

- `${DRONE_STACK}/launchers/rosmake_01.sh` : for experimental flights.


In order to run the stack, it was decided to run each node in a separate tab of a terminal window. The initialization of the architecture is done by executing shell scripts that open a new terminal with each node running in its tab. The scripts that are available are the following (please take a look at them to understand how do they work):

- `${DRONE_STACK}/launchers/quadrotor_Test02.sh` : runs all the nodes required for an experimental flight.

- `${DRONE_STACK}/launchers/quadrotor_Test02_no_logging.sh` : same as previous, but without logging.

- `${DRONE_STACK}/launchers/quadrotor_Testsim02.sh` : runs all the nodes required for simulation.

- `${DRONE_STACK}/launchers/quadrotor_Testsim03.sh` : same as previous, but runs the ArucoEye simulator module.

- `${DRONE_STACK}/launchers/quadrotor_Testsim03_logging.sh` : same as previous, but with logging.

- `${DRONE_STACK}/launchers/rvizInterface_Test.sh` : runs rviz with an specific configuration and an interfacing mode that converts some architecture messages to rviz markers.

The launch scripts have to be called using the following sintax in the shell terminal: 

```bash
$ cd ${DRONE_STACK}/launchers
$ launcher_script.sh NUMID_DRONE NETWORK_ROSCORE DRONE_IP DRONE_WIFI_CHANNEL
$ # example
$ launcher_script.sh 2 ROS_10 '' 11
```
- The configuration files (mission, known ArUco markers locations, controller configuration, etc) are located in `${DRONE_STACK}/configs/drone${NUMID\_DRONE}/` . Many of the stack nodes access these files in order to read their configuration parameters.



NOTE: all the launchfiles open a separate terminal with multiple tabs, where each tab usually runs only one tab. If you close the terminal tabs using the close button at the corner of the window which has multiple tabs, then only one of the tabs will be closed correctly (the one that is currently selected):

- The easiest way to do this fast, and cleanly is to: first, press `control+c` on every tab (navigating with `control+repag` and `control+avpag`), second, use the shortcut `ctrl+shift+w` to close first all terminal tabs and, third, `ctrl+shift+q` to close the las terminal tab (which closes the window too) including all tabs. 

- The following script might be used to send a SIG\_TERM to all the terminals (equivalent to pressing `control+c` in them): ${DRONE_STACK}/launchers/stop.sh .

## How to Run

The launch scripts have to be called using the following sintax in the shell terminal: 

        ```bash
        $ cd ${DRONE_STACK}/launchers
        $ launcher\_script.sh NUMID\_DRONE NETWORK\_ROSCORE DRONE\_IP DRONE\_WIFI\_CHANNEL
        ```

### Architecture, Map and Mission configuration

Check the `${DRONE_STACK}/documentation/matlab_dependencies.txt` file to understand how to configure a mission. More specifically, after adding the related Matlab libraries to your Matlab path, check the following files:
	`${DRONE_STACK}/configs/Mission_10b/script_Mission10b_Generator.m`, 
	`${DRONE_STACK}/configs/Mission_11c/script_Mission11c_Generator.m`, 
	`${DRONE_STACK}/configs/Mission_IMAV13/script_IMAV13_Generator.m` .
Once you run these scripts, copy the created drone${NUMID\_DRONE} configuration folders to the ${DRONE_STACK}/configs folder.

### Complete mission execution

In order to start the modules automatically the flight is started using the brain node, which starts the mission by clicking 's'.

### Navigation with console UI

The keybindings of the interface are specified in the file: `${DRONE_STACK}/droneInterfaceROSModule/other/keybindings_interfacejp_tentative.txt`; and are programmed in the following source file: `${DRONE_STACK}/droneInterfaceROSModule/src/sources/droneInterface_jp_ROSModuleNode.cpp` . 

In order to start the modules automatically the flight is started using the brain node, which starts the mission by clicking 's'. Once the mission is started, the user can enter the hovering mode of the AR Drone by clicking 'h' on the UI console. Then by killing the mission planner and the trajectory planner, he can access full control of the drone through the UI console (and send commands to the trajectory controller and so on).

As an alternative, the user can start the modules by hand (or editing a convenient shell script) by using the `/droneModuleName/start` service of every module in the architecture.

## Other README files

- `${DRONE_STACK}/documentation/how_to_setup_and_use_chrony.txt`

- `${DRONE_STACK}/documentation/how_to_use_dronelogger.txt`

- `${DRONE_STACK}/documentation/matlab_dependencies.txt`

- `${DRONE_STACK}/documentation/qtcreator_instructions.txt`

- `${DRONE_STACK}/droneInterfaceROSModule/other/keybindings_interfacejp_tentative.txt` : keybindings of the console UI, which are programmed in the following source file: `${DRONE_STACK}/droneInterfaceROSModule/src/sources/droneInterface_jp_ROSModuleNode.cpp` .


## License

All distributed software, except the packages listed in the following, are subject to `3-clause BSD` license (see the file: `LICENSE`). 

This software stack uses other third-party open-source libraries (some of them are inluded in the soure of the stack as separate packages):

- Robot Operating System ([ROS](http://ros.org/ "Robot Operating System")), license: `BSD` license, not included in the source of the stack.

- ardrone_autonomy ROS package ([ardrone_autonomy](https://github.com/AutonomyLab/ardrone_autonomy "ardrone_autonomy ROS package")), license: `BSD` license, not included in the source of the stack.

- Open Source Computer Vision library ([OpenCV](http://opencv.org/ "OpenCV")), license: `BSD` license, not included in the source of the stack.

- ArUco: a minimal library for Augmented Reality applications based on OpenCv ([ArUco](http://www.uco.es/investiga/grupos/ava/node/26 "ArUco")), original license: `BSD` license, included as source in the stack in the `lib_aruco` package.

- pugixml library ([pugixml](http://pugixml.org/ "pugixml")), original license: `MIT` license, included as source in the stack in the `lib_pugixml` package.

- newmat11 library, a matrix library in C++ ([newmat11](http://www.robertnz.net/nm11.htm "newmat11, a matrix library in C++")), original license: ([newmat11 license](http://www.robertnz.net/nm11.htm#use "newmat11 library license")), included as source in the stack in the `lib_newmat` package.

- other software libraries used by this stack also uses licenses similar to `BSD` and `MIT` licenses: [ncurses](https://www.gnu.org/software/ncurses/ "GNU ncurses") and [boost](http://www.boost.org "boost c++ libraries").


## Contributors

- [Msc. Jose Luis Sanchez-Lopez](http://www.vision4uav.com/?q=jlsanchez/personal "Msc. Jose Luis Sanchez-Lopez"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [Msc. Jesus Pestana Puerta](http://www.linkedin.com/in/jespestana/ "Msc. Jesus Pestana Puerta"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [PhD. Paloma De La Puente](http://es.linkedin.com/pub/paloma-de-la-puente/b/265/14  "PhD. Paloma De La Puente"): Postdoctoral position at [ACIN Institute of Automation and Control](http://www.acin.tuwien.ac.at/?id=248&amp;L=1 "ACIN Institute of Automation and Control"), V4R group, TU Vienna.

- [Eng. Adrian Carrio](http://es.linkedin.com/pub/adri%C3%A1n-carrio/57/a5a/753/en "Eng. Adrian Carrio"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [Msc. Ramon Suarez](http://www.vision4uav.com/?q=ramon/personal "Msc. Ramon Suarez"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [Professor Dr. Pascual Campoy](http://www.vision4uav.com/?q=pascual "Professor Dr. Pascual Campoy"): head of the , CAR, CSIC-UPM.


## Contact Information

Current CVG (CAR, UPM-CSIC) staff that can give limited support to the usage of this stack are:

- Jose Luis Sanchez-Lopez: jl.sanchez@upm.es

- Jesus Pestana Puerta: jesus.pestana@upm.es

- Adrian Carrio: adrian.carrio@upm.es

- Ramon Suarez: ramon.suarez.fernandez@alumnos.upm.es

NOTE: we know that this documentation is partial. If the stack gets the interest of the community we will continue adding information depending on the questions made by its users.
