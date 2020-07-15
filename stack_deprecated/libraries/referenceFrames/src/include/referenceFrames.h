/*
 * referenceFrames.h
 *
 *  Created on: 
 *      Author: jl.sanchez
 */

#ifndef REFERENCE_FRAMES_H
#define REFERENCE_FRAMES_H





//Cpp
#include <sstream>
#include <string>
#include <iostream>




#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/opencv.hpp>

namespace referenceFrames
{


//Otros

// Funciones auxiliares
int createRotMatrix_wYvPuR(cv::Mat * const pRotMat, double yaw, double pitch, double roll);
int createHomogMatrix_wYvPuR(cv::Mat * const pHomogMat, double x, double y, double z, double yaw, double pitch, double roll);
inline int createHomogMatrix_xYyPzR(cv::Mat *pHomogMat, double x, double y, double z, double yaw, double pitch, double roll) { return createHomogMatrix_wYvPuR( pHomogMat, x, y, z, roll, pitch, yaw); }
int getxyzYPRfromHomogMatrix_wYvPuR(const cv::Mat &HomogMat, double *px, double *py, double *pz, double *pyaw, double *ppitch, double *proll);
int getxyzYPRfromHomogMatrix_xYyPzR(const cv::Mat &HomogMat, double *px, double *py, double *pz, double *pyaw, double *ppitch, double *proll);

// from arUcoDefinition.cpp
int createMatHomogFromVecs(cv::Mat* MatHomog, const cv::Mat &TransVec, const cv::Mat &RotVec);

int invertHomogMatrix(const cv::Mat &pHomogMat_orig, cv::Mat &pHomogMat_target);
}
        
        
 

#endif
