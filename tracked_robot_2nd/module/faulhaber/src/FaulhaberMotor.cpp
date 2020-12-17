#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fcntl.h>      //Used for "open" function
#include <termios.h>    //Used for UART Baud Rate
#include <time.h>

#include "ros/ros.h"
#include "faulhaber/faulhaber.h"  //Used for faulhaber command function
#include "actionlib/server/simple_action_server.h"
#include "my_ros_action/FaulhaberAction.h"

#include "std_msgs/Int32.h"       //

/*------ Define Serial Port Name ------*/
#define SerialPortName "/dev/Faulhaber"
//#define SerialPortName "/dev/ttyUSB1"

int main(int argc,char** argv)
{
    char test[50]={0};
    int count = 1;
    ros::init(argc,argv,"FaulhaberMotor");
    ros::NodeHandle nh;
    Faulhaber faulhaber;
    int fd_faulhaber_port;

    ros::Rate r(100);
    int encoder_store[5]={0};

    fd_faulhaber_port = open(SerialPortName , O_RDWR | O_NOCTTY | O_NONBLOCK);   //set fd_port to read & write & tty interface

    switch(faulhaber.Init(fd_faulhaber_port,B19200))
    {
        case  1:
            printf("Powering Up All Faulhaber Motors... \n\n");
            break;
        case -1:
            return 0;
            break;
    }
    for(int i = 1; i <= 4 ; i++)
    {
        faulhaber.DI(i);
        faulhaber.EN(i);
        faulhaber.HO(i,0);
    }
    printf("\nPower Completed !\n\n");
    printf("Encoder has been initialized to 0 .\n");
    printf("Now keep listening Cmd that has published from other nodes ...\n\n");

    while(ros::ok())
    {
        if(count == 10)
        {
//            for(int i = 1 ; i <= 4 ; i++)
//            {
//                encoder_store[i] = faulhaber.Position(i);
//            }
            for(int i = 1 ; i <= 4 ; i++)
            {
                faulhaber.encoder.data.push_back(faulhaber.Position(i));
            }
            faulhaber.pub_encoder.publish(faulhaber.encoder);
            faulhaber.encoder.data.clear();
            count = 1;
        }
        else
        {
            count ++;
        }
        ros::spinOnce();                //Activate Cmd_Listener once
        r.sleep();
    }

    for(int i = 1;i <= 4;i ++)
    {
        faulhaber.DI(i);
    }
    printf("Power Off !\n");
    faulhaber.Close(fd_faulhaber_port);

    return 0;
}
