#include <stdio.h>
#include <iostream>
#include "Event.h"

using namespace std;

Event::Event(std::string eventDescription, std::vector<Condition> eventConditions, std::vector<Action> eventActions, missionSchedulerEndingStep::endingStep event_ending_step){
    //Intialize attributes.
    description       = eventDescription;
    conditions        = eventConditions;
    actions           = eventActions;
    remaining_actions = eventActions;
    ending_step       = event_ending_step;
}

Event::~Event(){
    //TO DO
    //Deallocate used memory.
}
bool Event::isEventActivated()
{
    bool activated = true;
    for(int i=0; i<conditions.size(); i++)
       activated = conditions.at(i).getConditionValue() && activated; 
    return activated;
}
std::string Event::getDescription(){
    return description;
}
std::vector<Action> * Event::getActions(){
    std::vector<Action> * actions_vector = &actions;
    return actions_vector;
}

std::vector<Action> * Event::getRemainingActions(){
    std::vector<Action> * actions_vector = &remaining_actions;
    return actions_vector;
}

missionSchedulerEndingStep::endingStep Event::getEndingStep(){
    return ending_step;
}

std::vector<Condition>* Event::getConditions(){
    std::vector<Condition>* conditions_vector = &conditions;
    return conditions_vector;
}
void Event::resetEvent()
{
    remaining_actions = actions;
    for (int i =0; i<conditions.size(); i++)
      conditions.at(i).resetConditionEvaluation();
}