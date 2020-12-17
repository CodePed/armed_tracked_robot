#include <stdlib.h>
#include <stdio.h>

#include "../include/robot/conio.h"
#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <my_ros_action/FaulhaberAction.h>


int main(int argc, char **argv)
{

    int cmd = 0;
    int front_leg_speed = 0;
    int rear_leg_speed = 0;
    ros::init(argc, argv, "Keyboard_Control");
    actionlib::SimpleActionClient<my_ros_action::FaulhaberAction> action_client("Faulhaber",true);
    ros::Rate r(100);
    ROS_INFO("Waiting for action server to start.");
    // wait for the action server to start
    action_client.waitForServer(); //will wait for infinite time

    ROS_INFO("Action server started, sending goal.");
    // send a goal to the action
    my_ros_action::FaulhaberGoal goal;
    goal.speed.clear();

    while(ros::ok())
    {
        goal.speed.push_back(0);
        goal.position.push_back(0);
        cmd = getch();
        if(cmd == 'W' || cmd == 'w')     //'W' or 'w'
        {
            goal.cmd = "vw_control";
            goal.v = 0.07;
            goal.w = 0;
            printf("%c Pressed !\t",cmd);
            printf("VW_CONTROL ordered !\n");
        }
        else if(cmd == 'A' || cmd == 'a')    //'A' or 'a'
        {
            goal.cmd = "vw_control";
            goal.v = 0;
            goal.w = 0.2;
            printf("%c Pressed !\t",cmd);
            printf("VW_CONTROL ordered !\n");
        }
        else if(cmd == 'S' || cmd == 's' )    //'S' or 's'
        {
            goal.cmd = "vw_control";
            goal.v = -0.07;
            goal.w = 0;
            printf("%c Pressed !\t",cmd);
            printf("VW_CONTROL ordered !\n");
        }
        else if(cmd == 'D' || cmd == 'd' )    //'D' or 'd'
        {
            goal.cmd = "vw_control";
            goal.v = 0;
            goal.w = -0.2;
            printf("%c Pressed !\t",cmd);
            printf("VW_CONTROL ordered !\n");
        }
        else if(cmd == ' ')    //'Space' or ' '
        {
            goal.cmd = "stop";
            goal.v = 0;
            goal.w = 0;
            front_leg_speed = 0;
            rear_leg_speed = 0;
            goal.speed.push_back(front_leg_speed);
            goal.speed.push_back(0);
            goal.speed.push_back(0);
            goal.speed.push_back(rear_leg_speed);

            printf("Space_Bar Pressed !\t");
            printf("STOP ordered !\n");
        }
        else if(cmd == 'F' || cmd == 'f')
        {
            goal.cmd = "leg_control";
            rear_leg_speed = 100;
            goal.speed.push_back(front_leg_speed);
            goal.speed.push_back(0);
            goal.speed.push_back(0);
            goal.speed.push_back(rear_leg_speed);
            printf("%c Pressed !\t",cmd);
            printf("LEG_CONTROL ordered !\n");
        }
        else if(cmd == 'V' || cmd == 'v')
        {
            goal.cmd = "leg_control";
            rear_leg_speed = -100;
            goal.speed.push_back(front_leg_speed);
            goal.speed.push_back(0);
            goal.speed.push_back(0);
            goal.speed.push_back(rear_leg_speed);
            printf("%c Pressed !\t",cmd);
            printf("LEG_CONTROL ordered !\n");
        }
        else if(cmd == 'G' || cmd == 'g')
        {
            goal.cmd = "leg_control";
            front_leg_speed = -100;
            goal.speed.push_back(front_leg_speed);
            goal.speed.push_back(0);
            goal.speed.push_back(0);
            goal.speed.push_back(rear_leg_speed);
            printf("%c Pressed !\t",cmd);
            printf("LEG_CONTROL ordered !\n");
        }
        else if(cmd == 'B' || cmd == 'b')
        {
            goal.cmd = "leg_control";
            front_leg_speed = 100;
            goal.speed.push_back(front_leg_speed);
            goal.speed.push_back(0);
            goal.speed.push_back(0);
            goal.speed.push_back(rear_leg_speed);
            printf("%c Pressed !\t",cmd);
            printf("LEG_CONTROL ordered !\n");
        }
        else if(cmd == 'E' || cmd == 'e')    //'E' or 'e'
        {
            printf("%c Pressed !\t",cmd);
            printf("Exciting Keyboard_Control ... \n");
            return 0;
        }
        else
        {
            goal.cmd = "unknown";
            printf("%c Pressed !\t",cmd);
            printf("Unknowned Command ordered !\n");
        }
        action_client.sendGoal(goal);
        //wait for the action to return
        bool finished_before_timeout = action_client.waitForResult(ros::Duration(0.5));
        if (finished_before_timeout)
        {
            actionlib::SimpleClientGoalState state = action_client.getState();
            ROS_INFO("Action finished: %s",state.toString().c_str());
        }
        else
        {
            ROS_INFO("Action did not finish before the time out.");
        }
        r.sleep();
        goal.speed.clear();
        goal.position.clear();
    }
    return 0;
}
