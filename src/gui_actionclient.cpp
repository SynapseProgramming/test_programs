#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int32.h>
#include <test_programs/dishesAction.h>
#include <iostream>

//initialise the global variables
bool goal_reached=false;
bool goal_received=false;
int  goal_index=0;


//update the goal index from labview.
void goal_indexcb(const std_msgs::Int32::ConstPtr &goal){
goal_index=goal->data;
}

//Function which is called when the goal is reached.
void donecb(const actionlib::SimpleClientGoalState& state,const test_programs::dishesResultConstPtr &result){
//print status and stuff.
std::cout<<"Status:"<<state.toString() <<std::endl;
std::cout<<"the result is: "<<(result->final_count)<<std::endl;
//declare goal reached as true.
goal_reached=true;
}
//Function when the action server receives a goal.
void activecb(){
std::cout<<"Just received a goal! "<<std::endl;
//declare goal received as true.
goal_received=true;
}
//Function when the action server sends feedback back.
void feedbackcb(const test_programs::dishesFeedbackConstPtr& feedback){
std::cout<<"The current value is: "<<feedback->current_count<<std::endl;

}

int main(int argc, char **argv){
//initialise the current goal as 0.
int current_goal=0;

ros::init(argc,argv,"dishes_client");
//create a simple action client object, and specify the name of the action server.
actionlib::SimpleActionClient<test_programs::dishesAction>ac("dish_server",true);

ros::NodeHandle n;
//create a subscriber to sub to the labview buttons topic.
ros::Subscriber sub=n.subscribe("goal_index",1000,goal_indexcb);


//wait for a connection with the server.
std::cout<<"Waiting for the server to start! "<<std::endl;
ac.waitForServer();
//when the server has started, run the main program.
std::cout<<"The server has started! "<<std::endl;
//loop rate object ensures that the loop runs at 10 hz.
ros::Rate loop_rate(10);

while(ros::ok()){
//delay the loop, just enough for it to run at 10 hz.
loop_rate.sleep();
//run the spin function
ros::spinOnce();

if(goal_reached==false&&goal_received==false&&goal_index!=0){
//create a variable which matches the goal type of the action server
test_programs::dishesGoal send_goal_index;
//copy the labview goal index into the variable to be sent to the action server
send_goal_index.count_goal=goal_index;
//used for debugging
std::cout<<"sending goal of: "<<send_goal_index.count_goal<<std::endl;
//send the goal to the action server, while specifying the callback functions.
ac.sendGoal(send_goal_index, &donecb,&activecb,&feedbackcb);
//copy the current goal into the current goal variable(this is used to prevent the program from sending a goal which it has just achieved)
current_goal=send_goal_index.count_goal;
}
//Check if the program as reached the goal.
else if(goal_reached==true&&goal_received==true){
//skip this loop iteration if the desired goal is the one which has just been achieved.
if(current_goal==goal_index){continue;}
//reset the goal reached and goal received variable to enable a new goal to be sent to the action server.
else{goal_reached=false;goal_received=false;}
}
//skip this iteration
else{continue;}

}


return 0;
}
