/*
 * referenceFrames.cpp
 *
 *  Created on: 
 *      Author: jl.sanchez
 */


#include "referenceFrames.h"
//#include "htrans.h"
#include <cmath>

namespace referenceFrames
{

int createRotMatrix_wYvPuR(cv::Mat * const pRotMat, double yaw, double pitch, double roll) {
    int error_ocurred = 0;

    if ( (pRotMat == NULL) || (pRotMat->empty()) || (pRotMat->size() != cv::Size(3,3)) ) {
        error_ocurred = 1;
        return error_ocurred;
    }

    pRotMat->at<float>(0,0) = cos(pitch)*cos(yaw);
    pRotMat->at<float>(1,0) = cos(pitch)*sin(yaw);
    pRotMat->at<float>(2,0) = -sin(pitch);

    pRotMat->at<float>(0,1) = cos(yaw)*sin(pitch)*sin(roll) - cos(roll)*sin(yaw);
    pRotMat->at<float>(1,1) = cos(roll)*cos(yaw) + sin(pitch)*sin(roll)*sin(yaw);
    pRotMat->at<float>(2,1) = cos(pitch)*sin(roll);

    pRotMat->at<float>(0,2) = sin(roll)*sin(yaw) + cos(roll)*cos(yaw)*sin(pitch);
    pRotMat->at<float>(1,2) = cos(roll)*sin(pitch)*sin(yaw) - cos(yaw)*sin(roll);
    pRotMat->at<float>(2,2) = cos(pitch)*cos(roll);

    return error_ocurred;
}


int createHomogMatrix_wYvPuR(cv::Mat * const pHomogMat, double x, double y, double z, double yaw, double pitch, double roll) {
    int error_ocurred = 0;

    if ( (pHomogMat == NULL) || (pHomogMat->empty()) || (pHomogMat->size() != cv::Size(4,4)) ) {
        error_ocurred = 1;
        return error_ocurred;
    }

    pHomogMat->at<float>(0,0) = cos(pitch)*cos(yaw);
    pHomogMat->at<float>(1,0) = cos(pitch)*sin(yaw);
    pHomogMat->at<float>(2,0) = -sin(pitch);
    pHomogMat->at<float>(3,0) = 0.0;

    pHomogMat->at<float>(0,1) = cos(yaw)*sin(pitch)*sin(roll) - cos(roll)*sin(yaw);
    pHomogMat->at<float>(1,1) = cos(roll)*cos(yaw) + sin(pitch)*sin(roll)*sin(yaw);
    pHomogMat->at<float>(2,1) = cos(pitch)*sin(roll);
    pHomogMat->at<float>(3,1) = 0.0;

    pHomogMat->at<float>(0,2) = sin(roll)*sin(yaw) + cos(roll)*cos(yaw)*sin(pitch);
    pHomogMat->at<float>(1,2) = cos(roll)*sin(pitch)*sin(yaw) - cos(yaw)*sin(roll);
    pHomogMat->at<float>(2,2) = cos(pitch)*cos(roll);
    pHomogMat->at<float>(3,2) = 0.0;

    pHomogMat->at<float>(0,3) = x;
    pHomogMat->at<float>(1,3) = y;
    pHomogMat->at<float>(2,3) = z;
    pHomogMat->at<float>(3,3) = 1.0;

    return error_ocurred;
}

int getxyzYPRfromHomogMatrix_wYvPuR(const cv::Mat &HomogMat, double *px, double *py, double *pz, double *pyaw, double *ppitch, double *proll) {
    int error_ocurred = 0;

    if ( (HomogMat.empty()) || (HomogMat.size() != cv::Size(4,4)) ) {
        error_ocurred = 1;
        return error_ocurred;
    }

    (*px) = HomogMat.at<float>(0,3);
    (*py) = HomogMat.at<float>(1,3);
    (*pz) = HomogMat.at<float>(2,3);

    // http://en.wikibooks.org/wiki/Robotics_Kinematics_and_Dynamics/Description_of_Position_and_Orientation#Inverse_Mapping_2
    // http://en.wikipedia.org/wiki/Euler_angles#Conversion_between_intrinsic_and_extrinsic_rotations
    float tol=1e-4;
    if ( (pow(HomogMat.at<float>(1,0),2) + pow(HomogMat.at<float>(0,0),2) <= tol) ||
         (pow(HomogMat.at<float>(2,1),2) + pow(HomogMat.at<float>(2,2),2) <= tol) ) {
        std::cout<<"referenceFrames::getxyzYPRfromHomogMatrix_wYvPuR: ¡Bad conditioning in Pitch! Pitch =+-pi/2" << std::endl;

        if ( HomogMat.at<float>(2,0) > 0 ) {
            (*ppitch) = -M_PI/2;
            (*proll)  =     0.0;
            (*pyaw)    = atan2( -HomogMat.at<float>(2,1), -HomogMat.at<float>(2,0));
        } else {
            (*ppitch) =  M_PI/2;
            (*proll)  =     0.0;
            (*pyaw)    = atan2(  HomogMat.at<float>(2,1),  HomogMat.at<float>(2,0));
        }
        error_ocurred = 1;
        return error_ocurred;
    }

    (*pyaw)   = atan2(  HomogMat.at<float>(1,0), HomogMat.at<float>(0,0));
    (*ppitch) = atan2( -HomogMat.at<float>(2,0), cos(*pyaw)*HomogMat.at<float>(0,0)+sin(*pyaw)*HomogMat.at<float>(1,0) );
    (*proll)  = atan2(  HomogMat.at<float>(2,1), HomogMat.at<float>(2,2));

    return error_ocurred;
}

int getxyzYPRfromHomogMatrix_xYyPzR(const cv::Mat &HomogMat, double *px, double *py, double *pz, double *pyaw, double *ppitch, double *proll) {
    int error_ocurred = 0;

    // http://en.wikipedia.org/wiki/Euler_angles#Conversion_between_intrinsic_and_extrinsic_rotations
    error_ocurred = getxyzYPRfromHomogMatrix_wYvPuR( HomogMat, px, py, pz, pyaw, ppitch, proll);
    double paux = (*pyaw);
    (*pyaw)  = (*proll);
    (*proll) = paux;

    return error_ocurred;
}

int createMatHomogFromVecs(cv::Mat* pHomogMat, const cv::Mat &TransVec, const cv::Mat &RotVec) {

    int error_ocurred = 0;
    if ( (pHomogMat == NULL) || (pHomogMat->empty()) || (pHomogMat->size() != cv::Size(4,4)) ) {
        error_ocurred = 1;
        return error_ocurred;
    }
//    (*pHomogMat) = cv::Mat::eye(4,4,CV_32F);

    // Rotation
    cv::Mat RotMat;
    cv::Rodrigues(RotVec,RotMat);

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            pHomogMat->at<float>(i,j)=RotMat.at<float>(i,j);
        }
    }


    //Translation
    for(int i=0;i<3;i++) {
        pHomogMat->at<float>(i,3)=TransVec.at<float>(i,0);
    }

    //Scale
    pHomogMat->at<float>(3,3)=1.0;

    for(int i=0;i<3;i++) {
        pHomogMat->at<float>(3,i) = 0.0;
    }

    return error_ocurred;
}

int invertHomogMatrix(const cv::Mat &pHomogMat_orig, cv::Mat &pHomogMat_target) {
    cv::Mat R, t;
    pHomogMat_orig.copyTo(pHomogMat_target);
    R = pHomogMat_target(cv::Rect(0,0,3,3));
    t = pHomogMat_target(cv::Rect(3,0,1,3));
    R = R.t(); // R = R.transpose();
    t = -R*t;
    return 1;
}

}







