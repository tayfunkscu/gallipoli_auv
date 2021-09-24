#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "gallipoli_msgs/Motorpwm.h"
#include <termios.h>

gallipoli_msgs::Motorpwm data;
int forward = 1700;
int backward = 1300;
int forward_r = 1600;
int backward_r = 1400;
int stop_sig = 1500;

void direction_cb(const std_msgs::UInt16 &direction_msg)
{
    if (direction_msg.data == 8)
    {
        data.m1 = forward;
        data.m2 = forward;
        data.m3 = forward;
        data.m4 = forward;
    }
    else if (direction_msg.data == 2)
    {
        data.m1 = backward;
        data.m2 = backward;
        data.m3 = backward;
        data.m4 = backward;
    }
    else if (direction_msg.data == 4)
    {
        data.m1 = forward_r;
        data.m2 = backward_r;
        data.m3 = forward_r;
        data.m4 = backward_r;
    }
    else if (direction_msg.data == 6)
    {
        data.m1 = backward_r;
        data.m2 = forward_r;
        data.m3 = backward_r;
        data.m4 = forward_r;
    }
    else if (direction_msg.data == 5)
    {
        data.m1 = stop_sig;
        data.m2 = stop_sig;
        data.m3 = stop_sig;
        data.m4 = stop_sig;
    }
    else if (direction_msg.data == 1)
    {
        data.m1 = backward;
        data.m2 = backward;
        data.m3 = forward;
        data.m4 = forward;
    }
    else if (direction_msg.data == 3)
    {
        data.m1 = forward;
        data.m2 = forward;
        data.m3 = backward;
        data.m4 = backward;
    }
    else if (direction_msg.data == 10)
    { // left cross
        data.m1 = 1600;
        data.m2 = 1600;
        data.m3 = 1700;
        data.m4 = 1700;
    }
    else if (direction_msg.data == 11)
    { // Right cross
        data.m1 = 1700;
        data.m2 = 1700;
        data.m3 = 1600;
        data.m4 = 1600;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "teleop_to_pwm");
    ros::NodeHandle n;

    ros::Subscriber direction_sub = n.subscribe("direction", 1000, direction_cb);
    ros::Publisher pub = n.advertise<gallipoli_msgs::Motorpwm>("direction_pwm", 1000);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        pub.publish(data);

        ros::spinOnce();
        loop_rate.sleep();
    }
}