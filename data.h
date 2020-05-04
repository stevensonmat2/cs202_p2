/*
Matt Stevenson
CS202 Program #2
4/22/2020

data.h

this file contains the class definitions for the Node and Data classes. these
classes work in unison to form the data structure for a program working with the
classes defined in classes.h. 

each Data object has Node which serves as the head of a DLL, while each node has
an array of base class ptrs that point to Activity objects defined in classes.h.

Data provides a client with all the needed functions to add, remove, edit, and 
display Activity objects.

*/

#include "classes.h"

//class allows for managing lists of Activity objects
class Node {

	public:
		//default constructor
		Node();

		//default constructor
		~Node();

		//returns next pointer's Node
		Node *& get_next();

		//returns prev pointer's Node
		Node *& get_prev();

		//takes a Node and sets it to calling Node's next pointer
		void set_next(Node *&node);
		
		//takes a Node and sets it to calling Node's prev pointer
		void set_prev(Node *&node);
		
		//wrapper; if node has Activity array, calls recursive function
		//and returns its boolean value. else, creates Activity array
		//and calls recursive function. if array if full, returns false
		bool insert(const Activity &to_copy);
		
		//wrapper; if node has Activity array, calls recursive function
		//to find object matching name argument; returns true if found
		bool display(char *name);
		
		//wrapper; calls recursive function to check Activity array for
		//object matching name; if found, returns true and found object
		//object via argument ptr
		bool retrieve(char *name, Activity *&retrieved);
		
		//wrapper; if array exists, calls recursive function to check
		//array for object matching argument name; returns value of
		//recusrsive function
		bool remove(char *name);

		//wrapper; calls display function for all Activity objects
		//in member array; return false if no array exists
		bool display_all();
		
		//checks argument objects priorty lvl against first object in node's array;
		//returns value of comparison; 0 = match, > 0 argument is lower priority
		int cmp_lvl(const Activity &to_check);


		//wrapper; calls recursive function to compare name of argument to name of
		//first of last object in Activity array; return integer result of comparison;
		//0 = same, > 0 if array object name comes before arguments, < 0 otherwise 
		int cmp_name(const Activity &to_check);


		//checks if node's array is empty; return if so, false otherwise
		bool is_empty();

	private:
		//sets the max size for member arrays
		const int MAX_LEN = 1;
		
		//recursively traverses node's array to find appropriate 
		//place to insert argument object; once found, copies argument
		//into new object and inserts new object into array; once 
		//index for insertion found, performs RTTI to determine which
		//kind of object argument is, inserts object, and returns true
		bool insert(const Activity &to_copy, int i);

		//recursive helper to shift objects in array if room; shifts
		//each object from the starting point one to the right
		void shuffle_right(int i);

		//recursive helper to shift objects in array when removing 
		//objects; shifts each object from the starting point one 
		//to the left
		void shuffle_left(int i);

		void copy_type(const Activity &source, Activity *&copy);
		
		//recursivley traverse Activity array to find Activity matching
		//argument name; if found, deletes object and return true; else,
		//return false
		bool remove(char *name, int i);

		//finds Activity matching argument name; calls object's display
		//returns true if found, false otherwise
		bool display(char *name, int i);
		
		//finds Activity matching argument name; returns object
		//via argument pointer
		bool retrieve(char *name, Activity *&retrieved, int i);

		//recursively traverses and call display function for each
		//Activity object in array
		void display_all(int i);
		
		//deletes any object array points to
		void delete_array(int i);

		//compares last object in arrays' name to argument's name and returns result
		//of comparison
		int cmp_name(const Activity &to_check, int i);

		//points to next node in DLL
		Node *next;

		//points to previous node in DLL
		Node *prev;

		//points to an array of Activity object pointers
		Activity **activities;
};



//class manages data structure. enables insertion, retrieval, and removal of 
//Activity objects. has a Node pointer to managae DLL of
//arrays of Activity pointers
class Data {

	public:
		Data();
		~Data();

		//copies argument object and inserts new object
		//into data structure
		bool insert(const Activity &to_copy);


		//wrapper; calls recusrive display function. return true if
		//object found, false if not
		bool display(char *name);

		//wrapper; calls recursive function to find object matching
		//name argument and return it via argument ptr; true if found
		bool retrieve(char *name, Activity *&retrieved);

		//wrapper; calls recursive function to remove object matching
		//argument name from array; return true if found
		bool remove(char *name);

		//calls display all function on head of DLL
		bool display_all_p();

	private:
		//deletes all nodes in DLL
		void remove_all();

		//finds Activity matching argument name; returns true if found
		bool display(char *name, Node *node);

		//finds Activity matching argument name; returns object
		//via argument pointer. true if found, false otherwise
		bool retrieve(char *name, Activity *&retrieved, Node *node);

		//finds Activity matching argument name; deletes object
		bool remove(Node *node, char *name);
		
		//find appropriate node to insert new object into based on
		//priority lvl; if none found, creates new node and inserts
		//returns true when done
		bool insert(Node *node, const Activity &to_copy);
		
		//recursively deletes all nodes in DLL
		void delete_list(Node *&head);

		//pointer to DLL of nodes; each node points to
		//array of Activity object pointers
		Node *activities;
};

