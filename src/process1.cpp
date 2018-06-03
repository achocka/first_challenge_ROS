#include "ros/ros.h"
#include "std_msgs/String.h"

#include <string>
#include <iostream>

std::string input;

void receive(const std_msgs::String::ConstPtr& msg)
{
  std::cout << " I heard Second Int to be:" << msg->data.c_str();

  int sum = std::stoi(input) + std::stoi(msg->data);
  std::cout << "\nTOTAL SUM: " << sum;

  ROS_INFO("\nI heard: [%s]", msg->data.c_str());
}

void send()
{
    ros::NodeHandle node;
    ros::Publisher chatter_pub = node.advertise<std_msgs::String>("process1", 1000, send);

    ros::Rate loop_rate(1000);

    if(ros::ok())
    {
      std_msgs::String msg;

      std::cout << "Enter First Integer between 0 and 1000:" << '\n';
      std::cin >> input;
      std::cout << "Inputted value:" << input;

      int input_val = std::stoi(input);

      if((input_val < 1000) && (input_val >0))
      {
        msg.data = input;
        ROS_INFO("send Out: [%s]", msg.data.c_str());
        chatter_pub.publish(msg);
        loop_rate.sleep();
        ros::spinOnce();
      }
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "process1");

  ros::NodeHandle node;

  send();

  ros::Subscriber sub = node.subscribe<std_msgs::String>("process2", 1000, receive);

  ros::spin();
  return 0;
}
