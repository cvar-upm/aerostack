#include "dronemoduleinterface.h"

DroneModuleInterface::DroneModuleInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in) {
    module_name_str  = module_name_str_in;
    module_name_enum = module_name_enum_in;
    moduleStarted = false;
    moduleOnline  = false;
    last_isStarted_timestamp = ros::Time( 0, 0);
}

DroneModuleInterface::DroneModuleInterface(const std::string &module_name_str_in) {
    module_name_str  = module_name_str_in;
    moduleStarted = false;
    moduleOnline  = false;
    last_isStarted_timestamp = ros::Time( 0, 0);
}

DroneModuleInterface::~DroneModuleInterface() {
    return;
}

void DroneModuleInterface::open(ros::NodeHandle &nIn) {
    n = nIn;

    //Services
    moduleIsStartedClientSrv = n.serviceClient<droneMsgsROS::askForModule>("moduleIsStarted");
    moduleIsOnlineClientSrv = n.serviceClient<droneMsgsROS::askForModule>("moduleIsOnline");
    startClientSrv=n.serviceClient<std_srvs::Empty>(module_name_str+"/start");
    stopClientSrv=n.serviceClient<std_srvs::Empty>(module_name_str+"/stop");
    resetClientSrv=n.serviceClient<std_srvs::Empty>(module_name_str+"/reset");

    //Topics
    //isStartedSub=n.subscribe(module_name_str+"/isStarted", 1, &DroneModuleInterface::isStartedSubCallback, this);
    return;
}

//void DroneModuleInterface::isStartedSubCallback(const std_msgs::Bool::ConstPtr &msg) {
//    last_isStarted_timestamp = ros::Time::now();
//    moduleStarted            = (bool) msg->data;
//    moduleOnline             = true;
//    return;
//}

bool DroneModuleInterface::start(bool block_execution_until_state_estimator_is_started)
{
    bool module_has_been_started = false;
    int isStartedResp=isStarted();
    if ( isStartedResp==0 )
    {

        if(startClientSrv.call(emptySrv))
        {
            module_has_been_started = true;
        }
        else
        {
            module_has_been_started = false;
        }
    }
    else if(isStartedResp==1)
    {
        module_has_been_started = true;
    }
    else
    {
        module_has_been_started = false;
    }

    if ( module_has_been_started && block_execution_until_state_estimator_is_started) {
        while ( !isStarted() ) {
            ros::spinOnce();
            ros::Duration(0.05).sleep();
        }
    }
    return module_has_been_started;
}

bool DroneModuleInterface::stop() {
    if ( isStarted() ) {
        if(stopClientSrv.call(emptySrv)) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

bool DroneModuleInterface::reset() {
    if(resetClientSrv.call(emptySrv)) {
        return true;
    } else {
        return false;
    }
}

//void DroneModuleInterface::checkStarted() {
//    ros::Time current_time = ros::Time::now();
//    if ( (current_time - last_isStarted_timestamp).toSec() > DRONE_MODULE_INTERFACE_ISSTARTED_TIME_THRESHOLD ) {
//        moduleStarted = false;
//        moduleOnline  = false;
//    }
//}
//bool DroneModuleInterface::isStarted() {
//    checkStarted();
//    return moduleStarted;
//}

//bool DroneModuleInterface::isOnline() {
//    checkStarted();
//    return moduleOnline;

//}

int DroneModuleInterface::isStarted()
{
    moduleStarted=false;
    droneMsgsROS::askForModule srv;
    srv.request.module_name = module_name_str;
    if(!moduleIsStartedClientSrv.call(srv))
        return -1;

    if(srv.response.ack)
    {
        moduleStarted = true;
        return 1;
    }
    else
    {
        moduleStarted = false;
        return 0;
    }

}

int DroneModuleInterface::isOnline()
{
    moduleOnline=false;
    droneMsgsROS::askForModule srv;
    srv.request.module_name = module_name_str;
    if(!moduleIsOnlineClientSrv.call(srv))
        return -1;

    if(srv.response.ack)
    {
        moduleOnline = true;
        return 1;
    }
    else
    {
        moduleOnline = false;
        return 0;
    }
}
