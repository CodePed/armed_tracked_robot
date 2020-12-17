#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>

#include "ros/ros.h"
#include "conio.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include <dynamixel_workbench_msgs/JointCommand.h>

#define PI 3.14

int vv1=1000,vv2=1000,y=0;
int wd1=0,wd2=0,wd3=0;
int act;
float top=0,bottom=2;//initial position
float topp=top,bottomm=bottom;//varible position
int cnt=0;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Manual_mode");
    ros::NodeHandle n;
    ros::Publisher pub1 = n.advertise<std_msgs::Int32MultiArray>("robot_speed" , 1);
    ros::Publisher pub2 = n.advertise<std_msgs::Int32MultiArray>("leg_speed" , 1);
    ros::Publisher pub3 = n.advertise<std_msgs::Int32MultiArray>("robot_MA" , 1);
    ros::Publisher pub4 = n.advertise<std_msgs::Int32MultiArray>("leg_MA" , 1);
    ros::Publisher pub5 = n.advertise<std_msgs::Int32MultiArray>("robot_HO" , 1);
    ros::Publisher pub6 = n.advertise<std_msgs::Int32MultiArray>("robot_VA" , 1);

    ros::Publisher pub7 = n.advertise<std_msgs::Int32>("robot_motion" , 1);
    ros::Publisher pub8 = n.advertise<std_msgs::Int32>("leg_motion" , 1);

    ros::Publisher pub9 = n.advertise<std_msgs::Int32MultiArray>("leg_HO" , 1);
    ros::Publisher pub10 = n.advertise<std_msgs::Int32MultiArray>("leg_VA" , 1);
    ros::Publisher pub11 = n.advertise<std_msgs::Int32MultiArray>("robot_MR" , 1);

    ros::Publisher pub12 = n.advertise<std_msgs::Float64>("head_top" , 1);
    ros::Publisher pub13 = n.advertise<std_msgs::Float64>("head_bottom" , 1);

    ros::ServiceClient joint_command_client =
                n.serviceClient<dynamixel_workbench_msgs::JointCommand>("joint_command");

    std_msgs::Int32MultiArray robot_speed,leg_speed,robot_MA,leg_MA,robot_HO,robot_VA,robot_MR,leg_HO,leg_VA;
    std_msgs::Int32 robot_motion,leg_motion;
    std_msgs::Float64 head_top,head_bottom;
    dynamixel_workbench_msgs::JointCommand joint_command;
//---robot_motion---
//1=fwd
//2=back
//3=left
//4=right
//0=stop
//-------------------
//---lef_motion---
//1=front up
//2=front down
//3=back up
//4=back down
//0=stop
//-------------------
    ros::Rate loop_rate(100);

    printf("Welcome to Tracked Robot Manual Control !\n");

    while(ros::ok())
    {
        robot_speed.data.clear();
        leg_speed.data.clear();
        robot_MA.data.clear();
        leg_MA.data.clear();
        robot_HO.data.clear();
        robot_VA.data.clear();
        robot_MR.data.clear();

        y=getch();


      if(y==32)     //"Space Bar"
        {
            printf("\nCommand Line : ==>  \t");
            printf("Stop , ");
            int rm=0;//robot_motion

            robot_motion.data=rm;

            pub7.publish(robot_motion);
            printf("Topic : ( robot_motion )\tPublished \n");
            ros::spinOnce();


          //bodyact("stop");
          //XtionMotor_stop();
          //legact("stop","stop");
          //usleep(50000);
            act = 0;
        }
      else if(y==65)								//"arrow_up"
        {
            printf("\nCommand Line : ==>  \t");
            printf("Forward , ");
            int rm=1;//robot_motion

            robot_motion.data=rm;

            pub7.publish(robot_motion);
            printf("Topic : ( robot_motion )\tPublished \n");
            ros::spinOnce();
        //bodyact("fwd");
        //usleep(50000);
            act = 1;
      }
      else if(y==66)								//"arrow_down"
        {
            printf("\nCommand Line : ==>  \t");
            printf("Backward , ");
            int rm=2;//robot_motion

            robot_motion.data=rm;

            pub7.publish(robot_motion);
            printf("Topic : ( robot_motion )\tPublished \n");
            ros::spinOnce();

         //bodyact("back");
         //usleep(50000);
            act = 2;
      }
      else if(y==68)								//"arrow_left"
        {
            printf("\nCommand Line : ==>  \t");
            printf("Turn Left , ");
            int rm=3;//robot_motion

            robot_motion.data=rm;

            pub7.publish(robot_motion);
            printf("Topic : ( robot_motion )\tPublished \n");
            ros::spinOnce();

            //bodyact("left");
            //usleep(50000);
            act = 3;
      }
      else if(y==67)								//"arrow_right"
        {
            printf("\nCommand Line : ==>  \t");
            printf("Turn Right , ");
            int rm=4;//robot_motion

            robot_motion.data=rm;

            pub7.publish(robot_motion);
            printf("Topic : ( robot_motion )\tPublished \n");
            ros::spinOnce();

         //bodyact("right");
            //usleep(50000);
            act = 4;
      }
      else if(y==97||y==65)							//'A' or 'a'
        {
            printf("\nCommand Line : ==>  \t");
            printf("Front Leg Up , ");
            int lm=2;//leg_motion:front up

            leg_motion.data=lm;

            pub8.publish(leg_motion);
            printf("Topic : ( leg_motion )\tPublished \n");
            ros::spinOnce();

         //usleep(50000);
            //legact("","rev");
        }
      else if(y==122||y==90)						//'Z' or 'z'
      {
            printf("\nCommand Line : ==>  \t");
            printf("Front Leg Down , ");
            int lm=1;//leg_motion:front down

            leg_motion.data=lm;

            pub8.publish(leg_motion);
            printf("Topic : ( leg_motion )\tPublished \n");
            ros::spinOnce();
            //legma(0,-5000);
        //legact("","fwd");
        }
      else if(y==83||y==115)						//'S' or 's'
      {
            printf("\nCommand Line : ==>  \t");
            printf("Rear Leg Down , ");
            int lm=4;//leg_motion:back up

            leg_motion.data=lm;

            pub8.publish(leg_motion);
            printf("Topic : ( leg_motion )\tPublished \n");
            ros::spinOnce();

        //legma(5000,0);
         //legact("rev","");
        }
      else if(y==120||y==88)						//'X' or 'x'
      {
            printf("\nCommand Line : ==>  \t");
            printf("Rear Leg Down , ");
            int lm=3;//leg_motion:back down

            leg_motion.data=lm;

            pub8.publish(leg_motion);
            printf("Topic : ( leg_motion )\tPublished \n");
            ros::spinOnce();

            //legma(-5000,0);
         //legact("fwd","");

        }
//-------------------------------------------------------
        else if(y==114||y==82)						//'R' or 'r' , reset speed
        {
                printf("\nCommand Line : ==>  \t");
                printf("Normal Speed , ");
                int rs[2];//robot_speed
                int ls[2];//leg_speed
                rs[0]=350;
                rs[1]=350;
                ls[0]=100;
                ls[1]=100;
                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                    leg_speed.data.push_back(ls[i]);
                }
                pub1.publish(robot_speed);
                pub2.publish(leg_speed);

                printf("Topic : ( robot_speed + leg_speed )\tPublished \n");

                ros::spinOnce();
            //bodyJOGvel(300,300);
            //legJOGvel(100,100);
            vv1=350;
            vv2=350;
        }
        /*else if(y==112)
        {
            XtionMotor_MR(1000,1000);
        }
        else if(y==111)
        {
            XtionMotor_MR(-1000,-1000);
        }*/
        else if(y==102||y==70)						//'F' or 'f' , fast speed
        {
            printf("\nCommand Line : ==>  \t");
            printf("Fast Speed , ");
            int rs[2];//robot_speed
                int ls[2];//leg_speed
                rs[0]=1000;
                rs[1]=1000;
                ls[0]=100;
                ls[1]=100;
                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                    leg_speed.data.push_back(ls[i]);
                }
                pub1.publish(robot_speed);
                pub2.publish(leg_speed);

                printf("Topic : ( robot_speed + leg_speed )\tPublished \n");

                ros::spinOnce();
                //bodyJOGvel(1000,1000);
            //legJOGvel(200,200);
            vv1=1000;
            vv2=1000;
        }
        else if(y==85||y==117)						//'U' or 'u' , add speed
        {
            printf("\nCommand Line : ==>  \t");
            printf("Speed Up , ");

            if(vv1<30000)
                vv1+=500;
            if(vv2<30000)
                vv2+=500;

                int rs[2];//robot_speed

                rs[0]=vv1;
                rs[1]=vv2;

                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                }
                pub1.publish(robot_speed);
                printf("Topic : ( robot_speed )\tPublished \n");

                ros::spinOnce();
                //bodyJOGvel(vv1,vv2);



                if (act == 1)
                {
                    int rm=1;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 2)
                {
                    int rm=2;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 3)
                {
                    int rm=3;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 4)
                {
                    int rm=4;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 0)
                {
                    int rm=0;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }

        }
        else if ( y == 59 ||y == 121)				//'Y' or 'y' , slow down
        {
            printf("\nCommand Line : ==>  \t");
            printf("Speed Down , ");
            if (vv1>1000)
                vv1 -= 500;
            if (vv2>1000)
                vv2 -= 500;
//------------------------------------------
            //bodyJOGvel(vv1, vv2);
            int rs[2];//robot_speed

            rs[0]=vv1;
            rs[1]=vv2;
            for (int i = 0; i < 2; i++)
            {
                robot_speed.data.push_back(rs[i]);
            }
            pub1.publish(robot_speed);
            printf("Topic : ( robot_speed )\tPublished \n");

            ros::spinOnce();
//------------------------------------------

                if (act == 1)
                {
                    int rm=1;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 2)
                {
                    int rm=2;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 3)
                {
                    int rm=3;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 4)
                {
                    int rm=4;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }
                else if (act == 0)
                {
                    int rm=0;//robot_motion
                    robot_motion.data=rm;
                    pub7.publish(robot_motion);
                    //printf("robot_motion publish\n");
                    ros::spinOnce();
                }

            /*if (act == 1)
                bodyact("fwd");
            else if (act == 2)
                bodyact("back");
            else if (act == 3)
                bodyact("left");
            else if (act == 4)
                bodyact("right");
            else if (act == 0)
                bodyact("stop");
            */

        }

        else if(y==101||y==69)//'E' or 'e' , end for break
         {
            printf("\nCommand Line : ==>  \t");
            printf("End of Manual Control\n");
            //bodyact("stop");
            //legact("stop","stop");
            break;
        }
        else if(y==106)// J
        {
            printf("\nCommand Line : ==>  \t");
            printf("Leg in Position , ");
            int l_MA[2];//leg_MA

            l_MA[0] = 33000;
            l_MA[1] = 23000;
            for (int i = 0; i < 2; i++)
            {
                leg_MA.data.push_back(l_MA[i]);
            }
            pub4.publish(leg_MA);
            printf("Topic : ( leg_MA )\tPublished \n");

            ros::spinOnce();
            //legma(-26000,-27000); //climb stairs legs initial
      }


        else if(y==57)//'9'	xtion return home
        {
            printf("\nCommand Line : ==>  \t");
            printf("Initialize MX28 , ");
            printf("Topic : (  )\tPublished \n");
            bottomm=bottom;topp=top;
            joint_command.request.unit = "rad";
            joint_command.request.id = 2;//bottom
            joint_command.request.goal_position = bottomm*PI/180;
            joint_command_client.call(joint_command);
            joint_command.request.unit = "rad";
            joint_command.request.id = 1;//top
            joint_command.request.goal_position = topp*PI/180;
            joint_command_client.call(joint_command);
            head_bottom.data=bottom;
            head_top.data=top;
            pub13.publish(head_bottom);
            pub12.publish(head_top);
            //printf("xtion pos_init\n");
            //printf("bottom:%.1f,top:%.1f\t\t",bottomm-bottom,topp-top);//ROS_INFO("bottom:%f,top:%f", bottomm,topp);
            ros::spinOnce();
        }
        else if(y==105)//'i'	xtion turn left
        {
            printf("\nCommand Line : ==>  \t");
            printf("MX28 Turn Left , ");
            printf("Topic : (  )\tPublished \n");
            if(bottomm>=150)
            {
                bottomm = bottomm;
                printf("Left Safe Zone Reached!!\n");
            }
            else
            {
                bottomm=bottomm+10;
            }

            head_bottom.data=bottomm;
            head_top.data=topp;
            pub13.publish(head_bottom);
            pub12.publish(head_top);
            joint_command.request.unit = "rad";
            joint_command.request.id = 2;//bottom
            joint_command.request.goal_position = bottomm*PI/180;
            joint_command_client.call(joint_command);
            joint_command.request.unit = "rad";
            joint_command.request.id = 1;//top
            joint_command.request.goal_position = topp*PI/180;
            joint_command_client.call(joint_command);
            //printf("xtion turn left\n");
            //printf("bottom:%.1f,top:%.1f\t\t",bottomm-bottom,topp-top);//ROS_INFO("bottom:%f,top:%f", bottomm,topp);
            ros::spinOnce();
        }
        else if(y==112)//p	xtion turn right
        {
            printf("\nCommand Line : ==>  \t");
            printf("MX28 Turn Right , ");
            printf("Topic : (  )\tPublished \n");
            if(bottomm <= -140)
            {
                bottomm = bottomm;
                printf("Right Safe Zone Reached!!\n");
            }
            else
            {
                bottomm=bottomm-10;
            }

            joint_command.request.unit = "rad";
            joint_command.request.id = 2;//bottom
            joint_command.request.goal_position = bottomm*PI/180;
            joint_command_client.call(joint_command);
            joint_command.request.unit = "rad";
            joint_command.request.id = 1;//top
            joint_command.request.goal_position = topp*PI/180;
            joint_command_client.call(joint_command);
            head_bottom.data=bottomm;
            head_top.data=topp;
            pub13.publish(head_bottom);
            pub12.publish(head_top);
            //printf("xtion turn right\n");
            //printf("bottom:%.1f,top:%.1f\t\t",bottomm-bottom,topp-top);//ROS_INFO("bottom:%f,top:%f", bottomm,topp);
            ros::spinOnce();
        }
        else if(y==111)//o	xtion turn up
        {
            printf("\nCommand Line : ==>  \t");
            printf("MX28 Turn Up , ");
            printf("Topic : (  )\tPublished \n");
            if(topp>=90)
            {
                topp = topp;
                printf("Down Safe Zone Reached !!\n");
            }
            else
            {
                topp=topp+10;
            }

            joint_command.request.unit = "rad";
            joint_command.request.id = 2;//bottom
            joint_command.request.goal_position = bottomm*PI/180;
            joint_command_client.call(joint_command);
            joint_command.request.unit = "rad";
            joint_command.request.id = 1;//top
            joint_command.request.goal_position = topp*PI/180;
            joint_command_client.call(joint_command);
            head_bottom.data=bottomm;
            head_top.data=topp;
            pub13.publish(head_bottom);
            pub12.publish(head_top);
            //printf("xtion turn up\n");
            //printf("bottom:%.1f,top:%.1f\t\t",bottomm-bottom,topp-top);//ROS_INFO("bottom:%f,top:%f", bottomm,topp);
            ros::spinOnce();
        }
        else if(y==108)//l	xtion turn down
        {
            printf("\nCommand Line : ==>  \t");
            printf("MX28 Turn Down , ");
            printf("Topic : (  )\tPublished \n");
            if(topp<=-20)
            {
                topp = topp;
                printf("Down Safe Zone Reached !!\n");
            }
            else
            {
                topp=topp-10;
            }

            joint_command.request.unit = "rad";
            joint_command.request.id = 2;//bottom
            joint_command.request.goal_position = bottomm*PI/180;
            joint_command.request.unit = "rad";
            joint_command.request.id = 1;//top
            joint_command.request.goal_position = topp*PI/180;
            joint_command_client.call(joint_command);
            head_bottom.data=bottomm;
            head_top.data=topp;
            pub13.publish(head_bottom);
            pub12.publish(head_top);
            //printf("xtion turn down\n");
            //printf("bottom:%.1f,top:%.1f\t\t",bottomm-bottom,topp-top);//ROS_INFO("bottom:%f,top:%f", bottomm,topp);
            ros::spinOnce();
        }

        if(y!=27&&y!=91)//for arrow key "^[[A" or "^[[B" or "^[[C" or "^[[D"
        {
            printf("bottom : %.1f , top : %.1f\t",bottomm-bottom,topp-top);
            printf("speed_left = %d , speed_right = %d \n",vv1,vv2);
        }

        loop_rate.sleep();

    }

    return 0;
}
