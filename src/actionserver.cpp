#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <test_programs/dishesAction.h>
#include <iostream>

class dishes{
protected:
  //Under the protected access statement, the nodehandle and
  //action server objects are called.
  ros::NodeHandle n_;
  actionlib::SimpleActionServer<test_programs::dishesAction> as_;

//create the feedback and result variables.
  test_programs::dishesFeedback feedback_;
  test_programs::dishesResult result_;


public:
  /* class constructor. initialise the action server object
with the nodehandle, action server name, and the execute callback function
  */
  dishes():
as_(n_,"dish_server",boost::bind(&dishes::executeCB,this,_1),false)
  {
as_.start();
std::cout<<" dishes action server started!"<<std::endl;
  }

//This is the execute callback function,which is called during execution.
void executeCB(const test_programs::dishesGoalConstPtr &goal){
// send data at 1hz
ros::Rate r(1);

bool success=true;
// write process here.
for(int i=0; i<=(goal->count_goal); i++){
//if ctrl c is pressed, set the status as Preempted
if(as_.isPreemptRequested()||!ros::ok()){
as_.setPreempted();
success=false;
break;
}
//if not, send feedback
else{
feedback_.current_count=i;
std::cout<<"sending: "<<i<<std::endl;
as_.publishFeedback(feedback_);
r.sleep();

}

  }
//once the process is complete, send the goal.
if(success){
result_.final_count=(goal->count_goal);
as_.setSucceeded(result_);
}

}

};

int main(int argc, char** argv){
ros::init(argc,argv,"dishes");
// instantiate the dishes object.
dishes dish;

ros::spin();

return 0;
}
