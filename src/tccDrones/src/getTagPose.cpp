#include <math.h>
#include <time.h>
#include <iostream>
#include <std_msgs/Float32.h>

#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
  
using namespace std;

#define TAG0 0
#define TAG1 0
#define TAG2 0
#define TAG3 0

geometry_msgs::Point tagPoseChild0;
geometry_msgs::Point tagPoseChild1;
geometry_msgs::Point tagPoseChild2;
geometry_msgs::Point tagPoseChild3;

void tagPoseCallback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg)
{
  for (int i = 0; i < msg->markers.size(); i++)
  {
    if(msg->markers[i].id == TAG0){
      tagPoseChild0.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild0.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild0.z = msg->markers[i].pose.pose.position.z;
    }
    if(msg->markers[i].id == TAG1){
      tagPoseChild1.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild1.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild1.z = msg->markers[i].pose.pose.position.z;
    }
    if(msg->markers[i].id == TAG2){
      tagPoseChild2.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild2.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild2.z = msg->markers[i].pose.pose.position.z;
    }
    if(msg->markers[i].id == TAG3){
      tagPoseChild3.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild3.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild3.z = msg->markers[i].pose.pose.position.z;
    }
  }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "getTagPose");
    ros::NodeHandle nh(""), nh_param("~");
    ros::Rate loop_rate(10);

    ros::Publisher pubPoseChild0;
    ros::Publisher pubRotChild0; 

    ros::Publisher pubPoseChild1;
    ros::Publisher pubRotChild1;

    ros::Publisher pubPoseChild2;
    ros::Publisher pubRotChild2;

    ros::Publisher pubPoseChild3;
    ros::Publisher pubRotChild3;

    ros::Subscriber tags;

    tags = nh.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, &tagPoseCallback);

    pubPoseChild0 = nh.advertise<geometry_msgs::Point>("/tag0/pose", 1);
    pubRotChild0 = nh.advertise<std_msgs::Float32>("/tag0/rot", 1);

    pubPoseChild1 = nh.advertise<geometry_msgs::Point>("/tag1/pose", 1);
    pubRotChild1 = nh.advertise<std_msgs::Float32>("/tag1/rot", 1);

    pubPoseChild2 = nh.advertise<geometry_msgs::Point>("/tag2/pose", 1);
    pubRotChild2 = nh.advertise<std_msgs::Float32>("/tag2/rot", 1);

    pubPoseChild3 = nh.advertise<geometry_msgs::Point>("/tag3/pose", 1);
    pubRotChild3 = nh.advertise<std_msgs::Float32>("/tag3/rot", 1);

    while(ros::ok())
    {
        ros::spinOnce();

        ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", tagPoseChild0.x, tagPoseChild0.y, tagPoseChild0.z);

        pubPoseChild0.publish(tagPoseChild0);
        
        // ROS_WARN("...Publicado");

    }
    
    return 0;
}