/*!*****************************************************************************
 *  \file    Task.h
 *  \brief   Definition of all the classes used in the file
 *           Task.cpp .
 *   
 *  \author  Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *       Released under license BSD-3.
 ********************************************************************************/
#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Action.h"
#include "Condition.h"

/*!***************************************************************************
 *  \class Task
 *  \brief This class represents an abstraction of a Task.
 *****************************************************************************/
class Task
{
private:
  std::string description;
  Action * task_action; //A task must have always one action. If the action is not specified, then the action is unknown.
  std::vector<missionSchedulerBehavior::taskBehaviors> behaviors;//A task may have several behaviors activated.
  std::vector<Condition> conditions;// NOT IMPLEMENTED YET

public:
  /*!************************************************************************
   *  \brief  This method sets the task's description from a given value. 
   *  \param  task_description Task's description.
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/  
  int setDescription(std::string task_description);
  /*!************************************************************************
   *  \brief  This method sets the task's action from a given value. 
   *  \param  task_action Task's action.
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/ 
  int setAction(Action task_action);
 /*!************************************************************************
   *  \brief  This method sets the task's behaviors from a given value. 
   *  \param  task_behaviors Task's behaviors.
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/ 
  int setBehaviors(std::vector<missionSchedulerBehavior::taskBehaviors> task_behaviors);
  /*!************************************************************************
   *  \brief  This method sets the task's conditions from a given value. 
   *  \param  task_conditions Task's conditions.
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/ 
  int setConditions(std::vector<Condition> task_conditions);
  /*!************************************************************************
   *  \brief  This method gets the task's description. 
   *  \return The task's description.
   *************************************************************************/ 
  std::string getDescription();
  /*!************************************************************************
   *  \brief  This method gets the task's action. 
   *  \return The task's action.
   *************************************************************************/ 
  Action * getAction();
  /*!************************************************************************
   *  \brief  This method gets the task's behaviors. 
   *  \return The task's description.
   *************************************************************************/ 
  std::vector<missionSchedulerBehavior::taskBehaviors> * getBehaviors();
  /*!************************************************************************
   *  \brief  This method gets the task's conditions. 
   *  \return A pointer to a vector of task's conditions.
   *************************************************************************/ 
  std::vector <Condition> * getConditions();

public:
  Task();  // Class constructor
  ~Task();   // Class destructor
};
#endif