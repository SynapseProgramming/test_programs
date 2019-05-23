#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

//create the publisher object(unreferenced at first)
ros::Publisher chatter_pub;


void chatterCallback(const std_msgs::Int32::ConstPtr &number)
{
  std::cout<<"I have received: "<<number->data<<std::endl;
  std_msgs::Int32 tosend;
  tosend.data=(number->data)+10;
  chatter_pub.publish(tosend);
}

int main(int argc, char **argv)
{
//run the initializer for ros
  ros::init(argc, argv, "ROSADDTEN");

//create the ros nodehandle.
  ros::NodeHandle n;

/*
subscribe to the topic of (anumber). when a message is received on the topic, call the function chatterCallback.
*/
  ros::Subscriber sub = n.subscribe("anumber", 1000, chatterCallback);
//define the publisher, and the topic that it should send messages to.
  chatter_pub = n.advertise<std_msgs::Int32>("addedten", 1000);

  ros::spin();


  return 0;
}
