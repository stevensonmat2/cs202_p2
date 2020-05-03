/*
Matt Stevenson
CS202 Program #2
4/22/2020

classes.h

this file contains the class definitions for the following:

abstract base class: Activity
subclasses of Node: Dining, Nature, and Entertainment


*/

#include <cctype>
#include <cstring>
#include <iostream>



using namespace std;



//abstract base class. provides common attributes and functions for derived
//classes: Dining, Nature, and Entertainment
class Activity {

	public:
		Activity();

		Activity(const Activity &to_copy);

		virtual ~Activity();

		//copies argument array and sets to name pointer
		virtual void set_name(char *name) = 0;

		//sets priority to argument
		virtual void set_priority(int lvl) = 0;

		//copies argument array and sets to date pointer
		virtual void set_date(char *date) = 0;
		
		//copies argument array and sets to duration pointer
		virtual void set_duration(char *duration) = 0;
		
		//flips solo boolean; true if false, false if true
		virtual void set_solo() = 0;

		//outputs all member data
		virtual void display() = 0;
		
		//compares argument to object value; returns true if match
		int cmp_obj(const Activity &compare);

		//compares argument's priority to object's, return true if match
		int cmp_lvl(const Activity &compare);
	
		//compares argument to object value; returns true if match
		int cmp_name(char *name);

	protected:
		//name of activity
		char *name;

		//priority level
		int priority;

		//date to complete
		char *date;

		//duration of activity
		char *duration;

		//solo activity or not
		bool solo;
};



//derived from Activity. represents a dining activity
class Dining: public Activity {

	public:
		Dining();
		Dining(const Activity &to_copy);
		~Dining();

		//copies argument array and sets to name pointer
		void set_name(char *name);

		//sets priority to argument
		void set_priority(int lvl);

		//copies argument array and sets to date pointer
		void set_date(char *date);
		
		//copies argument array and sets to duration pointer
		void set_duration(char *duration);
		
		//flips solo boolean; true if false, false if true
		void set_solo();

		//outputs all member data
		void display();
};



//derived from Activity. represents a nature activity (e.g. hiking)
class Nature: public Activity {

	public:
		Nature();

		Nature(const Activity &to_copy);

		~Nature();

		//copies argument array and sets to name pointer
		void set_name(char *name);

		//sets priority to argument
		void set_priority(int lvl);

		//copies argument array and sets to date pointer
		void set_date(char *date);
		
		//copies argument array and sets to duration pointer
		void set_duration(char *duration);
		
		//flips solo boolean; true if false, false if true
		void set_solo();

		//outputs all member data
		void display();
		
		//compares argument to object value; returns true if match
		int cmp_name(char *name);
};




//derived from Activity. represents an entertainment activity (e.g. movies)
class Entertainment: public Activity {

	public:
		Entertainment();
		
		Entertainment(const Activity &to_copy);

		~Entertainment();

		//copies argument array and sets to name pointer
		void set_name(char *name);

		//sets priority to argument
		void set_priority(int lvl);

		//copies argument array and sets to date pointer
		void set_date(char *date);
		
		//copies argument array and sets to duration pointer
		void set_duration(char *duration);
		
		//flips solo boolean; true if false, false if true
		void set_solo();

		//outputs all member data
		void display();
		
		//compares argument to object value; returns true if match
		int cmp_name(char *name);
};
