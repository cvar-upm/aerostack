#include "droneloggerrospublisher.h"

DroneLoggerROSPublisher::DroneLoggerROSPublisher() {
    module_opened = false;
}

DroneLoggerROSPublisher::~DroneLoggerROSPublisher() {
    module_opened = false;
}

void DroneLoggerROSPublisher::publishEventString( const std::string &event_string) { //Publish function
    if (module_opened) {
        std_msgs::String    eventStringMsg;
        eventStringMsg.data = event_string;
        eventStringPub.publish( eventStringMsg );
    }
}

bool DroneLoggerROSPublisher::logThisStringService( std::string &str2belogged) {
    if (module_opened) {
        //Prepare msg
        lib_cvgloggerROS::logThisString logThisStringSrvVar;
        logThisStringSrvVar.request.str2belogged = str2belogged;

        //use service
        if(logThisStringClientSrv.call(logThisStringSrvVar)) {
            return logThisStringSrvVar.response.ack;
        } else {
            return false;
        }
    }
    return false;
}

void DroneLoggerROSPublisher::open(ros::NodeHandle &nIn) {
    n = nIn;

    int drone_logger_ros_publisher_queue_size = 10;
    use_of_rosservice_is_allowed = false;
    try {
        int idDrone=0; ros::param::get("~droneId",idDrone);
        std::string stackPath = std::string(std::getenv("AEROSTACK_STACK")); ros::param::get("~stackPath",stackPath); stackPath+="/";
        XMLFileReader my_xml_reader(stackPath+"configs/drone"+ cvg_int_to_string(idDrone)+"/drone_logger_config.xml");
        drone_logger_ros_publisher_queue_size = my_xml_reader.readIntValue( "drone_logger_config:drone_logger_ros_publisher_queue_size" );
        use_of_rosservice_is_allowed = (bool) my_xml_reader.readIntValue( "drone_logger_config:use_of_rosservice_is_allowed" );
    } catch ( cvg_XMLFileReader_exception &e) {
    throw cvg_XMLFileReader_exception(std::string("[cvg_XMLFileReader_exception! caller_function: ") + BOOST_CURRENT_FUNCTION + e.what() + "]\n");
    }

    // Publishers
    eventStringPub         = n.advertise<std_msgs::String>(DRONE_LOGGER_EVENTSTRING_PUBL, drone_logger_ros_publisher_queue_size);
    // Service clients
    logThisStringClientSrv = n.serviceClient<lib_cvgloggerROS::logThisString>(DRONE_LOGGER_EVENTSTRING_SRV_CLIENT);

    module_opened = true;
}

bool DroneLoggerROSPublisher::run() {
    if (module_opened) {
        std::string all_my_debug_strings;
        bool priority_flag = false;
        all_my_debug_strings = DebugStringStacker::getAllStackedDebugStrings(priority_flag);
        if ( (!priority_flag) && (!use_of_rosservice_is_allowed) ) {
            publishEventString(all_my_debug_strings);
        } else {
            return logThisStringService(all_my_debug_strings);
        }
        return true;
    } else {
        return false;
    }
}
