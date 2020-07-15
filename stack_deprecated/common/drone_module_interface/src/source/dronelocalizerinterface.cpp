#include "dronelocalizerinterface.h"

DroneLocalizerInterface::DroneLocalizerInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in) :
    DroneModuleInterface( module_name_str_in, module_name_enum_in)
{
}

DroneLocalizerInterface::~DroneLocalizerInterface()
{
}

void DroneLocalizerInterface::open(ros::NodeHandle &nIn)
{
    DroneModuleInterface::open(nIn);

    // Subscribers
    drone_estimated_GMR_pose_subscriber    = n.subscribe(DRONE_LOCALIZER_INTERFACE_POSE_PUBLICATION   , 1, &DroneLocalizerInterface::drone_estimated_GMR_pose_callback_function   , this);
    drone_estimated_GMR_speeds_subscriber  = n.subscribe(DRONE_LOCALIZER_INTERFACE_SPEEDS_PUBLICATION , 1, &DroneLocalizerInterface::drone_estimated_GMR_speeds_callback_function , this);
}

std::stringstream *DroneLocalizerInterface::getLocalizerState_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Localizer, is_started: " << isStarted() << std::endl;
    return &interface_printout_stream;
}

std::stringstream *DroneLocalizerInterface::getPositionEstimates_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Pose estimates:" << std::endl
        << " x:" << last_drone_estimated_GMRwrtGFF_pose_msg_.x <<"  "<< std::endl
        << " y:" << last_drone_estimated_GMRwrtGFF_pose_msg_.y <<"  " << std::endl
        << " z:" << last_drone_estimated_GMRwrtGFF_pose_msg_.z <<"  " << std::endl
        << " yaw:" << last_drone_estimated_GMRwrtGFF_pose_msg_.yaw <<"  " << std::endl
        << " pitch:" << last_drone_estimated_GMRwrtGFF_pose_msg_.pitch <<"  " << std::endl
        << " roll:" << last_drone_estimated_GMRwrtGFF_pose_msg_.roll <<"  " << std::endl;
    return &interface_printout_stream;
}

std::stringstream *DroneLocalizerInterface::getSpeedEstimates_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Speed estimates:" << std::endl
        << " dx:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dx <<"  " << std::endl
        << " dy:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dy <<"  " << std::endl
        << " dz:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dz <<"  " << std::endl
        << " dyaw:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dyaw <<"  " << std::endl;
//        << " dpitch:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dpitch << std::endl
//        << " droll:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.droll << std::endl;
    return &interface_printout_stream;
}



