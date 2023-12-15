#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
std_msgs::String msg;
  
void chatterCallback(const std_msgs::String::ConstPtr& msg1)
{
  ROS_INFO("I heard: [%s]", msg1->data.c_str());
  msg.data=msg1->data;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mojnode");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("RaptorIN", 1000, chatterCallback);
  //ros::spin();

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("RaptorOUT", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    std::stringstream ss;
    ss << msg.data << " Aleksandra Bara " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 0;
}

