#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/version.hpp>

#include <string>
#include <iostream>
#include <math.h>
#include <chrono>
#include <time.h>
#include "droneMsgsROS/dronePose.h"
#include "droneMsgsROS/battery.h"
#include "droneMsgsROS/droneSpeeds.h"

//Mind 30 fps 
//cv::Scalar are color objects.
//Mind they are defined in BGRA order and alpha should be 255.
#define FONT cv::FONT_HERSHEY_DUPLEX
#define FONT_SCALE 0.45
#define SMALL_FONT_SCALE 0.75 //Not recommended more than 0.75
#define TEXT_THICKNESS 1 //Integer
#define LINE_TYPE CV_AA //Better looking line
//#define BORDER_TYPE CV_AA//If applied border. Unused
#define DARK_COLOR cv::Scalar(0,0, 0,255) //Black
#define TEXT_COLOR cv::Scalar(255,255,255,255) //White
#define FPS_CAP 0 //0=no cap  (max 30) Unused
#define LEFT_PANEL_POINT cv::Point(10,30) //10 pixels left, 30 pixels up
#define HORIZON_LINE_SCALE 1  //Recommeded values 1..2
#define POV_ANGLE 15 //Pov angle for pitch in horizon line == 42 degrees/2
#define PITCH_SCALE 1 //Pitch scale represented in pitch. Should be one.
#define PITCH_REFRESH_RATE 20 //Number of frames for pitch transition
#define ROLL_REFRESH_RATE 20 //Same as the pitch pitch refresh rate
#define BIG 0
#define SMALL 1

#define PITCH_NO 5 //Number of data in the pitch indicator
#define BRIGHTNESS_LEVEL 255*0.6  // 0 Black 255 White

static const std::string OPENCV_WINDOW = "Image window";//For debug with cv::imshow





class ImageConverter{


public:
    //Constructor & Destructor
     ImageConverter();
    ~ImageConverter();

public:


  void CheckUnderlay();
  void CheckOverlay(cv::Mat &overlay,int im_no);
  void poseInfoCb(const droneMsgsROS::dronePose::ConstPtr& msg);
  void spdInfoCb(const droneMsgsROS::droneSpeeds::ConstPtr& msg);
  void battInfoCb(const droneMsgsROS::battery::ConstPtr& msg );
  void imageOverlayCb(const sensor_msgs::ImageConstPtr& msg, const image_transport::Publisher &image_pub_small_, const image_transport::Publisher &image_pub_big_);
  void imageOverlayCbBlack(const image_transport::Publisher &image_pub_small_, const image_transport::Publisher &image_pub_big_);
  void secondOperations();
  void checkBrightness();
  void putText(cv::Mat &img, const std::string &text, cv::Point point, double text_size, cv::Scalar color_, int thickness);
  void overlayImage(cv::Mat* src, cv::Mat* overlay, const cv::Point& location);
  std::vector<int> linspace(int min, int max, int n);
  void generateOverlay(cv::Mat &overlay);
  void refreshVariables(cv::Mat &overlay, int im_no);
  void DrawCenterPannel(cv::Mat &overlay, int im_no);
  void DrawLeftPannel(cv::Mat &overlay);
  void DrawRightPannel(cv::Mat &overlay);
  void DrawRollIndicator(cv::Mat &overlay, int im_no);
  void DrawHorizonLine(cv::Mat &overlay, int im_no);
  void DrawYawIndicator(cv::Mat &overlay, int im_no);
  double DegToRad(double deg);
  double RadToDeg(double rad);
  std::string doToStr(double a, int n_dec);
  cv::Point rotatePoint(cv::Point center, cv::Point point, double angle);



time_t start, end;
int frame, real_fps, battery_status, measures, seconds, 
diff_time, minutes, published_frame, yaw, pitch, roll, 
radius, height, home_dist, brightness_change, dark_mode, icon_load, 
pitch_change, pitch_change_phase, tmp_pitch, 
roll_change, roll_change_phase, tmp_roll;

size_t total_size;
std::clock_t timer_start;
double duration, total_time, frame_time, 
pos_x, pos_y, pos_z, spd, 
initial_angle, final_angle, pitch_offset;
static double font_scale;

std::vector<int> path, pitch_transform, roll_transform;

typedef std::chrono::high_resolution_clock Clock;
cv::Size textSize;
static cv::Scalar color;
cv::Point start_left, start_right, draw_left, draw_right, ell_center, ell_init; //HUD position points
cv::Mat battery, position; 
bool hum, yeah; //Testing variables
  


private:

  /*ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_big_,image_pub_small_;
  ros::Subscriber pose_sub_,batt_sub_,spd_sub_;*/
  cv::Mat fixed_overlay,image_big,image_small,backup;
  cv_bridge::CvImagePtr cv_ptr;
  



};

#endif 