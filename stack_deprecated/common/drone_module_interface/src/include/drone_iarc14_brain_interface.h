#ifndef DRONE_IARC14_BRAIN_INTERFACE_H
#define DRONE_IARC14_BRAIN_INTERFACE_H

#include "dronemoduleinterface.h"
#include "communication_definition.h"
// Communications with mission_planner
#include "droneMsgsROS/droneHLCommand.h"
#include "droneMsgsROS/droneHLCommandAck.h"

class DroneIARC14BrainInterface : public DroneModuleInterface
{
public:
    DroneIARC14BrainInterface(const std::string &module_name_str_in, ModuleNames::name module_name_enum_in);
    ~DroneIARC14BrainInterface();

    void open(ros::NodeHandle & nIn);

    // Communications with brain_module
public:
    void newHLCommand(droneMsgsROS::droneHLCommand::_hlCommand_type HL_command_in);
    bool checkLastAck();
    void unflagAckWaiting();
    void droneHLCommandAckCallback(const droneMsgsROS::droneHLCommandAck::ConstPtr& msg);

private:
    //drone HL command (publisher)
    ros::Publisher  droneHLCommPub;
    //drone HL command ack (subs)
    ros::Subscriber droneHLCommAckSub;
    bool                                          new_HL_command;
    droneMsgsROS::droneHLCommand::_hlCommand_type last_sent_HL_command;
    bool                                          just_received_ack;
    bool                                          last_received_ack;
};

#endif // DRONE_IARC14_BRAIN_INTERFACE_H
