#include <stdlib.h>
#include <stdio.h>
#include "faulhaber/faulhaber.h"
#include "faulhaber/cmd_table.h"

//void Faulhaber::Cmd_Listener(const std_msgs::Int32MultiArray::ConstPtr &msg)
//{
//    switch(msg->data[0])
//    {
//        case cmd_table::VW_CONTROL :
//            Vel(2,msg->data[1]);
//            Vel(3,msg->data[2]);

//        case cmd_table::ROBOT_SPEED :
////            Speed(2,atoi(msg->data[1]));
////            Speed(3,atoi(msg->data[2]));

//        case cmd_table::Vel :
////            Speed(1,atoi(msg->data[1]));
////            Speed(4,atoi(msg->data[2]));

//        default:
//            printf("Unknown CMD !\n");
//    }
//}
