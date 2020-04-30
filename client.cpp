#include "client.h"



Client::Client()
{
	activities = new Data;
}



Client::~Client()
{
	if (activities) delete activities;
}



void Client::menu()
{
	int input = 0;

	do
	{
		cout << "choose command: " << endl
		     << endl
		     << "(1) add new Activity" << endl
		     << "(2) display Activity" << endl
		     << "(3) remove Activity" << endl
		     << "(4) display all top priority" << endl
		     << endl
		     << "enter command: ";

		     cin >> input;
		     cin.ignore(100, '\n');

		     cout << endl;

		     switch (input)
		     {
		     		case 1: //call insert function
					add();
					break;

				case 2: //call display function
					display();
					break;

				case 3: //call display function
					remove();
					break;
				
				case 4: //call display function
					display_top_p();
					break;

				case 0:
					break;

		     }

	} while (input != 0);//loop until user enters '0'
			 
}



void Client::add()
{
	Activity *temp = NULL;
	int input = 0;

	do
	{
		cout << "choose activity type:" << endl
		     << endl
		     << "(1) dining;" << endl
		     << "(2) nature;" << endl
		     << "(3) entertainmnet;" << endl
		     << endl
		     << "enter command: ";

		     cin >> input;
		     cin.ignore(100, '\n');

		     cout << endl;

		     switch (input)
		     {
		     		case 1: //call insert function
					temp = new Dining;
					build(temp);
					if (!activities->insert(*temp))
						cout << "activity not added" << endl
						     << endl;
					delete temp;
					input = 0;
					break;

				case 2: //call display function
					temp = new Nature;
					build(temp);
					if (!activities->insert(*temp))
						cout << "activity not added" << endl
						     << endl;
					delete temp;
					input = 0;
					break;
				
				case 3: //call display function
					temp = new Entertainment;
					build(temp);
					if (!activities->insert(*temp))
						cout << "activity not added" << endl
						     << endl;
					delete temp;
					input = 0;
					break;

				case 0:
					break;

		     }

	} while (input != 0);//loop until user enters '0'

}



//prompts user for a name of an Activity and calls Data object's remove
//function with the name as the argument
void Client::remove()
{
	char name[50];//stores user input for Activity name
	
	//prompt user for Activity name
	cout << "enter name: ";
	cin.get(name, '\n');
	cin.ignore(100, '\n');

	if (!activities->remove(name))
		cout << "activity not found" << endl
		     << endl;
}



//prompts user for name of Activity and calls Data object's display function
//with the name as an argument
void Client::display()
{
	char name[50];//stores user input for Activity name
	
	//prompt user for Activity name
	cout << "enter name: ";
	cin.get(name, '\n');
	cin.ignore(100, '\n');

	if (!activities->display(name))
		cout << "activity not found" << endl
		     << endl;
}



//calls Data objects display top priority function; if Activity objects
//exist, each is displayed
void Client::display_top_p()
{
	if (!activities->display_all_p())
	{
		cout << "no activities to display" << endl
		     << endl;
	}
}



//interface for user to input data for new Activity object
void Client::build(Activity *&activity)
{
	char temp[50];//stores user input for dynamic member data
	int input = 0;//stores user input for integer member data
	
	//prompt user for Activity name
	cout << "enter name: ";
	cin.get(temp, '\n');
	cin.ignore(100, '\n');
	
	//call Activity's set name function with user input as argument
	activity->set_name(temp);
	
	//prompt user for date info until valid input given
	do
	{
		cout << "enter date (ddmmyy): ";
		cin.get(temp, '\n');
		cin.ignore(100, '\n');

	} while (strlen(temp) != 6);
	
	//call Activity's set date function with user input
	activity->set_date(temp);
	
	//prompt user for duration info until valid input given
	do
	{
		cout << "enter duration (hhmm): ";
		cin.get(temp, '\n');
		cin.ignore(100, '\n');

	} while (strlen(temp) !=4);
	
	//call Activity's set duration function with user input
	activity->set_duration(temp);
	
	//prompt user for priority level
	cout << "enter priority (1 highest, 5 lowest): ";
	cin >> input;
	cin.ignore(100, '\n');
	
	//call Activity's set priority function with user input
	activity->set_priority(input);
	
	//prompt user for solo or group Acitivty
	cout << "(1) for solo, (2) for group: ";
	cin >> input;
	cin.ignore(100, '\n');
	
	//if not solo, call Activity's function to change solo boolean to false
	if (input != 1)
		activity->set_solo();

}
	