#include <stdio.h>
#include <iostream>
#include "ErrorHandler.h"

using namespace std;

ErrorHandler::ErrorHandler()
{
  //TO DO
}

ErrorHandler::~ErrorHandler()
{
  //TO DO
}

void ErrorHandler::errorFound(std::string message)
{
 	std::string error_message = "\033[0;31m[ERROR] " + message + "\n\033[0m";
 	errors.push_back(error_message);
}

void ErrorHandler::warningFound(std::string message)
{
 	std::string error_message = "\033[0;33m[WARNING] " + message + "\n\033[0m";
 	warnings.push_back(error_message);
}

void ErrorHandler::displayErrorsAndWarnings()
{	
  //Display warnings.
  for (int i = 0; i < warnings.size(); i++)
  	cout << warnings[i];

  //Display errors.
   if(errors.size() > 0){
    for (int j = 0; j < errors.size(); j++)
        cout << errors[j];
    //If errors have been produced during the execution of the main program, it cannot continue.
    cout << "\033[0;31m" << errors.size() << " errors found.\nAborting ...\n\033[0m";
    exit(1);
  }
} 

void ErrorHandler::checkParsingErrors(pugi::xml_parse_result result, std::string missionConfigFile)
{
  if(!fileExists(missionConfigFile))
  {
    errorFound("Mission'specification file has not been found. Parsing cannot continue.");
    displayErrorsAndWarnings();
  }

  if (!result)
  {
    offset_data_t offset_data;
    std::string message = result.description();
    //Obtaining line and column.
    buildOffsetData(offset_data, missionConfigFile);
    std::pair<int, int> num = getLocation(offset_data, result.offset);
    errorFound(message + ": line " + to_string(num.first) + ", column " + to_string(num.second) + ".");
    //The mission cannot continue if sintax errors exist.
    displayErrorsAndWarnings();
  }
}

std::pair<int, int> ErrorHandler::getLocation(const offset_data_t& data, ptrdiff_t offset)
{
    offset_data_t::const_iterator it = std::lower_bound(data.begin(), data.end(), offset);
    size_t index = it - data.begin();

    return std::make_pair(1 + index, index == 0 ? offset + 1 : offset - data[index - 1]);
}

void ErrorHandler::buildOffsetData(offset_data_t& result, std::string file)
{
  FILE* f = fopen(file.c_str(), "rb");
  ptrdiff_t offset = 0;

  char buffer[1024];
  size_t size;

  while ((size = fread(buffer, 1, sizeof(buffer), f)) > 0)
  {
  for (size_t i = 0; i < size; ++i)
    if (buffer[i] == '\n')
      result.push_back(offset + i);
    offset += size;
    }
    fclose(f);
}

inline bool ErrorHandler::fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}