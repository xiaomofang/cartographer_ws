#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <unistd.h>
#include <iomanip>
class wheel_odom{
	private:
		ros::NodeHandle n;
		ros::Publisher pub;
		ros::Subscriber sub;
		ros::Time current_time, last_time;
        double x = 0.0;
        double y = 0.0;
        double th = 0.0;
        double vx = 0.0;
        double vy = 0.0;
        double vth = 0.0;
		double dt = 0.0;
		double delta_x = 0.0;
		double delta_y = 0.0;
		double delta_th = 0.0;
	public:
		wheel_odom();
		void callback(const geometry_msgs::Twist::ConstPtr& odom_data);
};
