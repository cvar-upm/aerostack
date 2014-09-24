//////////////////////////////////////////////////////
//  DroneExamplePackageROSModule.h
//
//  Created on: Sep 10, 2014
//      Author: joselusl
//
//  Last modification on: Sep 10, 2014
//      Author: joselusl
//
//////////////////////////////////////////////////////

#ifndef DRONE_EXAMPLE_PACKAGE_ROS_MODULE_H
#define DRONE_EXAMPLE_PACKAGE_ROS_MODULE_H




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

//String stream
//std::istringstream
#include <sstream>


// ROS
#include "ros/ros.h"



//Drone module
#include "droneModuleROS.h"


//Main class -> Algorithm developed!
#include "droneExamplePackageHeader.h"



//Messages in
//ROS Images
//#include <image_transport/image_transport.h>
//#include <cv_bridge/cv_bridge.h>
//#include <sensor_msgs/Image.h>
//#include <sensor_msgs/image_encodings.h>


//OpenCV if needed
//#include <opencv2/opencv.hpp>


//Messages out
//Keypoints: Messages out
//#include <droneMsgsROS/vector2i.h>
//#include <droneMsgsROS/vectorPoints2DInt.h>


//Ground Robots: Messages out
//#include <droneMsgsROS/targetInImage.h>
//#include <droneMsgsROS/vectorTargetsInImageStamped.h>






/////////////////////////////////////////
// Class DroneKeypointsGridDetectorROSModule
//
//   Description
//
/////////////////////////////////////////
class DroneExamplePackageROSModule : public DroneModule
{	
protected:
    //Main class
    //IARC14_grid_node IA14G;

    //exchange info between the ROSModule and the main class
    //std::vector<cv::Point> gridIntersections; //cv::Point = cv::Point2i


    //Config files path names
protected:
    //std::string camCalibParamFile;
    //std::string gridIntersectionsParamFile;


    //Setter functions
public:
    //Configs
    //int setCalibCamera(std::string camCalibParamFile);
    //int setGridParameters(std::string gridIntersectionsParamFile);
    //Topics
    //int setTopicConfigs(std::string camSubsTopicName, std::string keypointsPublTopicName);



    //subscribers
protected:
    //Topic name
    //std::string camSubsTopicName;
    //Front image msgs
    //cv_bridge::CvImagePtr cvDroneImage;
    //cv::Mat droneImage;
    //Subscriber
    //ros::Subscriber droneImageSubs;
public:
    //Callback function
    //void droneImageCallback(const sensor_msgs::ImageConstPtr& msg);


    //publishers
protected:
    //Topic name
    //std::string keypointsPublTopicName;
    //Publisher
    //ros::Publisher droneKeypointsPubl;
    //Function
    //bool publishKeypoints();




public:
    DroneExamplePackageROSModule();
    ~DroneExamplePackageROSModule();
	
public:
    void open(ros::NodeHandle & nIn);
	void close();

protected:
    bool init();

    //Reset
protected:
    bool resetValues();

    //Start
protected:
    bool startVal();

    //Stop
protected:
    bool stopVal();

    //Run
public:
    bool run();


};







#endif
