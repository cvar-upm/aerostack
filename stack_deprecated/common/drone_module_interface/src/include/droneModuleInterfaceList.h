#ifndef DRONE_MODULE_INTERFACE_LIST_H
#define DRONE_MODULE_INTERFACE_LIST_H

// ROS
#include "ros/ros.h"

// C++ standar libraries
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


// Topic and Rosservice names
//#include "droneModuleROS.h"
#include "dronemoduleinterface.h"

#define	MAX_DRONEMODULES	50
//#define DEBUG_MODE

class DroneModuleInterfaceList 
{
private:
	DroneModuleInterface* modules_list[MAX_DRONEMODULES];
	int number_of_modules;

public:
    DroneModuleInterfaceList();
    ~DroneModuleInterfaceList();
    void Delete(DroneModuleInterface *d);
    void Delete(int index);
    void DestroyContent();
    bool Add(DroneModuleInterface *d);
    bool Add(std::string s);
    bool startModule(std::string s);
    bool startAllMdoules();
    bool stopModule(std::string s);
    bool stopAllModules();
    bool moduleIsStarted(std::string s);
    bool allModuleAreStarted();
    bool moduleIsOnline(std::string s);
    bool allModuleAreOnline();
    void Open(ros::NodeHandle &nIn);
    void openModule(ros::NodeHandle &nIn,std::string s);
    int GetNumberOfDroneModules(){return number_of_modules;}
    std::vector<std::string> GetNameOfDroneModules();
    int GetPosInList(DroneModuleInterface *d);




};

#endif // DRONE_MODULE_INTERFACE_LIST_H
