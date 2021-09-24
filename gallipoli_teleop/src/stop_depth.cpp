#include "ros/ros.h"
#include "gallipoli_msgs/Motorpwm.h"
#include "std_msgs/Float64.h"

std_msgs::Float64 depth;
gallipoli_msgs::Motorpwm vertical_pwm;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_depth");

    ros::NodeHandle n;
    ros::Publisher vertical_pwm_pub = n.advertise<gallipoli_msgs::Motorpwm>("vertical_pwm", 1000);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        vertical_pwm.m1 = 1500;
        vertical_pwm.m2 = 1500;
        vertical_pwm.m3 = 1500;
        vertical_pwm.m4 = 1500;

        vertical_pwm_pub.publish(vertical_pwm);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}