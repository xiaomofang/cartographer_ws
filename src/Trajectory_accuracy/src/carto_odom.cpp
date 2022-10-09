#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "carto_odom");
    ros::NodeHandle(n);
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("carto_odom", 1);
    double position_x, position_y, orientation_x, orientation_y, orientation_z, orientation_w;
    nav_msgs::Odometry tmp;

    ros::Time current_time, last_time;
    double current_x, last_x, current_yaw, last_yaw, lin_speed, ang_speed;
    while (ros::ok())
    {
        n.getParam("position_x",position_x);
        n.getParam("position_y",position_y);
        n.getParam("orientation_x",orientation_x);
        n.getParam("orientation_y",orientation_y);
        n.getParam("orientation_z",orientation_z);
        n.getParam("orientation_w",orientation_w);
        current_time = ros::Time::now();
        current_x = position_x;
        tmp.pose.pose.orientation.x = orientation_x;
        tmp.pose.pose.orientation.y = orientation_y;
        tmp.pose.pose.orientation.z = orientation_z;
        tmp.pose.pose.orientation.w = orientation_w;
        current_yaw = tf::getYaw(tmp.pose.pose.orientation);
        nav_msgs::Odometry msg;
        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "odom";
        msg.child_frame_id = "rslidar";
        msg.pose.pose.position.x = position_x;
        msg.pose.pose.position.y = position_y;
        msg.pose.pose.orientation.x = orientation_x;
        msg.pose.pose.orientation.y = orientation_y;
        msg.pose.pose.orientation.z = orientation_z;
        msg.pose.pose.orientation.w = orientation_w;
        lin_speed = (current_x - last_x)/((current_time - last_time).toSec());
        ang_speed = (current_yaw - last_yaw)/((current_time - last_time).toSec());
        msg.twist.twist.linear.x = lin_speed;
        msg.twist.twist.angular.z = ang_speed;
        pub.publish(msg);
        n.getParam("position_x",position_x);
        n.getParam("position_y",position_y);
        n.getParam("orientation_x",orientation_x);
        n.getParam("orientation_y",orientation_y);
        n.getParam("orientation_z",orientation_z);
        n.getParam("orientation_w",orientation_w);
        last_time = ros::Time::now();
        last_x = position_x;
        tmp.pose.pose.orientation.x = orientation_x;
        tmp.pose.pose.orientation.y = orientation_y;
        tmp.pose.pose.orientation.z = orientation_z;
        tmp.pose.pose.orientation.w = orientation_w;
        last_yaw = tf::getYaw(tmp.pose.pose.orientation);
        usleep(80 * 1000); //100ms
    }
    ros::spin();
    std::cout << "\n\n结束odom发布\n\n";
    return 0;
}
