#include <stdio.h>
#include <iostream>
#include "Parser.h"

using namespace std;

Parser::Parser(std::string mission_config_file)
{
  //Reading and loading file. 
  std::ifstream nameFile(mission_config_file.c_str());
  pugi::xml_parse_result result = mission_specification_file.load(nameFile);
  //Parsing errors
  parser_error_handler.checkParsingErrors(result, mission_config_file);
}

TreeNode<Task> Parser::generateTaskTree(){
  //Data structure where the task tree is going to be stored.
  TreeNode<Task> taskTree;
  pugi::xml_node current_task = mission_specification_file.first_child();
  //The first tag expected is the tag "mission".
  if(string(current_task.name())!= "mission")
    parser_error_handler.errorFound("Unexpected tag \"" + string(current_task.name()) + "\".The mission declararion is expected to be  <mission name=\"mission_name\">  " );
  if(string(current_task.first_attribute().name()) != "name")
    parser_error_handler.errorFound("Unexpected attribute \"" + string(current_task.first_attribute().name()) + "\".The mission declararion is expected to be <mission name=\"mission_name\">. " );
  if(current_task.first_attribute().next_attribute())
    parser_error_handler.errorFound("Too many attributes detected for mission tag. The mission declararion is expected to be <mission name=\"mission_name\">. " );

  taskTree = generateTaskTreeAux(current_task, taskTree);
  parser_error_handler.displayErrorsAndWarnings();
  return taskTree;
}

TreeNode<Task> Parser::generateTaskTreeAux(pugi::xml_node current_task, TreeNode<Task> tree)
{
  //Variable declaration.
  Task task_tree;
  std::vector<TreeNode<Task> > children;
  // For every child, a new sub-tree is generated recursively.
  for(pugi::xml_node child = current_task.first_child(); child; child = child.next_sibling())
  {
    if(string(child.name()) == "task")
    {
      TreeNode<Task> child_tree;
      child_tree = generateTaskTreeAux(child, child_tree);
      children.push_back(child_tree);
      //Tags different from "task and "event_handling are not allowed by definition"
      if(child.next_sibling() && string(child.next_sibling().name()) != "task" && string(child.next_sibling().name()) != "event_handling")
          parser_error_handler.errorFound("Unexpected tag \"" + string(child.next_sibling().name()) + "\".The task declararion is expected to be <task name=\"task_name\">. " );
    }
  }
  //Finally, task parameters have to be read  and set in the tree.
  readAndSetTaskParameters(current_task, tree.getNode());
  //Children have to be set as well.
  tree.setChildren(children);
  //Checking syntax errors.
  if(tree.getChildren()->empty() && tree.getNode()->getAction()->isEmpty())
    parser_error_handler.errorFound("Action required in task \"" + tree.getNode()->getDescription() + "\".");

  return tree;
}

void Parser::readAndSetTaskParameters(const pugi::xml_node taskRead, Task *taskInTree){
  //Read parameters
  std::string readingValue;
  //Vector where the behaviors of the task are going to be stored
  std::vector<missionSchedulerBehavior::taskBehaviors> task_behaviors;
  //Variable in which the messages refering to semantic errors are going to be stored.
  std::string semantic_errors;
  //Action that is going to be read.
  Action *task_action = new Action(missionSchedulerAction::unknown);
  //Action argument data structure.
  duo <std::string, std::string> action_argument;
  //Description reading.
  std::string task_description;
  if(string(taskRead.first_attribute().name()) == "name")
    task_description  = taskRead.first_attribute().value();
  else
    parser_error_handler.errorFound("Unexpected attribute \"" + string(taskRead.first_attribute().name()) + "\". The declaration of a task is expected to be <task name=\"task_name\"/>" );

  for(pugi::xml_node child = taskRead.first_child(); child && string(child.name())!= "task" && string(child.name())!= "event_handler"; child = child.next_sibling())
  {
    //First, it is mandatory to read the behaviors that need to be activated if any.
    if(string(child.name())=="behavior")
    {
      if(string(child.first_attribute().name()) == "name")
        task_behaviors.push_back(recognizeBehavior(child.first_attribute().value()));       
      else
        parser_error_handler.errorFound("Unexpected attribute \"" + string(child.first_attribute().name()) + "\".The declararion of a behavior is expected to be <behavior name=\"behavior_name\"/>. " );     
      if(child.first_attribute().next_attribute())
         parser_error_handler.errorFound("Too many attributes detected for behavior tag. The declaration of a behavior is expected to be <behavior name=\"behavior_name\"/>. " );
    }
    //Second, the action of the current task has to be read and recognized if any.
    else if(string(child.name())=="action")
    {
      //By definition, a mother task (an intern node in the tree) cannot have an action defined.  
      if(taskRead.child("task"))
        parser_error_handler.errorFound( "A mother task cannot have an action within. Task with description \""+ task_description + "\" has the ilegal action \"" + readingValue + "\".");
      if(string(child.first_attribute().name()) == "name" && task_action->isEmpty())
      {
        task_action = new Action(recognizeAction(child.first_attribute().value()));
        //Once the action has been recognized, the arguments must be found as well.
        for(pugi::xml_node argument = child.first_child(); argument; argument = argument.next_sibling())
        {
          if(string(argument.name())=="argument")
          {
            if(string(argument.first_attribute().name()) == "name")
            {
              if(string(argument.first_attribute().next_attribute().name()) == "value")
              {
                //Setting up the arguments
                action_argument.key = argument.first_attribute().value();
                action_argument.value = argument.first_attribute().next_attribute().value();
                //If the argument cannot be set up, then it means that the number of arguments is incorrect.
                if(!task_action->setArgument(action_argument))
                  parser_error_handler.errorFound("Too many arguments for action \"" + task_action->getReadableName() + "\" within the task \"" + task_description +"\"" );
                //If there are more attributes, an error has been found.
                if(argument.first_attribute().next_attribute().next_attribute())
                  parser_error_handler.errorFound("Too many attributes detected for argument tag. The declaration of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );              
              }
              else
                parser_error_handler.errorFound("Unexpected attribute \"" + string(argument.first_attribute().next_attribute().name()) + "\".The declararion of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );
            }
            else
              parser_error_handler.errorFound("Unexpected attribute \"" + string(argument.first_attribute().name()) + "\".The declararion of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );     
          }
          else 
            parser_error_handler.errorFound("Unexpected tag \"" + string(argument.name()) + "\" within the task \"" + task_description + "\". The declararion of an argument is expected to be  <argument name=\"action_name\" value=\"argument_value\">. " );
        }
        //Finally it is mandatory to check the semantic properties of the read action
        if(!task_action->checkActionSemanticErrors(semantic_errors, declared_variables))
          parser_error_handler.errorFound(semantic_errors);
      }
      else if(!task_action->isEmpty())
        parser_error_handler.errorFound("Unexpected action \"" + string(child.first_attribute().value()) + "\" within the task \"" + task_description + "\". A task can only have one action. " );     
      else
        parser_error_handler.errorFound("Unexpected attribute \"" + string(child.first_attribute().name()) + "\".The declararion of an action is expected to be <action name=\"action_name\"/>. " );     
      if(child.first_attribute().next_attribute())
         parser_error_handler.errorFound("Too many attributes detected for behavior tag. The declaration of a behavior is expected to be <behavior name=\"behavior_name\">. " );
    }
    else
      parser_error_handler.errorFound("Unexpected tag \"" + string(child.name()) + "\" within the task \"" + task_description + "\". The declararion of an action is expected to be  <action name=\"action_name\">. " );
  }

  //Setting task attributes.
  taskInTree->setDescription(task_description);
  taskInTree->setAction(*task_action);
  taskInTree->setBehaviors(task_behaviors);
}

std::vector<Event> Parser::generateEventVector(){

  pugi::xml_node event_handling_node = mission_specification_file.first_child();

  duo<std::string,std::string> action_argument;
  std::vector<Event> event_vector;
  std::vector<Condition> event_conditions;
  std::vector<Action> event_actions;
  std::string event_description;
  std::string event_ending_step;
  std::string semantic_errors;

  Action *event_action = new Action(missionSchedulerAction::unknown);
  
  if(string(event_handling_node.name())!= "mission")
    parser_error_handler.errorFound("Unexpected tag \"" + string(event_handling_node.name()) + "\".The mission declararion is expected to be  <mission name=\"mission_name\">  " );
  if(string(event_handling_node.first_attribute().name()) != "name")
    parser_error_handler.errorFound("Unexpected attribute \"" + string(event_handling_node.first_attribute().name()) + "\".The mission declararion is expected to be <mission name=\"mission_name\">. " );
  if(event_handling_node.first_attribute().next_attribute())
    parser_error_handler.errorFound("Too many attributes detected for mission tag. The mission declararion is expected to be <mission name=\"mission_name\">. " );

  
  for(event_handling_node = event_handling_node.first_child(); event_handling_node; event_handling_node = event_handling_node.next_sibling())
  {
    if(string(event_handling_node.name()) != "task" && string(event_handling_node.name()) != "event_handling")
      parser_error_handler.errorFound("Unexpected tag \"" + string(event_handling_node.name()) + "\".The task declararion is expected to be  <task name=\"task_name\">. " );
    else if( string(event_handling_node.name()) == "event_handling")
    {
      for(pugi::xml_node event = event_handling_node.first_child(); event; event = event.next_sibling())
      {
        if(string(event.name())== "event")
        {
          if(string(event.first_attribute().name())=="name")
          { 
            if(event.first_attribute().next_attribute())
              parser_error_handler.errorFound("Too many attributes detected for event tag. The declaration of an event is expected to be <event name=\"event_name\">. " );
            //Event Description.
            event_description = event.first_attribute().value();
            //Time to read the conditions of the event.
            for(pugi::xml_node child = event.first_child(); child; child = child.next_sibling())
            {
              if(string(child.name())=="condition")
              {
                if(string(child.first_attribute().name()) == "parameter" && string(child.first_attribute().next_attribute().name()) == "comparison" && string(child.first_attribute().next_attribute().next_attribute().name()) == "value" && !child.first_attribute().next_attribute().next_attribute().next_attribute())
                {
                  Condition condition(child.attribute("parameter").value(), child.attribute("comparison").value(), child.attribute("value").value());
                  event_conditions.push_back(condition);
                }
                else
                  parser_error_handler.errorFound("Syntax error in condition statement. The declaration of a condition is expected to be  <condition parameter=\"parameter_name\" comparison=\"expression\" value=\"condition_value\">. " );             
              }                      
              else if(string(child.name())=="action")
              {
               if(string(child.first_attribute().name()) == "name" )
                {
                  event_action = new Action(recognizeAction(child.first_attribute().value()));
                  //Once the action has been recognized, the arguments must be found as well.
                  for(pugi::xml_node argument = child.first_child(); argument; argument = argument.next_sibling())
                  {
                    if(string(argument.name())=="argument")
                    {
                      if(string(argument.first_attribute().name()) == "name")
                      {
                        if(string(argument.first_attribute().next_attribute().name()) == "value")
                        {   
                          //Setting up the arguments
                          action_argument.key   = argument.first_attribute().value();
                          action_argument.value = argument.first_attribute().next_attribute().value();
                          //If the argument cannot be set up, then it means that the number of arguments is incorrect.
                          if(!event_action->setArgument(action_argument))
                            parser_error_handler.errorFound("Too many arguments for action \"" + event_action->getReadableName() + "\" within the event \"" + event_description + "\". " );
                          //If there are more attributes, an error has been found.
                          if(argument.first_attribute().next_attribute().next_attribute())
                            parser_error_handler.errorFound("Too many attributes detected for argument tag. The declaration of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );              
                        }
                        else
                          parser_error_handler.errorFound("Unexpected attribute \"" + string(argument.first_attribute().next_attribute().name()) + "\".The declararion of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );
                      }
                      else
                        parser_error_handler.errorFound("Unexpected attribute \"" + string(argument.first_attribute().name()) + "\".The declararion of an argument is expected to be <argument name=\"argument_name\" value=\"argument_value\"/>. " );     
                    }
                    else 
                      parser_error_handler.errorFound("Unexpected tag \"" + string(argument.name()) + "\" within the event \"" + event_description + "\". The declararion of an argument is expected to be  <argument name=\"argument_name\" value=\"argument_value\">. " );
                  }
                  //Finally it is mandatory to check the semantic properties of the read action
                  if(!event_action->checkActionSemanticErrors(semantic_errors, declared_variables))
                    parser_error_handler.errorFound(semantic_errors);
                  event_actions.push_back(*event_action);
                }
                else if(!event_action->isEmpty())
                  parser_error_handler.errorFound("Unexpected action \"" + string(child.first_attribute().value()) + "\" within the event \"" + event_description + "\" .A task can only have one action. " );     
                else
                  parser_error_handler.errorFound("Unexpected attribute \"" + string(child.first_attribute().name()) + "\".The declararion of an action is expected to be <action name=\"action_name\"/>. " );     
                if(child.first_attribute().next_attribute())
                  parser_error_handler.errorFound("Too many attributes detected for behavior tag. The declaration of a behavior is expected to be <behavior name=\"behavior_name\">. " );
              }
              else if(string(child.name())=="ending")
              {
                if(string(child.first_attribute().name())=="step")
                {
                  event_ending_step = event.child("ending").attribute("step").value();
                  Event event_read(event_description, event_conditions, event_actions, recognizeEndingStep(event_ending_step));
                  event_vector.push_back(event_read);
                }
                else
                  parser_error_handler.errorFound("Unexpected attribute \"" + string(child.first_attribute().name()) + "\".The declaration of an ending step is expected to be <ending step=\"ending_step_name\">. " );
              }
              else
                parser_error_handler.errorFound("Unexpected tag \"" + string(child.name()) + "\" within the event \"" + event_description + "\".The declararion of an action is expected to be  <action name=\"action_name\"/>. " );
            }
          }
        }
        else
          parser_error_handler.errorFound("Unexpected tag \"" + string(event.name()) + "\" within the event \"" + event_description + "\".The declaration of an event is expected to be  <event name=\"event_name\">. " );
      }
    }
  }
  parser_error_handler.displayErrorsAndWarnings();
  return event_vector;
}

missionSchedulerAction::taskActions Parser::recognizeAction(std::string readingValue){

  missionSchedulerAction::taskActions task_action;

  if (readingValue==CMD_TAKEOFF)
  {
    task_action = missionSchedulerAction::takeOff;
  }
  else if(readingValue==CMD_HOVER)
  {
    task_action = missionSchedulerAction::hover;
  }
  else if(readingValue==CMD_LAND)
  {
    task_action = missionSchedulerAction::land;
  }
  else if(readingValue==CMD_MOVEMENT_POSITION)
  {
    task_action = missionSchedulerAction::positionMovement;
  }
  else if(readingValue==CMD_GO_TO_POINT)
  {
    task_action = missionSchedulerAction::goToPoint;
  }
  else if(readingValue==CMD_ROTATE_YAW)
  {
    task_action = missionSchedulerAction::rotateYaw;
  }
  else if(readingValue==CMD_FLIP_FRONT)
  {
    task_action = missionSchedulerAction::flipMovementFront;
  }
  else if(readingValue==CMD_FLIP_BACK)
  {
    task_action = missionSchedulerAction::flipMovementBack;
  }
  else if(readingValue==CMD_FLIP_RIGHT)
  {
    task_action = missionSchedulerAction::flipMovementRight;
  }
  else if(readingValue==CMD_FLIP_LEFT)
  {
    task_action = missionSchedulerAction::flipMovementLeft;
  }
  else if(readingValue==CMD_STABILIZE)
  {
    task_action = missionSchedulerAction::stabilize;
  }
  else if(readingValue==CMD_REMEMBER_POINT)
  {
    task_action = missionSchedulerAction::rememberPoint;
  }
  else
  {
    //Checking invalid action
    if(readingValue!="")
      parser_error_handler.errorFound("Unknown action \"" + readingValue + "\"");
    
  }
  return task_action;
}

missionSchedulerBehavior::taskBehaviors Parser::recognizeBehavior(std::string readingValue){

  missionSchedulerBehavior::taskBehaviors task_behavior;

  if(readingValue==BHV_AVOIDING_OBSTACLES)
  {
    task_behavior=missionSchedulerBehavior::avoidingObstacles;
  }
  else if(readingValue==BHV_RECOGNIZING_ARUCO_MARKERS)
  {
    task_behavior=missionSchedulerBehavior::recognizingArucoMarkers;
  }
  else if(readingValue==BHV_RECOGNIZING_VISUAL_MARKERS)
  {
    task_behavior=missionSchedulerBehavior::recognizingVisualMarkers;
  }
  else if(readingValue==BHV_SAYING_OUT_LOUD_CURRENT_TASK)
  {
    task_behavior=missionSchedulerBehavior::sayingOutLoudCurrentTask;
  }
  else
  {
    if(readingValue!="")
      parser_error_handler.errorFound("Unknown behavior \"" + readingValue + "\".");
  }

  return task_behavior;
}

missionSchedulerEndingStep::endingStep Parser::recognizeEndingStep(std::string readingValue)
{
  missionSchedulerEndingStep::endingStep ending_step;
  if (readingValue==END_NEXT_TASK)
  {
    ending_step = missionSchedulerEndingStep::nextTask;;
  }
  else if(readingValue==END_REPEAT_TASK)
  {
    ending_step = missionSchedulerEndingStep::repeatTask;
  }
  else if(readingValue==END_ABORT_MISSION)
  {
    ending_step = missionSchedulerEndingStep::abortMission;
  }
  else
  {
   parser_error_handler.errorFound("Unknown ending step \"" + readingValue + "\"."); 
  }
  return ending_step;
}