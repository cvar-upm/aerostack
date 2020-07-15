#include "droneIBVScontrollerinterface.h"

DroneIBVSControllerInterface::DroneIBVSControllerInterface(const std::string &module_name_str_in, const ModuleNames::name module_name_enum_in) :
    DroneModuleInterface( module_name_str_in, module_name_enum_in)
{

    bb_timestamp = ros::Time::now();
    bb_x = 320-50;bb_y = 180-50;bb_width = 100;bb_height = 100;
    tracker_is_tracking     = false;
    tracker_object_on_frame = false;
    Dxc = 0.0; Dyc = 0.0; Dyawc = 0.0; Dzc = 0.0;
    init_time = ros::Time::now();
    xc = 0.0; yc = 0.0; yawc = 0.0; zc = 0.7; vxc = 0.0; vyc = 0.0;

    fxci = 0.0; fyci = 0.0; fsci = 0.1; fDci = 1.0/sqrt(0.1);
}

DroneIBVSControllerInterface::~DroneIBVSControllerInterface() {

}

void DroneIBVSControllerInterface::open(ros::NodeHandle & nIn) {
    DroneModuleInterface::open(nIn);


    DronePitchRollCmdSubs            = n.subscribe("command/pitch_roll", 1, &DroneIBVSControllerInterface::dronePitchRollCmdCallback, this);
    DroneDAltitudeCmdSubs            = n.subscribe("command/dAltitude", 1, &DroneIBVSControllerInterface::droneDAltitudeCmdCallback, this);
    DroneDYawCmdSubs                 = n.subscribe("command/dYaw", 1, &DroneIBVSControllerInterface::droneDYawCmdCallback, this);
    tracking_object_sub              = n.subscribe("tracking_object",1,&DroneIBVSControllerInterface::trackingObjectCallback, this);
    is_object_on_frame_sub           = n.subscribe("is_object_on_frame",1,&DroneIBVSControllerInterface::isObjectOnFrameCallback, this);
    get_bounding_box_sub             = n.subscribe("get_bounding_box",1,&DroneIBVSControllerInterface::getBoundingBoxCallback, this);
    get_image_features_sub           = n.subscribe("controller_image_features",1,&DroneIBVSControllerInterface::getImageFeaturesCallback, this);
    get_image_features_feedback_sub  = n.subscribe("controller_image_features_feedback",1,&DroneIBVSControllerInterface::getImageFeaturesFeedbackCallback, this);
    drone_frontcamera_image_sub      = n.subscribe("camera/front/image_raw",1,&DroneIBVSControllerInterface::droneImageCallback, this);
}

void DroneIBVSControllerInterface::dronePitchRollCmdCallback(const droneMsgsROS::dronePitchRollCmd::ConstPtr &msg)
{
    DronePitchRollCmdMsgs = (*msg);
    return;
}

void DroneIBVSControllerInterface::droneDAltitudeCmdCallback(const droneMsgsROS::droneDAltitudeCmd::ConstPtr &msg)
{
    DroneDAltitudeCmdMsgs = (*msg);
    return;
}

void DroneIBVSControllerInterface::droneDYawCmdCallback(const droneMsgsROS::droneDYawCmd::ConstPtr &msg)
{
    DroneDYawCmdMsgs = (*msg);
    return;
}

void DroneIBVSControllerInterface::trackingObjectCallback(const std_msgs::Bool &msg)
{
     tracker_is_tracking = msg.data;
     return;
}

void DroneIBVSControllerInterface::isObjectOnFrameCallback(const std_msgs::Bool &msg)
{
    tracker_object_on_frame = msg.data;
    return;
}

void DroneIBVSControllerInterface::getBoundingBoxCallback(const droneMsgsROS::BoundingBox &msg)
{
    bb_x          = msg.x;
    bb_y          = msg.y;
    bb_width      = msg.width;
    bb_height     = msg.height;
    bb_confidence = msg.confidence;
    return;
}

void DroneIBVSControllerInterface::getImageFeaturesCallback(const droneMsgsROS::imageFeaturesIBVS &msg)
{
    fxci = msg.fx;
    fyci = msg.fy;
    fsci = msg.fs;
    fDci = msg.fD;
    return;
}

void DroneIBVSControllerInterface::getImageFeaturesFeedbackCallback(const droneMsgsROS::imageFeaturesFeedbackIBVS &msg)
{
    fxs_4DyC = msg.Dy;
    fxs_4DYC = msg.DY;
    fys_4DzC = msg.Dz;
    fDs_4DxC = msg.Dx;
    return;
}

void DroneIBVSControllerInterface::droneImageCallback(const sensor_msgs::Image &msg)
{

    image_height = msg.height;
    image_width  = msg.width;
    try
    {
        cvFrontImage = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);

    }
    catch (cv_bridge::Exception& e)
    {

        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    frontcameraimage = cvFrontImage->image;
    getIBVSControllerImage();
    return;
}

std::stringstream *DroneIBVSControllerInterface::getIBVSControllerCommands()
{


    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
            << "IBVSControllerCommands" << std::endl
            << "Pitch:" << DronePitchRollCmdMsgs.pitchCmd << std::endl
            << "Roll:"  << DronePitchRollCmdMsgs.rollCmd  << std::endl
            << "Dyaw:"  << DroneDYawCmdMsgs.dYawCmd  << std::endl
            <<  "Dz:"   << DroneDAltitudeCmdMsgs.dAltitudeCmd    << std::endl;

    return &interface_printout_stream;

}

std::stringstream *DroneIBVSControllerInterface::getOpenTLDTrackingStream()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
            << "+tracker status"  << std::endl;

    if (tracker_is_tracking && tracker_object_on_frame)
    {
     interface_printout_stream
          << "[TRACKING][IN_FRAME]" << std::endl;
    }
    else
    {
        if(!tracker_is_tracking)
        {
           interface_printout_stream
              << "[NOT_TRACKING]"  << std::endl;
        }
        else
        {
            interface_printout_stream
               << "[TRACKING][OUT_OF_FRAME]" << std::endl;
        }
    }
     return &interface_printout_stream;
}

std::stringstream *DroneIBVSControllerInterface::getOpenTLDStream()
{


    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
            << "x: "      <<  bb_x      << std::endl
            << "y: "      <<  bb_y      << std::endl
            << "width: "  <<  bb_width  << std::endl
            << "height: "  << bb_height << std::endl
            << "bb_fps: "  << bb_fps    << std::endl;

     return &interface_printout_stream;
}

std::stringstream *DroneIBVSControllerInterface::getIBVSControllerStatus()
{
    interface_printout_stream.clear();
    interface_printout_stream.str(std::string());
    interface_printout_stream
            << "\n+controller status" << std::endl;

    if (isStarted())
    {
        if(tracker_object_on_frame)
        {
            interface_printout_stream
               << "[CONTROL ON]" << std::endl;

        }
        else
        {
            interface_printout_stream
                << "[CONTROL OFF]" << std::endl;
         }
    }
    else
    {
        interface_printout_stream
                << "[CONTROL OFF]"  << std::endl;
    }

    return &interface_printout_stream;
}

void DroneIBVSControllerInterface::getIBVSControllerImage()
{
    drawText(frontcameraimage , tracker_is_tracking, tracker_object_on_frame, isStarted());
    if ( tracker_object_on_frame )
    {
        float fxci_scc = (fxci - 0.5)*image_width;
        float fyci_scc = (fyci - 0.5)*image_height;
        float fsci_scc = image_width*image_height/(fDci*fDci);
        float fxs_DyC_scc = (fxs_4DyC - 0.5)*image_width;
        float fys_DzC_scc = (fys_4DzC - 0.5)*image_height;
        drawIBVS_v2( frontcameraimage, bb_x, bb_y, bb_width, bb_height, fxci_scc, fyci_scc, fsci_scc, fxs_DyC_scc, fys_DzC_scc);
    }
#if DISPLAY_DRONE_IMAGE
    if(frontcameraimage.empty())
    {
        printf("front_cam image is empty");
    }
    else
    {
        cv::imshow( "Image", frontcameraimage);
        cv::waitKey(1);
    }
#endif
    return;
}

void DroneIBVSControllerInterface::drawArrow(cv::Mat &image, cv::Point pi, cv::Point pe, cv::Scalar color) {
    const int arrow_width = 2;
    cv::line( image, pi, pe, color, arrow_width);

    float L = sqrt( (pi.x-pe.x)*(pi.x-pe.x) + (pi.y-pe.y)*(pi.y-pe.y) );
    float l = ((float)image.size[1])/40.0;
    if ( L < l )
        return;
    float phi = atan2( (pe.y-pi.y), (pe.x-pi.x));

    // Draw triangle at end of arrow
    cv::Point pauxc, dp, p1, p2;
    pauxc.x = pe.x - (2.0/3.0)*l*cos(phi);
    pauxc.y = pe.y - (2.0/3.0)*l*sin(phi);
    dp.x = (2.0/3.0)*l*cos(phi + (120.0*M_PI/180.0));
    dp.y = (2.0/3.0)*l*sin(phi + (120.0*M_PI/180.0));
    p1   = pauxc + dp;
    dp.x = (2.0/3.0)*l*cos(phi - (120.0*M_PI/180.0));
    dp.y = (2.0/3.0)*l*sin(phi - (120.0*M_PI/180.0));
    p2   = pauxc + dp;
    cv::line( image, p1, pe, color, arrow_width);
    cv::line( image, p2, pe, color, arrow_width);
    cv::line( image, p1, p2, color, arrow_width);
    return;
}

void DroneIBVSControllerInterface::drawIBVS(cv::Mat &image, int bb_x, int bb_y, int bb_width, int bb_heigth, float Dxcd, float Dycd, float Sd) {
    const cv::Scalar blue_color( 214,   0,   0);
    const cv::Scalar green_color(  0, 153,   0);
    const cv::Scalar red_color(    0,   0, 214);
    const cv::Scalar orange_color( 0, 102, 204);

    // Detected target
    cv::Point p1( bb_x, bb_y);
    cv::Point p2( bb_x+bb_width, bb_y+bb_heigth);
    cv::rectangle( image, p1, p2, blue_color, 3);

    // Desired centroid
    float xcd = ((float)image.size[1])/2.0+Dxcd;
    float ycd = ((float)image.size[0])/2.0+Dycd;
    // Current centroid
    float xc = bb_x+((float)bb_width)/2.0;
    float yc = bb_y+((float)bb_heigth)/2.0;
    p1.x = xc;
    p1.y = yc;
    p2.x = xcd;
    p2.y = ycd;
    drawArrow( image, p1, p2, red_color);
    cv::circle( image, p1, 2, blue_color,  4);
    cv::circle( image, p2, 2, green_color, 4);

    // Desired size
    float k = sqrt( Sd/(bb_width*bb_heigth) );
    float des_bb_w = k*bb_width;
    float des_bb_h = k*bb_heigth;
    // desired size error arrows
    p1.x = xc-des_bb_w/2.0;
    p1.y = yc-des_bb_h/2.0;
    p2.x = xc-bb_width/2.0;
    p2.y = yc-bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.y = yc+des_bb_h/2.0;
    p2.y = yc+bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.x = xc+des_bb_w/2.0;
    p2.x = xc+bb_width/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.y = yc-des_bb_h/2.0;
    p2.y = yc-bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    // desired size target rectangle
    p1.x = xc-des_bb_w/2.0;
    p1.y = yc-des_bb_h/2.0;
    p2.x = xc+des_bb_w/2.0;
    p2.y = yc+des_bb_h/2.0;
    cv::rectangle( image, p1, p2, green_color, 3);

    return;
}

void DroneIBVSControllerInterface::drawIBVS_v2(cv::Mat &image, int bb_x, int bb_y, int bb_width, int bb_heigth, float Dxcd, float Dycd, float Sd, float Dxs2, float Dys2) {
    const cv::Scalar blue_color( 214,   0,   0);
    const cv::Scalar green_color(  0, 153,   0);
    const cv::Scalar red_color(    0,   0, 214);
    const cv::Scalar orange_color( 0, 102, 204);

    // Detected target
    cv::Point p1( bb_x, bb_y);
    cv::Point p2( bb_x+bb_width, bb_y+bb_heigth);
    cv::rectangle( image, p1, p2, blue_color, 3);

    // Desired centroid
    float xcd = ((float)image.size[1])/2.0+Dxcd;
    float ycd = ((float)image.size[0])/2.0+Dycd;
    // Current centroid
    float xc = bb_x+((float)bb_width)/2.0;
    float yc = bb_y+((float)bb_heigth)/2.0;
    p1.x = xc;
    p1.y = yc;
    p2.x = xcd;
    p2.y = ycd;
//    drawArrow( image, p1, p2, red_color);
    cv::circle( image, p1, 2, blue_color,  4);
    cv::circle( image, p2, 2, green_color, 4);

    // Desired size
    float k = sqrt( Sd/(bb_width*bb_heigth) );
    float des_bb_w = k*bb_width;
    float des_bb_h = k*bb_heigth;
    // desired size error arrows
    p1.x = xc-des_bb_w/2.0;
    p1.y = yc-des_bb_h/2.0;
    p2.x = xc-bb_width/2.0;
    p2.y = yc-bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.y = yc+des_bb_h/2.0;
    p2.y = yc+bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.x = xc+des_bb_w/2.0;
    p2.x = xc+bb_width/2.0;
    drawArrow( image, p2, p1, orange_color);
    p1.y = yc-des_bb_h/2.0;
    p2.y = yc-bb_heigth/2.0;
    drawArrow( image, p2, p1, orange_color);
    // desired size target rectangle
    p1.x = xc-des_bb_w/2.0;
    p1.y = yc-des_bb_h/2.0;
    p2.x = xc+des_bb_w/2.0;
    p2.y = yc+des_bb_h/2.0;
    cv::rectangle( image, p1, p2, green_color, 3);

    // Desired centroid
    xcd = ((float)image.size[1])/2.0+Dxcd;
    ycd = ((float)image.size[0])/2.0+Dycd;
    // Current centroid
    xc = ((float)image.size[1])/2.0+Dxs2;
    yc = ((float)image.size[0])/2.0+Dys2;
    // Current centroid
    float xc2 = bb_x+((float)bb_width)/2.0;
    float yc2 = bb_y+((float)bb_heigth)/2.0;
//    p1.x = xc;
//    p1.y = yc;
//    p2.x = xcd;
//    p2.y = ycd;
    p1.x = xcd;
    p1.y = ycd;
    p2.x = xcd+(xc-xcd);
    p2.y = ycd+(yc-ycd);
    drawArrow( image, p1, p2, orange_color);
// //    cv::circle( image, p1, 2, blue_color,  4);
// //    cv::circle( image, p2, 2, green_color, 4);

    return;
}

void DroneIBVSControllerInterface::drawText(cv::Mat &image, bool tracker_is_tracking, bool tracker_object_on_frame, bool isControllerStarted) {
    // Add controller state and tracker state to HUD image
//    const cv::Scalar blue_color( 214,   0,   0);
    const cv::Scalar green_color(  0, 153,   0);
    const cv::Scalar red_color(    0,   0, 214);
    const cv::Scalar orange_color( 0, 102, 204);
    const double font_scale = 0.6;
    const float text_size = 40*font_scale;
    const int text_thickness = 2;
    const int first_line_position = 7;

    cv::Point p1;
    p1.x = 0;
    p1.y = image_height - text_size - first_line_position;

    if ( tracker_is_tracking && tracker_object_on_frame ) {
        cv::putText( image, "[TRACKER][ON]", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, green_color, text_thickness);
    } else {
        if (!tracker_is_tracking) {
            cv::putText( image, "[TRACKER][OFF]", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, red_color, text_thickness);
        } else { // !tracker_object_on_frame
            cv::putText( image, "[TRACKER][ON][OUT_OF_FRAME]", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, orange_color, text_thickness);
        }
    }

    p1.x = 0;
    p1.y = image_height - first_line_position;

    if ( isControllerStarted ) {
        if (tracker_object_on_frame) {
            cv::putText( image, "[CONTROL][ON]", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, green_color, text_thickness);
        } else {
            cv::putText( image, "[CONTROL][ON][OFM]>>HOVER", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, orange_color, text_thickness);
        }
    } else { // !isControllerStarted
        cv::putText( image, "[CONTROL][OFF]", p1, cv::FONT_HERSHEY_SIMPLEX, font_scale, red_color, text_thickness);
    }

    return;
}
