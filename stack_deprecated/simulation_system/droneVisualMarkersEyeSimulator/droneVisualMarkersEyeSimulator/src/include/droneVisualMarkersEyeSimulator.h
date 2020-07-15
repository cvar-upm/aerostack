//////////////////////////////////////////////////////
//  droneVisualMarkersEyeSimulator.h
//
//  Created on: Jan 24, 2014
//      Author: joselusl
//
//  Last modification on: Jan 24, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////


#ifndef _DRONE_VISUAL_MARKERS_EYE_SIMULATOR_H
#define _DRONE_VISUAL_MARKERS_EYE_SIMULATOR_H



//I/O stream
//std::cout
#include <iostream>

//Vector
//std::vector
#include <vector>

//String
//std::string, std::getline()
#include <string>

//String stream
//std::istringstream
#include <sstream>

//File Stream
//std::ofstream, std::ifstream
#include <fstream>

//Math
#include <cmath>

//PugiXML
#include "pugixml.hpp"

#include "referenceFrames.h"
#include <stdexcept>
#include "cvg_utils_library.h"

#include "cvg_string_conversions.h"

// For ARDrone 2.0
//  size of Aruco: 0.253*0.253
//  min visible distance: 0.8
//  max visible distance: 5.5
// Solid angle definition, integral of(dS*cos(theta)/R^2)
const double VISUAL_ARUCO_SOLID_ANGLE_MIN = ( (0.253*0.253)/(5.5*5.5) );
const double VISUAL_ARUCO_SOLID_ANGLE_MAX = ( (0.253*0.253)/(0.8*0.8) );
const double MULTIROTOR_FRONTCAM_HORIZONTAL_ANGLE_OF_VIEW = 70.0;   // deg
const double MULTIROTOR_FRONTCAM_VERTICAL_ANGLE_OF_VIEW   = 38.0;   // deg

/////////////////////////////////////////
// Class VisualMark
//
//   Description
//
/////////////////////////////////////////
class Pose
{
protected:
    double x;
    double y;
    double z;
    double yaw;
    double pitch;
    double roll;

private:
    bool flagIsPoseDefined;

public:
    Pose();
    ~Pose();

public:
    int setPose(double xIn, double yIn, double zIn, double yawIn, double pitchIn, double rollIn);
    int getPose(double& xOut, double& yOut, double& zOut, double& yawOut, double& pitchOut, double& rollOut);

    bool isPoseDefined();

};


/////////////////////////////////////////
// Class VisualMark
//
//   Description
//
/////////////////////////////////////////
class VisualMark : public Pose
{
protected:
    //Visual Mark Caracteristics
    unsigned int id;
    double size;

    //flag
private:
    bool flagIsDefined;

public:
    VisualMark();
    VisualMark(unsigned int idIn, double sizeIn);
    ~VisualMark();

public:
    int setId(unsigned int idIn);

public:
    int configure(unsigned int idIn, double sizeIn);

public:
    int getId(unsigned int &idOut);
    int getSize(double& sizeOut);

public:
    bool isDefined();
};



/////////////////////////////////////////
// Class DroneVisualMarkersEyeSimulator
//
//   Description
//
/////////////////////////////////////////
class DroneVisualMarkersEyeSimulator : public Pose
{
protected:
    //Defined visual marks in the map
    std::vector<VisualMark> TheDefinedVisualMarks;
private:
    cv::Mat matHomog_aruco_GMR_wrt_drone_GMR;   // as required by droneLocalizer module
    cv::Mat matHomog_aruco_GMR_wrt_GFF;         // as specified in the "params_localization_obs.xml" configuration file
    cv::Mat matHomog_drone_GMR_wrt_GFF;         // as provided by droneSimulator
    cv::Mat matHomog_GFF_wrt_drone_GMR;         // as provided by droneSimulator

public:
    //Observated visual marks in each moment
    std::vector<VisualMark> TheObservedVisualMarks;


public:
    DroneVisualMarkersEyeSimulator();
    ~DroneVisualMarkersEyeSimulator();

public:
    int run();

private:
    int addConfigurationOfDefinedVisualMark(unsigned int idIn, double sizeIn);
    int addPoseOfDefinedVisualMark(unsigned int idIn, double xIn, double yIn, double zIn, double yawIn, double pitchIn, double rollIn);

public:
    int readVisualMarksDefinitionFile(std::string fileIn);
    int readVisualMarksPoseFile(std::string fileIn);

};











#endif
