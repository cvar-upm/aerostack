Any process (ROS node) that belongs to Aerostack must be correctly supervised by the process monitor. In order to facilitate this supervision, the process must be subclass of [[the class RobotProcess]] and it must be programmed following certain conventions. This section describes with an example how to program a new process for Aerostack in C++ language. 

### Example Description

The purpose of this example is to illustrate the common steps that the developer must perform to build a new process. So, the example process is a very simplified case. The example illustrates certain details that must be taking into account by the programmer such as how to handle error messages or other aspects related to the communication with the supervision system. We do not describe here specific algorithms for this process. 

In the example, we make the following assumptions:

- The process is called **my process**.

- The process is part of the **planning system**. 

- The process uses as input a topic called **my topic**. This topic includes a robot position (coordinates x, y).

- The specific algorithms for this process are externally encapsulated in a separate class called **my class**. The algorithms included in this class are independent of ROS. This division is a good practice that separates ROS dependent code from ROS independent code and, therefore, promotes the reusability of ROS independent code in other programming contexts.

## 1. Folder Organization

The folder organization corresponds to catking packages (see [creating ROS packages](http://wiki.ros.org/ROS/Tutorials/CreatingPackage)) within an system of the Aerostack architecture. In our example, the folder organization is the following:

```
planning_system/                       -- System to which our process belongs
  my_process/                          -- Name of my process
    my_class/
      CMakeLists.txt                   -- CMakeLists.txt file
      package.xml                      -- Package manifest 
      src/
        include/
          my_class.h                   -- Header file
        source/
          my_class.cpp                 -- C++ file
        test/
          my_class_test.cpp            -- C++ program to test the class
          ...                          -- Other files (xml, csv, etc.) to test the class
    my_process_process/
      CMakeLists.txt                   -- CMakeLists.txt file 
      package.xml                      -- Package manifest 
      README.md                        -- Process description (with ROS topics and services)
      launch/
        my_process_process.launch      -- Launcher
      msg/                             -- Messages and service types
      src/
        include/
          my_process_process.h         -- Header file (with the suffix "process")
        source/
          my_process_process.cpp       -- ROS dependent C++ program (with the suffix "process")
          my_process_process_main.cpp  -- Program with the main function (with the suffix "main")
        test/
          my_process_process_test.cpp  -- C++ program to test the process (with the suffix "test")
          ...                          -- Other files (xml, csv, etc.) to test the process
```


## 2. Header File

This section shows the header file corresponding to the MyProcess class. The complete content of the header file is the following:

```cpp
#ifndef MY_PROCESS
#define MY_PROCESS

#include "robot_process.h"
#include "my_class.h"
#include <cvg_stack_msgs/position.h>

/*!*************************************************************************************
 *  \class     MyProcess
 *
 *  \brief     This is an example that shows how a process should be programmed.
 *
 *  \details   This process receives a position message through an input topic.
 *             If either the x or y values are negative, an error is reported.
 *             This process uses algorithms defined by the MyClass class.
 *
 *  \authors   Martin Molina, Enrique Ortiz
 *
 *  \copyright Copyright 2016 Universidad Politecnica de Madrid (UPM)
 *  
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *  
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU General Public License for more details.
 *  
 *     You should have received a copy of the GNU General Public License
 *     along with this program. If not, see http://www.gnu.org/licenses/.
 ***************************************************************************************/
class MyProcess: public RobotProcess
{
public:
  //! Constructor. \details Same arguments as the ros::init function.
  MyProcess();

  //! Destructor.
  ~MyProcess();

/*!*************************************************************************************
 * \details The function ownSetUp() is executed to setup everything that 
 *          the process needs at the beginning such as read 
 *          configuration files, read ROS parameters, etc.
 **************************************************************************************/
  void ownSetUp();
 
/*!*************************************************************************************
 * \details The function ownStart() prepares the process to start running.
 *          Connects topics and services and set the appropiate values.
 **************************************************************************************/
  void ownStart();

/*!*************************************************************************************
 * \details The function ownStop() perform shutdown of topics and services and 
 *          reset values of variables.
 **************************************************************************************/
  void ownStop();

/*!*************************************************************************************
 * \details The function ownRun() the main body of execution to perform in the 
 *          running state. Only used when the process is synchronous.
 **************************************************************************************/
  void ownRun();

private:
  //! ROS NodeHandler used to manage the ROS communication
  ros::NodeHandle n;

  //! ROS subscriber handler used to receive messages. 
  ros::Subscriber my_topic_subscriber;
  
  //! Topic name used to subscribe 
  std::string my_topic;

  int x_position;   //!< Position x 
  int y_position;   //!< Position y

  //! Ros independent class
  MyClass my_class;
  
  //! Function launched when this process receives a message from my_topic
  void myTopicCallback(const cvg_stack_msgs::position::ConstPtr& position);

  //! This function will be called in the myTopicCallback
  void myFunction(int* x, int* y);

  //! This function is called periodically, between callbacks.
  void myOtherFunction();
};
#endif
```
The process is programmed using a C++ class called *MyProcess*. This class must be subclass of RobotProcess to inherit the required functionality to be monitored by the supervision system.

The following paragraphs describe in more detail the different parts of the header file. 

### 2.1. Dependence on Header Files

At the beginning of the file the following sentences are written: 

```cpp
#include "robot_process.h"
#include "my_class.h"
#include <cvg_stack_msgs/position.h>
```

Since MyProcess is subclass of RobotProcess, the header file robot_process has to be included. The my_class.h header class is also included to be able to use the class MyClass. The cvg_stack_msgs/position header file allows our class to receive position data.

### 2.2. Class Declaration, Constructor and Destructor

The declaration of the MyProcess class as subclass of RobotProcess, with its constructor and destructor functions is the following:

```cpp
class MyProcess: public RobotProcess
 {
   MyProcess();
   ~MyProcess();
   ...
 }
```
The constructor and destructor functions are always needed in C++ language. 

### 2.3. Own Functions

The declaration of the specific functions (own functions) for setUp(), start() and stop() is the following:

```cpp
void ownSetUp();
void ownStart();
void ownStop();
void ownRun();
```

These functions must be defined at every subclass of RobotProcess. The body of these functions with their algorithms are written in the cpp file.

### 2.4. Node Handle

The use of RobotProcess class abstracts certain details of the use of ROS. However, it is still needed that the programmer declares a node handle in the header file. The ROS handler is defined in the following way:

```cpp
  ros::NodeHandle n;
```

### 2.5. Topic Subscription

The following part of the header file is required for topic subscription:

```cpp
   //! ROS subscriber handler used to receive messages. 
  ros::Subscriber my_topic_subscriber;
  
  //! Topic name used to subscribe 
  std::string my_topic;

  int x_position;   //!< Position x 
  int y_position;   //!< Position y
  
  //! Function launched when this process receives a message from my_topic. The message is received as a pointer.
  void myTopicCallback(const cvg_stack_msgs::position::ConstPtr& position);
```

### 2.6. Function Definition

Different functions are declared.

```cpp
  //! This function will be called in the myTopicCallback
  void myFunction(int* x, int* y);

  //! This function is called periodically, between callbacks.
  void myOtherFunction();
```

## 3. The CPP File

This section shows the CPP file corresponding to MyProcess class. The complete content of the CPP file is the following:

```cpp
#include "my_process_process.h"

//Constructor
MyProcess::MyProcess():RobotProcess()
{
  MyClass my_class();
   
  if (!n.getParam("my_topic_name", my_topic))
    my_topic = "my_topic";
}

//Destructor
MyProcess::~MyProcess() {}

//myTopicCallback
void MyProcess::myTopicCallback(const cvg_stack_msgs::position::ConstPtr& position)
{
  //Input data validation
  if (position->x < 0 || position->y < 0)
  {
    notifyError(InvalidInputData,0,
                "myTopicCallback()",
                "Positive values expected for coordinates x and y");
  }
  else
  {
    ROS_INFO("Received from %s: x=%d, y=%d",
             my_topic.c_str(), position->x, position->y);
    x_position = position->x;
    y_position = position->y;

    try
    {
      myFunction(&x_position, &y_position);
    }
    catch (std::logic_error& exception)
    {
      //This is how the exception is catched. 
      notifyError(SafeguardFatalError,0,"myFunction()",exception.what());
      //This is a fatal error that can not be recovered.
      std::exit(EXIT_FAILURE);
    }
  }
}

//myFunction - any function for illustration purposes
void MyProcess::myFunction(int* x, int* y)
{
  ...
}

void MyProcess::myOtherFunction()
{
  ...
}

//ownSetUp()
void MyProcess::ownSetUp()
{
  x_position = 0;
  y_position = 0;
}

//ownStart()
void MyProcess::ownStart()
{
  my_topic_subcriber = n.subscribe(my_topic, 1000, &MyProcess::myTopicCallback, this);
}

//ownStop()
void MyProcess::ownStop()
{
  x_position = 0;
  y_position = 0;
  my_topic_subscriber.shutdown();
}

//ownRun()
void MyProcess::ownRun()
{
  myOtherFunction();
}
```

### 3.1. Constructor and Destructor

The code of the body for both constructor and destructor functions is the following:

```cpp
//Constructor
MyProcess::MyProcess():RobotProcess()
{
  MyClass my_class();
   
  if (!n.getParam("my_topic_name", my_topic))
    my_topic = "my_topic";
}

//Destructor
MyProcess::~MyProcess() {}
```

We use the ROS parameter server with the function getParam() to obtain the drone id value, as well as the name of the topic used to receive position messages. 

### 3.2. Input Data Validation

The code to validate input data with the corresponding message error is the following:

```cpp
  //Input data validation
  if (position->x < 0 || position->y < 0)
  {
    notifyError(InvalidInputData,0,
                "myTopicCallback()",
                "Positive values expected for coordinates x and y");
  }
  
```

The myTopicCallback function, which has the main logic of the process, checks the received position. If this position is noticed to be invalid, an invalid input data error is sent to the performance monitor.

### 3.3. Safeguard Error

The following example shows how the process detects and notifies a safeguard error, when the error cannot be recovered. To illustrate how to catch this type of error, we have the following piece of code:

```cpp
    try
    {
      myFunction(&x_position, &y_position);
    }
    catch (std::logic_error& exception)
    {
      //This is how the exception is catched. 
      notifyError(SafeguardFatalError,0,"myFunction()",exception.what());
      //This is a fatal error that can not be recovered.
      std::exit(EXIT_FAILURE);
    }
```

In this case, the error cannot be solved during process execution. That is why the type of the error notified is SafeguardFatalError. To detect these errors the exceptions are also used and, because the program cannot recover, it stops by using the std::exit() function.

### 3.4. Own Functions

The following piece of code illustrates how to write own functions:

```cpp

//ownSetUp()
void MyProcess::ownSetUp()
{
  x_position = 0;
  y_position = 0;
}

//ownStart()
void MyProcess::ownStart()
{
  my_topic_subcriber = n.subscribe(my_topic, 1000, &MyProcess::myTopicCallback, this);
}

//ownStop()
void MyProcess::ownStop()
{
  x_position = 0;
  y_position = 0;
  my_topic_subscriber.shutdown();
}

//ownRun()
void MyProcess::ownRun()
{
  myOtherFunction();
}
```

The ownSetUp() function is used to initialize the variables. 

The ownStop() function resets the values of variables and disconnect from the topic using shutdown. 

The ownStart() function connects to the topic my_topic.

The ownRun() function is called periodically when the process is running.

## 4. The Main File

This section shows the CPP file corresponding to the main function. A possible way to write a main function is:

```cpp
#include "my_process.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  MyProcess my_process;
  my_process.setUp();
  try
  {
    my_process.start();
  }
  catch (std::exception& exception)
  {
    notifyError(SafeguardRecoverableError,0,"ownStart()",exception.what());
    my_process.stop();  // The process will have to be started by a service call from another process
  }

  ros::Rate loop_rate(10);
  while(ros::ok())
  {
    ros::spinOnce();
    my_process.run();
    loop_rate.sleep();
  }

  return 0;
}
```

Other different execution modes can be programmed. For example, we can distinguish between two different execution modes:

- *Immediate start*. The process starts automatically after set up, without the intervention of any other process. 

- *Subordinated start*. After set up, this process waits until it is started by another process (using a ROS service). 

The previous example illustrates a process with immediate start. A process with subordinated start (and synchronous execution) has the following body for the main() function:

```cpp
int main(int argc, char **argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  MyProcess my_process;
  my_process.setUp();

  ros::Rate loop_rate(10);
  while(ros::ok())
  {
    ros::spinOnce();
    my_process.run();
    loop_rate.sleep();
  }

  return 0;
}
```

A process with subordinated start (and asynchronous execution) has the following body for the main() function:

```cpp
int main(int argc, char **argv)
{
  ros::init(argc, argv, ros::this_node::getName());
  MyProcess my_process;
  my_process.setUp();

  ros::spin();   // Waits for the service start

  return 0;
}
```
