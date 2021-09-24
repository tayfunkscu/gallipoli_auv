#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include <termios.h>

int getch()
{
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "teleop_key");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<std_msgs::UInt16>("direction", 1000);
    ros::Publisher vertical_pub = n.advertise<std_msgs::UInt16>("vertical_direction", 1000);

    ros::Rate loop_rate(10);
    std_msgs::UInt16 direction;
    std_msgs::UInt16 vertical_direction;

    while (ros::ok())
    {
        int c = getch();

        if (c == 'w')
        {
            direction.data = 8;
            pub.publish(direction);
        }
        else if (c == 's')
        {
            direction.data = 2;
            pub.publish(direction);
        }
        else if (c == 'a')
        {
            direction.data = 4;
            pub.publish(direction);
        }
        else if (c == 'd')
        {
            direction.data = 6;
            pub.publish(direction);
        }
        else if (c == 'p')
        {
            direction.data = 5;
            pub.publish(direction);
        }
        else if (c == 'z')
        { // Left in y axis
            direction.data = 1;
            pub.publish(direction);
        }
        else if (c == 'x')
        { // Right in y axis
            direction.data = 3;
            pub.publish(direction);
        }
        else if (c == 'c')
        { // Left corner
            direction.data = 10;
            pub.publish(direction);
        }
        else if (c == 'v')
        { // Right corner
            direction.data = 11;
            pub.publish(direction);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}