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
#define TAG2 13
#define TAG3 4

geometry_msgs::Point tagPoseChild0;
geometry_msgs::Point tagPoseChild1;
geometry_msgs::Point tagPoseChild2;
geometry_msgs::Point tagPoseChild3;

geometry_msgs::Point poseMother;
geometry_msgs::Point poseGPSChild0;
geometry_msgs::Point poseGPSChild1;
geometry_msgs::Point poseGPSChild2;
geometry_msgs::Point poseGPSChild3;


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

void ChildPose0Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseGPSChild0.x = msg->x;
  poseGPSChild0.y = msg->y;
  poseGPSChild0.z = msg->z;  
}

void ChildPose1Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseGPSChild1.x = msg->x;
  poseGPSChild1.y = msg->y;
  poseGPSChild1.z = msg->z;  
}

void ChildPose2Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseGPSChild2.x = msg->x;
  poseGPSChild2.y = msg->y;
  poseGPSChild2.z = msg->z;  
}

void ChildPose3Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  poseGPSChild3.x = msg->x;
  poseGPSChild3.y = msg->y;
  poseGPSChild3.z = msg->z;  
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

    ros::Publisher gotoMother;


    ros::Subscriber tags;
    ros::Subscriber posMon;
    ros::Subscriber posKid0;
    ros::Subscriber posKid1;
    ros::Subscriber posKid2;
    ros::Subscriber posKid3;

    tags = nh.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, &tagPoseCallback);
    posMon = nh.subscribe<geometry_msgs::Point>("/mother/checkPose", 1, &MotherPoseCallback);
    posKid0 = nh.subscribe<geometry_msgs::Point>("/child0/checkPose", 1, &ChildPose0Callback);
    posKid1 = nh.subscribe<geometry_msgs::Point>("/child1/checkPose", 1, &ChildPose1Callback);
    posKid2 = nh.subscribe<geometry_msgs::Point>("/child2/checkPose", 1, &ChildPose2Callback);
    posKid3 = nh.subscribe<geometry_msgs::Point>("/child3/checkPose", 1, &ChildPose3Callback);

    gotoChild0 = nh.advertise<geometry_msgs::Point>("/child0/position", 1);
    gotoChild1 = nh.advertise<geometry_msgs::Point>("/child1/position", 1);
    gotoChild2 = nh.advertise<geometry_msgs::Point>("/child2/position", 1);
    gotoChild3 = nh.advertise<geometry_msgs::Point>("/child3/position", 1);


    gotoMother = nh.advertise<geometry_msgs::Point>("/mother/position", 1);


    std::vector<geometry_msgs::Point> route0;
    std::vector<geometry_msgs::Point> route1;
    std::vector<geometry_msgs::Point> route2;
    std::vector<geometry_msgs::Point> route3;
    std::vector<geometry_msgs::Point> route4child0;
    std::vector<geometry_msgs::Point> route4child1;
    std::vector<geometry_msgs::Point> route4child2;
    std::vector<geometry_msgs::Point> route4child3;



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

    includePoints(&route4child0, 1.0, 0.0, 5.5);
    includePoints(&route4child0, 1.0, 0.0, 5.5);
    includePoints(&route4child0, 1.0, 1.0, 5.5);
    includePoints(&route4child0, -1.0, 1.0, 5.5);
    includePoints(&route4child0, -1.0, -1.0, 5.5);
    includePoints(&route4child0, 1.0, -1.0, 5.5);
    includePoints(&route4child0, 1.0, 0.0, 5.5);

    includePoints(&route4child1, -1.0, 0.0, 5.5);
    includePoints(&route4child1, -1.0, 0.0, 5.5);
    includePoints(&route4child1, -1.0, -1.0, 5.5);
    includePoints(&route4child1, 1.0, -1.0, 5.5);
    includePoints(&route4child1, 1.0, 1.0, 5.5);
    includePoints(&route4child1, -1.0, 1.0, 5.5);
    includePoints(&route4child1, -1.0, 0.0, 5.5);

    includePoints(&route4child2, 0.0, 1.0, 6.5);
    includePoints(&route4child2, 0.0, 1.4, 6.5);
    includePoints(&route4child2, -1.4, 1.4, 6.5);
    includePoints(&route4child2, -1.4, -1.4, 6.5);
    includePoints(&route4child2, 1.4, -1.4, 6.5);
    includePoints(&route4child2, 1.4, 1.4, 6.5);
    includePoints(&route4child2, 0.0, 1.0, 6.5);

    includePoints(&route4child3, 0.0, -1.0, 6.5);
    includePoints(&route4child3, 0.0, -1.4, 6.5);
    includePoints(&route4child3, 1.4, -1.4, 6.5);
    includePoints(&route4child3, 1.4, 1.4, 6.5);
    includePoints(&route4child3, -1.4, 1.4, 6.5);
    includePoints(&route4child3, -1.4, -1.4, 6.5);
    includePoints(&route4child3, 0.0, -1.0, 6.5);

    int i = 1;
    int j = 1;
    int estado = 0;
    int estadoRota = 0;

    string nameFile0, nameFile1, nameFile2, nameFile3;
    string data;
    string firstChild0, firstChild1, firstChild2, firstChild3 ;
    string second ;

    ofstream logFile0;
    ofstream logFile1;
    ofstream logFile2;
    ofstream logFile3;


    while(ros::ok())
    {
        ros::spinOnce();

        switch (estado)
        {
        case 0:
          cout << "Quadrado -> 1\nZigzag -> 2\nPercurso -> 3\nFollow -> 4\nMultiplos -> 5\n" << "Rotina de teste:";
          cin >> estado;
          estadoRota = 0;
          time_t rawtime;
          time (&rawtime);
          data = ctime (&rawtime);
          i=1;
        break;

        case 1:
          cout << "QUADRADO\n";          
          if(estadoRota < route0.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route0[estadoRota].x, route0[estadoRota].y, route0[estadoRota].z);
            gotoChild0.publish(route0[estadoRota]);
            if((abs(tagPoseChild0.x - route0[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route0[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            estado = 0;
          }          
          break;

        case 2:
          cout << "ZIGZAG\n";
          if(estadoRota < route1.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route1[estadoRota].x, route1[estadoRota].y, route1[estadoRota].z);
            gotoChild0.publish(route1[estadoRota]);
            if((abs(tagPoseChild0.x - route1[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route1[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            estado = 0;
          }
          break;

        case 3:
          cout << "PERCURSO\n";
          if(estadoRota < route2.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route2[estadoRota].x, route2[estadoRota].y, route2[estadoRota].z);
            gotoChild0.publish(route2[estadoRota]);
            if((abs(tagPoseChild0.x - route2[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route2[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            estado = 0;
          }
          break;

        case 4:
          cout << "FOLLOW\n";
          if(estadoRota < route3.size())
          {
            ROS_INFO("pose X: %f, pose Y: %f, pose Z: %f", route3[estadoRota].x, route3[estadoRota].y, route3[estadoRota].z);
            gotoMother.publish(route3[estadoRota]);
            if((abs(poseMother.x - route3[estadoRota].x) < 0.15) && (abs(poseMother.y - route3[estadoRota].y) < 0.15))
              estadoRota++;            
          }
          else
          {
            system("clear");
            estado = 0;
          }
          break;

        case 5:
          cout << "MULTIPLOS\n";
          if (i)
          {
            firstChild0 = "src/tccDrones/logsPos/logChild0";
            firstChild1 = "src/tccDrones/logsPos/logChild1";
            firstChild2 = "src/tccDrones/logsPos/logChild2";
            firstChild3 = "src/tccDrones/logsPos/logChild3";

            second = ".csv";

            nameFile0 = firstChild0 + data + second;
            nameFile1 = firstChild1 + data + second;
            nameFile2 = firstChild2 + data + second;
            nameFile3 = firstChild3 + data + second;

            logFile0.open (nameFile0, ios::out | ios::app);
            logFile1.open (nameFile1, ios::out | ios::app);
            logFile2.open (nameFile2, ios::out | ios::app);
            logFile3.open (nameFile3, ios::out | ios::app);

            logFile0 << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            logFile1 << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            logFile2 << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";
            logFile3 << "tagX;tagY;tagZ;GPSChildX;GPSChildY;GPSChildZ;GPSMotherX;GPSMotherY;GPSMotherZ;pontosX;pontosY;pontosZ\n";

            i = 0;
          }          
          if(estadoRota < route4child0.size())
          {
            ROS_INFO("ponto %d", estadoRota);

            gotoChild0.publish(route4child0[estadoRota]);
            gotoChild1.publish(route4child1[estadoRota]);
            gotoChild2.publish(route4child2[estadoRota]);
            gotoChild3.publish(route4child3[estadoRota]);

            logFile0 << tagPoseChild0.x  << ";" << tagPoseChild0.y << ";" << tagPoseChild0.z << ";" <<
                       poseGPSChild0.x   << ";" << poseGPSChild0.y  << ";" << poseGPSChild0.z  << ";" <<
                       poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
                       route4child0[estadoRota].x << ";" << route4child0[estadoRota].y << ";" << route4child0[estadoRota].z << "\n";

            logFile1 << tagPoseChild1.x  << ";" << tagPoseChild1.y << ";" << tagPoseChild1.z << ";" <<
                       poseGPSChild1.x   << ";" << poseGPSChild1.y  << ";" << poseGPSChild1.z  << ";" <<
                       poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
                       route4child1[estadoRota].x << ";" << route4child1[estadoRota].y << ";" << route4child1[estadoRota].z << "\n";
            
            logFile2 << tagPoseChild2.x  << ";" << tagPoseChild2.y << ";" << tagPoseChild2.z << ";" <<
                       poseGPSChild2.x   << ";" << poseGPSChild2.y  << ";" << poseGPSChild2.z  << ";" <<
                       poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
                       route4child2[estadoRota].x << ";" << route4child2[estadoRota].y << ";" << route4child2[estadoRota].z << "\n";
                    
            logFile3 << tagPoseChild3.x  << ";" << tagPoseChild3.y << ";" << tagPoseChild3.z << ";" <<
                       poseGPSChild3.x   << ";" << poseGPSChild3.y  << ";" << poseGPSChild3.z  << ";" <<
                       poseMother.x     << ";" << poseMother.y    << ";" << poseMother.z    << ";" <<
                       route4child3[estadoRota].x << ";" << route4child3[estadoRota].y << ";" << route4child3[estadoRota].z << "\n";
            
            if( ((abs(tagPoseChild0.x - route4child0[estadoRota].x) < 0.15) && (abs(tagPoseChild0.y - route4child0[estadoRota].y) < 0.15)) &&
                ((abs(tagPoseChild1.x - route4child1[estadoRota].x) < 0.15) && (abs(tagPoseChild1.y - route4child1[estadoRota].y) < 0.15)) &&
                ((abs(tagPoseChild2.x - route4child2[estadoRota].x) < 0.15) && (abs(tagPoseChild2.y - route4child2[estadoRota].y) < 0.15)) &&
                ((abs(tagPoseChild3.x - route4child3[estadoRota].x) < 0.15) && (abs(tagPoseChild3.y - route4child3[estadoRota].y) < 0.15))
              )
            {
              estadoRota++;            
            }
          }
          else
          {
            system("clear");
            logFile0.close();
            logFile1.close();
            logFile2.close();
            logFile3.close();
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