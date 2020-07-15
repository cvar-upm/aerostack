#ifndef DRONELOGGERROSPUBLISHER_H
#define DRONELOGGERROSPUBLISHER_H

#include <ros/ros.h>
#include "debugstringstacker.h"
#include "lib_cvgloggerROS/logThisString.h"
#include "communication_definition.h"
#include "std_msgs/String.h"
#include "xmlfilereader.h"

// Class Description:
//  - This class is to be added the ROSModuleNode of the nodes that want to log internal data.
//  - The debug_strings are stacked by DebugStringStackers objects and it is published information in the drone${ID}/event_string topic.
//  - The required code is small:
//      // Inside the software module where the log string is generated
//          DebugStringStacker debug_string_stacker1;          // define DebugStringStaker in the module where the log string is generated
//          debug_string_stacker1 << "prueba 1" << std::endl;  // put inside whatever information is required (respect the compatible format)
//
//      // In the ROSModuleNode code where the module is contained:
//          DroneLoggerROSPublisher drone_logger_ros_publisher;
//          drone_logger_ros_publisher.open(n); // ros::NodeHandle n;
//          drone_logger_ros_publisher.run();   // inside ros::spinOnce() while loop

class DroneLoggerROSPublisher {
public:
    DroneLoggerROSPublisher();
    ~DroneLoggerROSPublisher();

private:
    ros::NodeHandle n;
    bool module_opened;
    bool use_of_rosservice_is_allowed;
    // Subscribers
    // Publishers
    ros::Publisher      eventStringPub;

    // Services
        // logThisString
    ros::ServiceClient logThisStringClientSrv;

public:
    void publishEventString( const std::string &event_string);
    bool logThisStringService( std::string &str2belogged );

public:
    void open(ros::NodeHandle &nIn);
    bool run();
};

#endif // DRONELOGGERROSPUBLISHER_H
