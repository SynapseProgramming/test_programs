#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <iostream>


class substuff {
public:

  substuff() :
    sub(n.subscribe<std_msgs::Int32>("anumber", 5, &substuff::subcb, this))
  {
    std::cout << "Substuff object has been created!" << std::endl;
  }

  void subcb(const std_msgs::Int32::ConstPtr& msg)
  {
    std::cout << "received: " << msg->data << std::endl;
  }

private:

  ros::NodeHandle n;
  ros::Subscriber sub;
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "class_subscriber");

  // we will create the substuff object here.
  substuff obj;


  ros::spin();
  return 0;
}
