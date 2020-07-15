//////////////////////////////////////////////////////
//  pose.h
//
//  Created on: Mar 26, 2014
//      Author: jl.sanchez
//
//  Last modification on: Mar 26, 2014
//      Author: jl.sanchez
//
//////////////////////////////////////////////////////



#ifndef POSE_H
#define POSE_H


#include <iostream>
#include <string>
#include <vector>


#include "opencv2/opencv.hpp"





namespace SL //Spatial Localization
{


/////////////////////////////////////////
// Class Pose
//
//   Description
//
/////////////////////////////////////////
class Pose
{
    //Pose Drone Nav Data: wYvPuR
private:
    std::vector<double> positionDroneNavData; //x, y, z
    std::vector<double> attitudeDroneNavData; //Yaw, Pitch, Roll
    bool flagDroneNavData;


    //Pose Robot Nav Data: xYyPzR
private: //TODO
    std::vector<double> positionRobotNavData;
    std::vector<double> attitudeRobotNavData;
    bool flagRobotNavData;


    //Quaternions
private: //TODO




    //Pair: TVec, RVec
private:
    std::vector<double> tvec;
    std::vector<double> rvec;
    bool flagPair;


    //MatHomog
private:
    cv::Mat HomogMat;
    bool flagHomogMat;


private:
    int noneSet();


    //Transformations
private:
    int transfPair2HomogMat(); //Ok
    int transfHomogMat2Pair(); //Ok

    int transfPair2DroneNavData(); //Ok
    int transfDroneNavData2Pair(); //Ok

    int transfDroneNavData2HomogMat(); //Ok
    int transfHomogMat2DroneNavData(); //Ok -> TODO FIX?


    //Constructor
public:
    Pose();


    //Copy-constructor
public:
    Pose(const Pose& other);


    //Destructor
public:
    ~Pose();


    //Setters and getters
public:
    int setDroneNavData(const std::vector<double>& positionDroneNavData, const std::vector<double>& attitudeDroneNavData, bool newPose=true);
    int getDroneNavData(std::vector<double>& positionDroneNavData, std::vector<double>& attitudeDroneNavData);


public:
    int setPair(const std::vector<double>& tvec, const std::vector<double>& rvec, bool newPose=true);
    int getPair(std::vector<double>& tvec, std::vector<double>& rvec);


public:
    int setHomogMat(const cv::Mat& HomogMat, bool newPose=true);
    int getHomogMat(cv::Mat& HomogMat);


    //Operators
public:
    Pose& operator=(const Pose& rhs);






};

}






#endif
