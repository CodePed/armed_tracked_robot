#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/highgui.hpp"
#include "ros/ros.h"

#include "camera/depth_camera.h"

#define COL 640
#define ROW 480

using namespace cv;
using namespace std;

Camera::Camera()
{   
    image_depth.create(COL,ROW,CV_32FC1);
    image_bgr.create(COL,ROW,CV_8UC1);

    depth_data.clear();
    vector<float>().swap(depth_data);

    image_transport::ImageTransport it(nh);
    sub_depth = it.subscribe("/zed/depth/depth_registered",1,&Camera::Depth_CallBack,this);
    sub_bgr = it.subscribe("/rgb/image",1,&Camera::BGR_Callback,this);

    cv::startWindowThread();
}

Camera::~Camera()
{
    cv::destroyAllWindows();
    printf("Shut Down Camera Node !\n");
}

void Camera::Monitor(string option)
{    
    if(option == "BGR")
    {
        cv::namedWindow("BGR");
        cv::imshow("BGR",image_bgr);
    }
    else if(option == "Depth")
    {
        cv::namedWindow("Depth");
        cv::imshow("Depth",image_depth);
    }

    cv::waitKey(30);
}

void Camera::Depth_CallBack(const sensor_msgs::ImageConstPtr &msg)
{
    image_depth = cv_bridge::toCvCopy(msg,"32FC1")->image;
    for(int y = 0 ; y < ROW ; y++)
    {
        for(int x = 0 ; x < COL ;x++)
        {
        depth_data.push_back(image_depth.at<float>(cv::Point(x,y)));
//        cout<<"x : "<<x<<"\t"<<"y : "<<y<<"\t"<<"data : "<<depth_data[x+COL*y]<<endl;
        }
    }
//    cout<<(depth_data[320+COL*240])<<endl;
    Save_Depth_Data();
}
void Camera::BGR_Callback(const sensor_msgs::ImageConstPtr &msg)
{
    image_bgr = cv_bridge::toCvCopy(msg,"bgr8")->image;
}

void Camera::Depth_Label()
{
    depth_data.clear();
    vector<float>().swap(depth_data);
}
void Camera::BGR_Label()
{

}

void Camera::Save_Depth_Data()
{
    file.open("/home/cirlab/catkin_ws/src/tracked_robot_2nd/data/camera/depth.csv", ios::out | ios::trunc);
    if(!file)
        cout<<"Can't open file !\n";
    for(int y = 0 ; y < ROW ; y++)
    {
        for(int x = 0 ; x < COL ; x++)
        {
            file <<(depth_data[x+COL*y])<<",";
        }
        file <<"\n";
    }
    file.close();
    depth_data.clear();
    vector<float>().swap(depth_data);
}
