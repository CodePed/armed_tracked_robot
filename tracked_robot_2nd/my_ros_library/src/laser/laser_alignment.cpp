#include "ros/ros.h"                //include ros library
#include "sensor_msgs/LaserScan.h"  //include msg form form that had been published from your laser finder
#include "std_msgs/Float32.h"       //include msg form which you want to publish from this node
#include "std_msgs/String.h"        //include msg form wgich you want to publish from this node
#include "opencv2/highgui/highgui.hpp"      //include opencv2 library
#include "opencv2/imgproc/imgproc.hpp"      //include opencv2 library
//#include <vector>           //include vector library
#include <fstream>        //include File I/O library

#include "laser/laser_alignment.h"

//#define PI 3.14159          //define PI
//#define OFFSET -1.57        //define the angle offset to show on the LaserScatter Window

/*  If (X,Y) is (0,0), the origin will set on the top left corner of the window  */
//#define ORIGIN_X 250        //define the origin cordinate of x on the LaserScatter window
//#define ORIGIN_Y 500        //define the origin cordinate of y on the LaserScatter window

//#define RANGES_SCALE 100

/*  The amount of the element in msg->ranges[] can be checked with //   cout<<msg->ranges.size()<<endl; //   */
//#define RANGE_SIZE 512      //hokuyo publishes a msg which contains 512 element in msg->ranges[]

/*  All angles provided from hokuyo_node with msg is in radius(rad)  */
#define RadiusToDegree(x) ((x)*180/PI)      //define transform funcion for radius to degree

using namespace std;
using namespace cv;

//Mat img = Mat::zeros(Size(500,600), CV_8UC3);       //create a blank 800*600 pixels image to draw data points

//float x[RANGE_SIZE] = {0};      //Array that will be used in drawing        x[i] = msg->ranges[i]*scaling*cos(theta deg)
//float y[RANGE_SIZE] = {0};      //Array that will be used in drawing        y[i] = msg->ranges[i]*scaling*sin(theta deg)

//float data_ranges[RANGE_SIZE]={0};      //Array that will be used in Least Squares calculation  data_ranges[i] = msg->ranges[i]
//float data_x[RANGE_SIZE]={0};       //Array that will be used in Least Squares calculation      data_x[i] = x[i]
//float data_y[RANGE_SIZE]={0};       //Array that will be used in Least Squares calculation      data_y[i] = y[i]

//float beta = 0;         //The Result of our scope
//float alpha = 0;        //The Result of our offset

//int main( int argc , char **argv )
//{
//    ros::init( argc , argv , "laser" );

//    ros::NodeHandle nh;
//    ros::Subscriber laser_sub = nh.subscribe( "/scan" , 10 , lasercallback );//subscribe the topic "/scan" with a buffer sized of 10 and do the lasercallback function
//    ros::Rate r(10);        //set the loop will be executed with r.sleep() in the rate of r()Hz
//    while(ros::ok())          //the loop will execute until ros shutdown
//    {
//        img = Mat::zeros(Size(500,600), CV_8UC3);     //refresh a blank 500*600 pixels image to draw data points
//        ros::spinOnce();    //activate all the subsriber and it's callback function once
//        imshow("LaserScatter", img);    //open a Window named "LaserScatter" with img we have created previously
//        waitKey(1);         //set to 1 , 0 won't work properly
//        r.sleep();          //wait for 1/r() sec

//    }
//    return 0;

//}
/*  Constructor  */
Laser::Laser()
{
    beta = 0;
    alpha = 0;
    cout<<"Laser Alignment Online !\n";
    sub_laser = nh.subscribe("/scan",10,&Laser::laserCallback,this);
}
/*  Destructor  */
Laser::~Laser()
{
    sub_laser.shutdown();
    cout<<"Laser Alignment Offline !\n";
}
void Laser::laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    int RANGES_SCALE=100;
    int start = 200;
    int end = 320;
    int laser=258;
    float Max_Range=2;

    ros::param::get("/RANGES_SCALE",RANGES_SCALE);
    ros::param::get("/start",start);
    ros::param::get("/end",end);
    ros::param::get("/laser",laser);
    ros::param::get("/Max_Range",Max_Range);

    float cos_ranges;
    float sin_ranges;

    cout<<"\nLaser data recieved\n";
    cout<<"Ranges_scale : "<<RANGES_SCALE<<endl;
    Point p(ORIGIN_X,ORIGIN_Y);
    circle(img, p, 6, Scalar(255, 255, 0),-1);
    for(int i=0;i<RANGE_SIZE;i++)
    {
        data_ranges[i]=msg->ranges[i];      //Back up the msg->ranges data to data_ranges

        if(isinf(msg->ranges[i]))       //If the data recieved from hokuyo is infinity which is invalid data,set (x,y) to (0,0)
        {
            cos_ranges = 0;
            sin_ranges = 0;
        }
        else if(isnan(msg->ranges[i]))      //If the data recieved from hokuyo is Nan which is invalid data,set (x,y) to (0,0)//
        {
            cos_ranges = 0;
            sin_ranges = 0;
        }

        else
        {
            cos_ranges = ((RANGES_SCALE*msg->ranges[i])*cos(msg->angle_min+msg->angle_increment*i+OFFSET));     //Coordinate on the X axis can be evaluave as R * cos(theta deg)
            sin_ranges = ((RANGES_SCALE*msg->ranges[i])*sin(msg->angle_min+msg->angle_increment*i+OFFSET));     //Coordinate on the Y axis can be evaluate as R * sin(theta deg)
        }

        /*  Because the coordinate on the pixel windows must be integer  */
        x[i] = -roundf(cos_ranges)+ORIGIN_X;
        y[i] = roundf(sin_ranges)+ORIGIN_Y;
        Point p(x[i],y[i]);

        if(i>=start&&i<=end)
        {
            if(msg->ranges[i] <= Max_Range)
            {
                circle(img, p, 2, Scalar(255, 255, 0),-1);      //Analyzed points will be marked as light blue
            }
            else        //Laser point that is out of Max-range,they are invalid data point that should not be analyzed
               circle(img, p, 2, Scalar(0, 0, 255),-1);     //Non-analyze points will be marked as red
        }
        else
        {
            circle(img, p, 2, Scalar(0, 255, 0),-1);        //Non-analyze points will be marked as green
        }
//        cout<<"The "<<i<<"th laser: "<<100*msg->ranges[i]<<"\t"<<cos_ranges<<"\t"<<sin_ranges<<"\t angle: "<<msg->angle_min+msg->angle_increment*i+OFFSET<<endl;
//        cout<<x<<"\t"<<y<<endl;
//        cout<<"Radius to Degree: "<<(msg->angle_min+msg->angle_increment*i+OFFSET)/PI*180<<endl;

    }

    Save_txt(start,end);
    LaserAnalyzeSquare(start,end,Max_Range);

    cout<<"Mid-Laser[259]-degree : "<<roundf((msg->angle_min+msg->angle_increment*259-OFFSET)/PI*180)<<"deg"<<endl;
    cout<<"Analyze range from : "<<roundf((msg->angle_min+msg->angle_increment*start-OFFSET)/PI*180)<<"deg to "<<roundf((msg->angle_min+msg->angle_increment*end-OFFSET)/PI*180)<<"deg"<<endl;
    Point pstart_1(ORIGIN_X,ORIGIN_Y);
    Point pstart_2(x[start],y[start]);
    line(img, pstart_1, pstart_2, Scalar(0, 0, 255), 2);
    Point pend_1(ORIGIN_X,ORIGIN_Y);
    Point pend_2(x[end],y[end]);
    line(img, pend_1, pend_2, Scalar(0, 0, 255), 2);
    Point p1(0,roundf(alpha));
    Point p2(500,500*beta+roundf(alpha));
//    Point p1(0,0);
//    Point p2(500,500);
    line(img, p1, p2, Scalar(255, 0, 0), 2);
    cout<<"Beta : "<<beta<<"\t"<<"Alpha : "<<roundf(alpha)<<endl;
    ShowSelectedLaser(laser,msg->ranges[laser],msg->angle_min,msg->angle_increment,x[laser],y[laser]);
//    cout<<endl<<msg->range_min<<endl;

}

void Laser::LaserAnalyzeMask(int range,const sensor_msgs::LaserScan::ConstPtr &msg)
{

//    for( int i = 0 ; i < msg->ranges.size() ; i++ )
//    {

//    }

}

void Laser::LaserAnalyzeSquare(int start, int end, float max_range)
{
    float *ptr_x=x;
    float *ptr_y=y;

    float x_means = getMeans(ptr_x,start,end,max_range);
    float y_means = getMeans(ptr_y,start,end,max_range);
    float num_part=0;
    float den_part=0;
    for(int i=start;i<end;i++)
    {
        if(data_ranges[i] > max_range || isnan(data_ranges[i]) || isinf(data_ranges[i]))
        {
            continue;
        }
        else
        {
            num_part = num_part + (x[i] - x_means)*(y[i] - y_means);
            den_part = den_part + (x[i] - x_means)*(x[i] - x_means);
        }
    }

//    cout<<"x_means : "<<x_means<<"\t"<<"y_means : "<<y_means<<endl;


    beta = num_part/den_part;
    alpha = y_means - beta * x_means;

}

float Laser::getMeans(float *data,int start,int end,float max_range)
{
    float sum = 0;
    float means = 0;
    int total_N = end - start + 1;

    for(int i = start ; i <= end ; i++)
    {
        if(data_ranges[i] > max_range || isnan(data_ranges[i]) || isinf(data_ranges[i]))
        {
            sum = sum;
            total_N = total_N - 1;
        }
        else
        {
            sum = sum + data[i];
        }
    }

    means = sum / total_N;

//    cout<<"sum : "<<sum<<endl;
    return means;
}

void Laser::ShowSelectedLaser(int laser,float ranges,float min,float increment,float x,float y)
{
    cout<<laser<<"th laser range : "<<ranges<<"\t"<<(min+increment*laser-OFFSET)/PI*180<<" deg"<<endl;
    Point p1(ORIGIN_X,ORIGIN_Y);
    Point p2(x,y);
    line(img,p1,p2,Scalar(0,100,255),2);
}

float Laser::DegreeToRadius(float degree)
{
    float radius = (degree/180)*PI;
    return radius;
}

void Laser::Save_txt(int start,int end)
{
    fstream file;
    file.open("~/catkin_ws/src/Laser_point.txt",ios::out);     //Create a file to record our data in a text file
    if(file.fail())     //If the file cannot be opened, show the error message
    {
        cout<<"Can not open a file ! \n";
    }
    else
    {
        for(int i=start;i<end;i++)      //Record the i th laser data with it's coordinate x and y on the LaserScatter window
        {
            file<<i<<"\t"<<x[i]<<"\t"<<y[i]<<endl;
        }
        cout<<"File saved !\n";
    }
    file.close();

}
void Laser::LaserImshow(int fps,bool ShowOrNot)
{
    ros::Rate r(fps);        //set the loop will be executed with r.sleep() in the rate of r()Hz

    if(ShowOrNot)       //Run with window
    {
        while(ros::ok())          //the loop will execute until ros shutdown
        {
            img = Mat::zeros(Size(500,600), CV_8UC3);     //refresh a blank 500*600 pixels image to draw data points
            ros::spinOnce();    //activate all the subsriber and it's callback function once
            imshow("LaserScatter", img);    //open a Window named "LaserScatter" with img we have created previously
            waitKey(1);         //set to 1 , 0 won't work properly
            r.sleep();          //wait for 1/r() sec

        }
    }
    else        //Run without window
    {
        while(ros::ok())          //the loop will execute until ros shutdown
        {
//            img = Mat::zeros(Size(500,600), CV_8UC3);     //refresh a blank 500*600 pixels image to draw data points
            ros::spinOnce();    //activate all the subsriber and it's callback function once
//            imshow("LaserScatter", img);    //open a Window named "LaserScatter" with img we have created previously
//            waitKey(1);         //set to 1 , 0 won't work properly
            r.sleep();          //wait for 1/r() sec

        }
    }

}
