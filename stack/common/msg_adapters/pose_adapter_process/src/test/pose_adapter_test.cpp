#include <gtest/gtest.h>
#include "../include/pose_adapter_process.h"
#include <cstdio>

#include <iostream>

/*Parameters*/
ros::NodeHandle* nh;
class PoseListener{
public:
    ros::NodeHandle nh;

  //  ros::Subscriber geometric_pose_sub;
    ros::Subscriber trajectory_controller_geometric_pose_sub;
   // bool messageReceived;
    bool trajectory_controller_messageReceived;

    PoseListener(){
    //  messageReceived=false;
      trajectory_controller_messageReceived=false;
    }

   void start(){
      // geometric_pose_sub=nh.subscribe("/drone1/geometric_pose", 1,  &PoseListener::geometricPoseCallback, this);
       trajectory_controller_geometric_pose_sub=nh.subscribe("/drone1/trajectoryControllerPoseReferencesRebroadcast", 1,  &PoseListener::trajectoryControllerPoseCallback, this);
   }

   /*void geometricPoseCallback(const geometry_msgs::PoseStamped& message)
    {
        messageReceived=true;
    }*/

   void trajectoryControllerPoseCallback(const geometry_msgs::PoseStamped& message)
    {
        trajectory_controller_messageReceived=true;
    }


};


TEST(adaptersTests, poseAdapterTests)
{ ros::NodeHandle nh;
  PoseListener pL;
  PoseAdapter pose_adapter;



//  std::string estimated_pose_str;
  std::string trajectory_controller_pose_str;


  std::string drone_id;
  std::string drone_id_namespace;

  //ros::Publisher estimated_pose_pub;
  ros::Publisher trajectory_controller_pose_pub;


  droneMsgsROS::dronePose pose_msg;

  nh.param<std::string>("drone_id", drone_id, "1");
  nh.param<std::string>("drone_id_namespace", drone_id_namespace, "drone"+drone_id);

  //nh.param<std::string>("estimated_pose", estimated_pose_str, "estimated_pose");
  nh.param<std::string>("trajectoryControllerPositionReferencesRebroadcast", trajectory_controller_pose_str, "trajectoryControllerPositionReferencesRebroadcast");



  //estimated_pose_pub = nh.advertise<droneMsgsROS::dronePose>('/'+drone_id_namespace+'/'+estimated_pose_str, 1);
  trajectory_controller_pose_pub = nh.advertise<droneMsgsROS::dronePose>('/'+drone_id_namespace+'/'+trajectory_controller_pose_str, 1);

  pose_msg.x=1;
  pose_msg.y=1;
  pose_msg.z=1;
  pose_msg.roll=1;
  pose_msg.pitch=1;
  pose_msg.yaw=1;


  pose_adapter.setUp();
  pose_adapter.start();

  pL.start();

  ros::Rate rate(30);

  pose_adapter.run();
  //estimated_pose_pub.publish(pose_msg);
  trajectory_controller_pose_pub.publish(pose_msg);

  ros::spinOnce();
  rate.sleep();
  ros::spinOnce();
  rate.sleep();
  ros::spinOnce();

  EXPECT_TRUE( pL.trajectory_controller_messageReceived);

}

/*--------------------------------------------*/
/*  Main  */
int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, ros::this_node::getName());
  nh = new ros::NodeHandle;

  return RUN_ALL_TESTS();
}
