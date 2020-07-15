//////////////////////////////////////////////////////
//  droneVisualMarkersEyeSimulator.cpp
//
//  Created on: Jan 24, 2014
//      Author: joselusl
//
//  Last modification on: Jan 24, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////


#include "droneVisualMarkersEyeSimulator.h"


using namespace std;


/////// Pose
Pose::Pose()
{
    flagIsPoseDefined=false;
    return;
}
Pose::~Pose()
{
    return;
}

int Pose::setPose(double xIn, double yIn, double zIn, double yawIn, double pitchIn, double rollIn)
{
    x=xIn;
    y=yIn;
    z=zIn;
    yaw=yawIn;
    pitch=pitchIn;
    roll=rollIn;

    flagIsPoseDefined=true;

    return 1;
}
int Pose::getPose(double& xOut, double& yOut, double& zOut, double& yawOut, double& pitchOut, double& rollOut)
{
    if(flagIsPoseDefined)
    {
        xOut=x;
        yOut=y;
        zOut=z;
        yawOut=yaw;
        pitchOut=pitch;
        rollOut=roll;

        return 1;
    }
    else
        return 0;
}
bool Pose::isPoseDefined()
{
    return flagIsPoseDefined;
}



////////// Visual Mark
VisualMark::VisualMark()
{
    flagIsDefined=false;
    return;
}
VisualMark::VisualMark(unsigned int idIn, double sizeIn)
{
    id=idIn;
    size=sizeIn;

    flagIsDefined=true;

    return;
}
VisualMark::~VisualMark()
{
    return;
}
int VisualMark::setId(unsigned int idIn)
{
    id=idIn;

    return 1;
}
int VisualMark::configure(unsigned int idIn, double sizeIn)
{
    id=idIn;
    size=sizeIn;

    flagIsDefined=true;

    return 1;
}

int VisualMark::getId(unsigned int& idOut)
{
    if(flagIsDefined)
    {
        idOut=id;
        return 1;
    }
    else
        return 0;
}
int VisualMark::getSize(double &sizeOut)
{
    if(flagIsDefined)
    {
        sizeOut=size;
        return 1;
    }
    else
        return 0;
}
bool VisualMark::isDefined()
{
    return flagIsDefined;
}




////////// DroneVisualMarkersEyeSimulator
DroneVisualMarkersEyeSimulator::DroneVisualMarkersEyeSimulator()
{
    matHomog_aruco_GMR_wrt_drone_GMR = cv::Mat::eye(4,4,CV_32F);
    matHomog_aruco_GMR_wrt_GFF       = cv::Mat::eye(4,4,CV_32F);
    matHomog_drone_GMR_wrt_GFF       = cv::Mat::eye(4,4,CV_32F);
    matHomog_GFF_wrt_drone_GMR       = cv::Mat::eye(4,4,CV_32F);
}

DroneVisualMarkersEyeSimulator::~DroneVisualMarkersEyeSimulator()
{
    return;
}


int DroneVisualMarkersEyeSimulator::run()
{
    // The pose of the drone (matHomog_drone_GMR_wrt_GFF) is specified
    // by double x, y, z, yaw, pitch and roll member variables

    // Update matHomog_drone_GMR_wrt_GFF to current pose of the drone
    referenceFrames::createHomogMatrix_wYvPuR( &matHomog_drone_GMR_wrt_GFF, x, y, z, yaw, pitch, roll);
    referenceFrames::invertHomogMatrix( matHomog_drone_GMR_wrt_GFF, matHomog_GFF_wrt_drone_GMR);

//    cout<<"[DVMES] (run) dronePose: pose=["<<x<<";"<<y<<";"<<z<<";"<<yaw*(180/M_PI)<<";"<<pitch*(180/M_PI)<<";"<<roll*(180/M_PI)<<"]" <<endl;

    // The pose of the arucos (matHomog_aruco_GMR_wrt_GFF) is specified
    // in the memeber std::vector<VisualMark> TheDefinedVisualMarks.
    // (Not all the Arucos in the vector have a specified pose)
    TheObservedVisualMarks.clear();
    for(unsigned int i=0;i<TheDefinedVisualMarks.size();i++)
    {
        if(TheDefinedVisualMarks[i].isDefined())
        {
            double x_aruco, y_aruco, z_aruco, yaw_aruco, pitch_aruco, roll_aruco;
            if(TheDefinedVisualMarks[i].getPose( x_aruco, y_aruco, z_aruco, yaw_aruco, pitch_aruco, roll_aruco )) {
                unsigned int id_aruco;
                TheDefinedVisualMarks[i].getId(id_aruco);
                double aruco_side_length; TheDefinedVisualMarks[i].getSize(aruco_side_length);
                double aruco_size = aruco_side_length*aruco_side_length;

//                cout<<"[DVMES] (run) DefinedWithPoseVisualMark, matHomog_aruco_GMR_wrt_GFF: id="<<id_aruco<<"; size="<<aruco_side_length<<"; pose=["<<x_aruco<<";"<<y_aruco<<";"<<z_aruco<<";"<<yaw_aruco<<";"<<pitch_aruco<<";"<<roll_aruco<<endl;


                referenceFrames::createHomogMatrix_wYvPuR( &matHomog_aruco_GMR_wrt_GFF, x_aruco, y_aruco, z_aruco, yaw_aruco, pitch_aruco, roll_aruco);
                matHomog_aruco_GMR_wrt_drone_GMR = matHomog_GFF_wrt_drone_GMR*matHomog_aruco_GMR_wrt_GFF;
                referenceFrames::getxyzYPRfromHomogMatrix_wYvPuR( matHomog_aruco_GMR_wrt_drone_GMR, &x_aruco, &y_aruco, &z_aruco, &yaw_aruco, &pitch_aruco, &roll_aruco);

                // Calculate whether the marker is visible
                double aruco_visual_solid_angle;
                double distance = sqrt( x_aruco*x_aruco + y_aruco*y_aruco + z_aruco*z_aruco );



//                CVG::Vector ux_drone(3), ux_aruco(3);
//                ux_drone.setValueData( matHomog_drone_GMR_wrt_GFF.at<float>(0,0) , 1);
//                ux_drone.setValueData( matHomog_drone_GMR_wrt_GFF.at<float>(1,0) , 2);
//                ux_drone.setValueData( matHomog_drone_GMR_wrt_GFF.at<float>(2,0) , 3);
//                ux_aruco.setValueData( matHomog_aruco_GMR_wrt_GFF.at<float>(0,0) , 1);
//                ux_aruco.setValueData( matHomog_aruco_GMR_wrt_GFF.at<float>(1,0) , 2);
//                ux_aruco.setValueData( matHomog_aruco_GMR_wrt_GFF.at<float>(2,0) , 3);
//                double cos_theta = -cvg_utils_library::dotProduct( ux_drone, ux_aruco);
                double cos_theta = (-1.0)*matHomog_aruco_GMR_wrt_drone_GMR.at<float>(0,0);

                aruco_visual_solid_angle = aruco_size*cos_theta/distance;

//                cout<<"[DVMES] (run) DefinedWithPoseVisualMark, matHomog_aruco_GMR_wrt_drone_GMR: id="<<id_aruco<<"; size="<<aruco_side_length<<"; pose=["<<x_aruco<<";"<<y_aruco<<";"<<z_aruco<<";"<<yaw_aruco<<";"<<pitch_aruco<<";"<<roll_aruco<<"] aruco_visual_solid_angle:"<< aruco_visual_solid_angle <<endl;

                bool visibility_condition = ( x_aruco > 0.0 ) &&
                                            ( abs(atan2(y_aruco,x_aruco))*(180.0/M_PI) < MULTIROTOR_FRONTCAM_HORIZONTAL_ANGLE_OF_VIEW/2.0 ) &&
                                            ( abs(atan2(z_aruco,x_aruco))*(180.0/M_PI) < MULTIROTOR_FRONTCAM_VERTICAL_ANGLE_OF_VIEW  /2.0 ) &&
                                            ( VISUAL_ARUCO_SOLID_ANGLE_MIN < aruco_visual_solid_angle ) &&
                                            ( aruco_visual_solid_angle < VISUAL_ARUCO_SOLID_ANGLE_MAX );
                if (visibility_condition) {
//                    cout<<"[DVMES] (run) DefinedWithPoseVisualMark, matHomog_aruco_GMR_wrt_drone_GMR: id="<<id_aruco<<"; size="<<aruco_side_length<<"; pose=["<<x_aruco<<";"<<y_aruco<<";"<<z_aruco<<";"<<yaw_aruco<<";"<<pitch_aruco<<";"<<roll_aruco<<"] aruco_visual_solid_angle:"<< aruco_visual_solid_angle <<endl;
                    // The marker is visible, we add it to std::vector<VisualMark> TheObservedVisualMarks
                    VisualMark visible_aruco( id_aruco, aruco_side_length);
                    visible_aruco.setPose( x_aruco, y_aruco, z_aruco, yaw_aruco, pitch_aruco, roll_aruco);
                    TheObservedVisualMarks.push_back(visible_aruco);
                }
            } else {
                // this is common ocurrence, so no exception is thrown.
                // aruco in arucolist.xml but not in params_localization_obs.xml
            }
        } else {
            unsigned int id_aruco;
            TheDefinedVisualMarks[i].getId(id_aruco);
            std::string exception_str("");
            exception_str +=std::string("exception in DroneVisualMarkersEyeSimulator::run, aruco (id:")
                            + cvg_int_to_string(id_aruco) +
                            std::string(") was specified in params_localization_obs.xml but not in arucolist.xml.");
           throw std::runtime_error(exception_str);
        }
    }

    return 1;
}

int DroneVisualMarkersEyeSimulator::addConfigurationOfDefinedVisualMark(unsigned int idIn, double sizeIn)
{
    //search in the list if is already there
    for(unsigned int i=0;i<TheDefinedVisualMarks.size();i++)
    {
        unsigned int idMark;
        if(TheDefinedVisualMarks[i].getId(idMark))
        {
            if(idMark==idIn)
            {
                TheDefinedVisualMarks[i].configure(idIn,sizeIn);
                return 1;
            }
            else
                continue;
        }
        else
            continue;
    }

    //It is not in the list.
    VisualMark TheVisualMark(idIn,sizeIn);
    TheDefinedVisualMarks.push_back(TheVisualMark);

    return 1;
}

int DroneVisualMarkersEyeSimulator::addPoseOfDefinedVisualMark(unsigned int idIn, double xIn, double yIn, double zIn, double yawIn, double pitchIn, double rollIn)
{
    //search in the list if is already there
    for(unsigned int i=0;i<TheDefinedVisualMarks.size();i++)
    {
        unsigned int idMark;
        if(TheDefinedVisualMarks[i].getId(idMark))
        {
            if(idMark==idIn)
            {
                TheDefinedVisualMarks[i].setPose(xIn,yIn,zIn,yawIn,pitchIn,rollIn);
                return 1;
            }
            else
                continue;
        }
        else
            continue;
    }

    //It is not in the list.
    VisualMark TheVisualMark;
    TheVisualMark.setId(idIn);
    TheVisualMark.setPose(xIn,yIn,zIn,yawIn,pitchIn,rollIn);
    TheDefinedVisualMarks.push_back(TheVisualMark);

    return 1;
}



int DroneVisualMarkersEyeSimulator::readVisualMarksDefinitionFile(std::string fileIn)
{
    int noError=1;

    //XML document
    pugi::xml_document doc;
    std::ifstream nameFile(fileIn.c_str());
    pugi::xml_parse_result result = doc.load(nameFile);

    if(!result)
    {
        cout<<"[DVMES] I cannot open xml file: "<<fileIn<<endl;
        return 0;
    }


    ///Aruco lists
    pugi::xml_node aruco = doc.child("arucoList");


    std::string readingValue;
    int id;
    double size;

    for(pugi::xml_node arucoMarker = aruco.child("arucoMarker");arucoMarker; arucoMarker = arucoMarker.next_sibling("arucoMarker"))
    {
        readingValue=arucoMarker.child_value("id");
        istringstream convertid(readingValue);
        convertid>>id;

        readingValue=arucoMarker.child_value("size");
        istringstream convertsize(readingValue);
        convertsize>>size;

        if(!addConfigurationOfDefinedVisualMark(id,size))
        {
            noError=0;
        }
    }

    return noError;
}

int DroneVisualMarkersEyeSimulator::readVisualMarksPoseFile(std::string fileIn)
{
    int noError=1;

    //XML document
    pugi::xml_document doc;
    std::ifstream nameFile(fileIn.c_str());
    pugi::xml_parse_result result = doc.load(nameFile);

    if (!result) //FIXME, pass as argument
    {
        cout<<"[DVMES] I cannot open xml file: "<<fileIn<<endl;
        return 0;
    }


    pugi::xml_node Arucos = doc.child("main").child("params").child("Arucos");
    for (pugi::xml_node aruco = Arucos.child("Aruco"); aruco; aruco = aruco.next_sibling("Aruco"))
    {

        int id = atoi(aruco.attribute("id").value());
        double x = atof(aruco.attribute("x").value());
        double y = atof(aruco.attribute("y").value());
        double z = atof(aruco.attribute("z").value());
        double yaw = atof(aruco.attribute("yaw").value())*M_PI/180.0;
        double pitch = atof(aruco.attribute("pitch").value())*M_PI/180.0;
        double roll = atof(aruco.attribute("roll").value())*M_PI/180.0;

        if(!addPoseOfDefinedVisualMark(id,x,y,z,yaw,pitch,roll))
        {
            noError=0;
        }
    }

    return noError;
}


