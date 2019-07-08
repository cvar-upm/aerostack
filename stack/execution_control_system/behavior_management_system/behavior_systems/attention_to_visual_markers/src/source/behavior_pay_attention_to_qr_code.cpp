/*!*********************************************************************************
 *  \file       behavior_pay_attention_to_qr_code.cpp
 *  \brief      BehaviorPayAttentionToQRCode implementation file.
 *  \details    This file implements the BehaviorPayAttentionToQRCode class.
 *  \authors    Rafael Artiñano Muñoz, Guillermo Echegoyen Blanco
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

#include "../include/behavior_pay_attention_to_qr_code.h"
#include <pluginlib/class_list_macros.h>
namespace attention_to_visual_markers
{
BehaviorPayAttentionToQRCode::BehaviorPayAttentionToQRCode() : BehaviorExecutionController()
{
setName("pay_attention_to_qr_code"); 
}
BehaviorPayAttentionToQRCode::~BehaviorPayAttentionToQRCode()
{

}

void BehaviorPayAttentionToQRCode::checkProgress() 
{ 

}

void BehaviorPayAttentionToQRCode::checkProcesses() 
{ 

}

void BehaviorPayAttentionToQRCode::onExecute() 
{ 

}

void BehaviorPayAttentionToQRCode::checkGoal() 
{ 

}

/*Robot Process*/
void BehaviorPayAttentionToQRCode::onConfigure()
{
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();

  std::string refresh;
  nh.param<std::string>("refresh_rate", refresh, DEFAULT_REFRESH_RATE);
  refresh_rate = std::stod(refresh);

  nh.param<std::string>("qr_interpretation_topic", qr_interpretation_str, "qr_interpretation");
}

void BehaviorPayAttentionToQRCode::onActivate()
{
   // Start processes
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  request_processes_activation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "start_processes");
  request_processes_deactivation_cli =
      nh.serviceClient<aerostack_msgs::RequestProcesses>("/" + nspace + "/" + "stop_processes");

  processes = {"qr_recognizer_process"};

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

  qr_interpretation_sub =
      nh.subscribe("/" + nspace + "/" + qr_interpretation_str, 1, &BehaviorPayAttentionToQRCode::qrInterpretationCallBack, this);
  add_client = nh.serviceClient<droneMsgsROS::AddBelief>("/" + nspace + "/" + "add_belief");
  remove_client = nh.serviceClient<droneMsgsROS::RemoveBelief>("/" + nspace + "/" + "remove_belief");

  previous_qr = "";
  qr_code_belief_id = std::to_string(requestBeliefId());

}


void BehaviorPayAttentionToQRCode::onDeactivate()
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
  request_processes_activation_cli.shutdown();
  request_processes_deactivation_cli.shutdown();
  add_client.shutdown();
  remove_client.shutdown();
  qr_interpretation_sub.shutdown();
}

bool BehaviorPayAttentionToQRCode::checkSituation(){
  return true;
}

int BehaviorPayAttentionToQRCode::requestBeliefId()
{
  ros::NodeHandle nh = getNodeHandle();
  std::string nspace = getNamespace();
  int ret = 100;
  droneMsgsROS::GenerateID::Request req;
  droneMsgsROS::GenerateID::Response res;
  ros::ServiceClient id_gen_client = nh.serviceClient<droneMsgsROS::GenerateID>("/" + nspace + "/" + "generate_id");
  id_gen_client.call(req, res);

  if (res.ack)
  {
    ret = res.id;
  }

  id_gen_client.shutdown();
  return ret;
}

/*Callbacks*/
void BehaviorPayAttentionToQRCode::qrInterpretationCallBack(const droneMsgsROS::QRInterpretation &msg)
{
  if (msg.message != "")
  {
    if (previous_qr != msg.message)
    {
      if (previous_qr != "")
      {
        sendQRInterpretation(previous_qr, false);
      }
      sendQRInterpretation(msg.message, true);
      previous_qr = msg.message;
    }
  }
  else
  {
    if (previous_qr != "")
    {
      sendQRInterpretation(previous_qr, false);
      previous_qr = "";
    }
  }
}

bool BehaviorPayAttentionToQRCode::addBelief(std::string message, bool multivalued)
{
  droneMsgsROS::AddBelief::Request req;
  droneMsgsROS::AddBelief::Response res;
  req.belief_expression = message;
  req.multivalued = multivalued;
  add_client.call(req, res);
  return res.success;
}

bool BehaviorPayAttentionToQRCode::removeBelief(std::string message)
{
  droneMsgsROS::RemoveBelief::Request req;
  droneMsgsROS::RemoveBelief::Response res;
  req.belief_expression = message;
  remove_client.call(req, res);
  return res.success;
}

bool BehaviorPayAttentionToQRCode::setupBeliefs(std::string message)
{
  std::string msg1 = "object(" + qr_code_belief_id + ", qr_code)";
  std::string msg2 = "code(" + qr_code_belief_id + ", " + message + ")";
  std::string msg3 = "visible(" + qr_code_belief_id + ")";

  if (!addBelief(msg1, false))
  {
    removeBelief(msg1);
    return false;
  }

  if (!addBelief(msg2, false))
  {
    removeBelief(msg1);
    removeBelief(msg2);
    return false;
  }

  if (!addBelief(msg3, true))
  {
    removeBelief(msg1);
    removeBelief(msg2);
    removeBelief(msg3);
    return false;
  }

  return true;
}

bool BehaviorPayAttentionToQRCode::sendQRInterpretation(std::string message, bool visible)
{
  bool ret = false;

  if (visible)
  {
    ret = setupBeliefs(message);
  }
  else
  {
    ret = removeBelief("visible(" + qr_code_belief_id + ")");
  }
  return ret;
}


}
PLUGINLIB_EXPORT_CLASS(attention_to_visual_markers::BehaviorPayAttentionToQRCode, nodelet::Nodelet)
