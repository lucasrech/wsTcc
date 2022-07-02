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

    ros::Publisher gotoChild0;
    ros::Publisher gotoChild1;
    ros::Publisher gotoChild2;
    ros::Publisher gotoChild3;

    ros::Subscriber tags;

    tags = nh.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, &tagPoseCallback);

    std::vector<geometry_msgs::Point> route0;

    includePoints(&route0, 1.5, 1.5, 6.0);
    includePoints(&route0, -1.5, 1.5, 6.0);
    includePoints(&route0, -1.5, -1.5, 6.0);
    includePoints(&route0, 1.5, -1.5, 6.0);
    includePoints(&route0, 1.5, 1.5, 6.0);
    includePoints(&route0, 0.0, 0.0, 6.0);

    while(ros::ok())
    {
        ros::spinOnce();

        int estado = 0;

        switch (estado)
        {
        case 0:
            if(flag_square == 0)
            {
                //publica o proximo destino
                goto_pub_ID0.publish(line_ID0[state_square]);
                goto_pub_ID8.publish(line_ID8[state_square]);
                //garante que o pid foi atualizado
                if(pid_flag_ID0 == 0 && pid_flag_ID8 == 0)
                    flag_square = 1;
            }
            else
            {
            //verifica se chegou
                if(pid_flag_ID0 == 1 && pid_flag_ID8 == 1)
                {
                    flag_square = 0;
                    state_square++;
                    //verifica se terminou a rotina
                    if(state_square >= line_ID0.size())
                    {
                        state_square = 0;
                        state = PARA_PID;
                    }
                }
            }
            break;
        
        default:
            break;
        }









        // // ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", tagPoseChild0.x, tagPoseChild0.y, tagPoseChild0.z);
        // ROS_INFO("Rotacao: %f", toEuler(tagRotChild0).data);

        // pubPoseChild0.publish(tagPoseChild0);
        // pubRotChild0.publish(toEuler(tagRotChild0));
        
        // // ROS_WARN("...Publicado");
        loop_rate.sleep();
    }
    
    return 0;
}