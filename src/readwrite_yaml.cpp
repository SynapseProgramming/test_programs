#include <ros/ros.h>
#include <iostream>
#include <fstream>

  std::ofstream outfile;
void print_elements(std::vector<double> &x){
  //print out the elements in the vector
  std::cout<<"x: ";
  for(int i=0; i<x.size();i++){std::cout<<(x[i])<<" ";}
  std::cout<<std::endl;

}

void print_array(std::string array_head, std::vector<double> &array){

  outfile.open("/home/roald/catkin_ws/src/test_programs/param/readwrite_test.yaml");
  outfile<<array_head<< ": [";
  for(unsigned int i=0; i<array.size();i++){
  //if i is at the last element of the vector
  if(i==(array.size()-1)){outfile<<array[i]<<"]\n";}
  else{outfile<<array[i]<<",";}
  }
  outfile.close();

}



int main(int argc, char **argv){
ros::init(argc,argv,"yamltest");

//create a vector to store the values
std::vector<double> x;

//initialise the ros nodehandle
ros::NodeHandle n;
//load the elements from the yaml file
n.getParam("x",x);

std::cout<<"elements read from file: ";
print_elements(x);
std::cout<<std::endl;

std::cout<<"size of array: "<<x.size()<<std::endl;

int index=0;
int state=0;
double repl_value=0;
double new_value=0;
while(ros::ok()){
std::cout<<"If you would want to insert a new element into the vector, press 1.\n If you would want to modify an existing element, press 2."<<std::endl;
std::cout<<"If you would want to write the current elements in the vector to the text file, press and enter 3"<<std::endl;
std::cin>>state;
if(state==1){
std::cout<<"please enter the value of the new element"<<std::endl;
std::cin>>new_value;
x.push_back(new_value);
print_elements(x);
}

else if(state==2){
std::cout<<"Please enter the index of the element that you would want to edit"<<std::endl;
std::cin>>index;
std::cout<<"Please enter the value to put in that index"<<std::endl;
std::cin>>repl_value;

//replace that element with the new value
x[index]=repl_value;
print_elements(x);
}

else if(state==3){
print_array("x",x);
print_elements(x);
std::cout<<"The array has been saved to the text file."<<std::endl;
}


}//while loop bracket


return 0;
}
