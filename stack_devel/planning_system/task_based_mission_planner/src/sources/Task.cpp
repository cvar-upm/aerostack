#include <stdio.h>
#include <iostream>
#include "Task.h"

Task::Task(){
  description    = "Default description";
  task_action    = new Action(missionSchedulerAction::unknown);
}

Task::~Task(){
  //TO DO
}

int Task::setBehaviors(std::vector<missionSchedulerBehavior::taskBehaviors> task_behaviors)
{
  behaviors = task_behaviors;
  return 0;
}
int Task::setDescription(std::string task_description)
{
  description = task_description;
  return 0;
}
int Task::setAction(Action action_to_set)
{
  *task_action = action_to_set;
  return 0;
}
int Task::setConditions(std::vector<Condition> task_conditions)
{
  conditions = task_conditions;
  return 0;
}

Action * Task::getAction(){
  Action * action_to_return = task_action; 
  return action_to_return;
}

std::string Task::getDescription(){
  return description;
}
std::vector<missionSchedulerBehavior::taskBehaviors> * Task::getBehaviors(){
  std::vector<missionSchedulerBehavior::taskBehaviors>* behavior_vector = &behaviors;
  return behavior_vector;
}
std::vector<Condition> * Task::getConditions(){
  std::vector<Condition> * condition_vector = &conditions;
  return condition_vector;
}
