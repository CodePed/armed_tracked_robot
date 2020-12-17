#include "faulhaber/odometry.h"

Odometry::Odometry()
{
    sub_encoder = nh.subscribe("/faulhaber/encoder",10,&Odometry::Update_Odometry,this);
    sub_set_odometry = nh.subscribe("/set_odom",10,&Odometry::Set_Odometry,this);
    pub_odometry = nh.advertise<nav_msgs::Odometry>("/odom",10);
    current_time = ros::Time::now();
    previous_time = ros::Time::now();
}

Odometry::~Odometry()
{

    printf("Odometry Shutdown !\n");
}

void Odometry::Set_Odometry(const std_msgs::Int32MultiArray::ConstPtr &msg)
{
    x = msg->data[0];
    y = msg->data[1];
    theta = msg->data[2];
}

void Odometry::Update_Odometry(const std_msgs::Int32MultiArray::ConstPtr &msg)
{
    current_time = ros::Time::now();                                 //Get Time->Now
    dt = (current_time - previous_time).toSec();                     //Get Sampling Time

    Encoders.clear();                                                  //Flush Encoders

    for(int i = 0 ; i < 4 ; i++)
    {
        Encoders.push_back(msg->data[i]);                            //Update Encoders' Data
    }

    right_turns = -Encoders[1] / TURN_RATIO;                    //Get Right Wheel Turns
    left_turns  =  Encoders[2] / TURN_RATIO;                    //Get Left  Wheel Turns

    right_distance = WHEEL_CIRCUMFERENCE * (right_turns - right_turns_previous);    //Calculate how far Right Wheel have Driven during Sampling Time
    left_distance  = WHEEL_CIRCUMFERENCE * (left_turns - left_turns_previous);      //Calculate how far Left  Wheel have Driven during Sampling Time

    dtheta = (right_distance - left_distance) / ROBOT_WIDTH;    //Get dtheta

    theta = fmod( theta + dtheta , 2 * PI );                          //Update theta

    mean_distance = (right_distance + left_distance) / 2;

    x = x + mean_distance * cos(theta);
    y = y + mean_distance * sin(theta);

    right_velocity = right_distance / dt;
    left_velocity  = left_distance  / dt;

    vx = mean_distance * cos(theta) / dt;
    vy = mean_distance * sin(theta) / dt;

    vtheta = dtheta / dt;

    right_turns_previous = right_turns;
    left_turns_previous  = left_turns;

    previous_time = current_time;

    cout << "vL: " << left_velocity << " vR: " << right_velocity <<endl;
    cout << "vx: " << vx << " vy: " << vx <<endl;
    cout << "LPos: " << left_turns << " RPos: " << right_turns <<endl;
    cout << "SL: " << left_distance << " SR: " << right_distance << " SMean: " << mean_distance <<endl;
    cout << "x: " << x << " y: " << y << " theta: " << theta / (PI/180) <<endl<<endl;

    Publish_Odometry(x,y,theta);
}

void Odometry::Publish_Odometry(double x , double y , double theta)
{
    //construct a Quaternion Message from yaw only (about the Z axis)

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    tf_transfrom_broadcaster_odom.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS

    nav_msgs::Odometry odom;// ob'_'ov
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //Position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //Velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vtheta;


    pub_odometry.publish(odom);//Publish odom message
    printf("Odometry has published ...\n");
}
