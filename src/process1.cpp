#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include <iostream>
#include <limits>


int input_Val;

void receive(const std_msgs::Int64::ConstPtr& msg)
{
  std::cout << " I heard Second Int to be:" << msg->data;

  int sum = input_Val + msg->data;
  std::cout << "\nTOTAL SUM: " << sum;

  ROS_INFO("\nI heard: [%d]", msg->data);
}

int getInput()
{
  int input;

  bool valid = false;

  do
  {
    std::cout << "Enter First Integer between 0 and 1000:" << '\n';
    std::cin >> input;
    std::cout << "Inputted value:" << input;

    if(std::cin.good() && (input < 1000) && (input > 0)){
      valid = true;
      return input;
    }
    else{
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid Input. Please Enter Again." << '\n';
    }
  } while(!valid);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "process1");

  ros::NodeHandle node;

  ros::Publisher pub = node.advertise<std_msgs::Int64>("process1", 1000);
  ros::Subscriber sub = node.subscribe("process2", 1000, receive);

  input_Val = getInput();
  ros::Rate loop_rate(1000);

  while(ros::ok())
  {
    std_msgs::Int64 msg;
    msg.data = input_Val;
    ROS_INFO("send Out: [%d]", msg.data);
    pub.publish(msg);
    loop_rate.sleep();
    ros::spin();
  }

  ros::spin();
  return 0;
}
