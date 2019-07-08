/*!*******************************************************************************************
 *  \file       behavior_follow_path.cpp
 *  \brief      Behavior follow path implementation file.
 *  \details    This file implements the BehaviorFollowPathWithTrajectoryController class.
 *  \authors    Rafael Artiñano Muñoz, Abraham Carrera Groba
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

#include "../include/behavior_follow_path_with_trajectory_controller.h"
#include <pluginlib/class_list_macros.h>

namespace navigation_with_lidar
{
BehaviorFollowPathWithTrajectoryController::BehaviorFollowPathWithTrajectoryController() : BehaviorExecutionController() 
{ 
setName("follow_path_with_trajectory_controller"); 
}

BehaviorFollowPathWithTrajectoryController::~BehaviorFollowPathWithTrajectoryController() 
{
}

bool BehaviorFollowPathWithTrajectoryController::checkSituation()
{
  droneMsgsROS::ConsultBelief query_service;
  query_service.request.query = "battery_level(self,LOW)";

  if( query_client.call(query_service) == 0 ){
    std::cout<<"Warning: Belief Query service not ready, try again..."<<std::endl;
  }

  if(query_service.response.success)
  {
    setErrorMessage("Error: Battery low, unable to perform action");
    return false;
  }

  query_service.request.query = "flight_state(self,LANDED)";

  if( query_client.call(query_service) == 0 ){
    std::cout<<"Warning: Belief Query service not ready, try again..."<<std::endl;
  }

  if(query_service.response.success)
  {
    setErrorMessage("Error: Drone landed");
    return false;
  }
  return true;
}



void BehaviorFollowPathWithTrajectoryController::checkGoal() {
    if(iterate==lenght)
    {
      iterate=0;
      BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::GOAL_ACHIEVED);
      is_finished = true;
      return;
    }
    if(fail)
    {
      BehaviorExecutionController::setTerminationCause(aerostack_msgs::BehaviorActivationFinished::TIME_OUT);
      is_finished = true;
      return;
    }
    /*if(std::abs(target_position.z-estimated_pose_msg.z)<pose_variation_maximum &&
       std::abs(target_position.x-estimated_pose_msg.x)<pose_variation_maximum &&
       std::abs(target_position.y-estimated_pose_msg.y)<pose_variation_maximum &&
       estimated_speed_msg.dx>speed_maximum_at_end &&
       estimated_speed_msg.dz>speed_maximum_at_end &&
       estimated_speed_msg.dy>speed_maximum_at_end)
    {
      BehaviorProcess::setFinishEvent(aerostack_msgs::BehaviorEvent::WRONG_PROGRESS);
      BehaviorProcess::setFinishConditionSatisfied(true);
      is_finished = true;
      return;
    }*/


}

void BehaviorFollowPathWithTrajectoryController::checkProgress() 
{ 

}

void BehaviorFollowPathWithTrajectoryController::checkProcesses() 
{ 

}

void BehaviorFollowPathWithTrajectoryController::onConfigure()
{
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  nh.param<std::string>("estimated_pose_topic", estimated_pose_str, "EstimatedPose_droneGMR_wrt_GFF");
  nh.param<std::string>("controllers_topic", controllers_str, "command/high_level");
  nh.param<std::string>("rotation_angles_topic", rotation_angles_str, "rotation_angles");
  nh.param<std::string>("estimated_speed_topic",estimated_speed_str,"estimated_speed");
  nh.param<std::string>("yaw_controller_str",yaw_controller_str , "droneControllerYawRefCommand");
  nh.param<std::string>("service_topic_str",service_topic_str , "droneTrajectoryController/setControlMode");
  nh.param<std::string>("speed_reset", speed_reset_str,"droneSpeedsRefs");
  nh.param<std::string>("droneTrajectoryAbsRefCommand_topic", trajectory_ref_command_str, "droneTrajectoryAbsRefCommand");
  nh.param<std::string>("consult_belief",execute_query_srv,"consult_belief");
  nh.param<std::string>("society_pose_topic",society_pose_str,"societyPose");
 
  query_client = nh.serviceClient <droneMsgsROS::ConsultBelief> ("/" + nspace + "/" +execute_query_srv);
}

void BehaviorFollowPathWithTrajectoryController::onActivate()
{
   // Start processes
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  request_processes_activation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "start_processes");
  request_processes_deactivation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "stop_processes");

  processes = {"droneTrajectoryController"};

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

  // Activate communications
  estimated_pose_sub = nh.subscribe("/" + nspace + "/" + estimated_pose_str, 1000, &BehaviorFollowPathWithTrajectoryController::estimatedPoseCallBack, this);
  rotation_angles_sub = nh.subscribe("/" + nspace + "/" + rotation_angles_str, 1000, &BehaviorFollowPathWithTrajectoryController::rotationAnglesCallback, this);
  estimated_speed_sub = nh.subscribe("/" + nspace + "/" + estimated_speed_str, 1000, &BehaviorFollowPathWithTrajectoryController::estimatedSpeedCallback, this);
  controllers_pub = nh.advertise<droneMsgsROS::droneCommand>("/" + nspace + "/" + controllers_str, 1000, true);
  yaw_controller_pub=nh.advertise<droneMsgsROS::droneYawRefCommand>("/" + nspace + "/" + yaw_controller_str,1000);
  mode_service = nh.serviceClient<droneMsgsROS::setControlMode>("/" + nspace + "/" + service_topic_str);
  drone_speeds_reseter_pub = nh.advertise<droneMsgsROS::droneSpeeds>("/" + nspace + "/" + speed_reset_str, 1);
  reference_trajectory_pub = nh.advertise<droneMsgsROS::dronePositionTrajectoryRefCommand>("/" + nspace + "/" + trajectory_ref_command_str,100);
  query_client = nh.serviceClient <droneMsgsROS::ConsultBelief> ("/" + nspace + "/" + execute_query_srv);
  society_pose_sub=nh.subscribe("/" + nspace + "/" +society_pose_str,1000,&BehaviorFollowPathWithTrajectoryController::societyPoseCallback,this);



  // Behavior implementation
  
  estimated_pose_msg.x=0;
  estimated_pose_msg.y=0;
  estimated_pose_msg.z=0;
  /*behavior implementation*/
  std::cout << "topics initialized" << std::endl;
  // Extract target position
  std::string arguments = getParameters();
  YAML::Node config_file = YAML::Load(arguments);
  droneMsgsROS::dronePositionRefCommand real_position_msg;
  std::vector<droneMsgsROS::dronePositionRefCommand> droneTrajectoryAux;
  real_trajectory_msg.droneTrajectory=droneTrajectoryAux;
  real_position_msg.x = 0;
  real_position_msg.y = 0;
  real_position_msg.z = 0;
  lenght=0;
  int last=0;
  if(config_file["path"].IsDefined()){
    std::vector<std::vector<double>> points=config_file["path"].as<std::vector<std::vector<double>>>();
      target_position_first.x = points[0][0];
      target_position_first.y = points[0][1];
      target_position_first.z = points[0][2];
    last=points.size();
    for(int i=0;i<points.size();i++){
      // Selecting points with an euclidean longer or equal to an distance of 1 or the height must be higher than 0.5
      if(sqrt((real_position_msg.x-points[i][0])*(real_position_msg.x-points[i][0]) + (real_position_msg.y-points[i][1])*(real_position_msg.y-points[i][1])) >= 1 or abs(real_position_msg.z-points[i][2]) >= 0.5 ){
      real_trajectory_msg.header.stamp= ros::Time::now();
      real_position_msg.x = points[i][0];
      real_position_msg.y = points[i][1];
      real_position_msg.z = points[i][2];
      real_trajectory_msg.droneTrajectory.push_back(real_position_msg);
      lenght+=1;
      }
    }
    // Last point added
      real_trajectory_msg.header.stamp= ros::Time::now();
      real_position_msg.x = points[last-1][0];
      real_position_msg.y = points[last-1][1];
      real_position_msg.z = points[last-1][2];
      real_trajectory_msg.droneTrajectory.push_back(real_position_msg);
      lenght+=1;

  }
  else{
      std::cout << "fail while starting" << std::endl;
      return;

  }
  target_position.x=real_position_msg.x;
  target_position.y=real_position_msg.y;
  target_position.z=real_position_msg.z;
  std::cout << "The path sent is " << target_position << std::endl;
  std::cout << "The lenght is " << lenght << std::endl;
  // Publish controller reference
  droneMsgsROS::dronePositionTrajectoryRefCommand reference_trajectory_msg;
  droneMsgsROS::dronePositionRefCommand reference_position_msg;
  reference_trajectory_msg.header.frame_id="FOLLOW_PATH_WITH_TRAJECTORY_CONTROLLER";
  reference_trajectory_msg.header.stamp= ros::Time::now();
  reference_position_msg.x = estimated_pose_msg.x;
  reference_position_msg.y = estimated_pose_msg.y;
  reference_position_msg.z = estimated_pose_msg.z;
  reference_trajectory_msg.droneTrajectory.push_back(reference_position_msg);
  reference_trajectory_pub.publish(reference_trajectory_msg);

  droneMsgsROS::droneYawRefCommand reference_yaw_msg;
  reference_yaw_msg.yaw = estimated_pose_msg.yaw;
  reference_yaw_msg.header.stamp = ros::Time::now();
  yaw_controller_pub.publish(reference_yaw_msg);

  // Wait for controller to change mode
  ros::topic::waitForMessage<droneMsgsROS::droneTrajectoryControllerControlMode>(
    "/" + nspace + "/" + "droneTrajectoryController/controlMode", nh
  );
  for(int i=0;i<lenght;i++){
  droneMsgsROS::dronePositionTrajectoryRefCommand trajectory_msg;
  trajectory_msg.header.stamp= ros::Time::now();
  trajectory_msg.droneTrajectory.push_back(real_trajectory_msg.droneTrajectory[i]);
  reference_trajectory_pub.publish(trajectory_msg);
  }
  // Send target point

  std_msgs::Header header;
  header.frame_id = "behavior_follow_path_with_trajectory_controller";

  droneMsgsROS::droneCommand msg;
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::MOVE;
  controllers_pub.publish(msg);
  static_pose.x=estimated_pose_msg.x;
  static_pose.y=estimated_pose_msg.y;
  static_pose.z=estimated_pose_msg.z;
  std::cout << "The path sent is " << target_position << std::endl;
  // Publish controller reference
  reference_trajectory_msg.header.frame_id="FOLLOW_PATH_WITH_TRAJECTORY_CONTROLLER";
  reference_trajectory_msg.header.stamp= ros::Time::now();
  reference_position_msg.x = estimated_pose_msg.x;
  reference_position_msg.y = estimated_pose_msg.y;
  reference_position_msg.z = estimated_pose_msg.z;
  reference_trajectory_msg.droneTrajectory.push_back(reference_position_msg);
  reference_trajectory_pub.publish(reference_trajectory_msg);

  reference_yaw_msg.yaw = estimated_pose_msg.yaw;
  reference_yaw_msg.header.stamp = ros::Time::now();
  yaw_controller_pub.publish(reference_yaw_msg);

  // Wait for controller to change mode
  ros::topic::waitForMessage<droneMsgsROS::droneTrajectoryControllerControlMode>(
    "/" + nspace + "/" + "droneTrajectoryController/controlMode", nh
  );
  

}

void BehaviorFollowPathWithTrajectoryController::onDeactivate()
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
  estimated_pose_sub.shutdown();
  rotation_angles_sub.shutdown();
  estimated_speed_sub.shutdown();
  request_processes_activation_cli.shutdown();
  request_processes_deactivation_cli.shutdown();
}


void BehaviorFollowPathWithTrajectoryController::onExecute() 
{ 

  std_msgs::Header header;
  droneMsgsROS::droneCommand msg;
  header.frame_id = "behavior_follow_path_with_trajectory_controller";
  // Going to a point, and then waiting to reach it in order to go to another one.
  if(iterate<lenght){
   if(pass==0){
    droneMsgsROS::dronePositionTrajectoryRefCommand trajectory_msg;
    trajectory_msg.header.stamp= ros::Time::now();
    trajectory_msg.droneTrajectory.push_back(real_trajectory_msg.droneTrajectory[iterate]);
    reference_trajectory_pub.publish(trajectory_msg);
    pass=1;
   }
   if(std::abs(real_trajectory_msg.droneTrajectory[iterate].z-estimated_pose_msg.z)<0.3 &&
    std::abs(real_trajectory_msg.droneTrajectory[iterate].x-estimated_pose_msg.x)<0.3 &&
    std::abs(real_trajectory_msg.droneTrajectory[iterate].y- estimated_pose_msg.y)<0.3 && iterate<lenght-1 ||
    std::abs(real_trajectory_msg.droneTrajectory[iterate].z-estimated_pose_msg.z)<0.1 &&
    std::abs(real_trajectory_msg.droneTrajectory[iterate].x-estimated_pose_msg.x)<0.1 &&
    std::abs(real_trajectory_msg.droneTrajectory[iterate].y- estimated_pose_msg.y)<0.1 && iterate<=lenght-1 ){
      iterate+=1;
      pass=0;
      }
    else{
        std::cout << "Following " <<std::endl;
        std::cout <<real_trajectory_msg.droneTrajectory[iterate].x << std::endl;
        std::cout <<estimated_pose_msg.x << std::endl;
        }
   }
  msg.header = header;
  msg.command = droneMsgsROS::droneCommand::MOVE;
  controllers_pub.publish(msg);
  static_pose.x=estimated_pose_msg.x;
  static_pose.y=estimated_pose_msg.y;
  static_pose.z=estimated_pose_msg.z;

}

void BehaviorFollowPathWithTrajectoryController::estimatedSpeedCallback(const droneMsgsROS::droneSpeeds& msg)
{
  estimated_speed_msg=msg;
}
void BehaviorFollowPathWithTrajectoryController::estimatedPoseCallBack(const droneMsgsROS::dronePose& msg)
{
  std::cout << "estimating" << std::endl;
  estimated_pose_msg=msg;
}
void BehaviorFollowPathWithTrajectoryController::rotationAnglesCallback(const geometry_msgs::Vector3Stamped& msg)
{
  rotation_angles_msg=msg;
}


void BehaviorFollowPathWithTrajectoryController::societyPoseCallback(const droneMsgsROS::societyPose& msg)
{
  double proximity_limit = 1;
  for(unsigned int i=0;i<msg.societyDrone.size();i++)
  {
      if((sqrt(pow((msg.societyDrone[i].pose.x- estimated_pose_msg.x),2)+
      pow((msg.societyDrone[i].pose.y-estimated_pose_msg.y),2)))< proximity_limit){
      fail=true;}
  }
}
}
PLUGINLIB_EXPORT_CLASS(navigation_with_lidar::BehaviorFollowPathWithTrajectoryController, nodelet::Nodelet)
