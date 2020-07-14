
This section summarizes the main components of the Aerostack architecture and its structural organization.

### Main Components

The next figure shows the main functional components of the architecture. This design follows the hybrid reactive/deliberative paradigm, i.e., an architecture that integrates both a deliberative and reactive approaches [Arkin et al., 1987]. Our design includes several layers: physical, reactive, executive, deliberative and social. 

The three layers reactive-executive-deliberative are based on the popular hybrid design known as the three-layer architecture [Gat ,1998] that organizes algorithms according to whether they contain no internal state (reactive layer), contain state reflecting memories about the past (executive layer) or contain state reflecting predictions about the future (deliberative layer). 

[[Files/Architecture.png]]

The reactive layer creates a sensor-action loop that includes feature extractors and motion controllers. Feature extractors may read simple states of sensors or may implement complex vision and pattern recognition algorithms. Examples of feature extractors are: extract color, compute centroid of an image, recognize ArUco visual markers, detect power line tower, etc. A perceptual schema can integrate a set of perception procedures using different combination methods. Our reactive layer may also include methods for SLAM (self-localization and mapping). 

Motion controllers typically implement combinations of proportional-integral-derivative (PID) controllers (e.g., cascade controllers). For example, this type of controllers can accept orders about a desired value for a variable (position, speed, altitude, and yaw) in form of single commands or simultaneous commands that are translated into low level commands to be sent to the actuator interface.

The executive layer accepts directives from the deliberative layer and sequences them for the reactive layer. The executive layer follows a behavior-based approach including a behavior manager. The behavior manager receives a high level command about a desired action (e.g., go to a desired position) and translates it into references for controllers. The executive layer also integrates the sensor information into an internal state representation using a memory of symbolic beliefs.

The architecture includes also a social layer with communication abilities, as it is proposed in multiagent systems and other architectures with social coordination (e.g., [Duffy, 2000]).

The organization in separate layers is useful, for example, to organize the independent execution of processes that operate at high frequencies (e.g., reactive processes, with frequencies between 10 Hz and 1000 Hz) and processes that operate at low frequencies (e.g., deliberative processes, with frequencies between 0.1 Hz and 10 Hz). For example, planning algorithms can be computationally expensive, so they should be decoupled of the processes in the reactive layer to avoid slow down the reaction time.

The architecture is also consistent with the usual components related to guidance, navigation and control of unmanned rotorcraft systems [Kendoul, 2012]. In particular, the Navigation System (NS) corresponds to our perception system and situation awareness system, the Guidance System (GS) corresponds to our executive system and planning system and, finally, the Flight Control System (FCS) corresponds to our motion system.

### Architecture Organization: Processes and Systems

Aerostack uses the name of **process** to call each elemental component of the architecture. Each process has a function, i.e., a purpose or practical use for which the process is designed, and it is named as an agent according to its main function, for example: mission planner (main function: planning a mission) or obstacle recognizer (main function: recognize obstacles). Processes are grouped in **systems**. A system is a complex module that includes a set of interconnected processes that provides a common functionality. The ideas of process and system provide modularity and are useful to divide the whole problem of automated support for aerial robotic systems into partial functional roles.

The notions of process and system are similar to other concepts used in certain system design methodologies. For example, a process is similar to an atomic functional block used in SysML with input/output ports. The idea of system is also similar to the concept of functional block (composite block) used in SysML, with input/output ports. Next figure shows a graphical notation to describe the inter-process communication of data processors of the Aerostack architecture. This notation is based partially on functional block diagrams and SysML (internal block diagrams).

[[Files/Processes.png]]

 The computational support of a process is an atomic executable unit (a data processor) that receives input data and, as a result of a certain information processing, generates output data. The processes of Aerostack are implemented using ROS (Robot Operating System). Each process is a ROS node. When Aerostack is running for a particular robotic system, each process is normally an executable instance of a program running in a computer (in certain situations, a process can also have several executable instances). Aerostack executes independently processes in a multi-tasking operating system (Linux). Aerostack runs concurrently processes using the inter-process communication methods provided by ROS: (1) a publish-subscribe mechanism using messages and topics, and (2) a request-reply scheme (services).

Aerostack provides a library of reusable processes for aerial robotics. The library of processes is open, so new processes can be included easily in the future, without changing the core of the system and the rest of processes. To create a new process it is necessary to program the corresponding algorithms and data structures in a class (e.g., in C++ language) and apply certain Aerostack conventions to be part of the library. For example, it must be created as a ROS node and it must be subclass of a specific class (called RobotProcess) that provides a common functionality (supervision, execution control and standard error messages)

To consult the available processes provided by Aerostack, consult the following catalog:

- [[Catalog of Processes]]

### References

* Arkin, R. C., Riseman, E. M., and Hansen, A. (1987): “AuRA: An Architecture for Vision- Based Robot Navigation,” proceedings of the DARPA Image Understanding Work-shop, Los Angeles, CA, February, pp. 417–413.

* Duffy, B.R. (2001). “The Social Robot”. Doctoral dissertation, Dept. of Computer Science, University College Dublin, Ireland.

* Gat
, E. (1998): “On Three-Layer Architectures”. In “Artificial Intelligence and Mobile Robots”, (David Kortenkamp, R. Peter Bonnasso, and Robin Murphy, eds.) AAAI Press.

* Kendoul, F. (2012). Survey of advances in guidance, navigation, and control of unmanned rotorcraft systems. Journal of Field Robotics, 29(2), 315-378.

