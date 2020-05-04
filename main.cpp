/*
Matt Stevenson
CS202 Program #2
4/22/2020

main.cpp

this program allows a user to manage a collection of scheduled activities.
each Activity has a name, date, duration, and priority level. the user may
add, remove, edit, and display activities, as well as display all activities 
of the highest priority.

*/


#include "client.h"



//main loop
int main()
{
	//instantiate Client object
	Client session;
	
	//call object's main menu function
	session.menu();

	return 0;
}
