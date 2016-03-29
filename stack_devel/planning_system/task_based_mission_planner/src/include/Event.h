/*!*****************************************************************************
 *  \file      Event.h
 *  \brief     Definition of all the classes used in the file
 *             Event.cpp .
 *   
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/
#ifndef EVENT_H
#define EVENT_H
 
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Condition.h"
#include "Action.h"

/*!***************************************************************************
 *  \class Event
 *  \brief This class represents an abstraction of what a Event 
 *         is supossed to have and represent.
 *****************************************************************************/
class Event{
private:
    std::vector<Condition> conditions;
    std::vector<Action> actions;
    std::vector<Action> remaining_actions;
    std::string description;
    missionSchedulerEndingStep::endingStep ending_step;

public:
    //Constructor & Destructor
    Event(std::string eventDescription, std::vector<Condition> eventConditions, std::vector<Action> eventActions, missionSchedulerEndingStep::endingStep event_ending_step);
    ~Event();
  /*!************************************************************************
   *  \brief  Checks whether the event has been activated.
   *  \return True if the event has been activated, False in other case.
   *************************************************************************/
    bool isEventActivated();
  /*!************************************************************************
   *  \brief  Event's description is returned.
   *  \return A String with the event's description
   *************************************************************************/
    std::string getDescription();
  /*!************************************************************************
   *  \brief  Event's actions.
   *  \return Pointer to a vector of actions.
   *************************************************************************/
    std::vector<Action> * getActions();
  /*!************************************************************************
   *  \brief  Remaining actions to perform.
   *  \return Pointer to a vector of actions.
   *************************************************************************/
    std::vector<Action> * getRemainingActions();
  /*!************************************************************************
   *  \brief  Final step to perform is returned.
   *  \return A singular ending action.
   *************************************************************************/
    missionSchedulerEndingStep::endingStep getEndingStep();
  /*!************************************************************************
   *  \brief  Conditions that must be true in order to start an event are
   *          returned. 
   *  \return Pointer to a vector of conditions.
   *************************************************************************/
    std::vector<Condition> * getConditions();

    void resetEvent();
};
#endif