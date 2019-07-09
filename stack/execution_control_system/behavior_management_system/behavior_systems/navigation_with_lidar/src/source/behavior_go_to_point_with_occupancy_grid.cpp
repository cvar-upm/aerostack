/*!*******************************************************************************************
 *  \file       behavior_go_to_point_with_occupancy_grid.cpp
 *  \brief      Behavior Go To Point With Occupancy Grid implementation file.
 *  \details    This file implements the BehaviorGoToPointWithOccupancyGrid class.
 *  \authors    Raul Cruz
 *  \maintainer Raul Cruz
 *  \copyright  Copyright (c) 2019 Universidad Politecnica de Madrid
 *              All Rights Reserved
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/
#include "../include/behavior_go_to_point_with_occupancy_grid.h"
#include <pluginlib/class_list_macros.h>

namespace navigation_with_lidar
{

BehaviorGoToPointWithOccupancyGrid::BehaviorGoToPointWithOccupancyGrid() : BehaviorExecutionController()
{
  setName("go_to_point_with_occupancy_grid"); 
}
BehaviorGoToPointWithOccupancyGrid::~BehaviorGoToPointWithOccupancyGrid()
{

}

bool BehaviorGoToPointWithOccupancyGrid::checkSituation() 
{ 
 
  droneMsgsROS::ConsultBelief query_service;
  query_service.request.query = "battery_level(self,LOW)";

  if( belief_manager_client.call(query_service) == 0 ){
    std::cout<<"Warning: Belief Query service not ready, try again..."<<std::endl;
  }

  if(query_service.response.success)
  {
    setErrorMessage("Error: Battery low, unable to perform action");
    return false;
  }

  query_service.request.query = "flight_state(self,LANDED)";

  if( belief_manager_client.call(query_service) == 0 ){
    std::cout<<"Warning: Belief Query service not ready, try again..."<<std::endl;
  }

  if(query_service.response.success)
  {
    setErrorMessage("Error: Drone landed");
    return false;
  }
  return true;
}

void BehaviorGoToPointWithOccupancyGrid::checkGoal() 
{ 
  is_finished = goalReached(estimated_pose, target_position);
  if((is_finished && bad_args) ){
    std::cout<< "Behavior finished WITH error" << std::endl;
    BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::TIME_OUT);
  }else if( obstacle || is_finished ){
    std::cout<< "Behavior finished WITHOUT error" << std::endl;
    BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::GOAL_ACHIEVED);
  }
}

void BehaviorGoToPointWithOccupancyGrid::checkProgress() 
{ 
 
}

void BehaviorGoToPointWithOccupancyGrid::checkProcesses() 
{ 
 
}

void BehaviorGoToPointWithOccupancyGrid::onConfigure(){
  ros::NodeHandle nh = getNodeHandle();
  nh.param<std::string>("generated_path_topic", generated_path_topic_str, "path_with_id");
  nh.param<std::string>("generate_path_service", generate_path_service_str, "generate_path");
  nh.param<std::string>("estimated_pose_topic", estimated_pose_str, "EstimatedPose_droneGMR_wrt_GFF");
  nh.param<std::string>("yaw_controller_topic", yaw_controller_str , "droneControllerYawRefCommand");
  nh.param<std::string>("trajectory_topic", trajectory_topic, "droneTrajectoryAbsRefCommand");
  nh.param<std::string>("consult_belief", execute_query_srv,"consult_belief");
  nh.param<std::string>("controllers_topic", controllers_topic, "command/high_level");
  dumpTopicNames();
}

void BehaviorGoToPointWithOccupancyGrid::onActivate(){
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace(); 
  request_processes_activation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "start_processes");
  request_processes_deactivation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "stop_processes");

  processes = {"path_planner_in_occupancy_grid", "droneTrajectoryController"};

  aerostack_msgs::RequestProcesses request_processes_srv;
  for (std::string process : processes)
  {
    request_processes_srv.request.processes.push_back(process);
  }

  request_processes_activation_cli.call(request_processes_srv);

  if (!request_processes_srv.response.acknowledge)
  {
    setErrorMessage("Processes for Behavior: [ " + ros::this_node::getName() + " ] couldn't be started");
  }

  // Initialize topics
  path_sub = nh.subscribe("/" + nspace + "/" + generated_path_topic_str, 1000, &BehaviorGoToPointWithOccupancyGrid::generatedPathCallback, this);
  path_client = nh.serviceClient<aerostack_msgs::GeneratePath>("/" + nspace + "/" + generate_path_service_str);
  estimated_pose_sub = nh.subscribe("/" + nspace + "/" + estimated_pose_str, 1000, &BehaviorGoToPointWithOccupancyGrid::estimatedPoseCallBack, this);
  yaw_controller_pub = nh.advertise<droneMsgsROS::droneYawRefCommand>("/" + nspace + "/" + yaw_controller_str, 1000,true);
  trajectory_pub = nh.advertise<droneMsgsROS::dronePositionTrajectoryRefCommand>("/" + nspace + "/" + trajectory_topic, 1000,true);
  belief_manager_client = nh.serviceClient <droneMsgsROS::ConsultBelief> ("/" + nspace + "/" + execute_query_srv);
  controllers_pub = nh.advertise<droneMsgsROS::droneCommand>("/" + nspace + "/" + controllers_topic, 1000, true);


  is_finished = false;
  bad_args = false;
  obstacle = false;
  changing_yaw = false;
  pending_path = true;
  yaw_sent = false;

  setupStartPosition(estimated_pose);

  // Extract target position
  if( !grabInputPose(estimated_pose, target_position) ){
    bad_args = true;
    is_finished = true;
    return;
  }


  target_yaw = fixYaw(target_position.yaw);
  current_yaw = fixYaw(estimated_pose.yaw);
  
  changing_yaw = false;
  path_id = requestPath(target_position);
  return;

  yawOrRequest();
}


void BehaviorGoToPointWithOccupancyGrid::onExecute(){
  
}

void BehaviorGoToPointWithOccupancyGrid::onDeactivate()
{
  aerostack_msgs::RequestProcesses request_processes_srv;
  for (std::string process : processes)
  {
    request_processes_srv.request.processes.push_back(process);
  }

  request_processes_deactivation_cli.call(request_processes_srv);

  if (!request_processes_srv.response.acknowledge)
  {
    setErrorMessage("Processes for Behavior: [ " + ros::this_node::getName() + " ] couldn't be stopped");
  }

  path_sub.shutdown();
  path_client.shutdown();
  estimated_pose_sub.shutdown();
  yaw_controller_pub.shutdown();
  trajectory_pub.shutdown();
  belief_manager_client.shutdown();
  controllers_pub.shutdown();
}

// Callbacks
void BehaviorGoToPointWithOccupancyGrid::generatedPathCallback(const aerostack_msgs::PathWithID &resp_path){
  std::cout<< "Path is back id (" << resp_path.uid << "), our id (" << path_id << ")" <<std::endl;
  if( resp_path.uid != path_id ){
    // not for us
    return;
  }
  std::cout<< "Path is back size " << resp_path.poses.size() <<"\n";
  // No need to convert, just reusability
  nav_msgs::Path nav_path;
  nav_path.poses = resp_path.poses;
  setupTrajectory(current_traj);
  if( nav_path.poses.size() > 0 ){
    convertPath(nav_path, current_traj);
  }else{
    // Obstacle, stop!
    obstacle = true;
    droneMsgsROS::dronePositionRefCommand waypoint;
    waypoint.x = estimated_pose.x;
    waypoint.y = estimated_pose.y;
    waypoint.z = estimated_pose.z;
    // waypoint.yaw = target_yaw;
    current_traj.droneTrajectory.push_back(waypoint);
  }
  sendTrajectory(current_traj);
  // BehaviorProcess::setFinishEvent(aerostack_msgs::BehaviorEvent::GOAL_ACHIEVED);
  // BehaviorProcess::setFinishConditionSatisfied(true);
}

void BehaviorGoToPointWithOccupancyGrid::estimatedPoseCallBack(const droneMsgsROS::dronePose& msg){
  estimated_pose = msg;
  current_yaw = fixYaw(estimated_pose.yaw);
  /*if( is_finished = goalReached(estimated_pose, target_position) ){
    return;
  }*/
  /*if( pending_path || changing_yaw ){
    if( !yaw_sent ){
      yawOrRequest();
      sendYaw(target_yaw);
    }
  }*/
  // else executing trajectory
}

// Convert a navigation path to an aerostack one
void BehaviorGoToPointWithOccupancyGrid::convertPath(
  const nav_msgs::Path &path,
  droneMsgsROS::dronePositionTrajectoryRefCommand &return_path
){
  for(int i = 0; i < path.poses.size(); i++){
    droneMsgsROS::dronePositionRefCommand next_waypoint;
    next_waypoint.x = path.poses[i].pose.position.x;
    next_waypoint.y = path.poses[i].pose.position.y;
    next_waypoint.z = target_position.z;
    // ToDo := Is yaw necessary here?
    return_path.droneTrajectory.push_back(next_waypoint);
  }
}

// Extract input arguments
bool BehaviorGoToPointWithOccupancyGrid::grabInputPose(const droneMsgsROS::dronePose estimated_pose, droneMsgsROS::dronePose &position){
  // Extract target position
  std::string arguments = getParameters();
  YAML::Node config_file = YAML::Load(arguments);
  if(!config_file["coordinates"].IsDefined() && !config_file["relative_coordinates"].IsDefined()){
    std::cout<< "Null point" <<std::endl;
    return false;
  }else if( config_file["coordinates"].IsDefined() ){
    std::vector<double> points = config_file["coordinates"].as<std::vector<double>>();
    position.x   = std::isinf(points[0]) ? estimated_pose.x   : points[0];
    position.y   = std::isinf(points[1]) ? estimated_pose.y   : points[1];
    position.z   = std::isinf(points[2]) ? estimated_pose.z   : points[2];
    position.yaw = std::isinf(points[3]) ? estimated_pose.yaw : points[3];
    std::cout<< "Got point ["<<position.x << ", "<< position.y << ", " << position.z << ", " << position.yaw <<"]"<<std::endl;
  }else{
    std::vector<double> points = config_file["relative_coordinates"].as<std::vector<double>>();
    position.x   = std::isinf(points[0]) ? estimated_pose.x    : points[0] + estimated_pose.x;
    position.y   = std::isinf(points[1]) ? estimated_pose.y    : points[1] + estimated_pose.y;
    position.z   = std::isinf(points[2]) ? estimated_pose.z    : points[2] + estimated_pose.z;
    position.yaw = std::isinf(points[3]) ? estimated_pose.yaw  : points[3] + estimated_pose.yaw;
    std::cout<< "Got Relative point ["<<position.x << ", "<< position.y << ", " << position.z << ", " << position.yaw <<"]"<<std::endl;
  }
  return true;
}

// Send point to request path
int BehaviorGoToPointWithOccupancyGrid::requestPath(droneMsgsROS::dronePose position){

  // ask for a path to be generated
  aerostack_msgs::GeneratePath path_msg;

  geometry_msgs::PoseStamped target_stamped;
  target_stamped.pose.position.x = position.x;
  target_stamped.pose.position.y = position.y;
  target_stamped.pose.position.z = position.z;

  // ToDo := Yaw necessary?

  path_msg.request.goal = target_stamped;
  path_client.call(path_msg);
  int id = path_msg.response.uid;

  pending_path = false;

  std::cout<< "Run on point, got id "<< id << " name " << path_client.getService() <<std::endl;
  return id;
}


void BehaviorGoToPointWithOccupancyGrid::setControllerMode(){
  // set trajectory controller mode to move and wait for the change
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace(); 
  droneMsgsROS::droneCommand msg;
  std_msgs::Header header;
  header.frame_id = "behavior_go_to_point_in_occupancy_grid";
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::MOVE;
  controllers_pub.publish(msg);

  // Wait for controller to change mode
  ros::topic::waitForMessage<droneMsgsROS::droneTrajectoryControllerControlMode>(
    "/" + nspace + "/" + "droneTrajectoryController/controlMode", nh
  );
}

void BehaviorGoToPointWithOccupancyGrid::setupTrajectory(
  droneMsgsROS::dronePositionTrajectoryRefCommand &return_path
){
  return_path = droneMsgsROS::dronePositionTrajectoryRefCommand();
  return_path.header.stamp = ros::Time::now();
  return_path.initial_checkpoint = 0;
  return_path.is_periodic = false;
  return_path.droneTrajectory.clear();
}


void BehaviorGoToPointWithOccupancyGrid::setupStartPosition(droneMsgsROS::dronePose &position){
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace(); 
  // Get an initial estimate, just in case of a relative point
  position.x = 0;
  position.y = 0;
  position.z = 0;
  position = *ros::topic::waitForMessage<droneMsgsROS::dronePose>("/" + nspace + "/" + estimated_pose_str, nh);
}

void BehaviorGoToPointWithOccupancyGrid::sendTrajectory(droneMsgsROS::dronePositionTrajectoryRefCommand &traj){
  setControllerMode();
  std::cout<<"Trajectory sent with (" << traj.droneTrajectory.size() << ") points"<<std::endl;
  trajectory_pub.publish(traj);
}

double BehaviorGoToPointWithOccupancyGrid::fixYaw(double in_yaw){
  double ret_yaw = in_yaw;
  if( in_yaw < 0){
    ret_yaw += 2 * M_PI;  //No angles lower < 0 
  }
  return ret_yaw;
}

void BehaviorGoToPointWithOccupancyGrid::sendYaw(double yaw){
  setControllerMode();
  changing_yaw = true;
  // Ask for a move in yaw
  droneMsgsROS::droneYawRefCommand final_yaw;
  final_yaw.header.stamp = ros::Time::now();
  final_yaw.yaw = yaw;
  yaw_controller_pub.publish(final_yaw);
  yaw_sent = true;
}

bool BehaviorGoToPointWithOccupancyGrid::goalReached(droneMsgsROS::dronePose current, droneMsgsROS::dronePose target){
  /*std::cout<<"Goal "<< fabs(current.x - target.x);
  std::cout<<", "<< fabs(current.y - target.y);
  std::cout<<", "<< fabs(current.z - target.z)<<std::endl;*/
  return (
    fabs(current.x - target.x) < DIST_TOL &&
    fabs(current.y - target.y) < DIST_TOL &&
    fabs(current.z - target.z) < DIST_TOL
    // && fabs(current.yaw - target.yaw) < YAW_TOL
  );
}

void BehaviorGoToPointWithOccupancyGrid::yawOrRequest(){
  if( fabs(target_yaw - current_yaw) > YAW_TOL ){
    std::cout<< "Correcting yaw first..." << std::endl;
    std::cout<< "Requested (" << target_yaw << ") current(" << current_yaw << ")" << std::endl;
    changing_yaw = true;
    // Sleep a moment and ask again
    // sendYaw(target_yaw);
    // if( fabs(target_yaw - current_yaw) > YAW_TOL){
    //   ros::spinOnce();
    // }
  }else if( pending_path ){
    std::cout<< "Requesting path" << std::endl;
    changing_yaw = false;
    path_id = requestPath(target_position);
  }
}

void BehaviorGoToPointWithOccupancyGrid::dumpTopicNames(){
  std::cout<<"generated_path_topic_str "<<generated_path_topic_str<<std::endl;
  std::cout<<"generate_path_service_str "<<generate_path_service_str<<std::endl;
  std::cout<<"estimated_pose_str "<<estimated_pose_str<<std::endl;
  std::cout<<"yaw_controller_str "<<yaw_controller_str<<std::endl;
  std::cout<<"trajectory_topic "<<trajectory_topic<<std::endl;
  std::cout<<"execute_query_srv "<<execute_query_srv<<std::endl;
  std::cout<<"controllers_topic "<<controllers_topic<<std::endl;
}

}
PLUGINLIB_EXPORT_CLASS(navigation_with_lidar::BehaviorGoToPointWithOccupancyGrid, nodelet::Nodelet)
