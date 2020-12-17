#include <stdlib.h>
#include <stdio.h>

#include "faulhaber/faulhaber.h"
#include "faulhaber/cmd_table.h"
#include "std_msgs/Int32MultiArray.h"
#include "actionlib/server/simple_action_server.h"
#include "my_ros_action/FaulhaberAction.h"

#define R 0.06828
#define W 0.6343
#define Ratio 50
#define PI 3.14159

void Faulhaber::Cmd_Listener(const my_ros_action::FaulhaberGoalConstPtr &goal)
{
    switch(Cmd_Decode(goal->cmd))
    {
        case cmd_table::VW_CONTROL :

            Vel(2,(int)( -( goal->v - (W / 2) * goal->w ) *Ratio * 60 / (2 * PI*R) ) );
//            cout<<"Left:"<<(int)( -( goal->v - (W / 2) * goal->w ) *Ratio * 60 / (2 * PI*R) )<<endl;
            Vel(3,(int)(  ( goal->v + (W / 2) * goal->w ) *Ratio * 60 / (2 * PI*R) ) );
//            cout<<"Right:"<<(int)( ( goal->v - (W / 2) * goal->w ) *Ratio * 60 / (2 * PI*R) )<<endl;
        break;

        case cmd_table::LEG_CONTROL :
            Vel(1,-goal->speed[1]);
            Vel(4,goal->speed[4]);
        break;

        case cmd_table::STOP :
            Vel(1,0);
            Vel(2,0);
            Vel(3,0);
            Vel(4,0);
        break;

//        case cmd_table::ROBOT_SPEED :
//            Speed(2,goal->speed[2]);
//            Speed(3,goal->speed[3]);
//        break;

//        case cmd_table::LEG_SPEED :
//            Speed(1,goal->speed[1]);
//            Speed(4,goal->speed[4]);
//        break;

        case cmd_table::UNKNOWN :
            printf("Unknown Command !\n");
        break;

        default :
            printf("Unknown Command !\n");
        break;
    }
}


cmd_table Faulhaber::Cmd_Decode(const string& cmd)
{
    if(cmd == "vw_control")
        return cmd_table::VW_CONTROL;
    else if(cmd == "leg_control")
        return cmd_table::LEG_CONTROL;
    else if(cmd == "stop")
        return cmd_table::STOP;
    else if(cmd == "unknown")
        return cmd_table::UNKNOWN;
    else
        return cmd_table::UNKNOWN;
}
