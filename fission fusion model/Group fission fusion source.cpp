/*
	Group fission fusion model

		*spatial position is stored as a property of a group
		*individuals exist within groups
		*individuals can move between groups 
		*individuals can leave groups to form new ones
*/

#include <iostream>
#include <vector>	//needed for vectors
#include <conio.h>	//need for _getch()
#include <random>    //for built in C++ random numbers
#include <Windows.h> // need this to set the time, GetTickCount()

using namespace std;

//++++++++++Definitions
#define SEED GetTickCount() 
#define InitialGroups 10
#define InitialAgents 250
#define NumberOfDP 10000.0

//***random numbers
default_random_engine generator(SEED); //
uniform_int_distribution<int> pick_random(0, NumberOfDP);	// will generate integer 0 to 10000. pick_random(generator)/NumberOfDP is what you call when you want a random number 0 to 1
uniform_int_distribution<int> coin_flip(0, 1);	// coin_flip(generator), for 0 or 1.

//Global Variables
int UniqueID = 1;  //Increments by one every time a new group is added.  starts at 1 so that ungrouped individuals can use 0.


//******Functions 
int random_group(void);

//***procedures
void initialise(void);

//+++++++++Classes

class group
{
public:
	group();	//constructs an empty group object at a random possition. 

	void move(double x, double y);	//changes the x and y coordinates og the group
	
	int get_ID(void);	//returns the unique id of a group

	void size_modifier(int); //changes the number of agents recourded for a group. 

private:
	
	double GroupXpos;
	double GroupYpos;
	int size;
	int ID;
};

class agent
{
public:
	agent(int g);	//constructs an agent object

private:

	int groupID;

	/*
	other information about individuals will go here when i decide what I want to include
	*/
};

//Global vector of objects must be declared after the object class
vector<group> GroupList; //this will be a list of all the group objects, if a group looses all it's members i will rimove it from the list (and call a distructor to remove the object?)
vector<agent> AgentList; //a list of all the agents. might swap for a static array later but this will do for now. 

//Class functions 

group::group() 
{
	ID=UniqueID; //Gives this group obgect a unique identifyer to link it to it's members. 

	UniqueID++;		//Increments this value so that the next one will be different

	GroupXpos = pick_random(generator) / NumberOfDP;
	GroupYpos = pick_random(generator) / NumberOfDP; //random x and y coordinates between 0 & 1.

	size = 0;
}

void group::move(double x, double y)
{
	GroupXpos += x;
	GroupYpos += y;
}

int group::get_ID(void){
	return ID;
}

void group::size_modifier(int s){

	size += s;
}

agent::agent(int g){

	groupID = g;

}

//-------------------MAIN--------------------------------------

int main(){

	group();

	initialise();

	return 0;
}

void initialise(){

	for (int x = 0; x < InitialGroups; x++){

		GroupList.push_back(group());

	}


	for (int x = 0; x < InitialAgents; x++){

		int group = random_group();

		int gID = GroupList.at(group).get_ID();

		AgentList.push_back(agent(gID));	//adds an agent object, containing a unique id pertaining to a group, to the vector

		GroupList.at(group).size_modifier(1); //add one to the size of the group.

	}

}

int random_group(){

	int r = (pick_random(generator) / NumberOfDP * (GroupList.size() + 1)) - (1 / NumberOfDP);	//total number of groups+1 multiplyed by (0 to 0.999), floored to give an int

	return r;
}

