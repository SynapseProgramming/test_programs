#include <ros/ros.h>
//this is the header file to include to play sounds.
#include <sound_play/sound_play.h>
#include <iostream>
#include <string.h>


int main(int argc, char **argv){

ros::init(argc,argv,"nfs_test");
ros::NodeHandle n;
//create a sound client object.
sound_play::SoundClient sc;
//the absolute path of the tune to play.
std::string tune="/home/roald/Desktop/Tokyo_Drift.wav";

//the absolute path of gochiusa
std::string usa="/home/roald/Desktop/gochiusa.wav";

//the sentence to swear
std::string swear="yo nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga nigga ";

//the sentence to meme
std::string meme="open the door please. I have more meth than triple e in my bag for you to smoke. HE HE HE HE HE HE HE HE HE HE HE HE HE HE HE";

while(n.ok()){
int x=0;

std::cout<<"Enter 1 to play need for speed tokyo drift."<<std::endl;
std::cout<<"Enter 2 to start swearing."<<std::endl;
std::cout<<"Enter 3 to stop playing stuff."<<std::endl;
std::cout<<"Enter 4 to start memeing."<<std::endl;
std::cout<<"Enter 5 to start to play gochiusa."<<std::endl;
std::cout<<"Enter 6 to swear and play need for speed shortly afterwards."<<std::endl;

std::cin>>x;

if(x==1){
//send the tune to the sound player to play the tune.
sc.playWave(tune);

std::cout<<"currently playing need for speed!"<<std::endl;
}

else if(x==2){
//say something
sc.say(swear,"voice_kal_diphone");

std::cout<<"currently swearing!"<<std::endl;
}

else if(x==3){
//this function stops playing all sounds.
sc.stopAll();

std::cout<<"stopping all sounds!"<<std::endl;
}
else if(x==4){
//say something
sc.say(meme,"voice_kal_diphone");

std::cout<<"currently swearing!"<<std::endl;
}
else if(x==5){
//send the tune to the sound player to play the tune.
sc.playWave(usa);

std::cout<<"currently playing gochiusa!"<<std::endl;
}
else if(x==6){// swear first, then play need for speed.
sc.say(swear,"voice_kal_diphone");
ros::Duration(3).sleep();
sc.playWave(tune);
//std::cout<<"currently swearing!"<<std::endl;



}

}//while loop bracket

return 0;
}
