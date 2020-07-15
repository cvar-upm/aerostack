//////////////////////////////////////////////////////
//  poseOperations.h
//
//  Created on: Mar 26, 2014
//      Author: jl.sanchez
//
//  Last modification on: Mar 26, 2014
//      Author: jl.sanchez
//
//////////////////////////////////////////////////////



#ifndef POSE_OPERATIONS_H
#define POSE_OPERATIONS_H


#include <iostream>
#include <string>
#include <vector>


#include "opencv2/opencv.hpp"


#include "pose.h"



namespace SL //Spatial Localization
{
    //Calculate the inverse pose: PoseIn = Pose A wrt B; PoseOut = Pose B wrt A
    int inverse(Pose& PoseIn, Pose& PoseOut);
    Pose inverse(Pose& PoseIn);


    //Calculate the composition of poses:
    Pose operator+(Pose& PoseA, Pose& PoseB);


    //Calculate the composition of poses:
    Pose operator-(Pose& PoseA, Pose& PoseB); //TODO




}




#endif
