#include "ros/ros.h"
#include "test_programs/intarray.h"
#include <iostream>

// This is the publisher object
ros::Publisher pub;

// the callback function is called when an array from labview arrives.
void callback(const test_programs::intarray::ConstPtr &arr){
// create intarray variable to send data to.
test_programs::intarray send;
//set the size of the send variable(VERY IMPORTANT)
send.data.resize(3);
// we can use the for loop to transfer data from the raw laserscan topic to the data variable in the laserscan message.
for(int i=0; i<3; i++){
std::cout<<"The "<<(i+1)<< " element of the array is: "<<arr->data[i]<<std::endl;
//copy data from the received array to the send array
send.data[i]=arr->data[i];
}

//once all of the required elements have beeen copied, publish the data.
pub.publish(send);

}

int main(int argc, char**argv){

//run the ros init function.
ros::init(argc,argv,"arraysub");
//create the nodehandle.
ros::NodeHandle n;
//create a subscriber object
ros::Subscriber sub=n.subscribe("array",1000,callback);
//define the publisher object.
pub=n.advertise<test_programs::intarray>("thearr",1000);

ros::spin();

return 0;
}
