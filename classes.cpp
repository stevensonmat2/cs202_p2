/*
Matt Stevenson
CS202 Program #2
4/22/2020

classes.cpp

this file contains the function definitions for the Activity class and all
subclasses (Dining, Nature, Entertainment)

*/

#include "classes.h"



//default constructor; sets member data to default values
Activity::Activity()
{
	name = NULL;
	priority = 0;
	date = NULL;
	duration = NULL;
	solo = true;
}


//copy constrcutor; deep copies values from argument for new object
Activity::Activity(const Activity &to_copy)
{
	//create new array sized to argument's equivalent member;
	//copy argument's data into new array; repeat for all members
	name = new char[strlen(to_copy.name)+1];
	strcpy(name, to_copy.name);
	
	priority = to_copy.priority;

	date = new char[strlen(to_copy.date)+1];
	strcpy(date, to_copy.date);

	duration = new char[strlen(to_copy.duration)+1];
	strcpy(duration, to_copy.duration);

	solo = to_copy.solo;
}



//destructor; deallocates dynamic data member memory
Activity::~Activity()
{
	if (name) delete [] name;

	if (date) delete [] date;

	if (duration) delete [] duration;
}



//compares argument object's name to calling object's; return 0 if match,
//>0 if name value greater than arguments, 0 < if less
int Activity::cmp_obj(const Activity &compare)
{
	return strcmp(name, compare.name);
}



//compares argument's priority to object's, return 0 if match, > 0 if 
//priority is less than arguments, 0 < otherwise
int Activity::cmp_lvl(const Activity &compare)
{
	return compare.priority - priority;
}


//compars argument name to object value; return 0 if match, > 0 if name value
//greater than argument, 0 < if less
int Activity::cmp_name(char *_name)
{
	return strcmp(name, _name);
}



//default constructor
Dining::Dining()
{
}



//copy constructor; calls parent class constructor with argument object
Dining::Dining(const Activity &to_copy): Activity(to_copy)
{
}



//default destructor
Dining::~Dining()
{
}



//takes a character array and copies data into new array set to member pointer
void Dining::set_name(char *_name)
{
	//if name array exists, delete
	if (name)
		delete [] name;

	name = new char[strlen(_name)+1];
	strcpy(name, _name);
}



//takes an integer argument and sets the value to the member pointer
void Dining::set_priority(int lvl)
{
	priority = lvl;
}



//takes a character array and copies data into new array set to member pointer
void Dining::set_date(char *_date)
{
	date = new char[strlen(_date)+1];
	strcpy(date, _date);
}



//takes a character array and copies data into new array set to member pointer
void Dining::set_duration(char *_duration)
{
	duration = new char[strlen(_duration)+1];
	strcpy(duration, _duration);
}



//sets boolean member to opposite value
void Dining::set_solo()
{
	if (solo) solo = false;

	else
		solo = true;
}



//outputs member data
void Dining::display()
{
	//date and duration formatted for readability
	cout << name << endl
	     << "priority: " << priority << endl
	     << "date: " << date[0] << date[1] 
	     << "/" << date[2] << date[3] << "/"
	     << date[4] << date[5] << endl
	     << "duration: " << duration[0]
	     << duration[1] << ":" << duration[2]
	     << duration[3] << endl;
	
	if (solo)
		cout << "solo: yes" << endl;
	else
		cout << "solo: no" << endl;
	
	cout << endl;
}



//default constructor
Nature::Nature()
{
}



//copy constructor; calls parent class constructor with argument object
Nature::Nature(const Activity &to_copy): Activity(to_copy)
{
}


//default destructor
Nature::~Nature()
{
}



//takes a character array and copies data into new array set to member pointer
void Nature::set_name(char *_name)
{
	//if name array exists, delete
	if (name)
		delete [] name;

	name = new char[strlen(_name)+1];
	strcpy(name, _name);
}




//takes an integer argument and sets the value to the member pointer
void Nature::set_priority(int lvl)
{
	priority = lvl;
}



//takes a character array and copies data into new array set to member pointer
void Nature::set_date(char *_date)
{
	date = new char[strlen(_date)+1];
	strcpy(date, _date);
}



//takes a character array and copies data into new array set to member pointer
void Nature::set_duration(char *_duration)
{
	duration = new char[strlen(_duration)+1];
	strcpy(duration, _duration);
}



//sets boolean member to opposite value
void Nature::set_solo()
{
	if (solo) solo = false;

	else
		solo = true;
}



//outputs member data
void Nature::display()
{
	cout << name << endl
	     << "priority: " << priority << endl
	     << "date: " << date[0] << date[1] 
	     << "/" << date[2] << date[3] << "/"
	     << date[4] << date[5] << endl
	     << "duration: " << duration[0]
	     << duration[1] << ":" << duration[2]
	     << duration[3] << endl;
	
	if (solo)
		cout << "solo: yes" << endl;
	else
		cout << "solo: no" << endl;
	
	cout << endl;
}



//default constructor
Entertainment::Entertainment()
{
}



//copy constructor; calls parent class constructor with argument object
Entertainment::Entertainment(const Activity &to_copy): Activity(to_copy)
{
}



//default destructor
Entertainment::~Entertainment()
{
}



//takes a character array and copies data into new array set to member pointer
void Entertainment::set_name(char *_name)
{
	//if name array exists, delete
	if (name)
		delete [] name;

	name = new char[strlen(_name)+1];
	strcpy(name, _name);
}



//takes an integer argument and sets the value to the member pointer
void Entertainment::set_priority(int lvl)
{
	priority = lvl;
}



//takes a character array and copies data into new array set to member pointer
void Entertainment::set_date(char *_date)
{
	date = new char[strlen(_date)+1];
	strcpy(date, _date);
}



//takes a character array and copies data into new array set to member pointer
void Entertainment::set_duration(char *_duration)
{
	duration = new char[strlen(_duration)+1];
	strcpy(duration, _duration);
}



//sets boolean member to opposite value
void Entertainment::set_solo()
{
	if (solo) solo = false;

	else
		solo = true;
}



//outputs member data
void Entertainment::display()
{
	cout << name << endl
	     << "priority: " << priority << endl
	     << "date: " << date[0] << date[1] 
	     << "/" << date[2] << date[3] << "/"
	     << date[4] << date[5] << endl
	     << "duration: " << duration[0]
	     << duration[1] << ":" << duration[2]
	     << duration[3] << endl;
	
	if (solo)
		cout << "solo: yes" << endl;
	else
		cout << "solo: no" << endl;
	
	cout << endl;
}

