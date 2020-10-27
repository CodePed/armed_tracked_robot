
/*
 * read_write.cpp
 *
 *  Created on: 2016. 2. 21.
 *      Author: leon
 */

//
// *********     Read and Write Example      *********
//
//
// Available Dynamixel model on this example : All models using Protocol 2.0
// This example is designed for using a Dynamixel PRO 54-200, and an USB2DYNAMIXEL.
// To use another Dynamixel model, such as X series, see their details in E-Manual(support.robotis.com) and edit below "#define"d variables yourself.
// Be sure that Dynamixel PRO properties are already set as %% ID : 1 / Baudnum : 3 (Baudrate : 1000000 [1M])
//

#ifndef DYNAMIXEL_LIBRARY_FUNCTION_H_
#define DYNAMIXEL_LIBRARY_FUNCTION_H_

// For Unix system
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// General library
#include <stdio.h>
#include <stdlib.h>
#include "dynamixel_sdk.h"
#include "control_table_address.h"

#define PROTOCOL_VERSION 2.0        // See which protocol version is used in the Dynamixel

using namespace std;

class DXL
{
    public:

        DXL();
       ~DXL();
        int getch();
        int keyboard_hit();
    
    // private:



};
#endif