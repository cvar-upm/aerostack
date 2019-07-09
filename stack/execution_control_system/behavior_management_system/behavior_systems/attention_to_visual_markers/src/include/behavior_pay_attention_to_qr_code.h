/*!*********************************************************************************
 *  \file       behavior_pay_attention_to_qr_code.h
 *  \brief      BehaviorPayAttentionToQRCode definition file.
 *  \details    This file contains the BehaviorPayAttentionToQRCode declaration. To obtain more information about
 *              it's implementation consult the behavior_pay_attention_to_qr_code.cpp file.
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

#ifndef BEHAVIOR_PAY_ATTENTION_TO_QR_CODE
#define BEHAVIOR_PAY_ATTENTION_TO_QR_CODE

#include <ros/ros.h>
#include <tuple>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

#include <droneMsgsROS/AddBelief.h>
#include <droneMsgsROS/GenerateID.h>
#include <droneMsgsROS/QRInterpretation.h>
#include <droneMsgsROS/RemoveBelief.h>
#include <droneMsgsROS/RequestProcesses.h>
#include <behavior_execution_controller.h>
#include <aerostack_msgs/RequestProcesses.h>
#include <nodelet/nodelet.h>

#define DEFAULT_DRONE_ID "1"
#define DEFAULT_REFRESH_RATE "5"
namespace attention_to_visual_markers
{
class BehaviorPayAttentionToQRCode : public BehaviorExecutionController
{
private:
  // Communication variables

  ros::ServiceClient request_processes_activation_cli;
  ros::ServiceClient request_processes_deactivation_cli;
  double refresh_rate;
  std::vector<std::string> processes;
  std::string qr_interpretation_str;
  std::string previous_qr;
  std::string qr_code_belief_id;

  /*Subscribers & Publishers*/
  ros::Subscriber qr_interpretation_sub;
  ros::ServiceClient add_client;
  ros::ServiceClient remove_client;

  // BehaviorExecutionController
  bool checkSituation();
  void checkGoal();
  void checkProgress();
  void checkProcesses();

  void onConfigure();
  void onActivate();
  void onDeactivate();
  void onExecute();
  /* Callbacks */
  bool sendQRInterpretation(std::string message, bool visible);
  void qrInterpretationCallBack(const droneMsgsROS::QRInterpretation &msg);

  bool addBelief(std::string message, bool multivalued);
  bool removeBelief(std::string message);
  bool setupBeliefs(std::string message);
  int requestBeliefId();

public:
  BehaviorPayAttentionToQRCode();
  ~BehaviorPayAttentionToQRCode();
  inline double getRefreshRate() { return refresh_rate; }
};
}
#endif
