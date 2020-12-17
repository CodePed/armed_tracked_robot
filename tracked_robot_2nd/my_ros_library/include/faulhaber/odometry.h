#ifndef _ODOMETRY_H_
#define _ODOMETRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int32MultiArray.h"

#include "tf/tf.h"
#include "tf/transform_broadcaster.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>

#define PI 3.14159                                  //Define Circular Ratio as Constant -> PI
#define MOTOR_RESOLUTION 2048                       //Resolution of a Faulhaber Motor (2048 / per cycle)
#define GEAR_RATIO 50                               //Ratio of a Gear Box
#define WHEEL_RADIUS 0.06828                        //Radius of the Tracked Robot's Wheel
#define ROBOT_WIDTH 0.84112                         //Width of the Tracked Robot

#define WHEEL_CIRCUMFERENCE 2 * PI * WHEEL_RADIUS   //Define Circumference of a Tracked Robot's Wheel with Formula -> 2 * PI * r
#define TURN_RATIO MOTOR_RESOLUTION * GEAR_RATIO    //Convert Position to Turns betweenear Encoder and the Wheel with a Gear Box of the Tracked Robot (Motor_Resolution * Gear_Ratio / per turn)

using namespace std;

class Odometry
{
    public:

        Odometry();
        ~Odometry();
        void Set_Odometry(const std_msgs::Int32MultiArray::ConstPtr &msg);
        void Update_Odometry(const std_msgs::Int32MultiArray::ConstPtr &msg);
        void Publish_Odometry(double x , double y , double theta);

    private:

        ros::NodeHandle nh;
        ros::Publisher  pub_odometry;
        ros::Subscriber sub_encoder;
        ros::Subscriber sub_set_odometry;
        ros::Subscriber sub_reset_odometry;

        ros::Time current_time , previous_time;                 //Time Variable
        tf::TransformBroadcaster tf_transfrom_broadcaster_odom;

        std::vector<int>Encoders{0,0,0,0};                      //Encoder[i]
        double dt{0};                                            //Sampling Time
        double x{0};
        double y{0};
        double theta{0};
        double dtheta{0};
        double right_turns,left_turns,left_turns_previous,right_turns_previous,left_distance,right_distance;
        double mean_distance;
        double vx{0};
        double vy{0};
        double vtheta{0};
        double left_velocity,right_velocity;

};
#endif
