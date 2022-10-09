#include "wheel_odom.h"

wheel_odom::wheel_odom(){
	sub = n.subscribe<geometry_msgs::Twist>("/chassis/whell_data", 100, &wheel_odom::callback, this);
	pub = n.advertise<nav_msgs::Odometry>("/wheel_odom", 100);
	tf::TransformBroadcaster odom_broadcaster;
}

void wheel_odom::callback(const geometry_msgs::Twist::ConstPtr& odom_data){
	current_time = ros::Time::now();
	std::cout 	<< "x:" << x << std::endl <<"dt:" << dt << std::endl 
				<<"th:" << th << std::endl << "vx:" << vx << std::endl << std::endl;
    dt = 0.08;
    vx = (odom_data->linear.x) * cos(th);
	vy = (odom_data->linear.x) * sin(th);
	vth = (odom_data->linear.y-odom_data->linear.z)/0.6028;
    delta_x = vx * dt;
    delta_y = vy * dt;
	delta_th = vth * dt;
    x = x + delta_x;
    y = y + delta_y;
	th = th + delta_th;
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
	nav_msgs::Odometry odom;
	odom.header.stamp = current_time;
	odom.header.frame_id = "odom";
	odom.pose.pose.position.x = x;
	odom.pose.pose.position.y = y;
	odom.pose.pose.position.z = 0.0;
	odom.pose.pose.orientation = odom_quat;
	odom.child_frame_id = "base_link";
	odom.twist.twist.linear.x = vx;
	odom.twist.twist.linear.y = vy;
	odom.twist.twist.angular.z = vth;
	pub.publish(odom);
	last_time = ros::Time::now();
	        usleep(80 * 1000); //100ms
}

int main(int argc, char** argv){
	ros::init(argc, argv, "wheel_odom");
    wheel_odom wheel_odom;
		// std::cout <<"kkkk" <<std::endl;
    ros::spin();
    return 0;
}
