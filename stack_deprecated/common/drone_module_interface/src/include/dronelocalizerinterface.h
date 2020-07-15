#ifndef DRONELOCALIZERINTERFACE_H
#define DRONELOCALIZERINTERFACE_H

#include "dronemoduleinterface.h"
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/droneSpeeds.h"
#include "communication_definition.h"

class DroneLocalizerInterface : public DroneModuleInterface
{
public:
    DroneLocalizerInterface( const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in);
    ~DroneLocalizerInterface();

    void open(ros::NodeHandle & nIn);

    inline const droneMsgsROS::dronePose&   last_drone_estimated_GMRwrtGFF_pose_msg()    { return last_drone_estimated_GMRwrtGFF_pose_msg_; }
    inline const droneMsgsROS::droneSpeeds& last_drone_estimated_GMRwrtGFF_speeds_msg()  { return last_drone_estimated_GMRwrtGFF_speeds_msg_; }

private:
    ros::Subscriber drone_estimated_GMR_pose_subscriber;
    ros::Subscriber drone_estimated_GMR_speeds_subscriber;
    void drone_estimated_GMR_pose_callback_function(const  droneMsgsROS::dronePose &msg)     { last_drone_estimated_GMRwrtGFF_pose_msg_  = (msg); }
    void drone_estimated_GMR_speeds_callback_function(const  droneMsgsROS::droneSpeeds &msg) { last_drone_estimated_GMRwrtGFF_speeds_msg_  = (msg); }
    droneMsgsROS::dronePose   last_drone_estimated_GMRwrtGFF_pose_msg_;
    droneMsgsROS::droneSpeeds last_drone_estimated_GMRwrtGFF_speeds_msg_;

public:
    std::stringstream *getLocalizerState_Stream();
    std::stringstream *getPositionEstimates_GMRwrtGFF_Stream();
    std::stringstream *getSpeedEstimates_GMRwrtGFF_Stream();
private:
    std::stringstream interface_printout_stream;
};

#endif // DRONELOCALIZERINTERFACE_H
