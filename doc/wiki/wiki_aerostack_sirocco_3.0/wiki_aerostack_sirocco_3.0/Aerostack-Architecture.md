This section summarizes the main components of the Aerostack architecture and its structural organization.

### Main components

The next figure shows the main components of the Aerostack architecture. In the figure, circles represent data processing units (or processes in short) that are implemented as ROS nodes. Processes are organized in three main layers: interface, functional and executive. 

The interface layer includes processes that help interact with the world. They include processes that receive sensor data or command robot actuators, besides communication processes with the human operator and other robots. 

The other layers (functional and executive) are common components of multilayer architectures of autonomous systems. The Aerostack architecture also uses a standard communication channel, which is implemented with ROS message types that are common in aerial robotics. This channel facilitates process interoperability and also, it helps reuse components of the functional and the executive layers across different types of aerial platforms.

[[Files/Architecture.png]]

The functional layer of the Aerostack architecture includes processes for mechanical abilities of aerial robots. Aerostack provides a software library to implement these processes and the developer can use and combine them to build a particular robotic system architecture. Examples of these components are: 

- feature extractors that read simple states of sensors or implement vision recognition algorithms (e.g., recognizer of ArUco markers or QR codes), 

- motion controllers (e.g., PID controllers for pose control or speed control and trajectory controllers), 

- processes that perform self-localization and mapping (SLAM), 

- motion planners that generate obstacle-free paths to reach destination points, and

- methods for communicating with other agents (other robots or human operators). 

The third layer of the Aerostack architecture is the executive layer and includes the processes that make up the executive system. The main function of these processes is to execute the mission plan by activating and monitoring the execution of the mechanical abilities of the functional layer. 

The executive layer in Aerostack creates a logical interface that helps specify mission plans. This layer relieves the human operator from having to specify unnecessary execution details that are common for similar tasks and provides user error protection by verifying the correct syntax and semantics of written commands. The executive layer also verifies that a mission is executed as expected. For example, the executive system checks in advance that each task to be executed is consistent with the situation of the environment, preventing the robot from performing wrong or dangerous behaviors. The executive system also detects the presence of unexpected events and coordinate multiple decisions about what the robot must perform (e.g., deliberative or reactive decisions).

### Architecture organization in processes

Aerostack uses the name of *process* to call each elemental component of the architecture. Each process has a function, i.e., a purpose or practical use for which the process is designed, and it is named as an agent according to its main function, for example, mission planner (main function: planning a mission) or obstacle recognizer (main function: recognize obstacles). Each process of Aerostack is implemented as a ROS node.

Aerostack provides a library of reusable processes for aerial robotics. The library is open, so new processes can be included easily in the future, without changing the core of the system and the rest of the processes. To create a new process it is necessary to program the corresponding algorithms and data structures as a class (e.g., in C++ language) and apply certain Aerostack conventions to be part of the library. For example, each process is created as a subclass of a specific class (called RobotProcess) that provides common functionality for supervision and execution control.