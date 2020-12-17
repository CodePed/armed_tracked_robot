#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ros/ros.h"
#include "camera/depth_camera.h"

int main(int argc,char **argv)
{
    ros::init(argc,argv,"CameraNode");
    Camera camera;

    ros::Rate r(30);

    while(ros::ok())
    {
        ros::spinOnce();
        camera.Monitor("BGR");
        r.sleep();
    }

    return 0;
}
