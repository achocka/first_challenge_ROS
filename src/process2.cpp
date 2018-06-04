#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include <iostream>
#include <limits>

int globalInput = -1;

int getInput()
{
  int input;

  bool valid = false;

  do
  {
    std::cout << "Enter Second Integer between 0 and 1000:" << '\n';
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

class Pub_Sub
{
public:
  Pub_Sub()
  {
    pub = n.advertise<std_msgs::Int64>("process2", 1000);
    sub = n.subscribe("process1", 1000, &Pub_Sub::callBack, this);
  }

  void callBack(const std_msgs::Int64::ConstPtr&msg)
  {
    ROS_INFO("I heard: [%d]", msg->data);
    if((msg->data) != NULL){
      globalInput = getInput();
    }

    ros::Rate loop_rate(1000);
    if(ros::ok() && globalInput != -1)
    {
      std_msgs::Int64 msg;
      msg.data = globalInput;
      ROS_INFO("send Out: [%d]", msg.data);
      pub.publish(msg);
      loop_rate.sleep();
    }
  }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "process2");

  Pub_Sub publish;
  ros::spin();
  return 0;
}
