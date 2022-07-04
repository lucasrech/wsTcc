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

void includePoints(std::vector<geometry_msgs::Point>* line_ID0, float x, float y, float z)
{
    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    line_ID0->push_back(point);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "manager");
    ros::NodeHandle nh(""), nh_param("~");
    ros::Rate loop_rate(10);

    ros::Publisher gotoChild0;
    ros::Publisher gotoChild1;
    ros::Publisher gotoChild2;
    ros::Publisher gotoChild3;

    ros::Subscriber tags;

    tags = nh.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, &tagPoseCallback);

    gotoChild0 = nh.advertise<geometry_msgs::Point>("/child0/position", 1);

    std::vector<geometry_msgs::Point> route0;

    includePoints(&route0, 1.5, 1.5, 6.0);
    includePoints(&route0, -1.5, 1.5, 6.0);
    includePoints(&route0, -1.5, -1.5, 6.0);
    includePoints(&route0, 1.5, -1.5, 6.0);
    includePoints(&route0, 1.5, 1.5, 6.0);
    includePoints(&route0, 0.0, 0.0, 6.0);

    int estado = 0;
    int estadoRota = 0;

    int envieiPonto = 0;
    int cheguei = 0;

    int i;

    while(ros::ok())
    {
        ros::spinOnce();

        if(estadoRota < route0.size())
        {
          ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route0[estadoRota].x, route0[estadoRota].y, route0[estadoRota].z);
          gotoChild0.publish(route0[estadoRota]);

          if((abs(tagPoseChild0.x - route0[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route0[estadoRota].y) < 0.15))
            estadoRota++;
          
        }


        else
          break;

        loop_rate.sleep();
    }
    
    return 0;
}