#include "dronetrajectorycontrollerinterface.h"

DroneTrajectoryControllerInterface::DroneTrajectoryControllerInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in) :
    DroneModuleInterface( module_name_str_in, module_name_enum_in)
{
    last_received_control_mode = Controller_MidLevel_controlMode::UNKNOWN_CONTROL_MODE;
}

DroneTrajectoryControllerInterface::~DroneTrajectoryControllerInterface() {

}

void DroneTrajectoryControllerInterface::open(ros::NodeHandle & nIn) {
    DroneModuleInterface::open(nIn);

    // Subscribers
    controlModeSub=n.subscribe(std::string(MODULE_NAME_TRAJECTORY_CONTROLLER)+"/controlMode", 1, &DroneTrajectoryControllerInterface::controlModeSubCallback, this);
    drone_position_reference_subscriber   = n.subscribe(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_POSITION_REF_REBROADCAST_SUBSCRIPTION, 1, &DroneTrajectoryControllerInterface::droneCurrentPositionRefsSubCallback, this);
    drone_speed_reference_subscriber      = n.subscribe(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_SPEED_REF_REBROADCAST_SUBSCRIPTION, 1, &DroneTrajectoryControllerInterface::droneCurrentSpeedsRefsSubCallback, this);
    drone_trajectory_reference_subscriber = n.subscribe(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_TRAJECTORY_REF_REBROADCAST_SUBSCRIPTION, 1, &DroneTrajectoryControllerInterface::droneCurrentTrajectoryRefCommandCallback, this);

    // Publishers
    drone_position_reference_publisher   = n.advertise<droneMsgsROS::dronePositionRefCommandStamped>(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_POSITION_REF_PUBLICATION, 1);
    drone_speeds_reference_publisher     = n.advertise<droneMsgsROS::droneSpeeds>(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_SPEED_REF_PUBLICATION, 1);
    drone_abs_trajectory_reference_publisher = n.advertise<droneMsgsROS::dronePositionTrajectoryRefCommand>(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_ABS_TRAJ_REF_CMD_PUBLICATION, 1);
    drone_rel_trajectory_reference_publisher = n.advertise<droneMsgsROS::dronePositionTrajectoryRefCommand>(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_REL_TRAJ_REF_CMD_PUBLICATION, 1);
    drone_yaw_reference_publisher = n.advertise<droneMsgsROS::droneYawRefCommand>(DRONE_TRAJECTORY_CONTROLLER_INTERFACE_YAW_REF_CMD_PUBLICATION, 1);

    // Services
    setControlModeClientSrv=n.serviceClient<droneMsgsROS::setControlMode>(std::string(MODULE_NAME_TRAJECTORY_CONTROLLER)+"/setControlMode");
}

void DroneTrajectoryControllerInterface::controlModeSubCallback(const droneMsgsROS::droneTrajectoryControllerControlMode::ConstPtr &msg) {
    switch (msg->command) {
    case Controller_MidLevel_controlMode::TRAJECTORY_CONTROL:
        last_received_control_mode = Controller_MidLevel_controlMode::TRAJECTORY_CONTROL;
        break;
    case Controller_MidLevel_controlMode::POSITION_CONTROL:
        last_received_control_mode = Controller_MidLevel_controlMode::POSITION_CONTROL;
        break;
    case Controller_MidLevel_controlMode::SPEED_CONTROL:
        last_received_control_mode = Controller_MidLevel_controlMode::SPEED_CONTROL;
        break;

    default:
        last_received_control_mode = Controller_MidLevel_controlMode::UNKNOWN_CONTROL_MODE;
        break;
    }
}

bool DroneTrajectoryControllerInterface::setControlMode(Controller_MidLevel_controlMode::controlMode new_control_mode) {
    //Prepare service message
    droneMsgsROS::setControlMode setControlModeSrv;
    setControlModeSrv.request.controlMode.command = new_control_mode;

    //use service
    if(setControlModeClientSrv.call(setControlModeSrv)) {
        return setControlModeSrv.response.ack;
    } else {
        return false;
    }
}

void DroneTrajectoryControllerInterface::droneCurrentPositionRefsSubCallback(const droneMsgsROS::dronePose::ConstPtr &msg) {
    current_drone_position_reference_ = (*msg);
}

void DroneTrajectoryControllerInterface::droneCurrentSpeedsRefsSubCallback(const droneMsgsROS::droneSpeeds::ConstPtr &msg) {
    current_drone_speed_reference_    = (*msg);
}

void DroneTrajectoryControllerInterface::droneCurrentTrajectoryRefCommandCallback(const droneMsgsROS::dronePositionTrajectoryRefCommand::ConstPtr& msg) {
    current_drone_trajectory_command_ = (*msg);
}


void DroneTrajectoryControllerInterface::publishDronePositionReference(double x, double y, double z) {
    droneMsgsROS::dronePositionRefCommandStamped  drone_position_reference;
//    drone_position_reference.target_frame = "drone_GMR";
//    drone_position_reference.reference_frame = "GFF";
//    drone_position_reference.YPR_system = "wYvPuR";
    drone_position_reference.header.stamp  = ros::Time::now();
    drone_position_reference.position_command.x = x;
    drone_position_reference.position_command.y = y;
    drone_position_reference.position_command.z = z;

    drone_position_reference_publisher.publish(drone_position_reference);
}

void DroneTrajectoryControllerInterface::publishDroneYawReference(double yaw)
{
    droneMsgsROS::droneYawRefCommand drone_yaw_reference;
    drone_yaw_reference.header.stamp = ros::Time::now();
    drone_yaw_reference.yaw = yaw;

    drone_yaw_reference_publisher.publish(drone_yaw_reference);
}

void DroneTrajectoryControllerInterface::publishDroneSpeedsReference(double vxfi, double vyfi) {
    droneMsgsROS::droneSpeeds drone_speed_reference;
//    drone_speed_reference.target_frame = "drone_GMR";
//    drone_speed_reference.reference_frame = "GFF";
//    drone_speed_reference.YPR_system = "wYvPuR";
    drone_speed_reference.time = ros::Time::now().toSec();
    drone_speed_reference.dx = vxfi;
    drone_speed_reference.dy = vyfi;
    drone_speed_reference.dz     = 0.0;
    drone_speed_reference.dyaw   = 0.0;
    drone_speed_reference.dpitch = 0.0;
    drone_speed_reference.droll  = 0.0;

    drone_speeds_reference_publisher.publish(drone_speed_reference);
}

void DroneTrajectoryControllerInterface::publishDroneRelSpeedsReference(double vlx, double vly, double drone_yaw_rad)
{
    double vxfi, vyfi;
    vxfi = (+1.0) * cos(drone_yaw_rad) * vlx + (-1.0) * sin(drone_yaw_rad) * vly;
    vyfi = (+1.0) * sin(drone_yaw_rad) * vlx + (+1.0) * cos(drone_yaw_rad) * vly;
    publishDroneSpeedsReference( vxfi, vyfi);
}

void DroneTrajectoryControllerInterface::publishDroneAbsTrajecotryReference(const std::vector<SimpleTrajectoryWaypoint> * const trajectory_waypoints_out, const int initial_checkpoint_out, const bool is_periodic_out ) {
    droneMsgsROS::dronePositionTrajectoryRefCommand drone_trajectory_reference_command;
//    drone_trajectory_reference_command.target_frame = "drone_GMR";
//    drone_trajectory_reference_command.reference_frame = "GFF";
//    drone_trajectory_reference_command.YPR_system = "wYvPuR";
    drone_trajectory_reference_command.header.stamp = ros::Time::now();
    for (std::vector<SimpleTrajectoryWaypoint>::const_iterator it = (*trajectory_waypoints_out).begin();
         it != (*trajectory_waypoints_out).end();
         ++it) {
        droneMsgsROS::dronePositionRefCommand next_waypoint;
        next_waypoint.x = it->x;
        next_waypoint.y = it->y;
        next_waypoint.z = it->z;
        drone_trajectory_reference_command.droneTrajectory.push_back(next_waypoint);
    }
    drone_trajectory_reference_command.initial_checkpoint = initial_checkpoint_out;
    drone_trajectory_reference_command.is_periodic = is_periodic_out;

    drone_abs_trajectory_reference_publisher.publish(drone_trajectory_reference_command);
}

void DroneTrajectoryControllerInterface::publishDroneRelTrajecotryReference( const std::vector<SimpleTrajectoryWaypoint> * const trajectory_waypoints_out, const int initial_checkpoint_out, const bool is_periodic_out)
{
    droneMsgsROS::dronePositionTrajectoryRefCommand drone_trajectory_reference_command;
    //    drone_trajectory_reference_command.target_frame = "drone_GMR";
    //    drone_trajectory_reference_command.reference_frame = "current_drone_GMR";
    //    drone_trajectory_reference_command.YPR_system = "wYvPuR";
        drone_trajectory_reference_command.header.stamp = ros::Time::now();
        for (std::vector<SimpleTrajectoryWaypoint>::const_iterator it = (*trajectory_waypoints_out).begin();
             it != (*trajectory_waypoints_out).end();
             ++it) {
            droneMsgsROS::dronePositionRefCommand next_waypoint;
            next_waypoint.x = it->x;
            next_waypoint.y = it->y;
            next_waypoint.z = it->z;
            drone_trajectory_reference_command.droneTrajectory.push_back(next_waypoint);
        }
        drone_trajectory_reference_command.initial_checkpoint = initial_checkpoint_out;
        drone_trajectory_reference_command.is_periodic = is_periodic_out;

        drone_rel_trajectory_reference_publisher.publish(drone_trajectory_reference_command);
}


std::stringstream *DroneTrajectoryControllerInterface::getControllerState()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Controller: " << std::endl
        << " is_started: " << isStarted() << std::endl
        << " control_mode: ";
    switch (getControlMode()) {
    case Controller_MidLevel_controlMode::SPEED_CONTROL:
        interface_printout_stream << "SPEED     " << std::endl;
        break;
    case Controller_MidLevel_controlMode::POSITION_CONTROL:
        interface_printout_stream << "POSITION  " << std::endl;
        break;
    case Controller_MidLevel_controlMode::TRAJECTORY_CONTROL:
        interface_printout_stream << "TRAJECTORY" << std::endl;
        break;
     case Controller_MidLevel_controlMode::UNKNOWN_CONTROL_MODE:
    default:
        interface_printout_stream << "UNKNOWN   " << std::endl;
        break;
    }

    return &interface_printout_stream;
}

std::stringstream *DroneTrajectoryControllerInterface::getPositionReferences_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Position estimates:" << std::endl
        << " xci:" << current_drone_position_reference_.x << std::endl
        << " yci:" << current_drone_position_reference_.y << std::endl
        << " zci:" << current_drone_position_reference_.z << std::endl
        << " yawci:" << current_drone_position_reference_.yaw << std::endl;
//        << " pitchfi:" << current_drone_position_reference_.pitch << std::endl
//        << " rollfi:" << current_drone_position_reference_.roll << std::endl;
    return &interface_printout_stream;
}

std::stringstream *DroneTrajectoryControllerInterface::getSpeedReferences_GMRwrtGFF_Stream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
        << "+Speed estimates:" << std::endl
        << " vxfi:" << current_drone_speed_reference_.dx << std::endl
        << " vyfi:" << current_drone_speed_reference_.dy << std::endl
        << " vzfi:" << current_drone_speed_reference_.dz << std::endl
        << " dyawfi:" << current_drone_speed_reference_.dyaw << std::endl;

    return &interface_printout_stream;
}
