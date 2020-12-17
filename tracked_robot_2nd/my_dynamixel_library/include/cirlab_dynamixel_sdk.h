#ifndef _CIRLAB_DYNAMIXEL_SDK_H_
#define _CIRLAB_DYNAMIXEL_SDK_H_
#include "dynamxel_sdk.h"
#include "control_table.h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector.h>
#include <string.h>


using namespace std;

class DXL
{
    DXL(int motor_amount);
    ~DXL(int motor_amount);

    public:
    // Setup Function
        int Initial_Motor(string port_name , unit8* Motor_ID);
        int Reboot();
        int Reset();
        int Shutdown();
        int setid();
        int setbaudrate();
        int setport();

    // Command Function
        int Torque_Enable();
        int Led();
        int Goal_Position();
        int Present_Position();
        int Drive_Mode();
        int Operating_Mode();
        int Present_Load();

    private:
    // A struct for restore a series of motor info
        string port_name;
        unit8 Motor_ID[];
        unit32 command_value[];

};
#endif
