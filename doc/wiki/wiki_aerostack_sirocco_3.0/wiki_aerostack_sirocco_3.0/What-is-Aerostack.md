Aerostack is a software framework that helps developers design and build the control architecture of aerial robotic systems, integrating multiple heterogeneous computational solutions (e.g., computer vision algorithms, motion controllers, self-localization and mapping methods, motion planning algorithms, etc.). 

Aerostack is useful for building autonomous aerial systems in complex and dynamic environments and it is also a useful research tool for aerial robotics to test new algorithms and architectures.

Aerostack was created to be available for communities of researchers and developers and it is currently an active open-source project with periodic software releases. 

### Multipurpose software framework

Aerostack is versatile for building different system configurations with various degrees of autonomy:

- **From teleoperation to autonomous flight**. Aerostack can be used for teleoperation flights (with manual control) but it can also be used for building autonomous robot systems to perform aerial missions without operator assistance.

- **Single robots or multi-robot systems**. Aerostack can be used to fly a swarm of heterogeneous drones to perform multi-aerial-robot missions. It has been validated to operate with up to five drones simultaneously.

- **Flexible for different applications**. Aerostack can be used by system designers to develop their own systems in a wide range of applications. Aerostack provides languages and graphical tools to configure specific aerial missions.

- **Hardware independent**. Aerostack runs on conventional laptops and it has also run on onboard computers like mastermind or odroid XU3. Aerostack has been used in different aerial platforms, including, but not limited to:

    - Parrot AR Drone 1.0 & 2.0
    - Asctec Pelican
    - Mikrokopter Oktokopter
    - Pixhawk
    - Parrot Bebop 2
    - DJI Matrice 100

[[Files/BlocksDiagram.png]]

### Operational features

The main operational features of Aerostack are the following:

- **Library of software components for aerial robotics**. Aerostack provides a library of software components for aerial robotics (mainly programmed in C++). The components are ready to use and the library is open to add new components. For example, these components use general algorithms of aerial robotics for motion control, feature extraction (e.g., with computer vision algorithms), self localization and mapping, motion planning, etc.

- **Compositional modeling**. Aerostack uses a reference architecture with a combination scheme, based on the composition of configurable building blocks, to develop architectures for specific aerial robotic systems.

- **Distributed processing**. Distributed processing is supported by the middleware ROS (Robot Operating System). Each software component can be executed in an on-board computer or in ground computers connected in a local area network (LAN) or in a wireless local area network (WLAN), communicated using ROS.

- **Open source**. The license of the Aerostack kernel is BSD-3.

### Experience of use

Aerostack has been tested by real flight tests and simulations for different types of hardware platforms. Aerostack has been used as a tool in the following situations:

- Develop new applications in aerial robotics in problems such as infrastructure/surface inspection and air quality analysis.
- Create and test new methods in aerial robotics such as the following: using computer vision to track any object with an autonomous UAS, using a coordinator to accomplish high-level missions requested by the user with an autonomous swarm of UAS, experimenting with Natural User Interfaces for Human-Drone Interaction using hand gestures, speech, body movements and visual cues, etc.
- Participate in UAS competitions such as IMAV 2013, IARC 2014, IMAV 2016, and IMAV 2017 with successful results.



<p align="center">
<a href="http://www.youtube.com/watch?feature=player_embedded&v=t2mJftbBHWc
" target="_blank"><img src="http://img.youtube.com/vi/t2mJftbBHWc/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="480" height="360" border="1" /></a>
</p> 

<p align="center">Example of search and rescue mission using Aerostack (click to see video)</p>

### Type of applications

Developers can use Aerostack to fly UAV platforms in the following way:

- Perform tele-operated flights controlled by user commands using a graphical user interface. Examples of user commands are: take off, move forward, move backward, land, etc. The user operates with the keyboard and the mouse of the ground station computer to control the flight of the UAV.

- Following a specific mission plan, defined by the user as a set of waypoints or a set of tasks to be performed in a specific spatial area, with certain limits defined by the user.

- Use a specific physical configuration that modifies significantly the size or weight of the UAV. Our flight controllers can be adapted by the user to the new configuration.

Developers who are familiar with software programming (e.g., C++ language) can use Aerostack to fly new UAV platforms with the following characteristics:

- A UAV with new specific types of sensors. The developer can reuse Aerostack but she/he needs to program and integrate new software modules to process the information from the new sensors.

- A UAV with a different physical platform. The developer can reuse Aerostack for different UAV platforms, but she/he needs to program the interfaces between our architecture and the actuators of the new physical platform.

- A UAV with one or several software components that substitutes an existing software component (for example, a new algorithm for localization and mapping). The developer can reuse Aerostack but she/he might need to substitute the core algorithm used by the previous component.

- A UAV with new functionalities that needs additional software components. The developer can reuse Aerostack but she/he needs to program and integrate the new software modules for the new functionalities.

- Developers can also reuse specific algorithms (e.g., perception algorithms or certain controllers) that are encapsulated in their corresponding C++ classes in Aerostack. Developers can reuse these C++ classes with their algorithms to be part of their own development.

### Contributors

The main kernel of Aerostack was initially created and [pre-released in 2013](http://www.vision4uav.eu/?q=quadrotor_stack "http://www.vision4uav.eu") by Vision4UAV (Technical University of Madrid - Spain) based on the experience of this group in aerial robotics and computer vision during more than 20 years. It was firstly introduced and demonstrated during the participation of Vision4UAV in the 2013 International Micro Air Vehicle Indoor Flight Competition [IMAV2013](http://www.imav2013.org/ "2013 International Micro Air Vehicle Indoor Flight Competition") (Toulouse, France). 

In 2015, with the contribution of other members of the Technical University of Madrid from the Department of Artificial Intelligence, the software was redesigned and extended to create the present version with the name of Aerostack (AErial RObotics STACK). This new version was the evolution from a previous control-oriented architecture to a more structured multi-layered architecture following hybrid paradigms (e.g., with deliberative and reactive layers) and social coordination. The first release of Aerostack (Version 1.0, Gregale distribution) was in June 2016.

Currently, a team from the Technical University of Madrid provides support for Aerostack. You can contact the team support at the following address:

- aerostack.upm@gmail.com

The following list includes Aerostack contributors:

Aerostack administrators:

- Hriday Bavle
- Alberto Rodelgo
- Pablo Santamaría

Research professors:

- [Pascual Campoy](http://www.vision4uav.eu/?q=pascual)
- [Martin Molina](https://martinmolinagonzalez.wordpress.com)
- [Paloma de la Puente](http://www.upm.es/observatorio/vi/index.jsp?pageac=investigador.jsp&idInvestigador=12067) 

Research assistants (current):

- Adrián Alvarez
- Abraham Carrera
- Adrián Carrio
- Miguel Fernández
- Lu Liang
- Alberto Rodelgo
- Alejandro Rodríguez-Ramos
- Javier Rodríguez-Vazquez
- Carlos Sampedro
- Jose Luis Sánchez-Lopez
- Ramon Suárez-Fernandez

Research assistants (past):

- Alberto Camporredondo
- Jean-François Collumeau
- Jesus Pestana Puerta 
- Pablo Santofimia 

Software developers:

- Javier Melero [2020], John Bradley [2020]
- Pablo Santamaría [2019-2020], Javier Cabrera [2019-2020], Adrián Cabrera [2019-2020], Marcos Tirado [2019], Laura Colomer [2019] 
- Daniel del Olmo [2018-2019], José Martín-Antequera [2018-2019], Guillermo Echegoyen [2018], Raúl Cruz [2018-2019]
- Rafael Artiñano [2017-2018], Jorge Pascual [2017], Daniel Rabasco [2017], Jorge Sánchez [2017], Pedro Frau Amar [2017]
- Guillermo de Fermín [2016-2017], Carlos Valencia [2016-2017], Germán Quintero [2016]
- Adrian Díaz-Moreno [2015-2016], David Palacios [2015-2016], Enrique Ortiz [2015], Adrián Navarro [2015], Angel Luis González [2015], Laura García [2015], Oscar Fernández [2015]
- Yolanda de la Hoz [2014-2015], Marcos Bernal [2014-2015] 
- Jorge Martin [2013-2014]

### Funding support

The research work and development related to Aerostack has received the following public funding support:

* 2019-2021: Project "Comcise: Complex coordinated inspection and security missions by UAVs in cooperation with UGV". This project has received funding from the Ministry of Science, Innovation and Universities of Spain, reference RTI2018-100847-B-C21.

* 2018-2019: Focused technical project (FTP) "Aerostack 3.0: Aerial robotics framework for the industry". This FTP has received funding from the European Union’s Horizon 2020 research and innovation programme under the [project ROSIN](http://rosin-project.eu) with the grant agreement No 732287

* 2015-2017: Project "VA4UAV: Visual autonomy for UAV in Dynamic Environments". This project has received funding from the Ministry of Economy and Competitiveness of Spain, reference DPI2014-60139-R.

Besides public funding, Aerostack is being developed with the help of own funding of the research group CVAR-UPM.