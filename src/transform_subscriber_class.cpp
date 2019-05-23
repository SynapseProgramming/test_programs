#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <iostream>



class get_transform{
public:

void print_transform(const std::string &parent_frame,const std::string &child_frame){
tf::StampedTransform received_transform;

try{
//lookupTransform(parent frame,child frame) gets transform from parent frame to child frame.
listener.lookupTransform(parent_frame,child_frame,ros::Time(0),received_transform);

}
//if an exception has occured, print out what went wrong
catch(tf::TransformException &ex){
ROS_ERROR("%s",ex.what());
ros::Duration(1.0).sleep();
}
//if nothing went wrong(yay), we would obtain the transform data
//over here, we would get the xyz transforms
tx=received_transform.getOrigin().x();
ty=received_transform.getOrigin().y();
tz=received_transform.getOrigin().z();

//tf::Quaternion received_q;
//received_q=received_transform.getRotation();

//actually print out the text
std::cout<<"From: "<<parent_frame<<" To "<<child_frame<<"X:"<<tx<<" Y:"<<ty<<" Z:"<<tz<<std::endl;

}




private:
tf::TransformListener listener;
ros::NodeHandle n;
double tx,ty,tz;
//double rr,rp,ry;

};

int main(int argc, char **argv){
const std::string parent_frame="/odom", child_frame="/base_link";


ros::init(argc,argv,"Transform_Listener");
get_transform trans;
ros::Rate loop_rate(20);
while(ros::ok()){
trans.print_transform(parent_frame,child_frame);

loop_rate.sleep();
ros::spinOnce();
}




return 0;}
