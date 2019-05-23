#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <iostream>

class transform_pub{
public:
transform_pub(){

//initialise the position variables
tx=2.0;
ty=0;
tz=0;
rr=0;
rp=0;
ry=0;
}

void sendTransform(){

//create the transform variable to send over
tf::Transform tf_send;
//set the xyz translation values
tf_send.setOrigin(tf::Vector3(tx,ty,tz));
//specify the rpy rotation values as save them as a quaternion
tf::Quaternion q;
q.setRPY(rr,rp,ry);
//save the rotational values in the transform variable
tf_send.setRotation(q);
//send the transform over tf
//the stamped transform function timestamps the transform variable
//StampedTransform(transfrom, time,frame_id,child_frame_id)
br.sendTransform(tf::StampedTransform(tf_send,ros::Time::now(),"odom","base_link"));
}

private:

double tx,ty,tz;
double rr,rp,ry;

ros::NodeHandle n;
tf::TransformBroadcaster br;

};

int main(int argc, char **argv){
ros::init(argc,argv,"transform_publisher_test");
//the transform object must be called first before loop rate, as it calls
// the instance of a nodehandle for this thread
transform_pub tfpub;
ros::Rate loop_rate(10);//we will publish the transform at 10 hz


while(ros::ok()){

tfpub.sendTransform();
loop_rate.sleep();
std::cout<<"currently sending out transform! "<<std::endl;
ros::spinOnce();
}

return 0;}
