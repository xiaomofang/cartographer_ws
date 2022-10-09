#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include "carto_test/odom2tum.h"
ros::Publisher pub_gps;
ros::Publisher pub_carto;

void callback_gps(const nav_msgs::Odometry::ConstPtr& odom)
{
    carto_test::odom2tum msg;
    msg.x = odom->pose.pose.position.x;
    msg.y = odom->pose.pose.position.y;
    msg.z = odom->pose.pose.position.z;
    msg.q_x = odom->pose.pose.orientation.x;
    msg.q_y = odom->pose.pose.orientation.y;
    msg.q_z = odom->pose.pose.orientation.z;
    msg.q_w = odom->pose.pose.orientation.w;
    pub_gps.publish(msg);
    ROS_INFO("gps ok");
}
void callback_carto(const nav_msgs::Odometry::ConstPtr& odom)
{
    carto_test::odom2tum msg;
    msg.x = odom->pose.pose.position.x;
    msg.y = odom->pose.pose.position.y;
    msg.z = odom->pose.pose.position.z;
    msg.q_x = odom->pose.pose.orientation.x;
    msg.q_y = odom->pose.pose.orientation.y;
    msg.q_z = odom->pose.pose.orientation.z;
    msg.q_w = odom->pose.pose.orientation.w;
    pub_carto.publish(msg);
    ROS_INFO("carto ok");
}
int main (int argc, char **argv)
{
    ros::init (argc, argv, "odom2tum");
    ros::NodeHandle n;

    pub_gps = n.advertise<carto_test::odom2tum>("tum_gps", 10, true);
    pub_carto = n.advertise<carto_test::odom2tum>("tum_carto", 10, true);
    ros::Subscriber sub_gps = n.subscribe<nav_msgs::Odometry>("/odom/by_gps", 10, callback_gps);
    ros::Subscriber sub_carto = n.subscribe<nav_msgs::Odometry>("/carto_odom", 10, callback_carto);
    ros::Rate loop_rate(50);
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
