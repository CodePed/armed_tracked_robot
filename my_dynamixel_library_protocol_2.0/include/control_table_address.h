#ifndef _CONTROL_TABLE_ADDRESS_H
#define _CONTROL_TABLE_ADDRESS_H

#define DXL_ID                       1                   // Dynamixel ID: 1
#define BAUDRATE                     1000000             // 1M
#define DEVICE_NAME                 "/dev/ttyUSB0"       // Check which port is being used on your controller

#define TORQUE_ENABLE                1                   // Value for enabling the torque
#define TORQUE_DISABLE               0                   // Value for disableing the torque
#define DXL_MINIMUM_POSITION_VALUE  -150000              // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE   150000              // and this value
                                                         // ( Note that the Dynamixel would not move when the position is out of movable range.
                                                         //   Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD  20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE              0x1b                // Ascii code in hex





#endif