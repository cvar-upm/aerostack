#include "../include/image_converter.h"

double ImageConverter::font_scale = FONT_SCALE;
cv::Scalar ImageConverter::color =TEXT_COLOR;

ImageConverter::ImageConverter()
{
    // if(FPS_CAP) //Implementation of a linspaced fps cap.
    //   path=linspace(1, 30, FPS_CAP);//Same list for whole execution
    // else
    //   path=linspace(1, 30, 30);//Same list for whole execution
    seconds=0,minutes=0,
      total_time=0.0,measures=0,//time variables. Average and measures for statistics
      frame=1,//frame number: First frame is numbered 1
      yaw=-1000,pitch=-1000,roll=-1000,spd=0,
      dark_mode=0,battery_status=-1;//battery needs to start negative
    pos_x=0,pos_y=0,pos_z=0,
      pitch_change=0,pitch_change_phase=0,tmp_pitch=0,pitch_offset=0,
      roll_change=0,roll_change_phase=0,tmp_roll=0
      ;//Variables of state
    font_scale=FONT_SCALE;//initialize font_scale
    textSize = cv::getTextSize("V: 0.00 m/s", FONT,font_scale, TEXT_THICKNESS,NULL); //initialize sample textSize
    color=TEXT_COLOR;
    //hum=true,yeah=false;//Variables necessary for testing without interface
    //cv::namedWindow(OPENCV_WINDOW);//Only for demo without interface
}

  /*!************************************************************************
   *  \brief  This method runs on first image capture and creates a "fixed" overlay.
   *  \details First we check if the base image has been created and then we
   *           remove all the data stored and we generate the optional fixed drawings.
   *************************************************************************/
void ImageConverter::CheckUnderlay(){
    if(fixed_overlay.empty()){//Design overlay
      fixed_overlay=cv_ptr -> image.clone(); //Clones the first image
      cv::subtract(fixed_overlay,fixed_overlay , fixed_overlay);//Necessary to work properly. Removes the overlay data
      generateOverlay(fixed_overlay);//unused method, it could be used to create a water mark or create here certain parts of the overlay
    }
  }

  /*!************************************************************************
   *  \brief  This method runs on first image capture and creates a "fixed" overlay.
   *  \param  A matrix which corresponds to the overlay to be generated
   *  \param  An integer 
   *  \details The method prepares the drawing methods to run depending on the value of im_no.
   *           This method was implemented this way (with backups) because in the very start
   *           drawings were made on top of each other,
   *           for every image treated a clean image (or matrix) is used as a base.
   *************************************************************************/
void ImageConverter::CheckOverlay(cv::Mat &overlay,int im_no){
    // if(frame==path[published_frame]){//Check if actual frame is in the list of publishable frames
    overlay=fixed_overlay.clone();//to add extra content, we clone first the empty matrix
    if(im_no==BIG){
      backup=cv_ptr -> image.clone();//Raw Image gets a backup
      font_scale=FONT_SCALE; //Selection of the font scale
    }
    if(im_no == SMALL){
      cv_ptr -> image=backup;
      font_scale=SMALL_FONT_SCALE;
    }
    textSize = cv::getTextSize("V: "+doToStr(spd,2)+" m/s" , FONT,font_scale, TEXT_THICKNESS,NULL);
    start_right=cv::Point(overlay.cols-10-textSize.width,LEFT_PANEL_POINT.y); //Position of the right pannel
    start_left=LEFT_PANEL_POINT; //Position of the left pannel
    refreshVariables( overlay, im_no );//Add the extra content (non fixed) -> Drawing methods
    overlayImage( &(cv_ptr -> image), &(overlay), cv::Point() );//Necessary. Overlays the HUD on the image contained by cv_bridge object
    // if(im_no==1)
    //   published_frame++;//Success
  }
  // }

  /*!************************************************************************
   *  \brief Destructor. Can be empty -> Nothing to be done here.
   *  \details In the destructor we print some statistics of work time and 
   *           free time to be taken into account.
   *           To work propperly the free time printed should be positive.
   *           Work time should not exceed 33 ms/2=16 ms
   *************************************************************************/  
  ImageConverter::~ImageConverter() //!< destructor
  {
    //For this statistics we expect 30 fps.
    std::cout << "average: " << total_time/measures<<'\n' ; //Prints the average processing time. Should be complementary with free time.
    printf("total_time %f measures %d",total_time, measures); //prints total processing time and number of measures (or images) 
    std::cout << "free time: " << 1.0 / 30.0 * 1000.0 - ((double) total_time / (double) measures) << '\n'; //Prints the average of the free time.
    //cv::destroyWindow(OPENCV_WINDOW);//only for demo        
  }
  
  /*!************************************************************************
   *  \brief  This callback gives position info 
   *  \param  A Ros msg of type dronePose
   *  \details This callback treats the ros message. We cast the inclination 
   *           parameters to integer because the decimals are insignificant 
   *           when represented. To avoid errors we set pos_z to 0 when negative.
   *************************************************************************/
  void ImageConverter::poseInfoCb(const droneMsgsROS::dronePose::ConstPtr& msg){
    yaw = ((int)RadToDeg( (msg -> yaw) ));
    pitch = ((int)RadToDeg( (msg -> pitch) ));
    roll = ((int)RadToDeg( (msg->roll) ));
    pos_x = msg -> x;
    pos_y = msg -> y;
    pos_z = msg -> z;
    if(pos_z < 0)
      pos_z = 0;
  }

  /*!************************************************************************
   *  \brief  This callback gives speed info 
   *  \param  A Ros msg of type droneSpeeds
   *  \details This callback treats the ros message. We multiply the  speed 
   *           parameters. The speed represented is the ground speed or the 
   *           speed without taking into account the z edge
   *************************************************************************/
  void ImageConverter::spdInfoCb(const droneMsgsROS::droneSpeeds::ConstPtr& msg){
    double dx=(msg -> dx);
    double dy=(msg -> dy);
    spd=std::sqrt(dx*dx+dy*dy);
  }

  /*!************************************************************************
   *  \brief  This callback gives battery info 
   *  \param  A Ros msg of type battery
   *  \details This callback treats the ros message. Treats the battery parameter.
   *************************************************************************/
  void ImageConverter::battInfoCb(const droneMsgsROS::battery::ConstPtr& msg ){
    battery_status=msg -> batteryPercent;
  }

  /*!************************************************************************
   *  \brief  Image treatment callback
   *  \details  This callback edits a ros camera video stream, displays an 
   *            optional openCv viewer with extra info and republishes it 
   *            through a new ros topic depending on the type of the image image.
   *            The format of the CvCopied image requires to be BGRA8 because
   *            the alpha channel is needed to overlay.
   *  \param  msg Ros message of type sensor_msgs (ros image msg)
   *************************************************************************/
  void ImageConverter::imageOverlayCb(const sensor_msgs::ImageConstPtr& msg, const image_transport::Publisher &image_pub_small_, const image_transport::Publisher &image_pub_big_) //Transformation of the image callback
  {
    auto t1 = Clock::now();    // Start the frame timer
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGRA8);//Create a pointer that points the copy of the Ros MSG to OpenCv
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    secondOperations(); //Operations done each frame to check the timers

    //Check if fixed overlay is empty or create it
    CheckUnderlay();//Is fixed overlay empty?
    
    CheckOverlay(image_big,BIG); //Check the bigger font image  overlay
    //  if(cv::waitKey(1)=='p'||yeah){
    //   cv::imshow(OPENCV_WINDOW, cv_ptr -> image);
    //   yeah=true;
    //   hum=false;
    // }
    image_pub_big_.publish(cv_ptr -> toImageMsg());//Publish the  bigger font image

    /*Part 2: Small Image*/
    CheckOverlay(image_small,SMALL); //Check the small font image overlay
    // if(cv::waitKey(1)=='o'||hum){
    //   cv::imshow(OPENCV_WINDOW, cv_ptr -> image);
    //   hum=true;
    //   yeah=false;
    // }
    image_pub_small_.publish(cv_ptr -> toImageMsg());//Publish the smaller font image 

    //Time and fps limit. Estadistical purposes
    auto t2 = Clock::now();//End the frame timer
    frame_time=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count(); //Can be measured in seconds, milliseconds, nanoseconds
    total_time+=frame_time; 
    measures++;//Frames treated 
    // if(FPS_CAP)//Check the time
    // {
    //   //Total frame time - actual frame time - previous wait
    //   if(floor(1.0/FPS_CAP*1000.0-frame_time-1)<=0)
    //     printf("Excesive frame_time\n");
    //   
  }

  /*!************************************************************************
   *  \brief   Operations done each frame.
   *  \details  First measures the difference between the timers. Secondly,
   *            resets the timers and frame counters. Least, checks the brightness. 
   *            Note brightness is checked each second because it would
   *            be too fast to check it each frame.
   *************************************************************************/
  void ImageConverter::secondOperations(){
    //Start timer for next second
    time(&start);//Actual time
    frame++;
    diff_time=difftime (start, end);//Check is second passed. 
    time(&end);//Time of the last frame
    if(diff_time){//if second passed
      seconds++;
      if(seconds==60)
      {
        minutes++;//minute counter
        seconds=0;//second counter
      }
      real_fps=frame-1; //fps
      frame=1;//restart frame counter IMPORTANT
      published_frame=0;//to limit fps
      checkBrightness();
    }
  }

  /*!************************************************************************
   *  \brief   Checks the mean of the brightness and set the color depending on the brightness threshold
   *  \details Standard OpenCv to check the brightness of an image. 
   *           Check OpenCv docs the get further information.
   *  \param None. Simply takes the image received in the message.
   *************************************************************************/
  void ImageConverter::checkBrightness(){//Control the color of the overlay
    cv::Mat hsv_img;
    std::vector<cv::Mat> channels;//vector of HSV channels
    cv::cvtColor(cv_ptr -> image, hsv_img, CV_BGR2HSV_FULL); //Transformation of the image from BGR to HSV format. 
    cv::split(hsv_img, channels);//Save channels splitted in "channels"
    cv::Scalar m = cv::mean(channels[2]);//mean of the brightness 
    color= (m[0]<BRIGHTNESS_LEVEL) ? TEXT_COLOR : DARK_COLOR; //Set the color 
  }
  
  /*!************************************************************************
 *  \brief   Wrapper for OpenCv putText
 *  \details  This method puts a text with default parameters. Just needs a cv::Mat,
 *            the text and the point where to be displayed. Line type is fixed
 *            with CV_AA (Antialise). Font is fixed also. Check OpenCv Docs
 *            for further information.
 *  \param A cv::Mat where to be displayed
 *  \param text to be displayed
 *  \param A cv::Point to be placed in the mat
 *  \param (Optional) The scale of the text, the color and the thickness of the lines of the text.
 *************************************************************************/

void ImageConverter::putText(cv::Mat &img, const std::string &text, cv::Point point, double text_size=font_scale, cv::Scalar color_=color, int thickness=TEXT_THICKNESS){
  cv::putText(img, text, point, FONT, text_size, color_, thickness,  LINE_TYPE);//original
}

/*!************************************************************************
 *  \brief   Overlay an image into another. 
 *  \details  Can be used to copy an image to a ROI without overwritting 
 *            the transparent (alpha=0) pixels. Runs two nested for loops
 *            that takes the value of the opacity of the overlay in each 
 *            pixel and sets the value of the raw image.
 *  \warning DONT TOUCH this method, it is ok as it is.
 *  \param A cv::Mat to be overlayed. Raw image.
 *  \param A cv::Mat to overlay into the first. HUD matrix in this case.
 *  \param A cv::Point that acts as an offset. Should be cv::Point() if the whole matrix is being treated.
 *************************************************************************/
void ImageConverter::overlayImage(cv::Mat* src, cv::Mat* overlay, const cv::Point& location)
{
  for (int y = cv::max(location.y, 0); y < src -> rows; ++y)
  {
    int fY = y - location.y;
    if (fY >= overlay -> rows)
      break;
    for (int x =cv:: max(location.x, 0); x < src -> cols; ++x)
    {
      int fX = x - location.x;
      if (fX >= overlay -> cols)
        break;

      double opacity = ( (double) overlay -> data[fY * overlay -> step + fX * overlay -> channels() + 3]) / 255;
      for (int c = 0; opacity > 0 && c < src -> channels(); ++c)
      {
        unsigned char overlayPx = overlay -> data[fY * overlay -> step + fX * overlay -> channels() + c];
        unsigned char srcPx = src -> data[y * src -> step + x * src -> channels() + c];
        src -> data[y * src -> step + src -> channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
      }
    }
  }
}
    
/*!************************************************************************
 *  \brief  Returns a vector of n elements with equally distributed numbers between min and max
 *  \details  Nothing in particular. Just note this method was "casted" 
 *            to accept and return integers.
 *  \param an integer representing the minimum 
 *  \param an integer representing the maximum
 *  \param an integer representing the number of elements to be returned
 *************************************************************************/
std::vector<int> ImageConverter::linspace(int min, int max, int n)
{
  std::vector<int> result;
  int iterator = 0;
  int rev=1;
  int temp;
  // if(min>max)
  //   rev=0;
  for (int i = 0; i <= n-2; i++)
  {
    if(rev){
      temp = min + i * (max - min) / (round( (double) n) - 1);
    }else{
      temp = max + i * (min - max) / (round( (double) n) - 1);
    }
    result.insert(result.begin() + iterator, temp);
    iterator += 1;
  }
  if(rev)
    result.insert(result.begin() + iterator, max);
  else
    result.insert(result.begin() + iterator, min);
  int i;
  for (std::vector<int>::const_iterator i = result.begin(); i != result.end(); ++i)
    std::cout << *i << ' ';
  std::cout<<"max "<<max<<"min "<<min<<"\n";
  return result;
}

//Edit to add fixed content to overlay
void ImageConverter::generateOverlay(cv::Mat &overlay){
  //Unused 
}

//Just distributes the drawing methods to get code organized
void ImageConverter::refreshVariables(cv::Mat &overlay, int im_no){//Add dynamic content each frame
  DrawRightPannel(overlay);
  DrawLeftPannel(overlay);
  DrawCenterPannel(overlay, im_no);
}

//Sets the variables necessary to draw the indicators
void ImageConverter::DrawCenterPannel(cv::Mat &overlay, int im_no){
  ell_center=cv::Point(overlay.cols*0.5, overlay.rows*0.5); //Center of roll circumference
  ell_init=ell_center+cv::Point(overlay.cols/4, 0); //Initial rotating point. Goneometric circumference like.
  initial_angle=240.0, final_angle=300.0; //Angles of the roll display depending on the initial point
  DrawRollIndicator(overlay, im_no);
  DrawHorizonLine(overlay, im_no);
  DrawYawIndicator(overlay, im_no);
}

/*!************************************************************************
 *  \brief  Draws left pannel
 *  \details  Depending on the size of the longest text draws text and 
 *            moves the drawing point down.
 *  \param The cv::Mat in which we draw
 *************************************************************************/
void ImageConverter::DrawLeftPannel(cv::Mat &overlay){
  draw_left=start_left;
  cv::Size offset=cv::getTextSize("Battery: ", FONT, font_scale, TEXT_THICKNESS, NULL); //Needed to move the pointer
  std::string battery_str=" " + std::to_string(battery_status) + " %"; 
  if(battery_status<0)
    battery_str="N/A"; //To be displayed when not initialized
  putText( overlay, "Battery:",  draw_left);
  putText( overlay, battery_str, draw_left + cv::Point(offset.width,0) );
  draw_left=draw_left + cv::Point(0, textSize.height*2);
  putText( overlay, "Roll:", draw_left);
  if(roll != -1000) //To be displayed when initialized
    putText( overlay, std::to_string(tmp_roll) + " deg" , draw_left + cv::Point(offset.width, 0)); 
  draw_left=draw_left + cv::Point(0, textSize.height*2);
  putText( overlay, "Yaw:", draw_left);
  if(yaw != -1000)  //To be displayed when initialized
    putText( overlay, std::to_string(yaw) + " deg" , draw_left + cv::Point(offset.width, 0)); 
  draw_left=draw_left + cv::Point(0, textSize.height*2);
  putText( overlay, "Pitch:", draw_left);
  if(pitch != -1000)  //To be displayed when initialized
    putText( overlay, std::to_string(tmp_pitch) + " deg" , draw_left + cv::Point(offset.width, 0));
  draw_left=draw_left + cv::Point(0, textSize.height*2);
  putText( overlay, "FPS:", draw_left);
  putText( overlay, std::to_string(real_fps), draw_left + cv::Point(offset.width, 0)); //Add action
  // draw_left=draw_left + cv::Point(0, textSize.height*2); //For another put text
}

//Same as DrawLeftPannel
void ImageConverter::DrawRightPannel(cv::Mat &overlay){
  draw_right=start_right;
  cv::Size offset=cv::getTextSize("V: ", FONT, font_scale, TEXT_THICKNESS, NULL);
  putText( overlay, "T:", draw_right);
  putText( overlay, std::to_string(minutes) + ":" + ((seconds<10)?"0":"") + std::to_string(seconds), draw_right + cv::Point(offset.width, 0) );
  draw_right=draw_right + cv::Point(0, textSize.height*2);
  putText( overlay, "X:", draw_right);
  putText(overlay, doToStr(pos_x, 2) + " m",  draw_right + cv::Point(offset.width, 0));
  draw_right=draw_right + cv::Point(0, textSize.height*2);
  putText( overlay, "Y:", draw_right);
  putText(overlay, doToStr(pos_y, 2) + " m",  draw_right + cv::Point(offset.width, 0));
  draw_right=draw_right + cv::Point(0, textSize.height*2);
  putText( overlay, "Z:", draw_right);
  putText(overlay, doToStr(pos_z, 2) + " m",  draw_right + cv::Point(offset.width, 0));
  draw_right=draw_right + cv::Point(0,  textSize.height*2);
  putText( overlay, "V: " + doToStr(spd, 2) + " m/s" ,draw_right);
  //draw_right=draw_right + cv::Point(0, textSize.height*2);
}

/*!************************************************************************
 *  \brief  Draws roll indicator
 *  \details First checks the changes in the state machine. Second if the 
             roll is between -30 and 30.
 *  \param The cv::Mat in which we draw
 *  \param the number if image to display
 *************************************************************************/
void ImageConverter::DrawRollIndicator(cv::Mat &overlay, int im_no){ //240 to 300 degrees
  // double delta=(final_angle - initial_angle)/60.0;//Delta=1
  double rot_ang=-1.0;

  if(tmp_roll != roll && roll_change==0 && roll != -1000){
    roll_transform=linspace(tmp_roll, roll, ROLL_REFRESH_RATE);
    int i;
    while(i<ROLL_REFRESH_RATE*3/2)
      {
        i++;
        roll_transform.insert(roll_transform.end(), pitch);
      }
    roll_change=1;
  }
  //if it is in transition, phase++ 
  if(roll_change){
    tmp_roll=roll_transform[roll_change_phase++];
  }
  else if(roll != -1000){//if not in transition
    tmp_roll=roll;
  }
  
  if (tmp_roll<=30.0 && tmp_roll>=-30)//needed for reescale
    rot_ang=270 + tmp_roll;//270 + roll
  double x, y, norm,
    factor=8.0;//Proportion of the arrow depending on the vector (Which is unitary so it is the length of the line)
  if(rot_ang>=0){//draw the arrow if arrow is in range
    cv::Point origin=rotatePoint(ell_center, ell_init, rot_ang);
    cv::Point vec=(origin - ell_center);
    norm=cv::norm(vec);
    x=std::round(vec.x * factor/ norm), y=std::round(vec.y * factor / norm);
    vec=cv::Point( (int) x, (int) y);
    cv::arrowedLine(overlay,  origin - 3*vec, origin - vec, color, 1 + im_no, CV_AA, 0, 0.3);
  }
  int i;
  for(i=initial_angle;i<=final_angle;i += 10){//Marker loop
    cv::Point origin=rotatePoint(ell_center, ell_init, i);
    cv::Point vec=(origin - ell_center);
    norm=cv::norm(vec);
    x=std::round(vec.x /norm * factor), y=std::round(vec.y /norm * factor);
    vec=cv::Point((int)x, (int)y);
    std::string text= std::to_string((int)(i - 30-initial_angle));
    cv::Size halfTextSize = cv::getTextSize(text,  FONT, font_scale/2,  TEXT_THICKNESS, NULL);
    putText( overlay, text,   origin-vec + cv::Point( -halfTextSize.width/2, halfTextSize.height/2), font_scale/2);
    cv::line(overlay, origin, origin + vec,  color, 1 + im_no, CV_AA, 0);
  }
  if(roll_change_phase==(ROLL_REFRESH_RATE*3/2-1) && roll_change){//Restablece el sistema
    roll_change_phase=0;
    roll_change=0;
    tmp_roll=roll;
  }
}//END METHOD

/*!************************************************************************
 *  \brief  Draws pitch indicator
 *  \details First checks the changes in the state machine.
 *  \param The cv::Mat in which we draw
 *  \param the number if image to display
 *  \note The state machine algorithm isn't perfect but it does the job.
 *************************************************************************/
//inside a bounding box with size equals distance between the limit points of the roll indicator
//In part 1 we take measures for the Horizon line and later the pitch lines
void ImageConverter::DrawHorizonLine(cv::Mat &overlay, int im_no){
  /*  PART 1:Horizon Line   */
  cv::Point origin=rotatePoint(ell_center, ell_init, initial_angle);
  cv::Point end=rotatePoint(ell_center, ell_init, final_angle);
  int distance=end.x-origin.x;
  origin=ell_center-cv::Point(distance/2, 0);
  end=ell_center + cv::Point(distance/2, 0);
  cv::Point pitched_center=ell_center + cv::Point(0, overlay.rows/2/POV_ANGLE*-1*tmp_pitch);
  cv::Point hline_init(overlay.cols/2*std::sqrt(2), 0);
    
  cv::Point roll_l, roll_r;
  /*  PART 2: Pitch indicator    */
  //This method reuses the data of the horizon line so it needs to be in the same method
  int line_length=25; //Length of the pitch line
  double sml_tx=2.0/3; //Proportion of the pitch indicator text scale.
  pitch_offset=0;
  cv::Point marker[PITCH_NO];
  cv::Size mehTextSize= getTextSize("-100",  FONT, font_scale*sml_tx,  TEXT_THICKNESS, NULL);
  cv::Point init_markers=cv::Point(ell_center.x-line_length/2, origin.y-overlay.rows*0.2);//Where the pitch indicator centers
  //STATE MACHINE: PITCH
  //If there is any variation
  if(im_no==BIG && pitch != -1000){
    if(tmp_pitch != pitch && pitch_change==0 && pitch != -1000){
      pitch_transform=linspace(tmp_pitch, pitch, PITCH_REFRESH_RATE);
      int i=PITCH_REFRESH_RATE;
      while(i<PITCH_REFRESH_RATE*3/2)//Some filler to visualize correctly the result
      {
        i++;
        pitch_transform.insert(pitch_transform.end(), pitch);
      }
      pitch_change=1;
    }
    //if it is in transition,  phase++
    if(pitch_change){
      tmp_pitch=pitch_transform[pitch_change_phase];
      pitch_change_phase++;
      if(pitch_change_phase<PITCH_REFRESH_RATE){
        pitch_offset=(double) distance * pitch_change_phase/ PITCH_REFRESH_RATE /8 /PITCH_SCALE;
        pitch_offset = (pitch >= tmp_pitch) ? (pitch_offset) : (-pitch_offset);
      }
    }
    if(roll != -1000 && pitch != -1000){
      roll_r=rotatePoint(pitched_center, pitched_center + hline_init * HORIZON_LINE_SCALE, -tmp_roll);
      roll_l=rotatePoint(pitched_center, pitched_center + hline_init * HORIZON_LINE_SCALE, -tmp_roll + 180);
    }//1 + im_no is a hack. WARNING
    //This part is focused on text
    std::string text;
    for(int i=0;i<PITCH_NO;i++){//Number of text objects loop
      //TODO The angle values 180 y -180 aren't reescaled in the text, those cases should be treated apart
      if (pitch_change_phase && pitch_offset > 0)//Going down
        text  = std::to_string( (pitch_transform[pitch_change_phase-1]
                                 + ( (PITCH_NO-4)-i) * PITCH_SCALE) % 180);
      else if(pitch_change_phase && pitch_offset < 0) //Going up
        text  = std::to_string( (pitch_transform[pitch_change_phase-1]
                                 + (i-(PITCH_NO-3)) * PITCH_SCALE) % 180);
      else //Stating still
        text= std::to_string((tmp_pitch + (2-i) * PITCH_SCALE)%180);
      cv::Size halfTextSize= getTextSize(text,  FONT, font_scale * sml_tx,  TEXT_THICKNESS, NULL);
      if(text[0] == '-')//If number is negative, it gets shifted to the left
         marker[i] = marker[i] - cv::Point(cv::getTextSize("-",  FONT,  font_scale * sml_tx,  TEXT_THICKNESS, NULL).width, 0);
      if(pitch_offset >= 0){
        marker[i]=cv::Point(init_markers.x/*-line_length/2*/, 
                            (int)(init_markers.y-distance/4 + (distance/8) * i + pitch_offset));//Structure the marker points
        if(i < (PITCH_NO-1) || pitch_change_phase < PITCH_REFRESH_RATE/2)
          putText( overlay, text,   marker[i] + cv::Point(line_length/2 - halfTextSize.width/2, halfTextSize.height/2), font_scale * sml_tx);
      }
      else{
        marker[i]=cv::Point(init_markers.x/*-line_length/2*/, 
                            (int)(init_markers.y + distance/4-(distance/8) * i + pitch_offset));//Structure the marker points
        if(i < (PITCH_NO-1)||(i == 0 && pitch_change_phase < PITCH_REFRESH_RATE/2))
          putText( overlay, text,   marker[i] + cv::Point(line_length/2 - halfTextSize.width/2, halfTextSize.height/2), font_scale * sml_tx);
      }

      if(i==2){
        cv::line(overlay,  marker[2] + cv::Point(-mehTextSize.width/2, -mehTextSize.height-pitch_offset), 
                 marker[2] + cv::Point(line_length + mehTextSize.width/3, -mehTextSize.height-pitch_offset),  color, 1 + im_no);//linea de arribax
        cv::line(overlay,  marker[2] + cv::Point( -mehTextSize.width/2,  + mehTextSize.height-pitch_offset),
                 marker[2] + cv::Point(line_length + mehTextSize.width/3,  + mehTextSize.height-pitch_offset),  color, 1 + im_no);//linea de abajo
      }
    }
     if(roll != -1000 && pitch != -1000)
      cv::line(overlay,  roll_l,  roll_r,  color, 1 + im_no, CV_AA);//Draw the horizon line
    if(pitch_change_phase==(PITCH_REFRESH_RATE*3/2-1) && pitch_change){//Restablece el sistema
      pitch_change_phase=0;
      pitch_change=0;
     }
    printf("pitch_change%d  pitch_change_phase %d tmp_pitch %d pitch_offset %f pitch %d\n",pitch_change, pitch_change_phase,tmp_pitch,pitch_offset,pitch);

  }
 

}//END METHOD;;

/*!************************************************************************
 *  \brief  Draws yaw indicator
 *  \details Draws a circle, a number of markers and finally an arrow.
 *           Puts text on each marker depending on the value.
 *  \param The cv::Mat in which we draw
 *  \param the number if image to display
 *************************************************************************/
void ImageConverter::DrawYawIndicator(cv::Mat &overlay, int im_no){
  double radius=overlay.cols * 0.075;//Proportions require it to be less than 10% of the width
  cv::Point center(overlay.cols * 0.5, overlay.rows/4 * 3); //Centered and shifthed one quarter down
  cv::circle (overlay,  center, radius,  color, 1, CV_AA);//Given the center and the radius, draw the circle
  cv::Point init(0, -radius);
  int marker_n;
  if(im_no==SMALL)
    marker_n=8;
  else if (im_no==BIG)
    marker_n=16;
  for(int i=0;i < marker_n; i +=1){
    cv::Point tmp(rotatePoint(center, center + init, (int) std::round(360.0*i/marker_n) ));
    cv::Point vec(tmp - center);
    int norm=cv::norm(vec);
    int x=std::round(vec.x * 4 /norm);
    int y=std::round(vec.y * 4 /norm);
    vec=cv::Point(x, y);
    cv::line(overlay,  tmp,  tmp + vec*2,  color);
    cv::Size halfTextSize = cv::getTextSize(std::to_string((int)std::round(360.0*i/marker_n)),  FONT, font_scale/2,  TEXT_THICKNESS, NULL);
    putText( overlay, std::to_string((int)std::round(360.0*i/marker_n)),
             tmp + 5 * vec + cv::Point(-halfTextSize.width/2, halfTextSize.height/2), font_scale*2/3, color);
  }
  cv::Point tmp(rotatePoint(center, center + init, (yaw>0 ? yaw:360 + yaw)));
  if(yaw != -1000)
    cv::arrowedLine(overlay,  center, tmp ,  color, 1 + im_no, CV_AA, 0, 0.2);
}
//TOOLS
double ImageConverter::DegToRad(double deg){//converts a degree angle to radians
  return (double)deg/360.0 * 2 * M_PI;
}
double ImageConverter::RadToDeg(double rad){//converts a degree angle to radians
  return (double)rad * 360.0 /2 /M_PI;
}
//converts double to string with n_dec decimal numbers 
std::string ImageConverter::doToStr(double a, int n_dec){
  std::stringstream stream;
  stream<< std::fixed << std::setprecision(2) << a;
  return stream.str();
}

//method to rotate a point 'point' with center 'center' and through positive angle 'angle'
//Note that this method is only valid with y-axes inverted,  otherwise the minus would have to be removed
cv::Point ImageConverter::rotatePoint(cv::Point center, cv::Point point, double angle){
  if(angle<0)
    angle=360 + angle;
  angle=DegToRad(angle);
  int x=(point.x-center.x) * std::cos(angle) - (point.y - center.y) * sin(angle) + center.x;
  int y=(point.x-center.x) * std::sin(angle) + (point.y - center.y) * cos(angle) + center.y;//We need the minus because the y-axe is inverted
  return cv::Point(x, y);
}

void ImageConverter::imageOverlayCbBlack(const image_transport::Publisher &image_pub_small_, const image_transport::Publisher &image_pub_big_) //Transformation of the image callback
  {

    auto t1 = Clock::now();    // Start the frame timer
    cv::Mat image= cv::imread("/home/cefiro/workspace/ros/aerostack_catkin_ws/src/aerostack_stack/stack/ground_control_system/HUD/first_view/icons/black.png", CV_LOAD_IMAGE_COLOR);
    const sensor_msgs::ImageConstPtr& black_img  = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
    try
    {
      //const sensor_msgs::ImageConstPtr& black_img  = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
      cv_ptr = cv_bridge::toCvCopy(black_img, sensor_msgs::image_encodings::BGRA8);//Create a pointer that points the copy of the Ros MSG to OpenCv
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    secondOperations(); //Operations done each frame to check the timers

    //Check if fixed overlay is empty or create it
    CheckUnderlay();//Is fixed overlay empty?
    
    CheckOverlay(image_big,BIG); //Check the bigger font image  overlay
    //  if(cv::waitKey(1)=='p'||yeah){
    //   cv::imshow(OPENCV_WINDOW, cv_ptr -> image);
    //   yeah=true;
    //   hum=false;
    // }
    image_pub_big_.publish(cv_ptr -> toImageMsg());//Publish the  bigger font image

    /*Part 2: Small Image*/
    CheckOverlay(image_small,SMALL); //Check the small font image overlay
    // if(cv::waitKey(1)=='o'||hum){
    //   cv::imshow(OPENCV_WINDOW, cv_ptr -> image);
    //   hum=true;
    //   yeah=false;
    // }
    image_pub_small_.publish(cv_ptr -> toImageMsg());//Publish the smaller font image 

    //Time and fps limit. Estadistical purposes
    auto t2 = Clock::now();//End the frame timer
    frame_time=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count(); //Can be measured in seconds, milliseconds, nanoseconds
    total_time+=frame_time; 
    measures++;//Frames treated 
    // if(FPS_CAP)//Check the time
    // {
    //   //Total frame time - actual frame time - previous wait
    //   if(floor(1.0/FPS_CAP*1000.0-frame_time-1)<=0)
    //     printf("Excesive frame_time\n");
    //   
  }