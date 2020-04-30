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



int Activity::cmp_obj(const Activity &compare)
{
	return strcmp(name, compare.name);
}



//compares argument's priority to object's, return true if match
int Activity::cmp_lvl(const Activity &compare)
{
	return compare.priority - priority;
}


//compars argument name to object value; return true is match
int Activity::cmp_name(char *_name)
{
	return strcmp(name, _name);
}



Dining::Dining()
{
}



Dining::Dining(const Activity &to_copy): Activity(to_copy)
{
}

Dining::~Dining()
{
}

//takes a character array and copies data into new array set to member pointer
void Dining::set_name(char *_name)
{
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




/*

//compars argument name to object value; return true is match
int Dining::cmp_obj(const Activity &compare)
{
	return strcmp(name, compare.name);
}*/



Nature::Nature()
{
}


Nature::Nature(const Activity &to_copy): Activity(to_copy)
{
}

Nature::~Nature()
{
}

//takes a character array and copies data into new array set to member pointer
void Nature::set_name(char *_name)
{
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



/*
//compars argument name to object value; return true is match
int Nature::cmp_obj(const Activity &compare)
{
	return strcmp(name, compare.name);
}*/


Entertainment::Entertainment()
{
}



Entertainment::Entertainment(const Activity &to_copy): Activity(to_copy)
{
}

Entertainment::~Entertainment()
{
}


//takes a character array and copies data into new array set to member pointer
void Entertainment::set_name(char *_name)
{
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



/*
//compars argument name to object value; return true is match
int Entertainment::cmp_obj(const Activity &compare)
{
	return strcmp(name, compare.name);
}*/






