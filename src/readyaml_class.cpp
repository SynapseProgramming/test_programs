#include <ros/ros.h>
#include <iostream>

class read_yaml{
public:
read_yaml(){
if(
n.getParam("integer",a)!=true
||n.getParam("double",b)!=true
)
{ROS_ERROR("yaml parameters could not be loaded! please check the yaml file!");}


}//constructor bracket

void print_values(){
std::cout<<"a: "<<a<<" b: "<<b<<std::endl;
}

private:
ros::NodeHandle n;
int a;
double b;

};





int main(int argc, char **argv){
ros::init(argc,argv,"read_yaml");

read_yaml obj;

obj.print_values();

std::cin.get();
return 0;}
