#ifndef DRONETRAJECTORYCONTROLLERINTERFACE_H
#define DRONETRAJECTORYCONTROLLERINTERFACE_H

#include "dronemoduleinterface.h"
#include "control/Controller_MidLevel_controlModes.h"
#include "droneMsgsROS/droneTrajectoryControllerControlMode.h"
#include "droneMsgsROS/setControlMode.h"
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/droneSpeeds.h"
#include "droneMsgsROS/dronePositionTrajectoryRefCommand.h"
#include "droneMsgsROS/dronePositionRefCommandStamped.h"
#include "droneMsgsROS/droneYawRefCommand.h"
#include "droneMsgsROS/droneAltitudeCmd.h"
#include "control/simpletrajectorywaypoint.h"
#include "communication_definition.h"

class DroneTrajectoryControllerInterface : public DroneModuleInterface
{
public:
    DroneTrajectoryControllerInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in);
    ~DroneTrajectoryControllerInterface();

    void open(ros::NodeHandle & nIn);
    // controlMode
    bool setControlMode(Controller_MidLevel_controlMode::controlMode new_control_mode);
    inline Controller_MidLevel_controlMode::controlMode getControlMode() { return last_received_control_mode; }

private:
    // Subscribers
    ros::Subscriber controlModeSub;
    void controlModeSubCallback(const droneMsgsROS::droneTrajectoryControllerControlMode::ConstPtr &msg);
    Controller_MidLevel_controlMode::controlMode last_received_control_mode;
    // Controller references, meaning of useful values depend on the current control mode
    ros::Subscriber drone_position_reference_subscriber;
    droneMsgsROS::dronePose   current_drone_position_reference_;                      // useful values: x, y, z, yaw
    ros::Subscriber drone_speed_reference_subscriber;
    droneMsgsROS::droneSpeeds current_drone_speed_reference_;                         // useful values: vxfi, vyfi, vzfi (dyawfi is unused, undebugged)
    ros::Subscriber drone_trajectory_reference_subscriber;
    droneMsgsROS::dronePositionTrajectoryRefCommand current_drone_trajectory_command_;// useful values: current trajectory: initial_checkpoint,isPeridioc, checkpoints[]
    void droneCurrentPositionRefsSubCallback(const droneMsgsROS::dronePose::ConstPtr &msg);
    void droneCurrentSpeedsRefsSubCallback(const droneMsgsROS::droneSpeeds::ConstPtr &msg);
    void droneCurrentTrajectoryRefCommandCallback(const droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr& msg);
    void droneCurrentPBVSrefSubCallback(const droneMsgsROS::dronePose::ConstPtr& msg);
public:
    inline const droneMsgsROS::dronePose&   current_drone_position_reference() { return current_drone_position_reference_; }
    inline const droneMsgsROS::droneSpeeds& current_drone_speed_reference() { return current_drone_speed_reference_; }
    inline const droneMsgsROS::dronePositionTrajectoryRefCommand& current_drone_trajectory_command() { return current_drone_trajectory_command_; }

    // Publishers
    // Controller references
private:
    ros::Publisher drone_position_reference_publisher;
    ros::Publisher drone_speeds_reference_publisher;
    ros::Publisher drone_abs_trajectory_reference_publisher;
    ros::Publisher drone_rel_trajectory_reference_publisher;
    ros::Publisher drone_yaw_reference_publisher;

public:
    void publishDronePositionReference( double x, double y, double z);
    void publishDroneYawReference( double yaw);
    void publishDroneSpeedsReference( double vxfi, double vyfi);
    void publishDroneRelSpeedsReference( double vlx, double vly, double drone_yaw_rad);
    void publishDroneAbsTrajecotryReference( const std::vector<SimpleTrajectoryWaypoint> * const trajectory_waypoints_out, const int initial_checkpoint_out, const bool is_periodic_out);
    void publishDroneRelTrajecotryReference( const std::vector<SimpleTrajectoryWaypoint> * const trajectory_waypoints_out, const int initial_checkpoint_out, const bool is_periodic_out);


    // Services
private:
    ros::ServiceClient setControlModeClientSrv;

public:
    std::stringstream *getControllerState();
    std::stringstream *getPositionReferences_GMRwrtGFF_Stream();
    std::stringstream *getSpeedReferences_GMRwrtGFF_Stream();
private:
    std::stringstream interface_printout_stream;
};

#endif // DRONETRAJECTORYCONTROLLERINTERFACE_H
