#ifndef _FAULHABER_H_
#define _FAULHABER_H_

/*---RS232 Include---*/
#include <string.h>     //
#include <stdio.h>      //
#include <unistd.h>     //Used for UART
#include <fcntl.h>      //Used for UART
#include <termios.h>    //Used for UART
#include <errno.h>      //Used for errno
#include <pthread.h>

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include "cmd_table.h"
#include "actionlib/server/simple_action_server.h"
#include "my_ros_action/FaulhaberAction.h"

/*---  Define Port Name  ---*/
//#define serialPortName "/dev/Faulhaber"

using namespace std;

class Faulhaber
{
    public:

    //-- Faulhaber Setup --//	-------------------->	you can find them in /src/setup.cpp
        Faulhaber();                                      //Faulhaber Constructor : Initialize sub_cmd , pub_encoder , encoder
        ~Faulhaber();                                     //Faulhaber Destructor
        int  Init(int fd_faulhaber_port,int baud_rate);                 //Initilize Faulhaber -> Open port
        void Close(int fd_faulhaber_port);                //Close Faulhaber -> Close port
        void Buffer_Reset(int fd_faulhaber_port);         //Buffer Reset -> Flush Buffer
    //---------------------//

    //-- Buffer Operation --//	-------------------->	you can find them in /src/buffer.cpp
        void Reader();                                    //reader : only read
        void Writter(char *Command);                      //writter: only write
    //----------------------//

    //-- Cmd Listener --//  ------------------------>   you can find them in /src/cmd_listener.cpp
        void Cmd_Listener(const my_ros_action::FaulhaberGoalConstPtr &goal);
    //------------------//

    //-- Faulhaber Action Server CallBack Function --//
        cmd_table Cmd_Decode(const string& cmd);
        void ExecuteCB(const my_ros_action::FaulhaberGoalConstPtr &goal);
    //-----------------------------------------------//

    //-- Faulhaber Cmd Function --//	------------>	you can find them in /src/cmd.cpp
        int  Position(int motor_number);                  //Show motor position(for encoder)
        void Speed(int motor_number, int motor_speed);    //Motor speed control
        void Vel(int motor_number,int motor_vel);         //Motor velocity control
        void Acc(int motor_number,int motor_acc);         //Motor accekeration control
        void Dec(int motor_number,int motor_dec);         //Motor deceleration control
        void LA(int motor_number, int motor_LA);          //Motor Absolute Position
        void LR(int motor_number, int motor_LR);          //Motor Load Relative Position
        void M(int motor_number);                         //Activate position control and start positioning
        void HO(int motor_number, int motor_HO);          //Define target position as homeing offset(default target position is 0)
        void EN(int motor_number);                        //Enable Motor Drive
        void DI(int motor_number);                        //Disable Motor Drive
        int  GRC(int motor_number);                       //Get Real Current Consumption (mA)
    //----------------------------//

        ros::Publisher pub_encoder;                       //Publish encoder msg from faulhaber motors
        std_msgs::Int32MultiArray encoder;                //Be aware that in reality controller order i starts from 1
        int encArray[4]{0,0,0,0};                                  // Store encoder previous data
    private:

        ros::NodeHandle nh;
        ros::Subscriber sub_cmd;                          //Recieve cmd published from other node
        actionlib::SimpleActionServer<my_ros_action::FaulhaberAction> action_server
        {
            nh,"Faulhaber",boost::bind(&Faulhaber::ExecuteCB,this,_1),false
        };

        my_ros_action::FaulhaberFeedback feedback;
        my_ros_action::FaulhaberResult result;

        string action_name{"Faulhabr"};
        int  faulhaber;                                   //Save up for fd_faulhaber_port
        char WrittenBuff[50];                             //Save up for cammand code which will be sent to faulhaber hardware(be used in writter)
        char command[50];                                 //Save up for command code which will be sent to faulhaber hardware(be used in cmd function)
        char reader_response[50];                         //Save up for recording what have returned from faulhaber haedware
        int  reader_status;                               //
        char scanner;
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};
#endif
