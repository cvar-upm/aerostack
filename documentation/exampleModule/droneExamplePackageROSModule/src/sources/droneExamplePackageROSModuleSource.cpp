//////////////////////////////////////////////////////
//  droneExamplePackageROSModuleSource.cpp
//
//  Created on: Sep 10, 2014
//      Author: joselusl
//
//  Last modification on: Sep 10, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////


#include "droneExamplePackageROSModuleHeader.h"


// using namespaces only in cpp files!!
using namespace std;




DroneExamplePackageROSModule::DroneExamplePackageROSModule() : DroneModule(droneModule::active)
{

    return;
}


DroneExamplePackageROSModule::~DroneExamplePackageROSModule()
{
	close();
	return;
}

//Setters
/*
int DroneExamplePackageROSModule::setCalibCamera(std::string camCalibParamFile)
{
    this->camCalibParamFile=camCalibParamFile;
    return 1;
}

int DroneExamplePackageROSModule::setGridParameters(std::string gridIntersectionsParamFile)
{
    this->gridIntersectionsParamFile=gridIntersectionsParamFile;
    return 1;
}

int DroneExamplePackageROSModule::setTopicConfigs(std::string camSubsTopicName, std::string keypointsPublTopicName)
{
    this->camSubsTopicName=camSubsTopicName;
    this->keypointsPublTopicName=keypointsPublTopicName;
    return 1;
}
*/

bool DroneExamplePackageROSModule::init()
{
    DroneModule::init();


    /////Init main class
/*
    // Camera parameters
    IA14G.initializeCameraParameters(camCalibParamFile);


    // Load parameters from XML file
    // BOT-RELATED
    //XML document
    pugi::xml_document doc;
    std::ifstream nameFile(gridIntersectionsParamFile.c_str());
    pugi::xml_parse_result result = doc.load(nameFile);

    if(!result)
    {
        std::cout<<"Error opening grid intersections parameter file"<<std::endl;
        return false;
    }
    /////////////////////////////////////
    // GRID-RELATED
    cv::Size gridWorkSize, DTCells;
    cv::Vec3i BGR_valuesForBG=cv::Vec3i(0, 0, 0);
    double maskWhiteRatio;
    int ransac_max_iterations, ransac_max_inlier_distance, ransac_min_inliers, clusteringRadius, y_channel_threshold;

    std::string readingValue;
    pugi::xml_node GRID = doc.child("grid");


    readingValue=GRID.child_value("width");
    std::istringstream convertedValue1(readingValue);
    convertedValue1>> gridWorkSize.width;
    //cout<<"width="<<gridWorkSize.width<<endl;

    readingValue=GRID.child_value("height");
    std::istringstream convertedValue2(readingValue);
    convertedValue2>> gridWorkSize.height;

    readingValue=GRID.child_value("horizontalCells");
    std::istringstream convertedValue3(readingValue);
    convertedValue3>> DTCells.width;
    readingValue=GRID.child_value("verticalCells");
    std::istringstream convertedValue4(readingValue);
    convertedValue4>> DTCells.height;

    readingValue=GRID.child_value("maskWhiteRatio");
    std::istringstream convertedValue5(readingValue);
    convertedValue5>> maskWhiteRatio;
    readingValue=GRID.child_value("redColorBG");
    std::istringstream convertedValue6(readingValue);
    convertedValue6>> BGR_valuesForBG[2];
    readingValue=GRID.child_value("greenColorBG");
    std::istringstream convertedValue7(readingValue);
    convertedValue7>> BGR_valuesForBG[1];
    readingValue=GRID.child_value("blueColorBG");
    std::istringstream convertedValue8(readingValue);
    convertedValue8>> BGR_valuesForBG[0];

    readingValue=GRID.child_value("ransac_max_iterations");
    std::istringstream convertedValue9(readingValue);
    convertedValue9>> ransac_max_iterations;
    readingValue=GRID.child_value("ransac_max_inlier_distance");
    std::istringstream convertedValue10(readingValue);
    convertedValue10>> ransac_max_inlier_distance;
    readingValue=GRID.child_value("ransac_min_inliers");
    std::istringstream convertedValue11(readingValue);
    convertedValue11>> ransac_min_inliers;

    readingValue=GRID.child_value("clusteringRadius");
    std::istringstream convertedValue12(readingValue);
    convertedValue12>> clusteringRadius;
	
	readingValue=GRID.child_value("Y_channel_thresh");
    std::istringstream convertedValue13(readingValue);
    convertedValue13>> y_channel_threshold;


    IA14G.initializeGridModule(gridWorkSize, BGR_valuesForBG, maskWhiteRatio, DTCells, ransac_max_iterations,
        ransac_max_inlier_distance, ransac_min_inliers, clusteringRadius, y_channel_threshold);
*/


    //end
    return true;
}


void DroneExamplePackageROSModule::open(ros::NodeHandle & nIn)
{
	//Node
    DroneModule::open(nIn);


    //Init
    if(!init())
    {
        cout<<"Error init"<<endl;
        return;
    }



    //// TOPICS
    //Subscribers
    //droneImageSubs = n.subscribe(camSubsTopicName, 1, &DroneExamplePackageROSModule::droneImageCallback, this);



    //Publishers
    //droneKeypointsPubl=n.advertise<droneMsgsROS::vectorPoints2DInt>(keypointsPublTopicName, 1, true);



    //Flag of module opened
    droneModuleOpened=true;

    //autostart module!
    moduleStarted=true;

	
	//End
	return;
}


void DroneExamplePackageROSModule::close()
{
    DroneModule::close();



    //Do stuff

    return;
}


bool DroneExamplePackageROSModule::resetValues()
{
    //Do stuff

    return true;
}


bool DroneExamplePackageROSModule::startVal()
{
    //Do stuff

    //End
    return DroneModule::startVal();
}


bool DroneExamplePackageROSModule::stopVal()
{
    //Do stuff

    return DroneModule::stopVal();
}


bool DroneExamplePackageROSModule::run()
{
    if(!DroneModule::run())
        return false;

    if(droneModuleOpened==false)
        return false;

/*
    //Process image
    gridIntersections.clear(); //Clean
    cv::Mat undistortedFrame;
    //cout<<"lo veo"<<endl;
    int errorCodeG=IA14G.run(droneImage, undistortedFrame, gridIntersections);
    //cout<<"no lo veo"<<endl;

#ifdef CV_DEBUG
    // show the results
    cv::Mat results=undistortedFrame.clone();
    IA14G.showResults(results, gridIntersections);
    cv::imshow("grid intersections", results);
    cv::waitKey(1);
#endif

    // check for completion of the IA14G.run()
    if(errorCodeG<0)
    {
        //return false;
    }
*/

    //Publish
    /*
    if(!publishKeypoints())
    {
        cout<<"error publishing"<<endl;
        return false;
    }
    */


    return true;
}

//Callback
//void DroneExamplePackageROSModule::droneImageCallback(const sensor_msgs::ImageConstPtr& msg)
//{
//    /*
//    //Transform message to Opencv
//    try
//    {
//        cvDroneImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
//    }
//    catch (cv_bridge::Exception& e)
//    {
//        ROS_ERROR("cv_bridge exception: %s", e.what());
//        return;
//    }
//    droneImage=cvDroneImage->image;
//    */


//    //Run -> ashyncronous
//    if(!run())
//    {
//        cout<<"Error running"<<endl;
//        return;
//    }


//    return;
//}


//Publisher
//bool DroneExamplePackageROSModule::publishKeypoints()
//{
//    if(droneModuleOpened==false)
//        return false;

///*
//    //Transform to message
//    droneMsgsROS::vectorPoints2DInt keypointsDetectedMsg;
//    //Header: the header of the image
//    keypointsDetectedMsg.header.stamp=cvDroneImage->header.stamp;
//    //keypoints
//    for (std::vector<cv::Point>::iterator it = gridIntersections.begin() ; it != gridIntersections.end(); ++it)
//    {
//        droneMsgsROS::vector2i point2D;
//        point2D.x=it->x;
//        point2D.y=it->y;
//        keypointsDetectedMsg.point2DInt.push_back(point2D);
//    }


//    //Publish
//    droneKeypointsPubl.publish(keypointsDetectedMsg);
//*/

//    return true;

//}






