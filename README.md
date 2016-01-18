## Safety Warning and Disclaimer

You are using this software at your own risk. The authors decline any responsibility for personal injuries and/or property damage.

Some drones supported by this framework ARE NOT TOYS. Even operation by expert users might cause SERIOUS INJURIES to people around. So, please consider flying in a properly screened or isolated flight area.

## AeroStack

We present a cost-effective framework for the prototyping of vision-based quadrotor multi-robot systems, which core characteristics are: modularity, compatibility with different platforms and being flight-proven. The framework is fully operative and based on [ROS](http://ros.org/ "Robot Operating System"). It works in simulation and in real flight tests of up to 5 drones, and was firstly introduced and demonstrated during our participation in the 2013 International Micro Air Vehicle Indoor Flight Competition [IMAV2013](http://www.imav2013.org/ "2013 International Micro Air Vehicle Indoor Flight Competition") (Toulouse, France).

The current distribution supports the usage of mutiple aerial platdorms, including, but not limited to:

- Parrot AR Drone 1.0 & 2.0.
- Asctec Pelican
- Mikrokopter Oktokopter
- Pixhawk 
- Bebop drone/Ardrone 3 (currently under development)


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

This driver has been tested on Linux machines running Ubuntu 14.04 (64 bit). However it should also work on any other mainstream Linux distributions. The driver has been tested on ROS "Jade". The code requires a compiler that is compatible with the C++11 standard. Additional required libraries are: boost and ncurses. The ROS package depends on these ROS packages: `ardrone_autonomy`, `opencv2`, `roscpp`, `image_transport`, `sensor_msgs` and `std_srvs`.

### Installation Steps

The installation follows the same steps needed usually to compile a self-contained ROS stack.

* Create the following directories

   mkdir workspace/ros/quadrotor_stack_catkin
   cd workspace/ros/quadrotor_stack_catkin

* Download the Aerostack 

  git clone -b master https://bitbucket.org/joselusl/quadrotor_swarm_sub.git ./src/quadrotor_stack

* Run the installation script file
  
  cd ~/workspace/ros/quadrotor_stack_catkin/src/quadrotor_stack/installation
  ./Installation.sh
  
  Re-open the Terminal and the Aerostack in ready to be used. 
          
## Network setup

For network setup please refer to $DRONE_STACK/documentation/configureNetwork/LAN_GroundStations_Setup.txt.
NOTE: There is no need of a network setup when using an Ardrone as it can be connected directly to the groundstation using WIFI.

### Multirotor coordinate frame

For Documentation regarding coordinate frames please refer to $DRONE_STACK/documentation/Coordinate_Frames/Multirotor_coordinate_frames.txt

## Launch scripts

In order to launch files particular to a drone there are launch files provided for each drone inside $DRONE_STACK/launchers. 
For example, for launching ARdrone2 there are launch files present inside $DRONE_STACK/launchers/ardrone_launch. The launching instruction can for the ardrone can be found in a file called ardrone_realflight_instructions.md inside this same folder. 

NOTE: Screen needs to be installed for launching these files using screen which can be installed by sudo apt-get install screen. 
Also it is recommended not to launch the interface using screen and it should be launhced in a seperate terminal using the following command
${DRONE_STACK}/launchers/ardrone_launch/sh_files/run_interface_node.sh.

For launching an complete autonoumous mission using Ardrone2, please refer to $DRONE_STACK/documentation/launch_scripts.txt. 

## How to Run

For running an complete mission the launch scripts have to be called using the following syntax in the shell terminal: 

        ```bash
        $ cd ${DRONE_STACK}/launchers/Noche_de_los_investigadores
        $ quadrotor_laNocheInvestigadores.sh NUMID_DRONE NETWORK_ROSCORE DRONE_IP DRONE_WIFI_CHANNEL
        ```

### Architecture, Map and Mission configuration

NOT UPDATED!

Check the `${DRONE_STACK}/documentation/matlab_dependencies.txt` file to understand how to configure a mission. More specifically, after adding the related Matlab libraries to your Matlab path, check the following files:
	`${DRONE_STACK}/configs/Mission_10b/script_Mission10b_Generator.m`, 
	`${DRONE_STACK}/configs/Mission_11c/script_Mission11c_Generator.m`, 
	`${DRONE_STACK}/configs/Mission_IMAV13/script_IMAV13_Generator.m` .
Once you run these scripts, copy the created drone${NUMID\_DRONE} configuration folders to the ${DRONE_STACK}/configs folder.

### Complete mission execution

After launching all required launch files in order to start the mission type in a new terminal 
  `rosservice call /drone{NUMID_DRONE}/droneMissionScheduleProcessorROSModule/start` 

### Navigation with console UI

The drone Interface is the screen which shows all the data regarding the drone example the battery status, rotation angles etc. The user can also give manual commands to the drone using the drone interface

The keybindings of the interface are specified in the file: `${DRONE_STACK}/HMI/droneInterfaceROSModule/other/keybindings_interfacejp_tentative.txt`; and are programmed in the following source file: `${DRONE_STACK}/droneInterfaceROSModule/src/sources/droneInterface_jp_ROSModuleNode.cpp` . 

If something goes wrong during the execution of the mission the user can always make the drone land or hover by giving commands using the interface. 

## Other README files

- `${DRONE_STACK}/installation/installation_instructions.txt`

- `${DRONE_STACK}/droneInterfaceROSModule/other/keybindings_interfacejp_tentative.txt` : keybindings of the console UI, which are programmed in the following source file: `${DRONE_STACK}/droneInterfaceROSModule/src/sources/droneInterface_jp_ROSModuleNode.cpp` .

NOT UPDATED!

- `${DRONE_STACK}/documentation/how_to_setup_and_use_chrony.txt`

- `${DRONE_STACK}/documentation/how_to_use_dronelogger.txt`

- `${DRONE_STACK}/documentation/matlab_dependencies.txt`

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

NOT UPDATED!


## Contributors

- [Msc. Jose Luis Sanchez-Lopez](http://www.vision4uav.com/?q=jlsanchez/personal "Msc. Jose Luis Sanchez-Lopez"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [Msc. Jesus Pestana Puerta](http://www.linkedin.com/in/jespestana/ "Msc. Jesus Pestana Puerta"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [PhD. Paloma De La Puente](http://es.linkedin.com/pub/paloma-de-la-puente/b/265/14  "PhD. Paloma De La Puente"): Postdoctoral position at [ACIN Institute of Automation and Control](http://www.acin.tuwien.ac.at/?id=248&amp;L=1 "ACIN Institute of Automation and Control"), V4R group, TU Vienna.

- [Msc. Adrian Carrio](http://es.linkedin.com/pub/adri%C3%A1n-carrio/57/a5a/753/en "Eng. Adrian Carrio"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- [Msc. Ramon Suarez](http://www.vision4uav.com/?q=ramon/personal "Msc. Ramon Suarez"): PhD. Candidate at [CVG](http://www.vision4uav.com/ "Computer Vision Group, CVG, CAR, UPM-CSIC"), CAR, CSIC-UPM.

- Msc. Hriday Bavle

- Msc. Carlos Sampedro

- [Professor Dr. Pascual Campoy](http://www.vision4uav.com/?q=pascual "Professor Dr. Pascual Campoy"): head of the , CAR, CSIC-UPM.

- Professor Dr. Sergio Dominguez

- Professor Dr. Martin Molina

- Other Members of the CVG, CAR, CSIC-UPM

- Other Memebrs of the DIA, UPM


## Contact Information

Current CVG (CAR, UPM-CSIC) staff that can give limited support to the usage of this stack are:

- Jose Luis Sanchez-Lopez: jl.sanchez@upm.es

- Jesus Pestana Puerta: jesus.pestana@upm.es

- Adrian Carrio: adrian.carrio@upm.es

- Ramon Suarez: ramon.suarez.fernandez@alumnos.upm.es

NOTE: we know that this documentation is partial. If the stack gets the interest of the community we will continue adding information depending on the questions made by its users.
