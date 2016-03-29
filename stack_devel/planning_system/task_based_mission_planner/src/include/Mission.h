/*!*****************************************************************************
 *  \file      Mission.h
 *  \brief     Definition of all the classes used in the file
 *             Mission.cpp .
 *   
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/
#ifndef MISSION_H
#define MISSION_H
#include <iostream>
#include <cstdlib>
#include "Parser.h"
/*!***************************************************************************
 *  \class Mission
 *  \brief This class represents an abstraction of what a mission 
 *         is supossed to be.
 *****************************************************************************/
class Mission
{
private:
    Task current_mission_task;
    TreeNode<Task> taskTree;
    Parser * mission_parser;

public:
    //Constructor & Destructor
    Mission(std::string mission_config_file);
    ~Mission();

public:
  /*!************************************************************************
   *  \brief  This method prints the task tree where all mission steps
   *          are stored. 
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/
    int printTree();
  /*!************************************************************************
   *  \brief  This method checks if the main mission has been completed.
   *  \return True if the mission has been completed, false in other case.
   *************************************************************************/
    bool missionCompleted();
  /*!************************************************************************
   *  \brief  This method returns the next task of the mission 
   *  \return An object of the class Task which is the next task 
   *          to be performed.
   *************************************************************************/
    Task nextTask();
  /*!************************************************************************
   *  \brief  This method gets the current active behaviors of the mission.
   *  \return A vector of all the behaviors that are currently activated.
   *************************************************************************/
    std::vector<missionSchedulerBehavior::taskBehaviors> getActiveBehaviors();

private:  
  /*!************************************************************************
   *  \brief  This auxiliar method helps methods nextTask().
   *  \param  tree A TreeNode object in which search the next task to send.
   *  \return A task object.
   *  \see    nextTask().
   *************************************************************************/
    Task nextTaskAux(TreeNode<Task> &tree);
  /*!************************************************************************
   *  \brief  This auxiliar method helps function nextTask().
   *  \param  tree A TreeNode object in which search the next task to send.
   *  \return A task object.
   *  \see    nextTask().
   *************************************************************************/
    std::string printTreeAux(TreeNode<Task> tree, std::string message, std::string acc);
      /*!************************************************************************
   *  \brief  This auxiliar method helps function getActiveBehaviors().
   *  \param  tree TreeNode object where the mission is stored.
   *  \return A vector of active behaviors.
   *  \see    getActiveBehaviors()
   *************************************************************************/
    std::vector<missionSchedulerBehavior::taskBehaviors> getActiveBehaviorsAux(TreeNode<Task> tree);   
};
#endif