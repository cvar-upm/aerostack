#include <stdio.h>
#include <iostream>
#include "Action.h"
#include <boost/regex.hpp>

using namespace std;

Action::Action(missionSchedulerAction::taskActions name)
{
	action_name = name;
	number_of_arguments  = 0;

	switch (action_name)
	{
		case missionSchedulerAction::takeOff:
      readable_name = CMD_TAKEOFF;
      break;
    case missionSchedulerAction::hover:
      readable_name = CMD_HOVER;
      number_of_arguments = 1;
      break;
    case missionSchedulerAction::land:
      readable_name = CMD_LAND;
      break;
    case missionSchedulerAction::stabilize:
      readable_name = CMD_STABILIZE;
      break;
    case missionSchedulerAction::positionMovement:
      readable_name = CMD_MOVEMENT_POSITION;
      number_of_arguments  = 1;
      break;
    case missionSchedulerAction::goToPoint:
      readable_name = CMD_GO_TO_POINT;
      number_of_arguments  = 1;
      break;
    case missionSchedulerAction::rotateYaw:
      readable_name = CMD_ROTATE_YAW;
      number_of_arguments  = 1;
      break;
    case missionSchedulerAction::flipMovementRight:
      readable_name = CMD_FLIP_RIGHT;
      break;
    case missionSchedulerAction::flipMovementLeft:
      readable_name = CMD_FLIP_LEFT;
      break;
    case missionSchedulerAction::flipMovementFront:
      readable_name = CMD_FLIP_FRONT;
      break;
    case missionSchedulerAction::flipMovementBack:
      readable_name = CMD_FLIP_BACK;
      break;
    case missionSchedulerAction::rememberPoint:
      readable_name = CMD_REMEMBER_POINT;
      number_of_arguments = 1;
      break;
    case missionSchedulerAction::unknown:
      readable_name = "";
      break;
	}
}

Action::~Action()
{
  //TO DO
}
bool Action::setArgument(duo<std::string, std::string> argument)
{
  //If the argument can be set up, then true is returned.
  if(string_arguments.size() < number_of_arguments)
  {
    string_arguments.push_back(argument); 
    return true;
  }
  else return false;
}

std::string Action::getReadableName()
{
  return readable_name;
}

std::vector<duo<std::string, std::vector<double>>> Action::getArguments()
{  
  //Just in the case that the following transformation have not been done.
  if(arguments.empty())
  {
    duo<std::string, std::vector<double>> aux;
    for(int i = 0; i<string_arguments.size(); i++)
    {
      if(string_arguments.at(i).key == NAME_DURATION)
      { 
        aux.key   = NAME_DURATION;
        aux.value.push_back(stod(string_arguments.at(i).value));
      }
      else if(string_arguments.at(i).key == NAME_ROTATION)
      {
        aux.key   = NAME_ROTATION;
        aux.value.push_back(stod(string_arguments.at(i).value));
      }
      else if(string_arguments.at(i).key == NAME_DESTINATION)
      {
        aux.key   = NAME_DESTINATION;
        aux.value = pointToVector(string_arguments.at(i).value);
      }
      else if(string_arguments.at(i).key == NAME_POINT_NAME)
      {
        //In this case, the key is the name of the variable referenced.
        aux.key   = string_arguments.at(i).key;
        aux.value.push_back(stod(string_arguments.at(i).value));
      }
      //Setting up the arguments
      arguments.push_back(aux);
    }
  }
  return arguments;
}

bool Action::checkActionSemanticErrors(std::string & message, std::vector<std::string> & declared_variables)
{
  message = "";
  //First, it is mandatory to transform the arguments according to their type.
  switch (action_name)
  {
    case missionSchedulerAction::hover:
      if(string_arguments.size() == 0)
        message = "Not enough arguments for action \"" + readable_name + "\" Argument \"" + NAME_DURATION + "\" is needed.";
      else if(!isNumber(string_arguments.at(0).value))
        message = "Argument passed for action \"" + readable_name + "\" must be a number. To specify a decimal value use \".\" instead another symbols.";
      else if(string_arguments.at(0).key != NAME_DURATION)
        message = "Argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\" is not correct, Did you want to say \"" + NAME_DURATION + "\"?";
      else if(stod(string_arguments.at(0).value) <= 0)
        message = readable_name + " action cannot be performed for " + string_arguments.at(0).value +" seconds, you must specify a duration value greater than 0.";
      break;
    case missionSchedulerAction::rotateYaw:
      if(string_arguments.size() == 0)
        message = "Not enough arguments for action \"" + readable_name + "\" Argument \"" + NAME_ROTATION + "\" is needed.";
      else if(!isNumber(string_arguments.at(0).value))
        message = "Argument passed for action \"" + readable_name + "\" must be a number. To specify a decimal value use \".\" instead another symbols.";
      else if(string_arguments.at(0).key != NAME_ROTATION)
        message = "Argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\" is not correct, Did you want to say \"" + NAME_ROTATION + "\"?";
      break;
    case missionSchedulerAction::positionMovement:
      if(string_arguments.size() == 0)
        message = "Not enough arguments for action \"" + readable_name + "\" Argument \"" + NAME_DESTINATION + "\" is needed.";
      else if(!isPoint(string_arguments.at(0).value) && !isVariable(string_arguments.at(0).value))
        message = "Argument \"" + string_arguments.at(0).value + "\" passed for action \"" + readable_name + "\" must be a point or a variable.";
      else if(string_arguments.at(0).key != NAME_DESTINATION)
        message = "Argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\" is not correct, Did you want to say  \"" + NAME_DESTINATION + "\"?";
      else if(isVariable(string_arguments.at(0).value) && !isDeclared(string_arguments.at(0).value, declared_variables))
        message = "Variable \"" + string_arguments.at(0).value + "\" in action \"" + readable_name + "\" has not been declared.";
      else if(isVariable(string_arguments.at(0).value))
        setVariableValue(string_arguments.at(0), declared_variables);    
      break;     
    case missionSchedulerAction::goToPoint:
      if(string_arguments.size() == 0)
        message = "Not enough arguments for action \"" + readable_name + "\" Argument \"" + NAME_DESTINATION + "\" is needed.";
      else if(!isPoint(string_arguments.at(0).value) && !isVariable(string_arguments.at(0).value))
        message = "Argument \"" + string_arguments.at(0).value + "\" passed for action \"" + readable_name + "\" must be a point or a variable.";
      else if(!isVariable(string_arguments.at(0).value) && string_arguments.at(0).key != NAME_DESTINATION)
        message = "Argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\" is not correct, Did you want to say  \"" + NAME_DESTINATION+ "\"?";
      else if(isVariable(string_arguments.at(0).value) && !isDeclared(string_arguments.at(0).value, declared_variables))
        message = "Variable \"" + string_arguments.at(0).value + "\" in action \"" + readable_name + "\" has not been declared or it has the name of a reserved word.";
      else if(isVariable(string_arguments.at(0).value) && string_arguments.at(0).key != NAME_POINT_NAME)
        message = "Incorrect name of argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\". Did you want to say \"" + NAME_POINT_NAME +"\"?";
      //Now, semantic errors have been checked
      else if(isVariable(string_arguments.at(0).value))
        setVariableValue(string_arguments.at(0), declared_variables);
      break;
    case missionSchedulerAction::rememberPoint:
      if(string_arguments.size() == 0)
        message = "Not enough arguments for action \"" + readable_name + "\" Argument \"" + NAME_POINT_NAME + "\" is needed.";
      else if(string_arguments.at(0).key != NAME_POINT_NAME)
        message = "Argument \"" + string_arguments.at(0).key + "\" in action \"" + readable_name + "\" is not correct, Did you want to say  \"" + NAME_POINT_NAME + "\"?";
      else if(!isVariable(string_arguments.at(0).value))
        message = "Name \"" + string_arguments.at(0).value + "\" for point variable in action \"" + readable_name + "\" is not correct. The name of a point variable should not be a reserved word an it should start by a letter followed (optionaly) by alphanumerical characters. ";
      //Once the previous conditions have been checked, it is mandatory to set the given variable as declared.
      else if(isVariable(string_arguments.at(0).value))
      {
        //If the variable is still not declared...
        if(!isDeclared(string_arguments.at(0).value, declared_variables))
          declared_variables.push_back(string_arguments.at(0).value);
        //Calculating the value, it is just the position the variable takes in the vector. 
        string_arguments.at(0).value = to_string(declared_variables.size()-1);
      }
      break;
    default:
     //This should never be reached. Just in case.
     if(string_arguments.size()>0)
       message = "Action \"" + readable_name + "\" does not accept arguments";
     break;
  }
  //It returns true when no semantic errors have been identified
  return message == "";
}

bool Action::isEmpty()
{
  return action_name == missionSchedulerAction::unknown;
}
missionSchedulerAction::taskActions  Action::getName()
{
  return action_name;
}
bool Action::isVariable(const std::string & s)
{
  //If a name wants to be considered as variable it must be composed of letters and digits.,
  //In fact, the first character has to be a letter
  std::string spaces = "([[:blank:]]|[[:space:]])*";
  std::string expression = spaces + "[[:alpha:]]([[:alpha:]]|[[:digit:]]|_)*" + spaces;
  boost::regex ex (expression, boost::regex_constants::extended);
  //A name that wants to be considered as variable must not match with the name of other 
  //reserved words.
  return  boost::regex_match(s, ex) && !isReservedWord(s); 
}

bool  Action::setVariableValue(duo<std::string, std::string> & variable, std::vector<std::string> declared_variables)
{
  int counter;
  bool found = false;
  for(int counter =0; counter<declared_variables.size() && !found; counter++)
    found = variable.value == declared_variables.at(counter);        
  variable.value = to_string(counter);
  return found;
}

bool Action::isReservedWord(const std::string & s)
{
  return (s == NAME_ROTATION) || (s == NAME_DURATION) || (s == NAME_DESTINATION) || (s == NAME_POINT_NAME);
}

bool Action::isNumber(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
   char * p ;
   strtol(s.c_str(), &p, 10) ;
   return (*p == 0 || *p == '.') ;
}

bool Action::isPoint(const std::string & s)
{
  //In order to understand the following expressions, please see the POSIX syntax for regular expressions.
  std::string spaces = "([[:blank:]]|[[:space:]])*";
  std::string sign   = "(\\+|-)?";
  std::string digit  = sign + "[[:digit:]]+(\\.[[:digit:]]+)?"; 
  std::string expression = spaces + "\\(" + spaces + digit + spaces + "," + spaces + digit + spaces + "," + spaces + digit + spaces+ "\\)" +spaces;

  boost::regex ex (expression, boost::regex_constants::extended);
  //Is the expression expected equal to the recieved one?
  return boost::regex_match(s, ex); 
}

bool Action::isDeclared(std::string variable, std::vector<std::string> declared_variables)
{
  bool found_variable = false;
  for(int i = 0; i < declared_variables.size() && !found_variable; i++)
      found_variable = variable == declared_variables.at(i);
  return found_variable;
}

std::vector<double> Action::pointToVector(std::string s)
{
  std::vector<double> vector_to_return;
  //Auxiliar variables.
  bool last_symbol_was_a_digit = false;
  std::string number;
  for(int i = 0; i< s.size(); i++)
  {
    if(isdigit(s[i]) || s[i] == '.' || s[i] == '-')
    {
      last_symbol_was_a_digit = true;
      number = number + s[i]; 
    }
    else if(last_symbol_was_a_digit)
    {  
      vector_to_return.push_back(stod(number));
      last_symbol_was_a_digit = false;
      number = "";  
    }
  }
  return vector_to_return;
}