#include "task_based_mission_planner_process.h"
using namespace std;

TaskBasedMissionPlanner::TaskBasedMissionPlanner(int argc, char **argv):DroneProcess(argc, argv)
{   
  //Just get the parameters from the launcher file.
  TaskBasedMissionPlanner::getParametersFromFile();
  //Initialize mission attribute.
  current_mission = new Mission(mission_path);
  event_handler   = new EventHandler(mission_path); 
  //Printing mission tree.
  current_mission -> printTree();
  event_handler   -> printEventVector();
}

TaskBasedMissionPlanner::~TaskBasedMissionPlanner()
{
	//TO DO
}
void TaskBasedMissionPlanner::startMission()
{   
  //Sending the first task
  cout << "\033[1;34m--------------- STARTING MISSION ---------------\033[0m" << endl;
  sendNewTask();
}

void TaskBasedMissionPlanner::abortMission()
{
  //droneMsgsROS::actionData msg;
  //When a mission is aborted, action HOVER is sent
  //and current Mission is destroyed.
  delete  current_mission;
  //What happens if this action is rejected? Pray.
  //msg.mpAction = 2;
  //droneRequestedActionPub.publish(msg);
  cout << "\033[1;31mMission aborted.\n\033[0m"<<endl;
  exit(1);
}

void TaskBasedMissionPlanner::sendNewTask()
{
  int mpAction_to_send;
  current_task = new Task();
  missionSchedulerEndingStep::endingStep event_ending_step;
  std::vector<missionSchedulerBehavior::taskBehaviors> active_behaviors;
  std::vector<duo<std::string,std::vector<double>>>  arguments_to_send;
  std::string behavior_name_to_send;
  std::string aux_message = "";
  //Action duration
  double action_duration = 0;
  //Message to fill with information
  droneMsgsROS::actionData msg;
  //Message where the arguments of the action are going to be stored;
  droneMsgsROS::actionArguments arg_msg;
  //Service request.
  droneMsgsROS::behaviorRequest srv;
  //Checking wherter the mission is completed
  if(current_mission->missionCompleted())
  {
    cout << "\033[1;34m--------------- Mission Completed!---------------\033[0m\n" << endl;
    ros::spin();
  }
  // If an event has been activated, then the task and the actions to perform are the event's ones.
  if(event_handler->activeEvent())
  {
    //Next task to perform
    //If there is not next action to send, then the ending step should be executed.
    if(!event_handler->nextTask(current_task))
    {    
      event_ending_step = event_handler->getCurrentEventEndingStep();
      //Executing ending step...
      cout << "Executing ending step..." << endl;
      switch(event_ending_step)
      {
        case missionSchedulerEndingStep::repeatTask:
          event_handler->resetEventHandler();
          break;
        case missionSchedulerEndingStep::nextTask:
          event_handler->resetEventHandler();
          sendNewTask();
          break;
        case missionSchedulerEndingStep::abortMission:
          event_handler->resetEventHandler();
          abortMission();
          break;
        default:
          event_handler->resetEventHandler();
          break;
      }
    }
    //Behaviors needed to be activated.
    active_behaviors = *current_task->getBehaviors();
    //Action's arguments.   
    arguments_to_send = current_task->getAction()->getArguments();
  }
  else
  {
    //Behaviors needed to be activated.
    active_behaviors= current_mission->getActiveBehaviors();
    //Next task to perform
    *current_task = current_mission->nextTask();
    //Action's arguments.
    arguments_to_send = current_task->getAction()->getArguments();
  }
  cout << "Trying to perform "<< current_task->getAction()->getReadableName() << "..." << endl;
  //It is important to send first the active behaviors one by one.
  //That is the way the behavior manager expects to receive the needed behaviors.

  for(int i = 0; i<active_behaviors.size(); i++)
  {
    switch(active_behaviors.at(i))
    {    
      case missionSchedulerBehavior::avoidingObstacles:
        behavior_name_to_send = "avoidingObstacles";
        break; 
      case missionSchedulerBehavior::recognizingArucoMarkers:
        behavior_name_to_send = "recognizingArucoMarkers";
        break; 
      case missionSchedulerBehavior::recognizingVisualMarkers:
        behavior_name_to_send = "recognizingVisualMarkers";
        break; 
      case missionSchedulerBehavior::sayingOutLoudCurrentTask:
        behavior_name_to_send = "sayingOutLoudCurrentTask";
        break;         
    }
    //Setting service values.
    srv.request.behavior_name = behavior_name_to_send;
    //By convention, the behavior not specified in the service is understood to be deactivated.
    srv.request.activate = true;
    //Call and wait for response
    if (!behaviorRequestClient.call(srv) || !srv.response.ack){
      cout << "\033[0;31m[ERROR] Behavior " << behavior_name_to_send << " could not be sent. "<< srv.response.why <<"\nAborting mission...\033[0m"<<endl;
      abortMission();
    }
  }
  //Getting action from task.
  switch(current_task->getAction()->getName())
  {
    case missionSchedulerAction::takeOff:
      mpAction_to_send = droneMsgsROS::actionData::TAKE_OFF;
      break;
    case missionSchedulerAction::hover:
      mpAction_to_send = droneMsgsROS::actionData::HOVER;
      break;
    case missionSchedulerAction::land:
      mpAction_to_send = droneMsgsROS::actionData::LAND;
      break;
    case missionSchedulerAction::stabilize:
      mpAction_to_send = droneMsgsROS::actionData::STABILIZE;
      break;
    case missionSchedulerAction::positionMovement:
      mpAction_to_send = droneMsgsROS::actionData::MOVE;
      break;
    case missionSchedulerAction::goToPoint:
      mpAction_to_send = droneMsgsROS::actionData::GO_TO_POINT;
      break;
    case missionSchedulerAction::rotateYaw:
      mpAction_to_send = droneMsgsROS::actionData::ROTATE_YAW;
      break;
    case missionSchedulerAction::flipMovementRight:
      mpAction_to_send = droneMsgsROS::actionData::FLIP_RIGHT;
      break;
    case missionSchedulerAction::flipMovementLeft:
      mpAction_to_send = droneMsgsROS::actionData::FLIP_LEFT;
      break;
    case missionSchedulerAction::flipMovementFront:
      mpAction_to_send = droneMsgsROS::actionData::FLIP_FRONT;
      break;
    case missionSchedulerAction::flipMovementBack:
      mpAction_to_send = droneMsgsROS::actionData::FLIP_BACK;
      break;
    case missionSchedulerAction::rememberPoint:
      mpAction_to_send = -1; //Actions signed with -1 are considered inner actions that does not need to be sent to any other module.
      duo<std::string, std::vector<double>> point_to_remember;
      point_to_remember.key   = arguments_to_send.at(0).key;
      point_to_remember.value = {current_pose.x, current_pose.y, current_pose.z};
      //If the point has been rememebered before, then its value is overwriten.
      if(remembered_points.size() > arguments_to_send.at(0).value.at(0))  
        remembered_points.at(arguments_to_send.at(0).value.at(0)).value = point_to_remember.value;
      else 
        remembered_points.push_back(point_to_remember);
      //Time to inform the user that the current point has been memorized.
      cout << "\033[1;32mMemorizing point (" << point_to_remember.value.at(0) << ", " << point_to_remember.value.at(1)<< ", " << point_to_remember.value.at(2) <<"). \033[0m" << endl;
      break;       
  }
  // There are "special" actions that are not necessary to be sent.
  if(mpAction_to_send >= 0)
  {
    //Setting up the first parameter in the message.
    msg.mpAction = mpAction_to_send;
    //Setting up arguments
    for(int i = 0; i < arguments_to_send.size() ; i++)
    { 
      if(arguments_to_send.at(i).key == NAME_DURATION)
        arg_msg.argumentName = droneMsgsROS::actionArguments::DURATION;
      else if(arguments_to_send.at(i).key == NAME_DESTINATION)
        arg_msg.argumentName = droneMsgsROS::actionArguments::DESTINATION;
      else if(arguments_to_send.at(i).key == NAME_ROTATION)
        arg_msg.argumentName = droneMsgsROS::actionArguments::ROTATION;
      else if(arguments_to_send.at(i).key == NAME_POINT_NAME)
      {
        arguments_to_send.at(i).value = remembered_points.at(arguments_to_send.at(i).value.at(0)).value;
        arg_msg.argumentName = droneMsgsROS::actionArguments::DESTINATION;
      }
      for(int j = 0; j < arguments_to_send.at(i).value.size(); j++)
        arg_msg.value.push_back(arguments_to_send.at(i).value.at(j));

      msg.arguments.push_back(arg_msg);
      arg_msg.value.clear();
    }
    //Send task action and its arguments.
    droneRequestedActionPub.publish(msg);
    ros::spin();
  }
  //The task has been completed, so a new task has to be sent. (This kind of actions are quite special since it is not necessary to publish any message)
  else
  {
    cout << "\033[1;34m--------------- ACTION COMPLETED!---------------\033[0m" << endl;
    sendNewTask();
  }
}

void TaskBasedMissionPlanner::droneApprovedActionCallback(const droneMsgsROS::actionData &msg)
{
  if(!msg.ack){
    cout << "\033[1;31m[ERROR] The action has not been approved.\n Aborting mission...\033[0m"<<endl;
    abortMission();
  }
} 

void TaskBasedMissionPlanner::droneCompletedActionCallback(const droneMsgsROS::actionData &msg)
{
  if(msg.ack)
  {
    cout << "\033[1;34m--------------- ACTION COMPLETED!---------------\033[0m" << endl;
    sendNewTask();
  }
  else
    cout << "\033[1;31m--------------- ACTION FAILED!----------------\033[0m" << endl;
}

void TaskBasedMissionPlanner::droneArucoObservationCallback(const droneMsgsROS::obsVector &msg)
{
  //Checking if an event has to be activated.
  std::vector<droneMsgsROS::Observation3D> aux_vec = msg.obs; 
  if(!aux_vec.empty() && event_handler->checkEvents(aux_vec.at(0).id, PAR_ARUCO_VISUAL_MARKER))
    sendNewTask();
}
void TaskBasedMissionPlanner::droneBatteryCallback(const droneMsgsROS::battery &msg)
{ 
  //Checking if an event has to be activated.
  if(event_handler->checkEvents(msg.batteryPercent, PAR_BATTERY_CHARGE_PERCENTAGE))
    sendNewTask();
}
void TaskBasedMissionPlanner::droneCurrentPoseCallback(const droneMsgsROS::dronePose &msg)
{
  //Saving current position
  current_pose.x = msg.x;
  current_pose.y = msg.y;
  current_pose.z = msg.z;
}

void TaskBasedMissionPlanner::getParametersFromFile()
{
  //Mission's file name.
  std::string aux;
  ros::param::get("~mission_config_file", mission_path);

  ros::param::get("~droneId", aux);
  mission_path = aux+"/"+mission_path;

  ros::param::get("~stackPath", aux);
  mission_path = aux+"/configs/drone"+mission_path;

  /// SUBSCRIBERS ///
  ros::param::get("~drone_Approved_Action_Topic_Name", droneApprovedActionTopicName);
  if ( droneApprovedActionTopicName.length() == 0)
  {
    droneApprovedActionTopicName = "approved_action";
  }
  ros::param::get("~drone_Completed_Action_Topic_Name", droneCompletedActionTopicName);
  if ( droneCompletedActionTopicName.length() == 0)
  {
    droneCompletedActionTopicName = "completed_action";
  }
  ros::param::get("~drone_Aruco_Observation_Topic_Name", droneArucoObservationTopicName);
  if ( droneArucoObservationTopicName.length() == 0)
  {
    droneArucoObservationTopicName = "arucoObservation";
  }
  ros::param::get("~drone_Battery_Topic_Name", droneBatteryTopicName);
  if ( droneBatteryTopicName.length() == 0)
  {
    droneBatteryTopicName = "battery";
  }
  ros::param::get("~drone_Current_Pose_Topic_Name", droneCurrentPoseTopicName);
  if ( droneCurrentPoseTopicName.length() == 0)
  {
    droneCurrentPoseTopicName = "EstimatedPose_droneGMR_wrt_GFF";
  }
  /// PUBLISHERS ///
  ros::param::get("~drone_Requested_Action_Topic_Name", droneRequestedActionTopicName);
  if ( droneRequestedActionTopicName.length() == 0)
  {
    droneRequestedActionTopicName="requested_action";
  }
}
void TaskBasedMissionPlanner::ownOpen()
{
  //Subscribing to topics
  droneApprovedActionSub   = n.subscribe(droneApprovedActionTopicName, 1, &TaskBasedMissionPlanner::droneApprovedActionCallback, this);
  droneCompletedActionSub  = n.subscribe(droneCompletedActionTopicName, 1, &TaskBasedMissionPlanner::droneCompletedActionCallback, this);
  droneArucoObservationSub = n.subscribe(droneArucoObservationTopicName, 1, &TaskBasedMissionPlanner::droneArucoObservationCallback, this);
  droneBatterySub          = n.subscribe(droneBatteryTopicName, 1, &TaskBasedMissionPlanner::droneBatteryCallback, this);
  droneCurrentPoseSub      = n.subscribe(droneCurrentPoseTopicName, 1, &TaskBasedMissionPlanner::droneCurrentPoseCallback, this);
  //Publishing in topics
  droneRequestedActionPub = n.advertise<droneMsgsROS::actionData>(droneRequestedActionTopicName, 1, true);
  //This node will use the service behaviorRequest.
  behaviorRequestClient = n.serviceClient<droneMsgsROS::behaviorRequest>("request_behavior");
  
}
void TaskBasedMissionPlanner::ownRun()
{
  //All is ready to start the mission
  ros::Duration(5).sleep();
  startMission(); 
}
void TaskBasedMissionPlanner::ownRecover()
{

}
