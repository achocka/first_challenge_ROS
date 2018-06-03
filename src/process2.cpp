#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>


void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  std::string input2;
  std_msgs::String msg_out;

  ROS_INFO("I heard: [%s]", msg->data.c_str());

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::String>("process2", 1000);

  std::cout << "Enter Second Integer between 0 and 1000:" << '\n';
  std::cin >> input2;
  std::cout << "Inputted value:" << input2;

  int input_val = std::stoi(input2);

  if((input_val < 1000) && (input_val >0))
  {
    msg_out.data = input2;
    ROS_INFO("send Out: [%s]", msg_out.data.c_str());
    pub.publish(msg_out);
    ros::spinOnce();
  }

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "process2");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("process1", 1000, chatterCallback);

  ros::spin();

  return 0;
}
