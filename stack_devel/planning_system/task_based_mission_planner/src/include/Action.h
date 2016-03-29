/*!*****************************************************************************
 *  \file      Action.h
 *  \brief     Definition of all the classes used in the file
 *             EventHandler.cpp .
 *   
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/
#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include "ErrorHandler.h"
#include "Definitions.h"


class Action
{
  private:
    //The number of argument that an Action may have.
    int number_of_arguments;
    //The coded name of the action (an integer).
    missionSchedulerAction::taskActions action_name;
    //The user readable name.
    std::string readable_name;
    //The initial storage of the arguments
    std::vector<duo<std::string, std::string>> string_arguments;
    //The arguments that are goign to be returned.
    std::vector<duo<std::string, std::vector<double>>> arguments;
   
  public:
  	//Constructor & Destructor.
  	Action(missionSchedulerAction::taskActions name);
  	~Action();

  public:
  /*!************************************************************************
   *  \brief  This method gives the arguments of the action.
   *  \return A pair key-value in which the name of the argument and the
   *          value or values of the argument are stored.
   *************************************************************************/  
    std::vector<duo<std::string, std::vector<double>>> getArguments();
  /*!************************************************************************
   *  \brief  This function gets the coded name of the action.
   *  \return The coded name of the action.
   *************************************************************************/
    missionSchedulerAction::taskActions  getName();
  /*!************************************************************************
   *  \brief  This method gets the readable name of the action.
   *  \return A string in which the name of the action is stored.
   *************************************************************************/
    std::string getReadableName();
  /*!************************************************************************
   *  \brief  This function just checks whether the action has semantic
   *          errors in its arguments.
   *  \param  message The identified errors will be stored in this parameter.
   *  \param  declared_variable A vector where the declared variables
   *          identified by a xml parser are stored. 
   *  \return True if no semantic errors have been found, false in other case.
   *************************************************************************/
    bool checkActionSemanticErrors(std::string & message, std::vector<std::string> & declared_variables);
  /*!************************************************************************
   *  \brief  This method checks if the action has been set up before.
   *  \return True if the action has not been set up before, false in other
   *          case.
   *************************************************************************/
    bool isEmpty();
  /*!************************************************************************
   *  \brief  This function set the argument passed as parameter.
   *  \param  A pair key-value in which the key is the name of the argument
   *          and the value represent the value of the parameter in string 
   *          format.        
   *  \return True if the parameter has been ste, false in other case.
   *************************************************************************/
    bool setArgument(duo<std::string, std::string> argument);

  private:
  /*!************************************************************************
   *  \brief  This method checks if the string passed as parameter match 
   *          with the pattern that a TML variable should have.
   *  \param  s The string that is going to be checked out.
   *  \return True is variable, false if it is not.
   *************************************************************************/
    bool isVariable(const std::string & s);
  /*!************************************************************************
   *  \brief  This method checks if the string passed as parameter match 
   *          with the pattern that a real number should have.
   *  \param  s The string that is going to be checked out.
   *  \return True if it is a number , false if it is not.
   *************************************************************************/
    bool isNumber(const std::string & s);
  /*!************************************************************************
   *  \brief  This method checks if the string passed as parameter match 
   *          with a TML reserved word.
   *  \param  s The string that is going to be checked out.
   *  \return True if it is a TML reserved word , false if it is not.
   *************************************************************************/   
    bool isReservedWord(const std::string & s);
  /*!************************************************************************
   *  \brief  This method checks if the string passed as parameter match 
   *          with the pattern that a 3D point should have.
   *  \param  s The string that is going to be checked out.
   *  \return True if it is a 3D point, false if it is not.
   *************************************************************************/
    bool isPoint(const std::string & s);
  /*!************************************************************************
   *  \brief  This method checks if the name of the variable 
   *          passed as argument belongs to the vector of declared variables 
   *          passed  as argument as well.
   *  \param  variable The name of the variable that is going to be 
   *          checked out.
   *  \param  declared_variables The vector of declared variables
   *  \return True if the variable passed as argument is declared, false in
   *          other case.
   *************************************************************************/
    bool isDeclared(std::string variable, std::vector<std::string> declared_variables);
  /*!************************************************************************
   *  \brief  This method sets the value of the variable passed as argument
   *          according to the position it has in the vector passed as 
   *          argument as well
   *  \param  variable The name of the variable whose value is going to be 
   *          set up.
   *  \param  declared_variables The vector of declared variables
   *  \return True if the value of variable passed as argument has been set up, false in
   *          other case.
   *************************************************************************/
    bool setVariableValue(duo<std::string, std::string> & variable, std::vector<std::string> declared_variables);
      /*!************************************************************************
   *  \brief  This function transforms a string in point format into a vector
   *          of 3 real coordinates.
   *  \param  s The string that is going to be transformed.
   *  \return A vector of lenght 3.
   *************************************************************************/
    std::vector<double> pointToVector(std::string s);
};
#endif