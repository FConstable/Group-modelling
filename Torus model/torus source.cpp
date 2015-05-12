/*--------------------------------------------------------------------------------------------------------------
		Torus spacial model
---------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <fstream> 
#include <random>    //for built in C++ random numbers
#include <Windows.h> // need this to set the timer

using namespace std;

//Defining key variables
#define NumberOfAgents 100 //the number of individual agents, ie. organisms in the model
#define NumberOfDP 10000.0 //the number of dp on my random number, efectively controlls the size of the habbitat (allong side othre values) 
#define Max_group_distance 0.02 //how close two agents have to be to be considered part of the same group.
#define FitnessBenefit pow(number_of_neighbours,AlleeAdvantage)//used in function 'assesfitnes'
#define AlleeAdvantage 0.5 // between 0 and 1, the closer to one the stronger the alle effect. adjust here 
#define FitnessCost number_of_neighbours*Competition //
#define Competition 0.25 //how great the level of competition is 
#define Time_steps 100000 //howmany times agents are allowed to move

//for AlleeAdvantage=0.5 & Competition=0.25 maximum fitness =1 at number_of_neighbours=4


#define SEED GetTickCount() //should work for better pseudo random numbers
default_random_engine generator(SEED); //pick_random(generator)/NumberOfDP is what you call when you want a random number 0 to 1
uniform_int_distribution<int> pick_random(0,NumberOfDP);	// will generate integer 0 to 10000.
uniform_int_distribution<int> coin_flip(0,1);	// coin_flip(generator). 

double AgentProperties[NumberOfAgents][3]; //[agent number][0; x pos, 1; y pos, 2; fitnes]
int number_of_neighbours=0;
double Stop_threshold=0;
double Move_Distance=0;


void initialise(void); //distribute agents randomly within an area
void assesfitnes(void); //update fitnes of an individual. In later models this will be cumulative.
void move(void);
void output_AverageAgentFitnes(void); //

ofstream out_fit("AverageAgentFitnes.txt"); //hedder=T

int main()	
{
	int counter = 0;
	out_fit << "Move distance\tStop Threshold\tAverage Fitnes\n";
	
	for (Move_Distance = 0.002; Move_Distance < 0.05; Move_Distance += 0.002){
		for (Stop_threshold = 0.05; Stop_threshold < 1.05; Stop_threshold += 0.05){
			initialise();
			assesfitnes();

			for (int x = 0; x < Time_steps; x++){
				move();
				assesfitnes();
				cout << counter << "\t" << x <<"\n";
			}
			output_AverageAgentFitnes();
			
			counter++;
		}


	}

		

	return 0;
}

void initialise()
{
	for (int x=0; x<NumberOfAgents; x++){
		AgentProperties[x][0]=pick_random(generator)/NumberOfDP;
		AgentProperties[x][1]=pick_random(generator)/NumberOfDP;
	}

}

void assesfitnes()
{	
	int number_of_neighbours=0;

	for (int x=0; x<NumberOfAgents; x++){
		for (int y=0; y<NumberOfAgents; y++){
			//check if they are within Max_group_distance without crossing x OR y limet 
			if(abs(AgentProperties [x][0]-AgentProperties [y][0])<Max_group_distance  //if it is within the square
				&& abs(AgentProperties [x][1]-AgentProperties [y][1])<Max_group_distance){//without crossing the edge
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0];
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1];
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2+1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]+1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1])<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]+1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1];
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2-1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]-1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1])<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]-1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1];
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//y2+1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0])<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]+1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0];
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]+1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//y2-1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0])<Max_group_distance 
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]-1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0];
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]-1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2+1, y2+1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]+1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]+1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]+1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]+1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2+1, y2-1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]+1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]-1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]+1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]-1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2-1, y2+1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]-1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]+1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]-1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]+1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
			//x2-1, y2-1
			else if(abs(AgentProperties [x][0]-AgentProperties [y][0]-1)<Max_group_distance  
				&& abs(AgentProperties [x][1]-AgentProperties [y][1]-1)<Max_group_distance){
				
							double x1=AgentProperties[x][0];	
							double x2=AgentProperties[y][0]-1;
							double y1=AgentProperties[x][1];
							double y2=AgentProperties[y][1]-1;
		
								if((pow((pow((x2-x1),2)+pow((y2-y1),2)),0.5))<0.01)number_of_neighbours++;
				}
		}

	AgentProperties[x][2]=FitnessBenefit-FitnessCost;
	if (AgentProperties[x][2] < 0) AgentProperties[x][2] = 0;
	} 
}

void move(){
	for(int x=0; x<NumberOfAgents; x++)
		if(AgentProperties[x][2]<Stop_threshold){
			int coin=0;
			
			double radius2=pow(Move_Distance, 2);
			double x_translation=(pick_random(generator)/NumberOfDP); //random number between 0 and 1
			double y_translation=1-x_translation;
				x_translation=x_translation*radius2;
				y_translation=y_translation*radius2;
					x_translation=pow(x_translation,0.5);
					y_translation=pow(y_translation,0.5);

					coin=coin_flip(generator);
							if(coin==1)x_translation=x_translation*-1;	//random direction for the x translation 
						coin=coin_flip(generator);
							if(coin==1)y_translation=y_translation*-1;	//...and forthe y translation

								AgentProperties[x][0]=AgentProperties[x][0]+x_translation;
								AgentProperties[x][1]=AgentProperties[x][1]+y_translation;
				
					if(AgentProperties[x][0]>1) AgentProperties[x][0]=AgentProperties[x][0]-1;
					if(AgentProperties[x][1]>1) AgentProperties[x][1]=AgentProperties[x][1]-1;
			}

}

void output_AverageAgentFitnes(){

	double average_fitness = 0;

	for (int x = 0; x < NumberOfAgents; x++){
		average_fitness = average_fitness + AgentProperties[x][2];
		}
	average_fitness = average_fitness / NumberOfAgents;


	out_fit << Move_Distance << "\t" << Stop_threshold << "\t" << average_fitness << "\n";

}