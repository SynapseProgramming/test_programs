#include <ros/ros.h>
#include "test_programs/velocitycommands.h"
#include <iostream>

int main(int argc, char**argv){
ros::init(argc,argv,"velocity_sender");
ros::NodeHandle n;
ros::Publisher pub=n.advertise<test_programs::velocitycommands>("velocity",100);

ros::Rate loop_rate(20);

float count=0;

while(ros::ok()){
test_programs::velocitycommands vel;
vel.angular=count+1.048987;
vel.linear=count+2.489877;
std::cout<<"Sending linear velocity of: "<<vel.linear<<std::endl;
std::cout<<"Sending angular velocity of: "<<vel.angular<<std::endl;
pub.publish(vel);




loop_rate.sleep();

ros::spinOnce();
count++;
}





return 0;}
