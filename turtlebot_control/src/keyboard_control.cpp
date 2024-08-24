#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "keyboard_control");
    ros::NodeHandle nh;

    ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist cmd_msg;

    ROS_INFO("Keyboard control node started.");

    while (ros::ok()) {
        char c = getch();
        ROS_INFO("Key pressed: %c", c); // Debugging output

        switch (c) {
        case 'w':
            cmd_msg.linear.x = 1.0;
            cmd_msg.angular.z = 0.0;
            break;
        case 's':
            cmd_msg.linear.x = -1.0;
            cmd_msg.angular.z = 0.0;
            break;
        case 'a':
            cmd_msg.linear.x = 0.0;
            cmd_msg.angular.z = 1.0;
            break;
        case 'd':
            cmd_msg.linear.x = 0.0;
            cmd_msg.angular.z = -1.0;
            break;
        case 'x':
            cmd_msg.linear.x = 0.0;
            cmd_msg.angular.z = 0.0;
            break;
        default:
            continue;
        }
        ROS_INFO("Publishing command: linear.x = %f, angular.z = %f", cmd_msg.linear.x, cmd_msg.angular.z); // Debugging output
        cmd_pub.publish(cmd_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
