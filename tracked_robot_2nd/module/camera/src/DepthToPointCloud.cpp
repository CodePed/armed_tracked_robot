#include "ros/ros.h"
#include "depth_image_proc/depth_conversions.h"

int main(int argc,char** argv)
{
    ros::init(argc,argv,"DepthToPointCloud");
    ros::NodeHandle nh;
    return 0;
}



