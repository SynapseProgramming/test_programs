#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <test_programs/dishesAction.h>
#include <iostream>
//Function which is called when the goal is reached.
void donecb(const actionlib::SimpleClientGoalState& state,const test_programs::dishesResultConstPtr &result){

std::cout<<"Status:"<<state.toString() <<std::endl;
std::cout<<"the result is: "<<(result->final_count)<<std::endl;
std::cout<<"Please enter the number of dishes! "<<std::endl;
}
//Function when the action server receives a goal.
void activecb(){
std::cout<<"Just received a goal! "<<std::endl;
}
//Function when the action server sends feedback back.
void feedbackcb(const test_programs::dishesFeedbackConstPtr& feedback){
std::cout<<"The current value is: "<<feedback->current_count<<std::endl;

}

int main(int argc, char **argv){
ros::init(argc,argv,"dishes_client");
//create a simple action client object, and specify the name of the action server.
actionlib::SimpleActionClient<test_programs::dishesAction>ac("dish_server",true);

//wait for a connection with the server.
std::cout<<"Waiting for the server to start! "<<std::endl;
ac.waitForServer();
//when the server has started, send goal.
std::cout<<"The server has started. Please enter the number of dishes! "<<std::endl;
while(ros::ok()){
//create goal variable.
test_programs::dishesGoal goal;
//ask the user to enter a number
std::cin>>goal.count_goal;
//send the goal over to the server
ac.sendGoal(goal, &donecb,&activecb,&feedbackcb);

ros::spinOnce();
}



return 0;
}
