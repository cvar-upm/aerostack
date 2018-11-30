#include <gtest/gtest.h>
#include "../include/twist_adapter_process.h"
#include <cstdio>
#include <iostream>

/*Parameters*/
ros::NodeHandle* nh;
class TwistListener{
public:
    ros::NodeHandle nh;
    //ros::Subscriber geometric_speed_sub;
    ros::Subscriber trajectory_controller_geometric_speed_sub;
    //bool messageReceived;
    bool trajectory_controller_messageReceived;



    TwistListener(){
      //messageReceived=false;
      trajectory_controller_messageReceived=false;
    }

   void start(){
     /*  geometric_speed_sub=nh.subscribe("/drone1/geometric_speed", 1,
                                                                        &TwistListener::geometricSpeedCallback, this);*/
       trajectory_controller_geometric_speed_sub=nh.subscribe("/drone1/trajectoryControllerTwistReferencesRebroadcast", 1,
                                                                        &TwistListener::trajectoryControllerSpeedCallback, this);

   }

 /*  void geometricSpeedCallback(const geometry_msgs::Twist& message)
    {

       messageReceived=true;

    }*/
   void trajectoryControllerSpeedCallback(const geometry_msgs::Twist& message)
    {

       trajectory_controller_messageReceived=true;

    }


};


TEST(adaptersTests, poseAdapterTests)
{ ros::NodeHandle nh;
  TwistListener tL;
  TwistAdapter twist_adapter;




  std::string estimated_speed_str;
  std::string trajectory_controller_speed_str;

  std::string drone_id;
  std::string drone_id_namespace;

  //ros::Publisher estimated_speed_pub;
  ros::Publisher trajectory_controller_pose_pub;

  droneMsgsROS::droneSpeeds speed_msg;

  nh.param<std::string>("drone_id", drone_id, "1");
  nh.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);
 // nh.param<std::string>("estimated_speed", estimated_speed_str, "estimated_speed");
  nh.param<std::string>("trajectoryControllerSpeedReferencesRebroadcast", trajectory_controller_speed_str, "trajectoryControllerSpeedReferencesRebroadcast");

//  estimated_speed_pub = nh.advertise<droneMsgsROS::droneSpeeds>('/'+drone_id_namespace+'/'+estimated_speed_str, 1);
  trajectory_controller_pose_pub = nh.advertise<droneMsgsROS::droneSpeeds>('/'+drone_id_namespace+'/'+trajectory_controller_speed_str, 1);

  speed_msg.dx=1;
  speed_msg.dy=1;
  speed_msg.dz=1;
  speed_msg.dyaw=1;
  speed_msg.dpitch=1;
  speed_msg.droll=1;

  twist_adapter.setUp();
  twist_adapter.start();

  tL.start();

  ros::Rate rate(30);

  twist_adapter.run();
 // estimated_speed_pub.publish(speed_msg);
  trajectory_controller_pose_pub.publish(speed_msg);


  ros::spinOnce();
  rate.sleep();
  ros::spinOnce();
  rate.sleep();
  ros::spinOnce();

  EXPECT_TRUE(tL.trajectory_controller_messageReceived);

}

/*--------------------------------------------*/
/*  Main  */
int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, ros::this_node::getName());
  nh = new ros::NodeHandle;

  return RUN_ALL_TESTS();
}
