#include <stdio.h>
#include <iostream>
#include "Condition.h"

using namespace std;

Condition::Condition(std::string condition_parameter, std::string condition_comparison, std::string condition_value){
    //Default values
    parameter           = condition_parameter;
    comparison          = condition_comparison;
    value               = condition_value;
    condition_evaluation = false;
}

Condition::~Condition()
{
    //TO DO
}

std::string Condition::getConditionExpresion()
{
    return parameter+" "+comparison+" "+value;
}

bool Condition::evaluateCondition(int condition_parameter)
{
	//Condition values are supossed to be integers.
    if (comparison == COMP_EQUAL)
	  condition_evaluation = (condition_parameter == stoi(value));
    else if(comparison == COMP_LESS)
      condition_evaluation = (condition_parameter < stoi(value));

	return condition_evaluation; 
}

bool Condition::isParameterEqualTo(std::string condition_parameter)
{
	return condition_parameter == parameter;
}

bool Condition::getConditionValue()
{
    return condition_evaluation;
}

void Condition::resetConditionEvaluation()
{
 condition_evaluation = false;
}