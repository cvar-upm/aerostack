#ifndef DRONELOGGERROSBASICMODULE_H
#define DRONELOGGERROSBASICMODULE_H

#include <ros/ros.h>
#include <droneModuleROS.h>
#include <std_msgs/String.h>
#include <lib_cvgloggerROS/logThisString.h>
#include <dronelogfileswritter.h>
#include <debugstringstacker.h>
#include <stringstacker.h>
#include <communication_definition.h>
#include "xmlfilereader.h"

#define VERBOSE_DRONE_LOGGER

class DroneLoggerROSBasicModule : public DroneModule {
protected:
    StringStacker        string_stacker;
    DroneLogfilesWritter drone_logfile_writter;
    ros::Time init_rostime;

    // Subscribers
    ros::Subscriber             eventStringSub;
    void eventStringSubCallback(const std_msgs::String::ConstPtr &msg);
    // Services
        // logThisString
    ros::ServiceServer logThisStringServerSrv;
    bool logThisStringServCall(lib_cvgloggerROS::logThisString::Request& request, lib_cvgloggerROS::logThisString::Response& response);

public:
    DroneLoggerROSBasicModule( ros::NodeHandle n);
    ~DroneLoggerROSBasicModule();

    bool run();

    inline std::string getCurrentLogPath() { return drone_logfile_writter.getCurrentLogPath(); }

public:
    static std::string currentlog_path;
};

#endif // DRONELOGGERROSBASICMODULE_H
