#ifndef DRONEEKFSTATEESTIMATORINTERFACE_H
#define DRONEEKFSTATEESTIMATORINTERFACE_H

#include "dronemoduleinterface.h"
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/droneSpeeds.h"
#include "droneMsgsROS/setInitDroneYaw_srv_type.h"
#include "communication_definition.h"

class DroneEKFStateEstimatorInterface : public DroneModuleInterface
{
public:
    DroneEKFStateEstimatorInterface(const std::string &module_name_str_in, ModuleNames::name module_name_enum_in);
    ~DroneEKFStateEstimatorInterface();

    void open(ros::NodeHandle & nIn);

    inline const droneMsgsROS::dronePose&   last_drone_estimated_LMrTwrtEKF_pose_msg() { return last_drone_estimated_LMrTwrtEKF_pose_msg_; }
    inline const droneMsgsROS::dronePose&   last_drone_estimated_GMRwrtGFF_pose_msg()  { return last_drone_estimated_GMRwrtGFF_pose_msg_; }
    inline const droneMsgsROS::droneSpeeds& last_drone_estimated_LMrTwrtEKF_speeds_msg() { return last_drone_estimated_LMrTwrtEKF_speeds_msg_; }
    inline const droneMsgsROS::droneSpeeds& last_drone_estimated_GMRwrtGFF_speeds_msg()  { return last_drone_estimated_GMRwrtGFF_speeds_msg_; }

    bool sendInitDroneYaw( double current_yaw_droneLMrT_telemetry_rad);
private:
    // Subscribers
    ros::Subscriber drone_estimated_LMrT_pose_subscriber;
    ros::Subscriber drone_estimated_GMR_pose_subscriber;
    ros::Subscriber drone_estimated_LMrT_speeds_subscriber;
    ros::Subscriber drone_estimated_GMR_speeds_subscriber;
    void drone_estimated_LMrT_pose_callback_function(const droneMsgsROS::dronePose &msg) { last_drone_estimated_LMrTwrtEKF_pose_msg_ = (msg); }
    void drone_estimated_GMR_pose_callback_function(const  droneMsgsROS::dronePose &msg) { last_drone_estimated_GMRwrtGFF_pose_msg_  = (msg); }
    void drone_estimated_LMrT_speeds_callback_function(const droneMsgsROS::droneSpeeds &msg) { last_drone_estimated_LMrTwrtEKF_speeds_msg_ = (msg); }
    void drone_estimated_GMR_speeds_callback_function(const  droneMsgsROS::droneSpeeds &msg) { last_drone_estimated_GMRwrtGFF_speeds_msg_  = (msg); }
    droneMsgsROS::dronePose   last_drone_estimated_LMrTwrtEKF_pose_msg_;
    droneMsgsROS::dronePose   last_drone_estimated_GMRwrtGFF_pose_msg_;
    droneMsgsROS::droneSpeeds last_drone_estimated_LMrTwrtEKF_speeds_msg_;
    droneMsgsROS::droneSpeeds last_drone_estimated_GMRwrtGFF_speeds_msg_;

    // services
    ros::ServiceClient setInitDroneYaw_srv_server;

public:
    std::stringstream *getStateEstimatorState_Stream();
    std::stringstream *getPositionEstimates_GMRwrtGFF_Stream();
    std::stringstream *getSpeedEstimates_GMRwrtGFF_Stream();
private:
    std::stringstream interface_printout_stream;
};

#endif // DRONEEKFSTATEESTIMATORINTERFACE_H
