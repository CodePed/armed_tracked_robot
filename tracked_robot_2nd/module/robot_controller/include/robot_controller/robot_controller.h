#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ros/ros.h"

using namespace std;

class RobotController
{
    public:

    //-- RobotController Setup --//
        RobotController();
        ~RobotController();

    //---------------------------//


    private:
        ros::NodeHandle nh;

};
