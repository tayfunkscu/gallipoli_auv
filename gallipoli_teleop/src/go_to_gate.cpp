#include "ros/ros.h"
#include "ros/console.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "gallipoli_msgs/Motorpwm.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

int ref_x = 320;
int last_diff{1000};
bool turn = true;
gallipoli_msgs::Motorpwm data;

void x(const darknet_ros_msgs::BoundingBoxes &bbox_msg)
{
    auto msg = bbox_msg.bounding_boxes;
    int diff = ref_x - msg.back().xcenter;
    last_diff = diff;
    std::cout << "X center: " << msg.back().xcenter << std::endl;
    std::cout << "Diff: " << diff << std::endl;

    turn = false;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "go_to_gate");
    ros::NodeHandle n;
    ros::Subscriber bbox_sub = n.subscribe("/darknet_ros/bounding_boxes", 1000, x);
    ros::Publisher direction_pwm_pub = n.advertise<gallipoli_msgs::Motorpwm>("direction_pwm", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
    {

        if (turn)
        {
            data.m1 = 1550;
            data.m2 = 1450;
            data.m3 = 1550;
            data.m4 = 1450;
        }
        else
        {
            if (abs(last_diff) > 120)
            {
                if (last_diff > 0)
                {
                    data.m1 = 1450;
                    data.m2 = 1550;
                    data.m3 = 1450;
                    data.m4 = 1550;
                }
                else
                {
                    data.m1 = 1550;
                    data.m2 = 1450;
                    data.m3 = 1550;
                    data.m4 = 1450;
                }
            }
            else
            {
                data.m1 = 1600;
                data.m2 = 1600;
                data.m3 = 1600;
                data.m4 = 1600;
            }
        }

        direction_pwm_pub.publish(data);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
