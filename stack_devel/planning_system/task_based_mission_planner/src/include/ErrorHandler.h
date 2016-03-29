/*!*****************************************************************************
 *  \file      ErrorHandler.h
 *  \brief     Definition of all the classes used in the file
 *             EventHandler.cpp .
 *   
 *  \author    Adrian Diaz
 *  \copyright Copyright 2015 UPM. All rights reserved. 
 *             Released under license BSD-3.
 ********************************************************************************/
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
 
#include <iostream>
#include <stddef.h>
#include <sys/stat.h>
#include "pugixml.hpp"
#include <cstdlib>
#include <vector>

typedef std::vector<ptrdiff_t> offset_data_t;

class ErrorHandler{

  private:
  	std::vector<std::string> errors;
  	std::vector<std::string> warnings;

  public:
    //Constructor & destructor
  	ErrorHandler();
  	~ErrorHandler();

  public:
  /*!************************************************************************
   *  \brief  This method is called when an error has been detected.
   *  \param  message Error information. 
   *************************************************************************/
  	void errorFound(std::string message);
  /*!************************************************************************
   *  \brief  This method is called when a warning has been detected.
   *  \param  message Warning information. 
   *************************************************************************/
  	void warningFound(std::string message);
  /*!************************************************************************
   *  \brief  This method displays all the error and warning messages 
   *          stored in memory.
   *************************************************************************/
  	void displayErrorsAndWarnings();
  /*!************************************************************************
   *  \brief  This method checks whether parsing errors have occur.
   *  \param  result Pugi parser's result.
   *  \param  missionConfigFile File's name where the mission has 
   *          been writen.
   *************************************************************************/
    void checkParsingErrors(pugi::xml_parse_result result, std::string missionConfigFile);

  //Auxiliar methods
  private:
  /*!************************************************************************
   *  \brief  This method builds the offset_data type necesary to transform
   *          the offset given by pugixml into a correct offset.
   *  \param  data An offset_data_t memory direction.
   *  \param  missionConfigFile File's name where the mission has 
   *          been writen.
   *************************************************************************/
    void buildOffsetData(offset_data_t& data, std::string missionConfigFile);
  /*!************************************************************************
   *  \brief  This method calculates the correct offset.
   *  \param  data An offset_data_t memory direction.
   *  \param  offset pugixml's offset.
   *  \return A pair structure containing the line and the column 
   *          respectively where the error has been found.
   *************************************************************************/
    std::pair<int, int> getLocation(const offset_data_t& data, ptrdiff_t offset);
  /*!************************************************************************
   *  \brief  This method checks whether a file exists.
   *  \param  name File's name..
   *  \return True if the given name matchs with a file's name, 
   *          false in other case.
   *************************************************************************/
    inline bool fileExists (const std::string& name);
};
#endif