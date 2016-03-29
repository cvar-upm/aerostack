#ifndef PARSER_H
#define PARSER_H
 
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "pugixml.hpp"

#include "ErrorHandler.h"
#include "Event.h"
#include "TreeNode.h"
#include "Task.h"

class Parser
{
private:
	pugi::xml_document mission_specification_file;
	ErrorHandler parser_error_handler;
  // In order to know what variables can be used, it is necessary to 
  // store each declared variable in the vector below.
  std::vector<std::string> declared_variables;

public:
	//Constructor & Destructor
	Parser(std::string mission_config_file);
	~Parser();
public:
  /*!************************************************************************
   *  \brief  This method generates the task tree where all mission steps
   *          are going to be stored. 
   *  \return Generated task tree.
   *************************************************************************/
  TreeNode<Task> generateTaskTree();

  /*!************************************************************************
   *  \brief  This method generates the event vector where all mission events
   *          are going to be stored. 
   *  \return Generated event vector.
   *************************************************************************/
  std::vector<Event> generateEventVector();  

private:
	//Auxiliar methods
  /*!************************************************************************
   *  \brief  This method read and set a new task in the mission's tree.
   *  \param  taskRead Task's data obtained from the xml file.
   *  \param  taskInTree Pointer to a certain task of the mission's tree.
   *  \return 0 if finished without errors, !=0 in other case.
   *************************************************************************/
    void readAndSetTaskParameters(const pugi::xml_node nodeRead, Task *taskInTree);
   /*!************************************************************************
   *  \brief  This method translates a read value into an action command. 
   *  \param  readingValue String to be recognized or translated.
   *  \return An action command is returned.
   *************************************************************************/
    missionSchedulerAction::taskActions recognizeAction(std::string readingValue);
  /*!************************************************************************
   *  \brief  This method translates a read value into a behavior command. 
   *  \param  readingValue String to be recognized or translated.
   *  \return A behavior command is returned.
   *************************************************************************/
    missionSchedulerBehavior::taskBehaviors recognizeBehavior(std::string readingValue);
  /*!************************************************************************
   *  \brief  This method translates a read value into an action command. 
   *  \param  readingValue String to be recognized or translated.
   *  \return An action command is returned.
   *************************************************************************/
  missionSchedulerEndingStep::endingStep recognizeEndingStep(std::string readingValue);
  /*!************************************************************************
   *  \brief  This auxiliar method helps function generateTaskTree().
   *  \param  curent_task Current task's data obtained from the xml file.
   *  \param  tree TreeNode object in which current_task information is 
   *          going to be stored.
   *  \return A TreeNode object in which the information read from the xml
   *          file has been stored.
   *  \see    generateTaskTree()
   *************************************************************************/
    TreeNode<Task> generateTaskTreeAux(pugi::xml_node current_task, TreeNode<Task> tree); 
};
#endif