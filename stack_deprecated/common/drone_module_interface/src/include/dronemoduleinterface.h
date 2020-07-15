#ifndef DRONEMODULEINTERFACE_H
#define DRONEMODULEINTERFACE_H

// ROS
#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "std_msgs/Bool.h"
#include "droneMsgsROS/askForModule.h"

// C++ standar libraries
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

// Topic and Rosservice names
#include "communication_definition.h"

#define DRONE_MODULE_INTERFACE_ISSTARTED_TIME_THRESHOLD     (2.0)

class DroneModuleInterface {
    //Ros node
protected:
    ros::NodeHandle   n;
    std::string       module_name_str;
    ModuleNames::name module_name_enum;

private:
    std_srvs::Empty    emptySrv;
    ros::ServiceClient moduleIsStartedClientSrv;
    ros::ServiceClient moduleIsOnlineClientSrv;
    ros::ServiceClient resetClientSrv;
    ros::ServiceClient startClientSrv;
    ros::ServiceClient stopClientSrv;
    //ros::Subscriber    isStartedSub;
    bool      moduleStarted;
    bool      moduleOnline;
    ros::Time last_isStarted_timestamp;
    //void isStartedSubCallback(const std_msgs::Bool::ConstPtr &msg);
    //void checkStarted();

public:
    DroneModuleInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in);
    DroneModuleInterface(const std::string &module_name_str_in);
    ~DroneModuleInterface();
    void open(ros::NodeHandle & nIn);

    bool start( bool block_execution_until_state_estimator_is_started = false);
    bool stop();
    bool reset();
    int isStarted();
    int isOnline();
    std::string getModuleName(){return module_name_str;}
};

#endif // DRONEMODULEINTERFACE_H
