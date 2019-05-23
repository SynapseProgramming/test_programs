#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <iostream>

//when using classes, it is best to enable c++11 compilation in the Cmake lists txt file.

class pubstuff{
public://public members of the class can be accessed by stuff outside the class.
// constructor of the class. over here, we would have to initialise objects and variables.
pubstuff():
pub(n.advertise<std_msgs::Int32>("anumber",100)),  loop_rate(10)//initialise the loop rate object, which we have defined as a private member of this class. objects in classes must be initialised here.
{
std::cout<<"just instantiated a pubstuff object."<<std::endl;//stuff to do when the constructor function is called.
}

void send_counted_number(){//the send counted number function sends out numbers 1 to 9 on the topic of anumber, till the program is killed.
while(n.ok()){
number+=1;//add 1 to number
if(number==10){number=0;}//if number has the value of 10, reset the value of number.
std_msgs::Int32 sendnumber;//create a int32 variable.

sendnumber.data=number;//copy data into sendnumber.
pub.publish(sendnumber);//publish the message.

print_counted_number();//call the print counted number function. This statement shows that functions in the same class can call each other.
loop_rate.sleep();
}

}// send counted number bracket

void print_counted_number(){
std::cout<<"the send counted number is: "<<number<<std::endl;
}

private://private members of the class can only be accessed by members within the class.
ros::NodeHandle n; //create the nodehandle.
ros::Publisher pub;//declare the ros publisher.
ros::Rate loop_rate; //declare the loop rate object.
int number=0;

};

int main(int argc, char **argv){
ros::init(argc,argv,"class_test");
// create the pubstuff object.
pubstuff obj;
//call the send counted number function.
obj.send_counted_number();

ros::spin();
return 0;}
