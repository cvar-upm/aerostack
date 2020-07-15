#include "drone_iarc14_brain_interface.h"

DroneIARC14BrainInterface::DroneIARC14BrainInterface(const std::string &module_name_str_in, ModuleNames::name module_name_enum_in) :
    DroneModuleInterface( module_name_str_in, module_name_enum_in),
    new_HL_command(false),
    just_received_ack(false),
    last_received_ack(false)
{
    last_sent_HL_command = droneMsgsROS::droneHLCommand::SLEEP;
}

DroneIARC14BrainInterface::~DroneIARC14BrainInterface()
{
}

void DroneIARC14BrainInterface::open(ros::NodeHandle &nIn)
{
    DroneModuleInterface::open(nIn);

    // Subscribers
    droneHLCommAckSub = n.subscribe(DRONE_MISSION_PLANNER_HL_COMMAND_ACK, 1, &DroneIARC14BrainInterface::droneHLCommandAckCallback, this);

    // Publishers
    droneHLCommPub    = n.advertise<droneMsgsROS::droneHLCommand>(DRONE_MISSION_PLANNER_HL_COMMAND, 1, true);

    // Services

    return;
}

void DroneIARC14BrainInterface::newHLCommand(droneMsgsROS::droneHLCommand::_hlCommand_type HL_command_in)
{
    new_HL_command  = true;
    last_sent_HL_command = HL_command_in;

    droneMsgsROS::droneHLCommand drone_HL_command_msg;
    drone_HL_command_msg.time      = ros::Time::now();
    drone_HL_command_msg.hlCommand = HL_command_in;

    droneHLCommPub.publish(drone_HL_command_msg);
    return;
}

bool DroneIARC14BrainInterface::checkLastAck()
{
    if (new_HL_command && just_received_ack) {
        just_received_ack = false;
        if (last_received_ack) {
            unflagAckWaiting();
            return true;
        } else {
            newHLCommand(last_sent_HL_command);
            return false;
        }
    }
    return false;
}

void DroneIARC14BrainInterface::unflagAckWaiting()
{
    new_HL_command       = false;
    last_sent_HL_command = droneMsgsROS::droneHLCommand::SLEEP;
    just_received_ack    = false;
    last_received_ack    = false;
}

void DroneIARC14BrainInterface::droneHLCommandAckCallback(const droneMsgsROS::droneHLCommandAck::ConstPtr &msg)
{
    just_received_ack = true;
    last_received_ack = msg->ack;
}


