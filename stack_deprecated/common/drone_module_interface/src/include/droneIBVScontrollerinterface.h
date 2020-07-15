
#include "dronemoduleinterface.h"
#include "droneMsgsROS/dronePitchRollCmd.h"
#include "droneMsgsROS/droneDAltitudeCmd.h"
#include "droneMsgsROS/droneDYawCmd.h"
#include "droneMsgsROS/BoundingBox.h"
#include "droneMsgsROS/imageFeaturesIBVS.h"
#include "droneMsgsROS/imageFeaturesFeedbackIBVS.h"

#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

#include "communication_definition.h"

//OpenCV
#include <opencv2/highgui/highgui.hpp>

#define DISPLAY_DRONE_IMAGE 0


class DroneIBVSControllerInterface : public DroneModuleInterface
{
public:
    DroneIBVSControllerInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in);
    ~DroneIBVSControllerInterface();

    void open(ros::NodeHandle & nIn);


private:

    ros::Subscriber drone_frontcamera_image_sub;
    void droneImageCallback(const sensor_msgs::Image& msg);

    ros::Subscriber DronePitchRollCmdSubs;
    void dronePitchRollCmdCallback(const droneMsgsROS::dronePitchRollCmd::ConstPtr& msg);

    ros::Subscriber DroneDAltitudeCmdSubs;
    void droneDAltitudeCmdCallback(const droneMsgsROS::droneDAltitudeCmd::ConstPtr& msg);

    ros::Subscriber DroneDYawCmdSubs;
    void droneDYawCmdCallback(const droneMsgsROS::droneDYawCmd::ConstPtr& msg);

    ros::Subscriber tracking_object_sub;
    void trackingObjectCallback(const std_msgs::Bool& msg);

    ros::Subscriber is_object_on_frame_sub;
    void isObjectOnFrameCallback(const std_msgs::Bool& msg);

    ros::Subscriber get_bounding_box_sub;
    void getBoundingBoxCallback(const droneMsgsROS::BoundingBox& msg);

    ros::Subscriber get_image_features_sub;
    void getImageFeaturesCallback(const droneMsgsROS::imageFeaturesIBVS& msg);

    ros::Subscriber get_image_features_feedback_sub;
    void getImageFeaturesFeedbackCallback(const droneMsgsROS::imageFeaturesFeedbackIBVS& msg);

public:
    droneMsgsROS::dronePitchRollCmd DronePitchRollCmdMsgs;
    droneMsgsROS::droneDAltitudeCmd DroneDAltitudeCmdMsgs;
    droneMsgsROS::droneDYawCmd DroneDYawCmdMsgs;

    // Services
private:
    ros::ServiceClient setControlModeClientSrv;

public:
    std::stringstream *getIBVSControllerCommands();
    std::stringstream *getIBVSControllerStatus();
    std::stringstream *getOpenTLDTrackingStream();
    std::stringstream *getOpenTLDStream();
    std::stringstream *getOpenTLDFeatures();


public:

    void getIBVSControllerImage();
    void drawArrow(cv::Mat &image, cv::Point pi, cv::Point pe, cv::Scalar color);
    void drawIBVS(cv::Mat &image, int bb_x, int bb_y, int bb_width, int bb_heigth, float Dxcd, float Dycd, float Sd);
    void drawIBVS_v2(cv::Mat &image, int bb_x, int bb_y, int bb_width, int bb_heigth, float Dxcd, float Dycd, float Sd, float Dxs2, float Dys2);
    void drawText(cv::Mat &image, bool tracker_is_tracking, bool tracker_object_on_frame, bool isControllerStarted);


     cv_bridge::CvImagePtr cvFrontImage;
     cv::Mat  frontcameraimage;

    // OpenTLD
public:

    ros::Time bb_timestamp;
    int     bb_x, bb_y, bb_width, bb_height;
    float   bb_confidence, bb_fps;
    bool    tracker_is_tracking;
    bool    tracker_object_on_frame;
    float Dxc, Dyc, Dyawc, Dzc;
    ros::Time init_time;
    double xc, yc, yawc, zc, vxc, vyc;
    float fx,    fy,    fs,    fD;
    float fxref, fyref, fsref, fDref;

    float fxci, fyci, fsci, fDci;
    float fxs_4DyC, fxs_4DYC, fys_4DzC, fDs_4DxC;

    float image_width, image_height;
private:
    std::stringstream interface_printout_stream;
};


