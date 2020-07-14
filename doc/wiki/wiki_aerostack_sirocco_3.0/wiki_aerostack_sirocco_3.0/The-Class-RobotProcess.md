The class RobotProcess has been designed to support the development of processes in Aerostack. The following sections describe the main features provided by this class.

## 1. Alive Signal for Process Monitoring

The supervision system in Aerostack monitors the correct execution processes. To facilitate this, each process generates automatically a periodic alive signal that allows the supervision system to detect unexpected stops.

The class RobotProcess provides the mechanism to generate the alive signal. This is done by creating a thread that is responsible of the periodical alive signal sending. By using this thread, the generation of the alive signals does no produce undesired delays in the implemented algorithm of the process. Every process sends alive signals at the same frequency, making more reliable a process stop detection.

[[Files/ProcessMonitor.png]]

## 2. Controlling the Process Execution

The class RobotProcess provides a set of services that allow to control the execution of the process by other processes (start, restart, stop, pause and continue). 

In general, the execution of a process has the following characteristics:

- *Set up*. Before the process can be executed, the process must be configured with an initial set of parameter values and/or configuration files.

- *Interprocess communication*. When the process starts its execution it is connected to the data channels for inter-process communication in a network of processes through an external interface of input/output variables (ROS topics) and ROS services.

- *Synchronous/asynchronous execution*. During the execution, the process develops a series of data transformations. The execution can be asynchronous if data transformations are performed in response to changes in inputs (new messages in subscribed ROS topics) or in response to service calls from other processes (ROS services). The execution can be synchronous if data transformations are periodically performed with a certain frequency (e.g., frequency of 10 hertzs). As a result of its execution, the process generates output data to be used by other processes (new published messages in ROS topics or responses to ROS services).

- *Sequential logic*. Some processes follow a sequential logic (as opposite of combinatorial logic). This means that the outputs depend not only on the present value of the input but also on the input history. In this case, the process has memory, represented with memory states with a set of variables. At the beginning of the execution of a process, the memory has an initial state (with certain initial values for the variables) and, then, the memory state changes with the execution progress.

- *Termination*. In any moment, the normal execution can be forced to stop, i.e., finish the execution and return to the initial state of the memory. This is useful to cancel the execution of certain processes that can be in conflict with others. This can be done, for example, by a process that controls the correct execution of groups of processes to give an adequate and efficient support to certain actions and skills. The operator can also terminate a process to solve an operational problem or to check certain functionalities. When the execution is finished, the process transits to a state that ignores changes in inputs and service calls (other than certain special services, such as “start” again the execution).

- *Pause*. The normal execution of the process can be paused, i.e., stop the execution keeping the current state of the memory. When the execution is paused, the process transits to a state that ignores changes in inputs and service calls (other than certain special services, such as “continue” the execution).

- Other possible changes of the flow execution (not implemented yet). The normal execution of the process can also be changed with the following types of actions: (1) pause a period of time, i.e., stop the execution keeping the current state of the memory and, after a period of time, continue the execution, (2) recover fault, i.e., recover from a detected fault, (3) update memory state, i.e., set a given state as the current memory state.

[[Files/StateTransitionDiagram.png]]

The states of a process are the following:

- *Created*: The process has been created but it is not set up yet (it is not configured and it is disconnected to the network of processes).

- *Ready to start*: The process has been set up so it is ready to start running. The memory has its initial state. The process is not executing yet, so it is not reading and writing any message (only certain reserved messages related to its supervision). The process does not respond to any service call (except execution control services like “start”).

- *Running*: The process is running. The process reads and writes messages and responds to service calls.

- *Paused*: The process execution is paused indefinitely. The memory keeps its current state. The process is not executing, so it is not reading and writing any message (only execution control messages related to its supervision). The process does not respond any service call (except execution control services like “start”).

The class RobotProcess uses this set of states that are common for all processes. The services provided by the class RobotProcess to control the execution of processes are the following:

- START: Initiates the normal execution of a process that is ready to start.

- STOP: Cancel the execution of a process that is running or paused, and reset variables, i.e., the variables are changed to their initial values (initial state of the memory). 
 
- RESTART: Restart the normal execution of a process that is running or paused. The process starts again from the initial state of memory.

- PAUSE: Pause the process execution, keeping the state of the memory. 

- CONTINUE: Continue the normal execution from the paused state.

To support these services, the class RobotProcess includes a set of predefined functions:

- *constructor*: This function performs the following steps: (1) construct the process with default values for some variables and (2) set the process state to the initial value (created).

- *setUp*(): This function must be called in the main program and performs the following steps: (1) subscribe the ROS topics related to execution control, (2) call the function ownSetUp(), and (3) set the process state to the value ready to start.

- *start*(): This function implements the service START. For immediate execution of a process, this function can be called in the main program of the process, just after the function setUp(). The function performs the following steps: (1) set the process state to the value running, (2) call the function ownStart().

- *stop*(): This function implements the service STOP. This function performs the following steps: (1) call the function ownPause(), (2) call the function ownReset() and (3) set the process state to the value ready to start.
 
- *restart*(): This function implements the service RESTART. This function perform the following steps: (1) call the function stop() and (2) call the function start().

- *pause*(): This function implements the service PAUSE. This function performs the following steps: (1) call the function ownPause() and (2) set the process state to the value paused.

- *continue*(): This function implements the service CONTINUE. This function performs the following steps: (1) set the process state to the value running, and (2) call the function ownContinue().

- *run*(): This is a function that can be called from the main function to be executed periodically. This function performs the following: if the current state is running then call the function ownRun().

The class RobotProcess defines also a set of specific functions, with the prefix *own*, that the programmer must complete for each particular process:

- *ownSetUp*(): This function includes specific actions to set up the process such as read ROS parameters or read configuration files (e.g., XML files). This function can initiate ROS topics and services related to static information that do not depend on the execution.

- *ownStart*(): This function includes specific actions to start running the process such as initiate ROS topics and services specific for this process whose values depend on the execution.

- *ownRun*(): This function develops the main body of execution to perform in the running state. This does not include the tasks to be done as an answer to the service calls or topic messages. If the process execution is asynchronous, i.e., it only reacts to ROS topics and services, then the function ownRun() is empty.

- *ownPause*(): This function pauses the process execution by doing shutdown of ROS topics and services (specific for this process that depend on the execution).

- *ownReset*(): This function reset the memory state of the process.

- *ownContinue*(): This function continue the process execution by subscribing again ROS topics and services (specific for this process).

## 3. Centralized Error Notification 

The class RobotProcess provides the function notifyError() to notify errors to the supervision system. This function needs four parameters: *error_type*, *error_reference_code*, *error_location* and *error_description*. For example:

```cpp
      notifyError(InvalidInputData,32,"determineTrajectory()",exception.what());
```

Please notice the last function attribute. It is using the exception’s function what() which returns the description of a captured exception. Using exceptions is an appropriate way to notice errors during execution and thus the recommended way for handling them. 

To handle invalid input data errors, each process should include a validation procedure for the input data and the corresponding notification message. For example, let us consider a process that receives as input a degree value of a robot joint, using the variable KneeDegree. Because this joint can only bend from 0 to 90 degrees, the process receiving this data must check if the value of KneeDegree is within this interval, before using this value in the corresponding procedure. The following C++ code example illustrates how to do this validation and the corresponding notification:

```cpp
void kneePositionCallback(const KneeDegree::ConstPtr& degree)
{
  if (degree < 0 || degree >90)
  {
     notifyError(InvalidInputData,0,"kneePositionCallback()",
                 "Invalid knee bend value");
     return;
  }  
  //Functional code
  ...
}
```

To handle safeguard errors, C++ exceptions should be used. An exception brings the ability of advertising an error (throw an exception) and dealing with it at any other part of the process code, where the error may actually be solved (catching an exception). For instance, let us consider a process with the function positionOperation() that can throw an exception in the case something goes wrong. The particular error that can detect the function positionOperation() is that some of the position values have a negative value, which is against the logic of the program. The try code block checks if an exception is thrown. If that is the case and the exception is the one defined at the catch block (std::logic_error), the error is handled by the catch code block. In this particular example, the error is notified to the performance monitor using the function notifyError(). The corresponding C++ code is the following:

```cpp
    try
    {
      positionOperation(&x_position, &y_position);    
    }
    catch (std::logic_error& exception)
    {
      notifyError(SafeguardRecoverableError,0,     
                  "positionOperation",exception.what());
      ...
      return;
    }
```

## 4. The class DroneModule

The class DroneModule has a similar purpose as the class RobotProcess. However the class DroneModule is a simplified and previous version that was implemented for old processes. New processes are now implemented as subclasses of RobotProcess. The class DroneModule is still part of the software architecture to provide compatibility with old processes that keep their original C++ implementation.

One of the consequences of this is that these processes do not have the same capabilities to be supervised by the performance monitor. In particular, in contrast to the supervised processes that are subclass of RobotProcess, the old processes only have the following states:

- Started (same as running): The process has started and it is running. It is activated with the function start().

- NotStarted (same as ready to start): The process has not started yet. It is activated with the function stop().

These processes also send alive signals (AliveSignal message), so that the performance monitor is able to verify their state.