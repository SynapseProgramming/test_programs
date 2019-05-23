#include <ros/ros.h>
#include <iostream>


int main(int argc, char **argv){
ros::init(argc,argv,"yamltest");

//create variables to store the parameters from the text file
std::vector<double> x,y,w,z;

//initialise the ros nodehandle
ros::NodeHandle n;


//the getparam function gets the param values from the yaml text file.
if(n.getParam("x",x)&&n.getParam("y",y)&&n.getParam("z",z)&&n.getParam("w",w)){


//print out the elements in the arrays, only if the number of elements in all of them match.
int net_elements=x.size();
if(y.size()==net_elements&&z.size()==net_elements&&w.size()==net_elements){
std::cout<<"x: ";
for(int i=0; i<x.size();i++){std::cout<<(x[i])<<" ";}
std::cout<<std::endl;

std::cout<<"y: ";
for(int i=0; i<y.size();i++){std::cout<<(y[i])<<" ";}
std::cout<<std::endl;

std::cout<<"z: ";
for(int i=0; i<z.size();i++){std::cout<<(z[i])<<" ";}
std::cout<<std::endl;

std::cout<<"w: ";
for(int i=0; i<w.size();i++){std::cout<<(w[i])<<" ";}
std::cout<<std::endl;

}
//if the number of elements do not match, print this statement.
else{std::cout<<"The number of elements in the positional arrays dont match!"<<std::endl;}

  }
// if the getparam function cant read the stuff from the yaml file for some reason, print something went wrong :)
else{
  std::cout<<"Something went wrong.\n"<<std::endl;
  }
//pause the program, to print the text.
std::cin.get();

return 0;
}
