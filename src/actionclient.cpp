#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <test_programs/dishesAction.h>
#include <iostream>




int main(int argc , char**argv){

ros::init(argc,argv,"dishes_client");
//create the action client object, specifying the name of the action server.
actionlib::SimpleActionClient<test_programs::dishesAction>ac("dish_server",true);

std::cout<<"Waiting for the server to start running!"<<std::endl;
// wait for the server to be connected.
ac.waitForServer();

while(ros::ok()){
std::cout<<"The server has started. Please enter the number of dishes! "<<std::endl;

test_programs::dishesGoal goal;
//ask the user to enter a number
std::cin>>goal.count_goal;
//send the goal over to the server
ac.sendGoal(goal);

//time out function. once the specified time is exceeded, a false would be returned.
bool before_timeout=ac.waitForResult(ros::Duration(30.0));

if(before_timeout){
//get the current state of the goal.
actionlib::SimpleClientGoalState state=ac.getState();
//print out the current state
std::cout<<state.toString().c_str()<<std::endl;
}
else{
std::cout<<"sadly, did not finish by timeout."<<std::endl;
break;
}

}



return 0;
}
