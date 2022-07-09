#include <math.h>
#include <time.h>
#include <string>
#include <fstream>
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

geometry_msgs::Point poseMother;
geometry_msgs::Point poseGPSChild;

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

void MotherPoseCallback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseMother.x = msg->x;
  poseMother.y = msg->y;
  poseMother.z = msg->z; 
}

void ChildPoseCallback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseGPSChild.x = msg->x;
  poseGPSChild.y = msg->y;
  poseGPSChild.z = msg->z;  
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
    string nameFile;
    string data;
    string first ;
    string second ;
    ofstream logFile; 

    ros::init(argc, argv, "manager");
    ros::NodeHandle nh(""), nh_param("~");
    ros::Rate loop_rate(10);

    ros::Publisher gotoChild0;
    ros::Publisher gotoChild1;
    ros::Publisher gotoChild2;
    ros::Publisher gotoChild3;

    ros::Publisher gotoMother;


    ros::Subscriber tags;
    ros::Subscriber posMon;
    ros::Subscriber posKid;

    tags = nh.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, &tagPoseCallback);
    posMon = nh.subscribe<geometry_msgs::Point>("/mother/checkPose", 1, &MotherPoseCallback);
    posKid = nh.subscribe<geometry_msgs::Point>("/child0/checkPose", 1, &ChildPoseCallback);

    gotoChild0 = nh.advertise<geometry_msgs::Point>("/child0/position", 1);

    gotoMother = nh.advertise<geometry_msgs::Point>("/mother/position", 1);


    std::vector<geometry_msgs::Point> route0;
    std::vector<geometry_msgs::Point> route1;
    std::vector<geometry_msgs::Point> route2;
    std::vector<geometry_msgs::Point> route3;


    includePoints(&route0, 1.0, 1.0, 6.0);
    includePoints(&route0, -1.0, 1.0, 6.0);
    includePoints(&route0, -1.0, -1.0, 6.0);
    includePoints(&route0, 1.0, -1.0, 6.0);
    includePoints(&route0, 1.0, 1.0, 6.0);
    includePoints(&route0, 0.0, 0.0, 6.0);

    includePoints(&route1, 1.0, 1.0, 6.0);
    includePoints(&route1, -1.0, -1.0, 6.0);
    includePoints(&route1, 1.0, -1.0, 6.0);
    includePoints(&route1, -1.0, 1.0, 6.0);
    includePoints(&route1, 1.0, 1.0, 6.0);
    includePoints(&route1, 0.0, 0.0, 6.0);

    includePoints(&route2, 1.0, 1.0, 6.0);
    includePoints(&route2, -1.0, 1.0, 6.0);
    includePoints(&route2, -1.0, 0.0, 6.0);
    includePoints(&route2, 1.0, 0.0, 6.0);
    includePoints(&route2, 1.0, -1.0, 6.0);
    includePoints(&route2, -1.0, -1.0, 6.0);
    includePoints(&route2, 0.0, 0.0, 6.0);

    // includePoints(&route3, 1.0, 0.0, 9.0);
    // includePoints(&route3, 1.0, 2.0, 9.0);
    // includePoints(&route3, 2.0, 2.0, 9.0);
    // includePoints(&route3, 2.0, -2.0, 9.0);
    // includePoints(&route3, 3.0, -2.0, 9.0);
    // includePoints(&route3, 3.0, 0.0, 9.0);
    // includePoints(&route3, 4.0, 0.0, 9.0);

    includePoints(&route3, 2.0, 2.0, 9.0);
    includePoints(&route3, -2.0, 2.0, 9.0);
    includePoints(&route3, -2.0, -2.0, 9.0);
    includePoints(&route3, 2.0, -2.0, 9.0);
    includePoints(&route3, 2.0, 2.0, 9.0);
    includePoints(&route3, 0.0, 0.0, 9.0);


    int i = 1;
    int j = 1;
    int estado = 0;
    int estadoRota = 0;
    ofstream * piroca;

    while(ros::ok())
    {
        ros::spinOnce();

        switch (estado)
        {
        case 0:
          cout << "Quadrado -> 1\nZigzag -> 2\nPercurso -> 3\n" << "Rotina de teste:";
          cin >> estado;
          estadoRota = 0;
          time_t rawtime;
          time (&rawtime);
          data = ctime (&rawtime);
          i=0;
          j=1;
        break;

        case 1:
          cout << "QUADRADO\n";          
          if (i)
          {
            first = "src/tccDrones/logsPos/log";
            second = ".csv";
            nameFile = first + data + second;
            logFile.open (nameFile, ios::out | ios::app);
            logFile << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            i = 0;
          }
          if(estadoRota < route0.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route0[estadoRota].x, route0[estadoRota].y, route0[estadoRota].z);
            gotoChild0.publish(route0[estadoRota]);
            // logFile << tagPoseChild0.x  << ";" << tagPoseChild0.y << ";" << tagPoseChild0.z << ";" <<
            //            poseGPSChild.x   << ";" << poseGPSChild.y  << ";" << poseGPSChild.z  << ";" <<
            //            poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
            //            route0[estadoRota].x          << ";" << route0[estadoRota].y         << ";" << route0[estadoRota].z         << "\n";

            if((abs(tagPoseChild0.x - route0[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route0[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            // logFile.close();
            estado = 0;
          }          
          break;

        case 2:
          cout << "ZIGZAG\n";
          if (i)
          {
            first = "src/tccDrones/logsPos/log";
            second = ".csv";
            nameFile = first + data + second;
            logFile.open (nameFile, ios::out | ios::app);
            logFile << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            i = 0;
          }
          if(estadoRota < route1.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route1[estadoRota].x, route1[estadoRota].y, route1[estadoRota].z);
            gotoChild0.publish(route1[estadoRota]);
            // logFile << tagPoseChild0.x  << ";" << tagPoseChild0.y << ";" << tagPoseChild0.z << ";" <<
            //            poseGPSChild.x   << ";" << poseGPSChild.y  << ";" << poseGPSChild.z  << ";" <<
            //            poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
            //            route1[estadoRota].x          << ";" << route1[estadoRota].y         << ";" << route1[estadoRota].z         << "\n";

            if((abs(tagPoseChild0.x - route1[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route1[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            // logFile.close();
            estado = 0;
          }
          break;

        case 3:
          cout << "PERCURSO\n";
          if (i)
          {
            first = "src/tccDrones/logsPos/log";
            second = ".csv";
            nameFile = first + data + second;
            logFile.open (nameFile, ios::out | ios::app);
            logFile << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            i = 0;
          }
          if(estadoRota < route2.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route2[estadoRota].x, route2[estadoRota].y, route2[estadoRota].z);
            gotoChild0.publish(route2[estadoRota]);
            // logFile << tagPoseChild0.x  << ";" << tagPoseChild0.y << ";" << tagPoseChild0.z << ";" <<
            //            poseGPSChild.x   << ";" << poseGPSChild.y  << ";" << poseGPSChild.z  << ";" <<
            //            poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
            //            route2[estadoRota].x          << ";" << route2[estadoRota].y         << ";" << route2[estadoRota].z         << "\n";

            if((abs(tagPoseChild0.x - route2[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route2[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            // logFile.close();
            estado = 0;
          }
          break;

        case 4:
          cout << "FOLLOW\n";
          if (j)
          {
            first = "src/tccDrones/logsPos/log";
            second = ".csv";
            nameFile = first + data + second;
            logFile.open (nameFile, ios::out | ios::app);
            logFile << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            j = 0;
          }
          if(estadoRota < route3.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route3[estadoRota].x, route3[estadoRota].y, route3[estadoRota].z);
            gotoMother.publish(route3[estadoRota]);
            logFile << tagPoseChild0.x  << ";" << tagPoseChild0.y << ";" << tagPoseChild0.z << ";" <<
                       poseGPSChild.x   << ";" << poseGPSChild.y  << ";" << poseGPSChild.z  << ";" <<
                       poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
                       route3[estadoRota].x          << ";" << route3[estadoRota].y         << ";" << route3[estadoRota].z << "\n";

            if((abs(poseMother.x - route3[estadoRota].x) < 0.15) && (abs(poseMother.y - route3[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            logFile.close();
            estado = 0;
          }
          break;

        default:
          break;
        }
        loop_rate.sleep();
    }    
    return 0;
}