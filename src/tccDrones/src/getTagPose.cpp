#include <math.h>
#include <time.h>
#include <iostream>
#include <std_msgs/Float32.h>

#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
  
using namespace std;

#define TAG0 10
#define TAG1 0
#define TAG2 13
#define TAG3 4

geometry_msgs::Point tagPoseChild0;
geometry_msgs::Point tagPoseChild1;
geometry_msgs::Point tagPoseChild2;
geometry_msgs::Point tagPoseChild3;

geometry_msgs::Point last;

geometry_msgs::Quaternion tagRotChild0;
geometry_msgs::Quaternion tagRotChild1;
geometry_msgs::Quaternion tagRotChild2;
geometry_msgs::Quaternion tagRotChild3;

void tagPoseCallback(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg)
{
  for (int i = 0; i < msg->markers.size(); i++)
  {
    // ROS_INFO("Tag: %d", msg->markers[i].id);
    if(msg->markers[i].id == TAG0){
      tagPoseChild0.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild0.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild0.z = msg->markers[i].pose.pose.position.z;
      tagRotChild0.x = msg->markers[i].pose.pose.orientation.x;
      tagRotChild0.y = msg->markers[i].pose.pose.orientation.y;
      tagRotChild0.z = msg->markers[i].pose.pose.orientation.z;
      tagRotChild0.w = msg->markers[i].pose.pose.orientation.w;
    }
    if(msg->markers[i].id == TAG1){
      tagPoseChild1.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild1.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild1.z = msg->markers[i].pose.pose.position.z;
      tagRotChild1.x = msg->markers[i].pose.pose.orientation.x;
      tagRotChild1.y = msg->markers[i].pose.pose.orientation.y;
      tagRotChild1.z = msg->markers[i].pose.pose.orientation.z;
      tagRotChild1.w = msg->markers[i].pose.pose.orientation.w;
    }
    if(msg->markers[i].id == TAG2){
      tagPoseChild2.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild2.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild2.z = msg->markers[i].pose.pose.position.z;
      tagRotChild2.x = msg->markers[i].pose.pose.orientation.x;
      tagRotChild2.y = msg->markers[i].pose.pose.orientation.y;
      tagRotChild2.z = msg->markers[i].pose.pose.orientation.z;
      tagRotChild2.w = msg->markers[i].pose.pose.orientation.w;
    }
    if(msg->markers[i].id == TAG3){
      tagPoseChild3.x = msg->markers[i].pose.pose.position.x;
      tagPoseChild3.y = msg->markers[i].pose.pose.position.y;
      tagPoseChild3.z = msg->markers[i].pose.pose.position.z;
      tagRotChild3.x = msg->markers[i].pose.pose.orientation.x;
      tagRotChild3.y = msg->markers[i].pose.pose.orientation.y;
      tagRotChild3.z = msg->markers[i].pose.pose.orientation.z;
      tagRotChild3.w = msg->markers[i].pose.pose.orientation.w;
    }
  }
}

std_msgs::Float32 toEuler(geometry_msgs::Quaternion q)
{
    std_msgs::Float32 rotZRads;
    // yaw (z-axis rotation, in rad).
    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);

    rotZRads.data = std::atan2(siny_cosp, cosy_cosp);

    return rotZRads;
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

        // ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", tagPoseChild2.x, tagPoseChild2.y, tagPoseChild2.z);
        // ROS_INFO("Rotacao: %f", toEuler(tagRotChild0).data);

        pubPoseChild0.publish(tagPoseChild0);
        pubRotChild0.publish(toEuler(tagRotChild0));

        pubPoseChild1.publish(tagPoseChild1);
        pubRotChild1.publish(toEuler(tagRotChild1));

        pubPoseChild2.publish(tagPoseChild2);
        pubRotChild2.publish(toEuler(tagRotChild2));

        pubPoseChild3.publish(tagPoseChild3);
        pubRotChild3.publish(toEuler(tagRotChild3));
        
        // ROS_WARN("...Publicado");

        loop_rate.sleep();
    }
    
    return 0;
}
