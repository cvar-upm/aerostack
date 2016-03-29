/*!*****************************************************************************
 *  \file    Condition.h
 *  \brief   Definition of all the classes used in the file
 *           Condition.cpp .
 *   
 *  \author  Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *       Released under license BSD-3.
 ********************************************************************************/
#ifndef CONDITION_H
#define CONDITION_H

//Condition Parameters (UNCOMPLETE)
#define PAR_ARUCO_VISUAL_MARKER                         "ArucoVisualMarker"
#define PAR_BATTERY_CHARGE_PERCENTAGE                   "percentageBatteryCharge"

//Condition comparison symbol (UNCOMPLETE)
#define COMP_EQUAL                                    "equal"
#define COMP_LESS                                     "less"
 
#include <iostream>
#include <cstdlib>

/*!***************************************************************************
 *  \class Condition
 *  \brief This class represents a definition of what a condition is.
 *****************************************************************************/
class Condition{
private:
bool condition_evaluation;
std::string parameter;
std::string comparison;
std::string value;
public:
  //Constructor & Destructor
  Condition(std::string condition_parameter, std::string condition_comparison, std::string condition_value);
  ~Condition();

public:

 /*!************************************************************************
  *  \brief  This method evaluates the condition according to the parameter
  *          that is passed.
  *  \param  condition_parameter Parameter needed to evaluate 
  *          the whole condition.
  *  \return The boolean evaluation of the condition.
  *************************************************************************/
  bool evaluateCondition(int condition_parameter);
 /*!************************************************************************
  *  \brief  This method checks if the param,eter passed as argument is equal
  *          to the parameter of the condition.
  *  \param  condition_parameter Parameter needed to evaluate 
  *          the whole condition.
  *  \return True if the argument passed is equal to the condition's 
  *          parameter.
  *************************************************************************/
  bool isParameterEqualTo(std::string condition_parameter);
 /*!************************************************************************
  *  \brief  This method returns the value of the condition.
  *  \return The value of the condition.
  *************************************************************************/
  bool getConditionValue();
 /*!************************************************************************
  *  \brief  Reset the condition's attributes to its default values.
  *************************************************************************/
  void resetConditionEvaluation();
 /*!************************************************************************
  *  \brief  This method returns the expression of the condition .
  *  \return A trsing with the proper expression.
  *************************************************************************/  
  std::string getConditionExpresion();
};
#endif