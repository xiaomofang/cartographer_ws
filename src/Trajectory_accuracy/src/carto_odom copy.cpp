#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <unistd.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "carto_odom");
    ros::NodeHandle(n);
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("carto_odom_test", 1);
    double  carto_x, carto_y, carto_yaw, carto_qx, carto_qy, carto_qz, carto_qw,
            aruco_x, aruco_y, aruco_yaw, aruco_qx, aruco_qy, aruco_qz, aruco_qw,
            update_x, update_y, update_yaw, update_qx, update_qy, update_qz, update_qw;
    double  current_carto_x,  current_carto_y, current_carto_yaw, current_carto_qx, current_carto_qy, current_carto_qz, current_carto_qw,
            last_carto_x,     last_carto_y,    last_carto_yaw,    last_carto_qx,    last_carto_qy,    last_carto_qz,    last_carto_qw,
            current_update_x, current_update_yaw,
            last_update_x,    last_update_yaw,
            lin_speed, ang_speed;
    int flag;
    ros::Time current_time, last_time;
    while (ros::ok())
    {
        n.getParam("carto_x",carto_x);
        n.getParam("carto_y",carto_y);
        n.getParam("carto_yaw",carto_yaw);
        n.getParam("carto_qx",carto_qx);
        n.getParam("carto_qy",carto_qy);
        n.getParam("carto_qz",carto_qz);
        n.getParam("carto_qw",carto_qw);
        n.getParam("flag",flag);
        n.getParam("aruco_x",aruco_x);
        n.getParam("aruco_y",aruco_y);
        n.getParam("aruco_yaw",aruco_yaw);
		n.getParam("aruco_qx", aruco_qx);
		n.getParam("aruco_qy", aruco_qy);
		n.getParam("aruco_qz", aruco_qz);
		n.getParam("aruco_qw", aruco_qw);

        current_time = ros::Time::now();
        current_carto_x = carto_x;
        current_carto_y = carto_y;
        current_carto_yaw = carto_yaw;
        current_carto_qx = carto_qx;
        current_carto_qy = carto_qy;
        current_carto_qz = carto_qz;
        current_carto_qw = carto_qw;
        if(flag ==1)
        {
            update_x = aruco_x;
            update_y = aruco_y;
            update_yaw = aruco_yaw;
            update_qx = aruco_qx;
            update_qy = aruco_qy;
            update_qz = aruco_qz;
            update_qw = aruco_qw;
        }
        else if(flag == 0)
        {
            update_x = update_x + current_carto_x - last_carto_x;
            update_y = update_y + current_carto_y - last_carto_y;
            update_yaw = update_yaw + current_carto_yaw - last_carto_yaw;
            update_qx = update_qx + current_carto_qx - last_carto_qx;
            update_qy = update_qy + current_carto_qy - last_carto_qy;
            update_qz = update_qz + current_carto_qz - last_carto_qz;
            update_qw = update_qw + current_carto_qw - last_carto_qw;
        }
        current_update_x = update_x;
        current_update_yaw = update_yaw;


        nav_msgs::Odometry msg;
        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "odom";
        msg.child_frame_id = "rslidar";
        msg.pose.pose.position.x = update_x;
        msg.pose.pose.position.y = update_y;
        msg.pose.pose.orientation.x = update_qx;
        msg.pose.pose.orientation.y = update_qy;
        msg.pose.pose.orientation.z = update_qz;
        msg.pose.pose.orientation.w = update_qw;
        lin_speed = (current_update_x - last_update_x)/((current_time - last_time).toSec());
        ang_speed = (current_update_yaw - last_update_yaw)/((current_time - last_time).toSec());
        msg.twist.twist.linear.x = lin_speed;
        msg.twist.twist.angular.z = ang_speed;
        pub.publish(msg);
        
        n.getParam("carto_x",carto_x);
        n.getParam("carto_y",carto_y);
        n.getParam("carto_yaw",carto_yaw);
        n.getParam("carto_qx",carto_qx);
        n.getParam("carto_qy",carto_qy);
        n.getParam("carto_qz",carto_qz);
        n.getParam("carto_qw",carto_qw);
        n.getParam("flag",flag);
        n.getParam("aruco_x",aruco_x);
        n.getParam("aruco_y",aruco_y);
        n.getParam("aruco_yaw",aruco_yaw);
		n.getParam("aruco_qx", aruco_qx);
		n.getParam("aruco_qy", aruco_qy);
		n.getParam("aruco_qz", aruco_qz);
		n.getParam("aruco_qw", aruco_qw);

        last_time = ros::Time::now();
        last_carto_x = carto_x;
        last_carto_y = carto_y;
        last_carto_yaw = carto_yaw;
        last_carto_qx = carto_qx;
        last_carto_qy = carto_qy;
        last_carto_qz = carto_qz;
        last_carto_qw = carto_qw;
        if(flag ==1)
        {
            update_x = aruco_x;
            update_y = aruco_y;
            update_yaw = aruco_yaw;
            update_qx = aruco_qx;
            update_qy = aruco_qy;
            update_qz = aruco_qz;
            update_qw = aruco_qw;
        }
        else if(flag == 0)
        {
            update_x = update_x;
            update_y = update_y;
            update_yaw = update_yaw;
            update_qx = update_qx;
            update_qy = update_qy;
            update_qz = update_qz;
            update_qw = update_qw;
        }
        last_update_x = update_x;
        last_update_yaw = update_yaw;

        usleep(80 * 1000); //100ms
    }
    ros::spin();
    std::cout << "\n\n结束odom发布\n\n";
    return 0;
}


