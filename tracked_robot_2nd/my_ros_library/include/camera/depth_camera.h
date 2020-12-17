#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/highgui.hpp"
#include "ros/ros.h"

#define COL 640
#define ROW 480

using namespace std;
using namespace cv;

class Camera
{
    public:
        Camera();
        ~Camera();

        void BGR_Callback(const sensor_msgs::ImageConstPtr& msg);
        void Depth_CallBack(const sensor_msgs::ImageConstPtr& msg);
        void BGR_Label();
        void Depth_Label();
        void Monitor(string option);
        void Save_Depth_Data();

        ros::NodeHandle nh;

        image_transport::Subscriber sub_bgr;
        image_transport::Subscriber sub_depth;

    private:

        Mat image_bgr;
        Mat image_depth;
        vector<float> depth_data;
        fstream file;
};
