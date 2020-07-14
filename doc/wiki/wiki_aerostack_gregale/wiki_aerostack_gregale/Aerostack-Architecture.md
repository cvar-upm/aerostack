

This section summarizes the main components of the Aerostack architecture and its structural organization.

### Main Components

The next figure shows the main functional components of the architecture. This architecture follows the hybrid reactive/deliberative paradigm, i.e., an architecture that integrates both a deliberative and reactive approaches [Arkin et al., 1987]. Our design includes five layers: reactive, executive, deliberative, reflective and social. The first three layers correspond to the popular hybrid design known as the three layer architecture [Gat ,1998] that organizes algorithms according to whether they contain no internal state (reactive layer), contain state reflecting memories about the past (executive layer) or contain state reflecting predictions about the future (deliberative layer). 

[[images/Architecture.png]]

In particular, the Aerostack architecture includes the following layers [Russel, Norvig, 2003]: (1) reactive layer with low-level control with sensor-action loops; (2) executive layer (or sequencing layer) that accepts directives from the deliberative layer and sequences them for the reactive layer; this layer also integrates the sensor information into an internal state representation; and (3) the deliberative layer generates global solutions to complex tasks using planning.

The reactive layer is a sensor-action loop that includes perceptual schemas (in the feature extraction system) and controllers (in the motor system):

- Perceptual schemas may read simple states of sensors or may implement complex vision and pattern recognition algorithms. Examples of perceptual schemas are: read bumper, extract color, compute centroid of an image (white), recognize Aruco visual marker, detect power line tower, detect IARC ground robot, detect IARC obstacle, etc. A perceptual schema can integrate a set of perception procedures using different combination methods (e.g., fusion, sequence, etc.). 

- Maneuver controllers typically implement combinations of Proportional-Integral-Derivative (PID) controllers (e.g., cascade controllers). For example, these type of controllers can accept orders about a desired value for a variable (position, speed, altitude, and yaw) in form of single commands or simultaneous commands that are translated into low level commands to be sent to the actuator interface. Controllers are used by the behavior manager. The behavior manager receives a high level command about a desired action (e.g., follow a trajectory, move to a desired position, etc.) and translates it into setpoints for controllers. 

Besides the mentioned three layers, the architecture includes other two, inspired by certain cognitive architectures in artificial intelligence. We include a self reflective layer [Singh, Minsky, 2005] to supervise the first three layers and include fault recovery actions. A social layer is also included with communication abilities, as it is proposed in multiagent systems and other architectures with social coordination (e.g., [Duffy, 2000]).

The architecture is also consistent with the usual components related to guidance, navigation and control of unmanned rotorcraft systems [Kendoul, 2012]. In particular, the Navigation System (NS) corresponds to our perception system and situation awareness system, the Guidance System (GS) corresponds to our executive system, planning system and supervision system and, finally, the Flight Control System (FCS) corresponds to our motor system.


### Architecture Organization: Processes and Systems

Aerostack has been developed as a multi-process architecture supported by ROS (Robotic Operating System). The basic component of the architecture is the process. We distinguish between the intuitive meaning of a process (what represents) and its computational support (how it is implemented). In general, the intuitive meaning of a process is a series of actions taken in order to achieve a particular end. A process acts through time to change certain parameters of objects (e.g., certain physical quantities), consuming resources (e.g., time or space) to convert inputs into outputs. It is important to note that a process has a function, i.e., a purpose or practical use for which the process is designed or exists (the intention or the objective of the process). 

The idea of process is an appropriate concept to describe the components of the architecture of Aerosack. It helps to divide the whole problem of automated support for UAVs into partial functional roles. Each process in Aerostack is named as an active processor with its main function, for example: mission planner (main function: planning a mission) or obstacle recognizer (main function: recognize obstacles). 

The computational support of a process is designed as an atomic executable unit (a data processor) that receives input data and, as a result of a certain information processing, generates output data. A process in Aerostack corresponds to the concept of a ROS node. The idea of a process is also similar to the concept of an atomic functional block used in SysML with input/output ports. When Aerostack is running for a particular UAV, each process is an executable instance of a program running in a computer (each process can also call subprocesses, child computational processes). 

Processes are grouped in systems. A system is a complex module that includes a set of interconnected processes that provides a common functionality. The idea of system is also similar to the concept of functional block (composite block) used in SysML, with input/output ports.

To consult the available processes provided by Aerostack, consult the following catalog:

- [[Catalog of Available Processes]]

### Inter-Process Communication

In general, the inter-process communication (IPC) in multitasking operating systems, where different processes run concurrently, admits different communication mechanisms such as pipes, message queues, semaphores, sockets, shared memory, etc. Aerostack uses communication methods provided by ROS: 

- Topics. Processes can communicate input and output data using topics. According to ROS, topics are named buses over which processes exchange messages. In general, processes are not aware of who they are communicating with. Instead, processes that are interested in data read (or subscribe) the relevant topic and processors that generate data write (or publish) to the relevant topic. Processes can communicate with each other by publishing messages to topics. A message is a simple data structure, comprising typed fields. Messages can include arbitrarily nested structures and arrays. Files .msg files are simple text files for specifying the data structure of a message. 

- Services. A service is a communication mechanism between processes based on a request-reply scheme. A service is defined by a pair of messages: one for the request and one for the reply.

Next figure shows a graphical notation to describe the inter-process communication of data processors of the Aerostack architecture. This notation is based partially on functional block diagrams and SysML (internal block diagrams).

[[images/Processes.png]]

### References

- Arkin, R. C., Riseman, E. M., and Hansen, A. (1987): “AuRA: An Architecture for Vision- Based Robot Navigation,” proceedings of the DARPA Image Understanding Work-shop, Los Angeles, CA, February, pp. 417–413.

- Duffy, B.R. (2001). “The Social Robot”. Doctoral dissertation, Dept. of Computer Science, University College Dublin, Ireland.

- Gat , E. (1998): “On Three-Layer Architectures”. In “Artificial Intelligence and Mobile Robots”, (David Kortenkamp, R. Peter Bonnasso, and Robin Murphy, eds.) AAAI Press.

- Kendoul, F. (2012). Survey of advances in guidance, navigation, and control of unmanned rotorcraft systems. Journal of Field Robotics, 29(2), 315-378.

- Qi, X., Theilliol, D., Qi, J., Zhang, Y., Han, J., Song, D., Wang, L., Xia, Y. (2013): ”Fault diagnosis and fault tolerant control methods for manned and unmanned helicopters: a literature review”. Proceedings of the Conference on Control and Fault-Tolerant Systems (SysTol) (pp. 132-139), October 9-11, 2013, Nice, France. IEEE.

- Russel, S; Norvig, P (2003): “Artificial Intelligence: A Modern Approach (Second Edition)” Prentice Hall.

- Sadeghzadeh, I., Zhang, Y. M. (2011): “A review on fault-tolerant control for unmanned aerial vehicles (UAVs)”. Infotech@ Aerospace, St. Louis, MO.

- Sanchez-Lopez, J.L.,; Pestana, J.; de la Puente, P.; Campoy, P. (2015): “Reusable Open-source System Architecture for the Fast Designing and Prototyping of Autonomous Multi-UAV Systems: Simulation and Experimentation”. Journal of Intelligent and Robotic Systems.

- Sing P., Minsky M. (2005). “An Architecture for Cognitive Diversity”. In “Visions of Mind”. Edited by Darryl Davis. London: Idea Group.
