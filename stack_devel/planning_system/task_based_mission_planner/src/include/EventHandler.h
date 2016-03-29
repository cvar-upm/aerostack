/*!*****************************************************************************
 *  \file      EventHandler.h
 *  \brief     Definition of all the classes used in the file
 *             EventHandler.cpp .
 *   
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
 
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Task.h"
#include "Event.h"
#include "Parser.h"
/*!***************************************************************************
 *  \class EventHandler
 *  \brief This class is supossed to be able to support all the events that 
 *         may occur during the execution.
 *****************************************************************************/
class EventHandler
{
private:
  bool active_event;
  std::vector<Event> event_vector;
  Event  * activated_event;
  Parser * event_handler_parser;

public:
  //Constructor & Destructor
  EventHandler(std::string mission_config_file);
  ~EventHandler();

public:
  /*!************************************************************************
   *  \brief  This method prints the event vector. 
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/
  int printEventVector();
  /*!************************************************************************
   *  \brief  This method checks if an event has been activated.
   *  \param  id Value to be compared.
   *  \param  parameter_name Conditions'parameter.
   *  \return True if an event has been activated.
   *************************************************************************/
  bool checkEvents(double parameter_value, std::string parameter_name);
  /*!************************************************************************
   *  \brief  This method pass the next task of the current event through the
   *          given argument,
   *  \param  next_task Variable where the next task is going to be stored.
   *  \return True if the next task exist, false in other case.
   *************************************************************************/
  bool nextTask(Task *next_task);
  /*!************************************************************************
   *  \brief  This method returns if an event is currently activated.
   *  \return True if an event is activated.
   *************************************************************************/
  bool activeEvent();
 /*!************************************************************************
  *  \brief  Reset the event handler's attributes to its default values.
  *************************************************************************/
  void resetEventHandler();
  /*!************************************************************************
   *  \brief  This method returns the ending step of the current event.
   *  \return The ending step.
   *************************************************************************/  
  missionSchedulerEndingStep::endingStep  getCurrentEventEndingStep();
};
#endif