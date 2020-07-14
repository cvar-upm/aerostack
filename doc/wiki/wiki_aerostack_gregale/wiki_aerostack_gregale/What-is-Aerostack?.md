Aerostack is a software framework that helps developers design and build the control architecture of aerial robotic systems, integrating multiple heterogeneous computational solutions (e.g., computer vision algorithms, motion controllers, self localization and mapping methods, planning algorithms, etc.). 

Aerostack is useful for building autonomous aerial systems in complex and dynamic environments and it is also a useful research tool for aerial robotics to test new algorithms and architectures.

Aerostack was created to be available for communities of researchers and developers and it is currently an active open-source project (with license GPL) with periodic software releases. 

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
    - Bebop

### Operational features

The main operational features of Aerostack are the following:

- **Library of software components for aerial robotics**. Aerostack provides a library of software components for aerial robotics programmed in C++ and Python. The components are flight-proven and ready to use and the library is open to add new components. For example, these components use general algorithms of aerial robotics for motion control, feature extraction (e.g., with computer vision algorithms), self localization and mapping, motion planning, etc.

- **Compositional modeling**. Aerostack provides an architectural pattern with a combination scheme, based on the composition of configurable building blocks, to develop different specific architectures. 

- **Distributed processing**. Distributed processing is supported by the middleware ROS (Robot Operating System). Each software component can be executed in an on-board computer or in ground computers connected in a local area network (LAN) or in a wireless local area network (WLAN), communicated using ROS.

- **Open source**. License GPL v3.

- **Reusable components**. Aerostack uses ROS as the middleware, but we divided all the functionalities into non-ROS libraries and ROS-nodes. That means, all the functionalities and algorithm cores are coded without ROS, in a pure C++ or Python style.

[[images/BlocksDiagram.png]]

### Experience of Use

Aerostack is fully operative, validated by real flight tests and simulations for different types of hardware platforms. Aerostack has been used as a tool in the following situations:

- Develop new applications in aerial robotics in problems such as infrastructure/surface inspection and air quality analysis.
- Create and test new methods in aerial robotics such as the following: using computer vision to track any object with an autonomous UAS, using a coordinator to accomplish high-level missions requested by the user with an autonomous swarm of UAS, experimenting with Natural User Interfaces for Human-Drone Interaction using hand gestures, speech, body movements and visual cues, etc.
- Participate in UAS competitions such as IMAV 2013, and IARC 2014, IMAV 2016 with successful results. 

### Types of Applications

Developers can use Aerostack to fly UAV platforms in the following way:

- Perform tele-operated flights controlled by user commands using the Human Machine Interface. Examples of user commands are: take off, move forward, move backward, turn, move up, move down, land, etc. The user operates with the keyboard and the mouse of the ground station computer to control the flight of the UAV.

- Tracking a selected object by visual contact. The user can select the object to track by selecting camera images using the Human Machine Interface.

- Following a specific mission plan, defined by the user as a set of waypoints or a set of tasks to be performed in a specific spatial area, with certain limits defined by the user.

- Use a specific physical configuration that modifies significantly the size or weight of the UAV. Our flight controllers can be adapted by the user to the new configuration (in a XML file).

Developers who are familiar with software programming (e.g., C++ language) can use Aerostack to fly new UAV platforms with the following characteristics:

- A UAV with new specific types of sensors. The developer can reuse Aerostack but she/he needs to program and integrate new software modules to process the information from the new sensors.

- A UAV with different physical platform. The developer can reuse Aerostack for different UAV platforms, but she/he needs to program the interfaces between our architecture and the actuators of the new physical platform.

- A UAV with one or several software components that substitutes an existing software component (for example, a new localization and mapping). The developer can reuse Aerostack but she/he might need to substitute the core algorithm used by the previous component within the package of optional processes.

- A UAV with new functionalities that needs additional software components. The developer can reuse Aerostack but she/he needs to program and integrate the new software modules for the new functionalities.

- Developers can also reuse specific algorithms (e.g., perception algorithms or certain controllers) that are encapsulated in their corresponding C++ classes in Aerostack. Developers can reuse these C++ classes with their algorithms to be part of their own development.

### Contributors

The main kernel of Aerostack was initially created and pre-released in 2013 by Vision4UAV (Technical University of Madrid - Spain) based on the experience of this group in aerial robotics and computer vision during more than 20 years. It was firstly introduced and demonstrated during the participation of Vision4UAV in the 2013 International Micro Air Vehicle Indoor Flight Competition [IMAV2013](http://www.imav2013.org/ "2013 International Micro Air Vehicle Indoor Flight Competition") (Toulouse, France). 

In 2015, with the contribution of other members of the Technical University of Madrid from the Department of Artificial Intelligence, the software was redesigned and extended to create the present version with the name of Aerostack (AErial RObotics STACK). This new version was the evolution from a previous control-oriented architecture to a more structured multi-layered architecture following hybrid paradigms (e.g., with deliberative and reactive layers) and social coordination. The first release of Aerostack (Version 1.0, Gregale distribution), as a mature documented product, was in June 2016.

Currently, a team from the Technical University of Madrid provides support for Aerostack. You can contact the team support at the following address:

- aerostack.vision4uav@gmail.com

The following list includes Aerostack contributors:

Aerostack administrators:
- Jose Luis Sanchez-Lopez
- Hriday Bavle

Research professors:
- [Pascual Campoy](http://www.vision4uav.eu/?q=pascual)
- [Martin Molina](https://martinmolinagonzalez.wordpress.com)
- [Paloma de la Puente](http://www.upm.es/observatorio/vi/index.jsp?pageac=investigador.jsp&idInvestigador=12067) 

Research assistants:
- Adrian Carrio
- Jean-François Collumeau
- Jesus Pestana Puerta 
- Alejandro Rodriguez Ramos
- Carlos Sampedro 
- Ramon Suarez-Fernandez

Software developers:
- Jorge Martin [2013-2014]
- Marcos Bernal [2014-2015]
- Yolanda de la Hoz [2014-2015]
- Enrique Ortiz [2015]
- Adrian Navarro [2015]
- Angel Luis Gonzalez [2015]
- Laura Garcia [2015]
- Oscar Fernandez [2015]
- Adrian Diaz-Moreno [2015-2016]
- David Palacios [2015-2016]
- German Quintero [2016]
- Guillermo de Fermín [2016-2017]
- Alberto Camporredondo [2016-2017]
- Carlos Valencia [2016-2017]
- Jorge Pascual [2017]
- Rafael Artiñano [2017]
- Daniel Rabasco [2017]

### Funding Support

The development of Aerostack has been partially supported by the Spanish Ministry of Economy and Competitiveness through the
project VA4UAV (Visual autonomy for UAV in Dynamic Environments) reference DPI2014-60139-R.