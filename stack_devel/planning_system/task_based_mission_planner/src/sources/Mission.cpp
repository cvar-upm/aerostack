#include <stdio.h>
#include <iostream>
#include "Mission.h"

using namespace std;

Mission::Mission(std::string mission_config_file){
  //Starting parser.
  mission_parser = new Parser(mission_config_file);
  //Obtaining generated task tree from parsing.
  taskTree = mission_parser->generateTaskTree();
}
Mission::~Mission(){
  //Deallocate used memory.
  //TO DO
}

bool Mission::missionCompleted()
{
  return taskTree.getChildren()->empty();
}

std::vector<missionSchedulerBehavior::taskBehaviors> Mission::getActiveBehaviors()
{
  return getActiveBehaviorsAux(taskTree);
}

std::vector<missionSchedulerBehavior::taskBehaviors> Mission::getActiveBehaviorsAux(TreeNode<Task> tree)
{ 
  //Variable declaration
  std::vector<missionSchedulerBehavior::taskBehaviors> toReturn;
  std::vector<missionSchedulerBehavior::taskBehaviors> auxVector;
  std::vector<missionSchedulerBehavior::taskBehaviors> activeBehaviors = *(tree.getNode()->getBehaviors());
 
  if(!tree.getChildren()->empty())
    auxVector = getActiveBehaviorsAux(tree.getChildren()->at(0));

  //Preallocate memory
  toReturn.reserve( activeBehaviors.size() + auxVector.size() ); 
  //Concatenate  
  toReturn.insert( toReturn.end(), activeBehaviors.begin(), activeBehaviors.end() );
  toReturn.insert( toReturn.end(), auxVector.begin(), auxVector.end() );
  
  return toReturn;
}

Task Mission::nextTask(){
  return nextTaskAux(taskTree);
}

Task Mission::nextTaskAux(TreeNode<Task> &tree){
  std::vector <TreeNode<Task> > *child = tree.getChildren();
  Task taskToReturn;
  for(std::vector<TreeNode<Task> >::iterator iter = child->begin(); !child->empty() && iter != child->end(); ++iter){
    if(iter->getChildren()->empty() && !iter->getNode()->getAction()->isEmpty()){
      taskToReturn = *(iter->getNode());
      iter = child->erase(iter);
    }
    else if(!iter->getChildren()->empty()) taskToReturn = Mission::nextTaskAux(*iter);
    if(iter->getChildren()->empty() && iter->getNode()->getAction()->isEmpty()) child->erase(iter);
    return taskToReturn;    
  }
}

int Mission::printTree(){
  std::string message ="";//Message to display.
  std::string acc   ="";//Just to make the print readable, it is a tab accumulator.
  cout << "--------------------TASK TREE--------------------" << endl;
  cout << Mission::printTreeAux(taskTree, message, acc); 
  return 0;
}

std::string Mission::printTreeAux(TreeNode<Task> taskTree, std::string message, std::string acc){
  Task *current_task = taskTree.getNode();
  std::vector <TreeNode<Task> > *child= taskTree.getChildren();
  std::vector <missionSchedulerBehavior::taskBehaviors> *behaviors = current_task->getBehaviors();
  std::vector <Condition> *conditions = current_task->getConditions();

  //Printing task attributes
  message = message +  acc + "\033[1;34mTask: " + current_task->getDescription() + "\033[0m\n";

  if(!conditions->empty()){
    for(int j =0; j < conditions->size(); j++) 
      message = message + acc +"\t Condition: " + conditions-> at(j).getConditionExpresion() + "\n"; 
  }   
  if(!behaviors->empty()){
    for(int j=0; j< behaviors->size(); j++)
      message = message + acc + "\t Behavior: " + std::to_string(behaviors->at(j)) + "\n";
  }
  if(!current_task->getAction()->isEmpty())
    message = message+ acc + "\t Action: " + current_task->getAction()->getReadableName() + "\n";

  //For every child of the current task, repeat the action.
  acc = acc + "\t";
  if(!child -> empty()){
    for(int i=0; i < child->size(); i++){ 
      message = Mission::printTreeAux(child->at(i), message, acc); 
    }
  }
  return message;         
 }

