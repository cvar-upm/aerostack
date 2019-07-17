/*!*******************************************************************************************
 *  \file       behavior_generate_path_with_occupancy_grid.cpp
 *  \brief      Behavior Generate Path With Occupancy Grid implementation file.
 *  \details    This file implements the BehaviorGeneratePathWithOccupancyGrid class.
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
#include "../include/behavior_generate_path_with_occupancy_grid.h"
#include <pluginlib/class_list_macros.h>
namespace navigation_with_lidar
{

BehaviorGeneratePathWithOccupancyGrid::BehaviorGeneratePathWithOccupancyGrid() : BehaviorExecutionController()
{
setName("generate_path_with_occupancy_grid"); 
}
BehaviorGeneratePathWithOccupancyGrid::~BehaviorGeneratePathWithOccupancyGrid()
{

}

void BehaviorGeneratePathWithOccupancyGrid::checkProgress() 
{ 

}

void BehaviorGeneratePathWithOccupancyGrid::checkProcesses() 
{ 

}

void BehaviorGeneratePathWithOccupancyGrid::onExecute() 
{ 

}

void BehaviorGeneratePathWithOccupancyGrid::onConfigure(){
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();

  nh.param<std::string>("generated_path_topic_str", generated_path_topic_str, "path_with_id");
  nh.param<std::string>("generate_path_service_str", generate_path_service_str, "generate_path");
  nh.param<std::string>("add_belief_service_str", add_belief_service_str, "add_belief");
}

void BehaviorGeneratePathWithOccupancyGrid::onActivate(){
   // Start processes
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

  is_finished = false;
  bad_args = false;
  // Extract target position
  if( !grabInputPose(target_position) ){
    bad_args = true;
    is_finished = true;
    return;
  }


  path_sub = nh.subscribe("/" + nspace + "/" + generated_path_topic_str, 1000, &BehaviorGeneratePathWithOccupancyGrid::generatedPathCallback, this);
  path_client = nh.serviceClient<aerostack_msgs::GeneratePath>("/" + nspace + "/" + generate_path_service_str);
  belief_manager_client = nh.serviceClient<droneMsgsROS::AddBelief>("/" + nspace + "/" + add_belief_service_str);

  path_id = requestPath(target_position);
}

void BehaviorGeneratePathWithOccupancyGrid::checkGoal(){
  if( (is_finished && bad_args) ){
    std::cout<< "Behavior finished WITH error" << std::endl;
    BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::TIME_OUT);
  }else if( is_finished ){
    std::cout<< "Behavior finished WITHOUT error" << std::endl;
    BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::GOAL_ACHIEVED);
  }
}

void BehaviorGeneratePathWithOccupancyGrid::onDeactivate(){

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
  request_processes_activation_cli.shutdown();
  request_processes_deactivation_cli.shutdown();

  path_sub.shutdown();
  path_client.shutdown();
  belief_manager_client.shutdown();
}

bool BehaviorGeneratePathWithOccupancyGrid::checkSituation(){
  return true;
}

// Callbacks
void BehaviorGeneratePathWithOccupancyGrid::generatedPathCallback(const aerostack_msgs::PathWithID &resp_path){
  // not for us
  if(!is_finished){
  std::cout<< "Path is back id (" << resp_path.uid << "), our id (" << path_id << ")" <<std::endl;
  if( resp_path.uid != path_id ){
    return;
  }
  std::cout<< "Path is back size " << resp_path.poses.size() <<"\n";
  // No need to convert, just reusability
  droneMsgsROS::dronePositionTrajectoryRefCommand path;
  nav_msgs::Path nav_path;
  nav_path.poses = resp_path.poses;
  convertPath(nav_path, path);
  std::string serialized = serializePath(requestBeliefId(), path);
  addBelief(serialized);
  }
  is_finished = true;
}

///////////
// Utils //
///////////

// Get new id for a path
int BehaviorGeneratePathWithOccupancyGrid::requestBeliefId(){
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  int ret = 100;
  droneMsgsROS::GenerateID::Request req;
  droneMsgsROS::GenerateID::Response res;
  ros::ServiceClient id_gen_client = nh.serviceClient<droneMsgsROS::GenerateID>("/" + nspace + "/" + "belief_manager_process/generate_id");
  id_gen_client.call(req, res);

  if( res.ack ){
    ret = res.id;
  }

  id_gen_client.shutdown();
  return ret;
}

// Convert a navigation path to an aerostack one
void BehaviorGeneratePathWithOccupancyGrid::convertPath(
  const nav_msgs::Path &path,
  droneMsgsROS::dronePositionTrajectoryRefCommand &return_path
){
  return_path.header.stamp = ros::Time::now();
  return_path.initial_checkpoint = 0;
  return_path.is_periodic = false;

  for(int i = 0; i < path.poses.size(); i++){
    droneMsgsROS::dronePositionRefCommand next_waypoint;
    next_waypoint.x = path.poses[i].pose.position.x;
    next_waypoint.y = path.poses[i].pose.position.y;
    next_waypoint.z = target_position.z;
    return_path.droneTrajectory.push_back(next_waypoint);
  }
}

// Convert aerostack path to string (for belief)
std::string BehaviorGeneratePathWithOccupancyGrid::serializePath(int id, droneMsgsROS::dronePositionTrajectoryRefCommand &path){
  std::ostringstream ret_stream;
  ret_stream << "path(" << id << ",(";
  for(int i = 0; i < path.droneTrajectory.size(); i++){
    ret_stream << "(";
    ret_stream << path.droneTrajectory[i].x << ",";
    ret_stream << path.droneTrajectory[i].y << ",";
    ret_stream << path.droneTrajectory[i].z;
    ret_stream << ")" << (i < path.droneTrajectory.size() -1 ? ", " : "");
  }
  ret_stream << "))";
  std::ostringstream ret_stream2;
  ret_stream2 << "object(" << id << ",path)";
  addBelief(ret_stream2.str());
  return ret_stream.str();
}

// Add a string belief
void BehaviorGeneratePathWithOccupancyGrid::addBelief(std::string belief){
  droneMsgsROS::AddBelief belief_msg;
  belief_msg.request.multivalued = true;
  belief_msg.request.belief_expression = belief;
  belief_manager_client.call(belief_msg);
}

// Extract input arguments
bool BehaviorGeneratePathWithOccupancyGrid::grabInputPose(droneMsgsROS::dronePose &position){
  // Extract target position
  std::string arguments = getParameters();
  YAML::Node config_file = YAML::Load(arguments);
  if(!config_file["coordinates"].IsDefined()){
    std::cout<< "Null point" <<std::endl;
    return false;
  }
  std::vector<double> points = config_file["coordinates"].as<std::vector<double>>();
  position.x = points[0];
  position.y = points[1];
  position.z = points[2];
  std::cout<< "Got point ["<<position.x << ", "<< position.y << ", " << position.z <<"]"<<std::endl;
  return true;
}

// Send point to request path
int BehaviorGeneratePathWithOccupancyGrid::requestPath(droneMsgsROS::dronePose position){

  // ask for a path to be generated
  aerostack_msgs::GeneratePath path_msg;

  geometry_msgs::PoseStamped target_stamped;
  target_stamped.pose.position.x = position.x;
  target_stamped.pose.position.y = position.y;
  target_stamped.pose.position.z = position.z;

  path_msg.request.goal = target_stamped;
  path_client.call(path_msg);
  int id = path_msg.response.uid;

  std::cout<< "Run on point, got id "<< id << " name " << path_client.getService() <<std::endl;
  return id;
}

}
PLUGINLIB_EXPORT_CLASS(navigation_with_lidar::BehaviorGeneratePathWithOccupancyGrid, nodelet::Nodelet)
