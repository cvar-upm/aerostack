#include <stdio.h>
#include <iostream>
#include "EventHandler.h"

using namespace std;

EventHandler::EventHandler(std::string mission_config_file)
{
  //Default attribute values
  active_event = false;
  //Starting parser.
  event_handler_parser = new Parser(mission_config_file);
  //Generating event vector
	event_vector = event_handler_parser->generateEventVector();
}

EventHandler::~EventHandler()
{
	//TO DO
}

int EventHandler::printEventVector()
{
  cout << "----------------------EVENTS---------------------" << endl;
  //Print event vector.
  for (int i = 0; i<event_vector.size(); i++){
    cout << "\033[1;34mEvent: " << event_vector[i].getDescription() << "\033[0m" << endl;
    std::vector<Action> * actions_vector = event_vector[i].getActions();
    std::vector<Condition> * conditions_vector = event_vector[i].getConditions();
    for(int j =0; j < conditions_vector->size(); j++) 
      cout << "\tCondition: " << conditions_vector-> at(j).getConditionExpresion() << endl;    
    for(int j = 0; j < actions_vector->size(); j++)
      cout << "\tAction: " << actions_vector->at(j).getReadableName() << endl;

    cout << "\tEnding step: " << event_vector[i].getEndingStep() << endl;
  }
  cout << "------------------------END----------------------" << endl;
}

bool EventHandler::checkEvents(double parameter_value, std::string parameter_name)
{
  std::vector<Condition> * event_conditions;
  //If an event is being executed, the new event have to wait.
  if(!active_event){
    for(int i=0; i<event_vector.size() && !active_event; i++)
    {
      //Obtaining conditions
      event_conditions = event_vector.at(i).getConditions();
      //Cheking event conditions

      for(int j=0; j<event_conditions->size(); j++)
        if(event_conditions->at(j).isParameterEqualTo(parameter_name)) event_conditions->at(j).evaluateCondition(parameter_value);

      // IMPORTANT: Notice that the first event to be evaluated is the one which is going to be executed. As a consequence,
      // the closer the position of an event is to the first, the highest priority it will have.
      // If an event has been activated, then return and execute its actions, in other case just continue.   
      active_event = event_vector.at(i).isEventActivated();
      //Remember which event has been activated
      activated_event = &event_vector.at(i);       
    }
    if(active_event)  
        cout << "--------------------EVENT ACTIVATED-------------------" << endl;
      return active_event; 
  }
  else
  {
    return !active_event;
  }    
}

bool EventHandler::activeEvent()
{
  return active_event;
}

bool EventHandler::nextTask(Task *next_task)
{
  std::vector<Action> * remaining_actions;
  //First, it is necessary to get the action to perform from the remaining ones.
  remaining_actions = activated_event->getRemainingActions();
  if(!remaining_actions->empty())
  {
    Action event_action_to_perform = *remaining_actions->erase(remaining_actions->begin());
    //Arguments are not implemented yet just like behaviors.
    next_task->setAction(event_action_to_perform);
    next_task->setDescription(activated_event->getDescription());
    return true;
  }
  else
    return false;
  
}

missionSchedulerEndingStep::endingStep  EventHandler::getCurrentEventEndingStep()
{
  return activated_event->getEndingStep();
}

void EventHandler::resetEventHandler()
{
  //Reseting event
  active_event = false;
  activated_event -> resetEvent();
  cout << "--------------------EVENT FINISHED-------------------" << endl;
}