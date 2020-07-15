#include "droneekfstateestimatorinterface.h"

DroneEKFStateEstimatorInterface::DroneEKFStateEstimatorInterface(const std::string &module_name_str_in, ModuleNames::name module_name_enum_in) :
    DroneModuleInterface( module_name_str_in, module_name_enum_in)
{
}

DroneEKFStateEstimatorInterface::~DroneEKFStateEstimatorInterface() {
}

void DroneEKFStateEstimatorInterface::open(ros::NodeHandle & nIn) {
    DroneModuleInterface::open(nIn);

    // Subscribers
    drone_estimated_LMrT_pose_subscriber   = n.subscribe(DRONE_STATE_ESTIMATOR_INTERFACE_POSE_SUBSCRIPTION_LMrT  , 1, &DroneEKFStateEstimatorInterface::drone_estimated_LMrT_pose_callback_function  , this);
    drone_estimated_GMR_pose_subscriber    = n.subscribe(DRONE_STATE_ESTIMATOR_INTERFACE_POSE_SUBSCRIPTION_GMR   , 1, &DroneEKFStateEstimatorInterface::drone_estimated_GMR_pose_callback_function   , this);
    drone_estimated_LMrT_speeds_subscriber = n.subscribe(DRONE_STATE_ESTIMATOR_INTERFACE_SPEEDS_SUBSCRIPTION_LMrT, 1, &DroneEKFStateEstimatorInterface::drone_estimated_LMrT_speeds_callback_function, this);
    drone_estimated_GMR_speeds_subscriber  = n.subscribe(DRONE_STATE_ESTIMATOR_INTERFACE_SPEEDS_SUBSCRIPTION_GMR , 1, &DroneEKFStateEstimatorInterface::drone_estimated_GMR_speeds_callback_function , this);

    // Publishers

    // Services
    setInitDroneYaw_srv_server = n.serviceClient<droneMsgsROS::setInitDroneYaw_srv_type>(std::string(MODULE_NAME_ODOMETRY_STATE_ESTIMATOR)+"/setInitDroneYaw");
}

bool DroneEKFStateEstimatorInterface::sendInitDroneYaw(double current_yaw_droneLMrT_telemetry_rad)
{
    droneMsgsROS::setInitDroneYaw_srv_type setInitDroneYaw_srv_var;
    setInitDroneYaw_srv_var.request.yaw_droneLMrT_telemetry_rad = current_yaw_droneLMrT_telemetry_rad;
    return setInitDroneYaw_srv_server.call(setInitDroneYaw_srv_var);
}

std::stringstream *DroneEKFStateEstimatorInterface::getStateEstimatorState_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+EKF, is_started: " << isStarted() << std::endl;
    return &interface_printout_stream;
}

std::stringstream *DroneEKFStateEstimatorInterface::getPositionEstimates_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Position estimates:" << std::endl
        << " x:" << last_drone_estimated_GMRwrtGFF_pose_msg_.x << std::endl
        << " y:" << last_drone_estimated_GMRwrtGFF_pose_msg_.y << std::endl
        << " z:" << last_drone_estimated_GMRwrtGFF_pose_msg_.z << std::endl
        << " yaw:" << last_drone_estimated_GMRwrtGFF_pose_msg_.yaw << std::endl
        << " pitch:" << last_drone_estimated_GMRwrtGFF_pose_msg_.pitch << std::endl
        << " roll:" << last_drone_estimated_GMRwrtGFF_pose_msg_.roll << std::endl;
    return &interface_printout_stream;
}

std::stringstream *DroneEKFStateEstimatorInterface::getSpeedEstimates_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Speed estimates:" << std::endl
        << " dx:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dx << std::endl
        << " dy:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dy << std::endl
        << " dz:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dz << std::endl
        << " dyaw:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dyaw << std::endl;
//        << " dpitch:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.dpitch << std::endl
//        << " droll:" << last_drone_estimated_GMRwrtGFF_speeds_msg_.droll << std::endl;
    return &interface_printout_stream;
}
