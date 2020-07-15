#include "droneloggerrosbasicmodule.h"

std::string DroneLoggerROSBasicModule::currentlog_path = "";

DroneLoggerROSBasicModule::DroneLoggerROSBasicModule( ros::NodeHandle n) :
    DroneModule(droneModule::active, 120.0) ,
    drone_logfile_writter(stackPath),
    init_rostime( 0, 0)
{
    // init_rostime initialization
    {
        int32_t inittime__sec;
        int32_t inittime_nsec;
        if ( ros::param::has("/drone_log_init_rostime__sec") && ros::param::has("/drone_log_init_rostime_nsec") ) {
            // init_rostime was initialized
            ros::param::get( "/drone_log_init_rostime__sec", inittime__sec);
            ros::param::get( "/drone_log_init_rostime_nsec", inittime_nsec);
            init_rostime.sec  = inittime__sec;
            init_rostime.nsec = inittime_nsec;
#ifdef VERBOSE_DRONE_LOGGER
            std::cout << "init_rostime was initialized in The ROS Parameter Server"
                      << " init_rostime:" << init_rostime.sec << "." << std::setfill('0') << std::setw(9) << init_rostime.nsec << std::endl;
#endif // VERBOSE_DRONE_LOGGER
        } else {
            // init_rostime was not initialized
            init_rostime = ros::Time::now();
            inittime__sec = init_rostime.sec;
            inittime_nsec = init_rostime.nsec;
            ros::param::set("/drone_log_init_rostime__sec", inittime__sec);
            ros::param::set("/drone_log_init_rostime_nsec", inittime_nsec);
#ifdef VERBOSE_DRONE_LOGGER
            std::cout << "init_rostime was NOT initialized in The ROS Parameter Server"
                      << " init_rostime:" << init_rostime.sec << "." << std::setfill('0') << std::setw(9) << init_rostime.nsec << std::endl;
#endif // VERBOSE_DRONE_LOGGER
        }
    }

    // droneModuleROS gets the stackPath and idDrone automatically
    try {
        XMLFileReader my_xml_reader(stackPath+"configs/drone"+ cvg_int_to_string(idDrone)+"/drone_logger_config.xml");
        set_moduleRate(my_xml_reader.readDoubleValue( "drone_logger_config:module_frequency" ));
    } catch ( cvg_XMLFileReader_exception &e) {
    throw cvg_XMLFileReader_exception(std::string("[cvg_XMLFileReader_exception! caller_function: ") + BOOST_CURRENT_FUNCTION + e.what() + "]\n");
    }

    DroneLoggerROSBasicModule::currentlog_path = drone_logfile_writter.getCurrentLogPath();
    DroneModule::open(n,MODULE_NAME_DRONE_LOGGER);

    // Subscribers
    eventStringSub = n.subscribe( DRONE_LOGGER_EVENTSTRING_SUBS, DRONE_LOGGER_EVENTSTRING_QUEUE_LENGTH, &DroneLoggerROSBasicModule::eventStringSubCallback, this);;

    // Services
    // logThisString
    logThisStringServerSrv = n.advertiseService( DRONE_LOGGER_EVENTSTRING_SRV_SERVER, &DroneLoggerROSBasicModule::logThisStringServCall, this);

    string_stacker << "[DroneLogger]"
                   << " init_rostime:" << init_rostime.sec << "." << std::setfill('0') << std::setw(9) << init_rostime.nsec << std::endl;



    //Flag of module opened
    droneModuleOpened=true;

    //Autostart the module
    moduleStarted=true; //JL to remove!
}

DroneLoggerROSBasicModule::~DroneLoggerROSBasicModule() {
}

void DroneLoggerROSBasicModule::eventStringSubCallback(const std_msgs::String::ConstPtr &msg) {
    string_stacker << msg->data;
}

bool DroneLoggerROSBasicModule::logThisStringServCall(lib_cvgloggerROS::logThisString::Request& request, lib_cvgloggerROS::logThisString::Response& response) {
    string_stacker << request.str2belogged;
    response.ack = true;

    return response.ack;
}

bool DroneLoggerROSBasicModule::run() {
    if(!DroneModule::run())
    {
        return false;
    }

    ros::Time current_rostime = ros::Time::now();
    ros::Duration elapsed_rostime = current_rostime - init_rostime;

    // get messages from DRONE_LOGGER_EVENTSTRING_SUBS rostopic
    {
        std::string     line;
        StringStacker   debug_log_msgs, prueba_ss = string_stacker;
        string_stacker.str(std::string()); // flush string_stacker;
        while( std::getline( prueba_ss, line, '\n') ) {
            debug_log_msgs << elapsed_rostime.sec << "." << std::setfill('0') << std::setw(9) << elapsed_rostime.nsec << " "
                               << line << std::endl; // note that messages include a [tag_name] already
        }
        drone_logfile_writter.writeString2Logfile(debug_log_msgs.getStackedString());
    }

    // get messages from DroneLoggerROSTopicSubscriber objects
    std::string other_log_msgs;
    bool priority_flag_unnecessary_here;
    other_log_msgs = DebugStringStacker::getAllStackedDebugStrings(priority_flag_unnecessary_here);
    drone_logfile_writter.writeString2Logfile(other_log_msgs);

    return true;
}
