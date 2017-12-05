// Main File Information//////////////////////////////////////////
/**
  *@file main.cpp
  *
  *@brief 
  *
  *@details None
  *
  *@version 1.00
  *			Mercedes Anderson (21 Nov 2017)
  *			Austin Emery (21 Nov 2017)
  *			Nickolas Johnson (21 Nov 2017)
  *
  *@note: One command line argument is needed: The amount of drones that are desired to run.
  */
//
//
// Included Files /////////////////////////////////
//
	#include <iostream>
  	#include <stdlib.h>
  	#include <time.h>
	#include "classes.h"
	using namespace std;
//
void populateEvents( int simulatedEvents[][2] , int amountOfDrones );
//
// Main Function /////////////////////////////////
//
	int main(int argc, char const *argv[])
	{
		int amountOfDrones = atoi(argv[1]); //Turn argv[1] back into a number
		int simulatedEvents[1000][2] = {0};
				//Two cols. One for the drone it's going to, one indicating what the event was.
		
		populateEvents(simulatedEvents , amountOfDrones);
			//M: consider also writing to a file or just having a file so all the input is the same while testing.
			//M: I don't know how to get these to the drones yet. We need to talk about it.
		CCObject ComCon(amountOfDrones);

		ComCon.printFleet();

		ComCon.proactiveSimulation();

		ComCon.printFleet();

		return 0;
	}
//

void populateEvents( int simulatedEvents[][2] , int amountOfDrones )
{
	srand (time(NULL));

	for( int row = 0 ; row < 1000 ; row++ )
	{
		simulatedEvents[row][0] = rand() % amountOfDrones;
			//randomly assigns drone that encounters the event
		simulatedEvents[row][1] = rand() % 10;
			//randomly generates the event.
	}
}