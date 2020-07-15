#include "poseOperations.h"


namespace SL
{




int inverse(Pose& PoseIn, Pose& PoseOut)
{
    cv::Mat HomogMatIn, HomogMatOut;

    PoseIn.getHomogMat(HomogMatIn);

    cv::invert(HomogMatIn,HomogMatOut);

    PoseOut.setHomogMat(HomogMatOut);


    return 1;
}


Pose inverse(Pose& PoseIn)
{
    Pose PoseOut;

    cv::Mat HomogMatIn, HomogMatOut;

    PoseIn.getHomogMat(HomogMatIn);

    cv::invert(HomogMatIn,HomogMatOut);

    PoseOut.setHomogMat(HomogMatOut);


    return PoseOut;
}



Pose operator+(Pose& PoseA, Pose& PoseB)
{
    Pose PoseOut;

    cv::Mat HomogMatInA, HomogMatInB, HomogMatOut;

    PoseA.getHomogMat(HomogMatInA);
    PoseB.getHomogMat(HomogMatInB);

    HomogMatOut=HomogMatInA*HomogMatInB;


    PoseOut.setHomogMat(HomogMatOut);



    return PoseOut;

}



Pose operator-(Pose& PoseA, Pose& PoseB)
{
    Pose PoseBInv, PoseOut;

    cv::Mat HomogMatInA, HomogMatInBInv, HomogMatOut;

    PoseA.getHomogMat(HomogMatInA);

    PoseBInv=inverse(PoseB);
    PoseBInv.getHomogMat(HomogMatInBInv);

    HomogMatOut=HomogMatInA*HomogMatInBInv;


    PoseOut.setHomogMat(HomogMatOut);



    return PoseOut;

}






//Pose Pose::operator+(const Pose& Pose1, const Pose& Pose2)
//{
//    Pose PoseOut;




//    return PoseOut;
//}



}
