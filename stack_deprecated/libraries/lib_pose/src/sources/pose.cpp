#include "pose.h"


using namespace std;



namespace SL
{

Pose::Pose() :
    //Nav angles + trans
    positionDroneNavData(3),
    attitudeDroneNavData(3),
    //Nav angles + trans
    positionRobotNavData(3),
    attitudeRobotNavData(3),
    //Rvec, Tvec
    rvec(3),
    tvec(3),
    //HomogMat
    HomogMat(4,4,CV_64FC1)
{
    //Set flags to false
    noneSet();


    return;
}

Pose::~Pose()
{

    return;
}


int Pose::noneSet()
{
    //Set flags to false
    flagDroneNavData=false;
    flagRobotNavData=false;
    flagPair=false;
    flagHomogMat=false;



    return 1;
}


int Pose::setDroneNavData(const std::vector<double> &positionDroneNavData, const std::vector<double> &attitudeDroneNavData, bool newPose)
{
    if(newPose)
        noneSet();

    this->positionDroneNavData=positionDroneNavData;
    this->attitudeDroneNavData=attitudeDroneNavData;

    flagDroneNavData=true;

    return 1;
}

int Pose::getDroneNavData(std::vector<double>& positionDroneNavData, std::vector<double>& attitudeDroneNavData)
{
    if(flagDroneNavData)
    {
        positionDroneNavData=this->positionDroneNavData;
        attitudeDroneNavData=this->attitudeDroneNavData;
        return 1;
    }
    else
    {
        //Convert from HomogMat
        if(transfHomogMat2DroneNavData())
        {
            positionDroneNavData=this->positionDroneNavData;
            attitudeDroneNavData=this->attitudeDroneNavData;
            return 1;
        }
        //Convert from Pair
        if(transfPair2DroneNavData())
        {
            positionDroneNavData=this->positionDroneNavData;
            attitudeDroneNavData=this->attitudeDroneNavData;
            return 1;
        }
    }

    return 0;
}



int Pose::setPair(const std::vector<double> &tvec, const std::vector<double> &rvec, bool newPose)
{
    if(newPose)
        noneSet();

    this->tvec=tvec;
    this->rvec=rvec;

    flagPair=true;

    return 1;
}


int Pose::getPair(std::vector<double>& tvec, std::vector<double>& rvec)
{
    if(flagPair)
    {
        tvec=this->tvec;
        rvec=this->rvec;
        return 1;
    }
    else
    {
        //Convert from HomogMat
        if(transfHomogMat2Pair())
        {
            tvec=this->tvec;
            rvec=this->rvec;
            return 1;
        }

        //Convert from NavData
        if(transfDroneNavData2Pair())
        {
            tvec=this->tvec;
            rvec=this->rvec;
            return 1;
        }

    }

    return 0;
}


int Pose::setHomogMat(const cv::Mat &HomogMat, bool newPose)
{
    if(newPose)
        noneSet();

    HomogMat.copyTo(this->HomogMat);

    flagHomogMat=true;

    return 1;

}
int Pose::getHomogMat(cv::Mat& HomogMat)
{
    if(flagHomogMat)
    {
        this->HomogMat.copyTo(HomogMat);
        return 1;
    }
    else
    {
        if(transfPair2HomogMat())
        {
            this->HomogMat.copyTo(HomogMat);
            return 1;
        }

        if(transfDroneNavData2HomogMat())
        {
            this->HomogMat.copyTo(HomogMat);
            return 1;
        }
    }

    return 0;
}



//Transformations!!!!!

int Pose::transfPair2HomogMat()  //OK???
{
    if(!flagPair)
        return 0;

    if(flagHomogMat)
        return 1;


    //Transformation
    HomogMat=cv::Mat::zeros(4,4,CV_64FC1);

    //Checks
    if ( (HomogMat.empty()) || (HomogMat.size() != cv::Size(4,4)) )
    {
        return 0;
    }

    cv::Mat rotationMat(3,3,CV_64F);

    cv::Rodrigues(rvec,rotationMat);




    //Rotation
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            HomogMat.at<double>(i,j)=rotationMat.at<double>(i,j);



    //Translation
    for(int i=0;i<3;i++)
    {
        HomogMat.at<double>(i,3)=tvec[i];
    }


    //Scale
    HomogMat.at<double>(3,3)=1.0;


    //cout<<"HomogMat="<<HomogMat<<endl;



    flagHomogMat=true;


    return 1;
}

int Pose::transfHomogMat2Pair()
{
    if(!flagHomogMat)
        return 0;

    if(flagPair)
        return 1;


    ////Transformation


    cv::Rect rotMatPos(0,0,3,3);
    cv::Rect traVecPos(3,0,1,3);

    cv::Mat rotationMat(HomogMat,rotMatPos);
    cv::Mat translaVec(HomogMat,traVecPos);

    //cout<<"RotationMat="<<rotationMat<<endl;
    //cout<<"translaVec="<<translaVec<<endl;

    //Rotation vec
    cv::Rodrigues(rotationMat,rvec);

    //Translation vec //CHECK!!
    tvec[0]=translaVec.at<double>(0,0);
    tvec[1]=translaVec.at<double>(1,0);
    tvec[2]=translaVec.at<double>(2,0);


    flagPair=true;



    return 1;
}


int Pose::transfPair2DroneNavData()
{
    if(!flagPair)
        return 0;

    if(flagDroneNavData)
        return 1;


    if(!transfPair2HomogMat())
        return 0;

    if(!transfHomogMat2DroneNavData())
        return 0;


    flagDroneNavData=true;



    return 1;
}

int Pose::transfDroneNavData2Pair()
{
    if(!flagDroneNavData)
        return 0;

    if(flagPair)
        return 1;

    if(!transfDroneNavData2HomogMat())
        return 0;

    if(!transfHomogMat2Pair())
        return 0;


    flagPair=true;

    return 1;
}


int Pose::transfDroneNavData2HomogMat()
{
    if(!flagDroneNavData)
        return 0;

    if(flagHomogMat)
        return 1;



    ///Transformation

    //translation
    double x=positionDroneNavData[0];
    double y=positionDroneNavData[1];
    double z=positionDroneNavData[2];
    //this->translation=translation;

    //nav angles

    double yaw=attitudeDroneNavData[0];
    double pitch=attitudeDroneNavData[1];
    double roll=attitudeDroneNavData[2];


    //
    HomogMat=cv::Mat::zeros(4,4,CV_64FC1);

    //this->rotation=navAngles;



    if ( (HomogMat.empty()) || (HomogMat.size() != cv::Size(4,4)) )
    {
        return 0;
    }


    HomogMat.at<double>(0,0) = cos(pitch)*cos(yaw);
    HomogMat.at<double>(1,0) = cos(pitch)*sin(yaw);
    HomogMat.at<double>(2,0) = -sin(pitch);
    HomogMat.at<double>(3,0) = 0.0;

    HomogMat.at<double>(0,1) = cos(yaw)*sin(pitch)*sin(roll) - cos(roll)*sin(yaw);
    HomogMat.at<double>(1,1) = cos(roll)*cos(yaw) + sin(pitch)*sin(roll)*sin(yaw);
    HomogMat.at<double>(2,1) = cos(pitch)*sin(roll);
    HomogMat.at<double>(3,1) = 0.0;

    HomogMat.at<double>(0,2) = sin(roll)*sin(yaw) + cos(roll)*cos(yaw)*sin(pitch);
    HomogMat.at<double>(1,2) = cos(roll)*sin(pitch)*sin(yaw) - cos(yaw)*sin(roll);
    HomogMat.at<double>(2,2) = cos(pitch)*cos(roll);
    HomogMat.at<double>(3,2) = 0.0;

    HomogMat.at<double>(0,3) = x;
    HomogMat.at<double>(1,3) = y;
    HomogMat.at<double>(2,3) = z;
    HomogMat.at<double>(3,3) = 1.0;


    //cout<<"MatHomog="<<pHomogMat<<endl;

    flagHomogMat=true;


    return 1;
}

int Pose::transfHomogMat2DroneNavData()
{
    if(!flagHomogMat)
        return 0;

    if(flagDroneNavData)
        return 1;


    //Transformation
    //Translation
    for(int i=0;i<3;i++)
    {
        positionDroneNavData[i]=HomogMat.at<double>(i,3);
    }



    double yaw, pitch, roll;


    ///http://en.wikibooks.org/wiki/Robotics_Kinematics_and_Dynamics/Description_of_Position_and_Orientation
    double tol=1e-4;

    //Pitch
    if(pow(HomogMat.at<double>(0,0),2) + pow(HomogMat.at<double>(0,1),2) >=tol)
    {
      double my_sign = HomogMat.at<double>(0,0) > 0 ? 1.0 : -1.0;
      pitch=atan2(HomogMat.at<double>(0,2), my_sign*sqrt(pow(HomogMat.at<double>(0,0),2) + pow(HomogMat.at<double>(0,1),2))); // mal condicionada si está cerca de pi/2 o -pi/2


    //	if (MatHomog.at<float>(0,2) < 0 && MatHomog.at<float>(0,2) < 0 && MatHomog.at<float>(0,1))

      /*
    cout << "YPR Calculation ........... GOOD Pitch!!!!!!";
    cout <<  " 0,2= " << MatHomog.at<float>(0,2);
    cout <<  " 0,0= " << MatHomog.at<float>(0,0);
    cout <<  " 0,1= " << MatHomog.at<float>(0,1) << endl;
      */
    }
    else
    {
        //TODO
      cout<<"!Bad conditioning in Pitch. Pitch =+-pi/2" << endl;
//      pitch = cvg_utils_library::asin_ws(HomogMat.at<double>(0,2));
      pitch = asin(HomogMat.at<double>(0,2));
    }



    double tol2=-1e-1;

    //Roll =f(pitch) -> pitch=+-pi/2 || yaw=+-pi/2
    if(abs(HomogMat.at<double>(2,2))<=tol2)
    {
      cout<<"!Bad conditioning in Roll. Roll =+-pi/2" << endl;
        //TODO
        roll=0.0;
    }
    else
    {
        roll=atan2(-HomogMat.at<double>(1,2),HomogMat.at<double>(2,2));
    }


    //Yaw =f(roll)
    if(abs(HomogMat.at<double>(0,0))<=tol2)
    {
      cout<<"!Bad conditioning in Yaw. Yaw =+-pi/2" << endl;
        //TODO
      float aux = (cos(roll)-HomogMat.at<double>(1,1)/HomogMat.at<double>(2,1)*sin(roll)) / (HomogMat.at<double>(1,0)-HomogMat.at<double>(1,1)*HomogMat.at<double>(2,0)/HomogMat.at<double>(2,1));
//      yaw = cvg_utils_library::asin_ws(aux);
      yaw = asin(aux);
    }
    else
    {
        yaw=atan2(-HomogMat.at<double>(0,1),HomogMat.at<double>(0,0));
    }


    //end
    attitudeDroneNavData[0]=yaw;
    attitudeDroneNavData[1]=pitch;
    attitudeDroneNavData[2]=roll;







    flagDroneNavData=true;


    return 1;
}



Pose& Pose::operator=(const Pose &rhs)
{
    // Check for self-assignment!
    if (this == &rhs)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.

    // Deallocate, allocate new space, copy values...

    //Flags
    this->flagHomogMat=rhs.flagHomogMat;
    this->flagDroneNavData=rhs.flagDroneNavData;
    this->flagRobotNavData=rhs.flagRobotNavData;
    this->flagPair=rhs.flagPair;

    //values
    this->attitudeDroneNavData=rhs.attitudeDroneNavData;
    this->positionDroneNavData=rhs.positionDroneNavData;

    this->attitudeRobotNavData=rhs.attitudeRobotNavData;
    this->positionRobotNavData=rhs.positionRobotNavData;

    rhs.HomogMat.copyTo(this->HomogMat);

    this->rvec=rhs.rvec;
    this->tvec=rhs.tvec;



    return *this;
}


Pose::Pose(const Pose& other)
{

    this->flagHomogMat=other.flagHomogMat;
    this->flagDroneNavData=other.flagDroneNavData;
    this->flagRobotNavData=other.flagRobotNavData;
    this->flagPair=other.flagPair;

    //values
    this->attitudeDroneNavData=other.attitudeDroneNavData;
    this->positionDroneNavData=other.positionDroneNavData;

    this->attitudeRobotNavData=other.attitudeRobotNavData;
    this->positionRobotNavData=other.positionRobotNavData;

    other.HomogMat.copyTo(this->HomogMat);

    this->rvec=other.rvec;
    this->tvec=other.tvec;

    return;
}




}







