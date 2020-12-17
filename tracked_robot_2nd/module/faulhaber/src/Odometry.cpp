#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ros/ros.h"
#include "faulhaber/odometry.h"             //Used for faulhaber command function

using namespace std;

int main(int argc,char** argv)
{
    ros::init(argc,argv,"Odometry");
    Odometry odom;

    cout<<"Start Odometry ...\n";

    while(ros::ok())
    {
        ros::spinOnce();
    }

    return 0;
}
