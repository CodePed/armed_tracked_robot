#ifndef LASER_ALIMENT_H
#define LASER_ALIMENT_H

#include "ros/ros.h"                //include ros library
#include "sensor_msgs/LaserScan.h"  //include msg form form that had been published from your laser finder
#include "std_msgs/Float32.h"       //include msg form which you want to publish from this node
#include "std_msgs/String.h"        //include msg form wgich you want to publish from this node
#include "opencv2/highgui/highgui.hpp"      //include opencv2 library
#include "opencv2/imgproc/imgproc.hpp"      //include opencv2 library
//#include <vector>           //include vector library
#include <fstream>        //include File I/O library

#define PI 3.14159          //define PI
#define OFFSET -1.57        //define the angle offset to show on the LaserScatter Window

/*  If (X,Y) is (0,0), the origin will set on the top left corner of the window  */
#define ORIGIN_X 250        //define the origin cordinate of x on the LaserScatter window
#define ORIGIN_Y 500        //define the origin cordinate of y on the LaserScatter window

//#define RANGES_SCALE 100

/*  The amount of the element in msg->ranges[] can be checked with //   cout<<msg->ranges.size()<<endl; //   */
#define RANGE_SIZE 512      //hokuyo publishes a msg which contains 512 element in msg->ranges[]

/*  All angles provided from hokuyo_node with msg is in radius(rad)  */
#define RadiusToDegree(x) ((x)*180/PI)      //define transform funcion for radius to degree

using namespace std;
using namespace cv;

class Laser
{
    private:

        Mat img = Mat::zeros(Size(500,600), CV_8UC3);       //create a blank 800*600 pixels image to draw data points

        float x[RANGE_SIZE] = {0};      //Array that will be used in drawing        x[i] = msg->ranges[i]*scaling*cos(theta deg)
        float y[RANGE_SIZE] = {0};      //Array that will be used in drawing        y[i] = msg->ranges[i]*scaling*sin(theta deg)

        float data_ranges[RANGE_SIZE]={0};      //Array that will be used in Least Squares calculation  data_ranges[i] = msg->ranges[i]
        float data_x[RANGE_SIZE]={0};       //Array that will be used in Least Squares calculation      data_x[i] = x[i]
        float data_y[RANGE_SIZE]={0};       //Array that will be used in Least Squares calculation      data_y[i] = y[i]

        ros::NodeHandle nh;
        ros::Subscriber sub_laser;

    public:
        /*  Constructor  */
        Laser();
        /*  Destructor  */
        ~Laser();
        void laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg);        //recieve "/scan" message from laser finder's publisher

        void LaserAnalyzeSquare(int start, int end, float max_range);        //Analyze laser point with linear regression by applying least squares method
        float getMeans(float *data,int start,int end,float max_range);      //Calculate the means of all data points

        void LaserAnalyzeMask(int range,const sensor_msgs::LaserScan::ConstPtr &msg);        //apply linear regression to multiple selected laser data
        void Save_txt(int start,int end);       //Save data points in text file

        void ShowSelectedLaser(int i,float ranges,float min,float increment,float x,float y);      //Mark the seleced laser line and show the info
        float DegreeToRadius(float degree);
        void LaserImshow(int fps,bool ShowOrNot);

        float beta = 0;         //The Result of our scope
        float alpha = 0;        //The Result of our offset

};
#endif
