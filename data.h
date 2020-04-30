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
		
		//copies argument object and inserts new object
		//into data structure
		bool insert(const Activity &to_copy);

		//finds Activity matching argument name; calls object's display
		bool display(char *name);

		//finds Activity matching argument name; returns object
		//via argument pointer
		void retrieve(char *name, Activity *retrieved);
		
		//wrapper; if array exists, calls recursive function to check
		//array for object matching argument name; returns value of
		//recusrsive function
		bool remove(char *name);

		//deletes all objects matching argument priorty level
		//void remove_all_p(int p_lvl);

		//wrapper; calls display function for all Activity objects
		//in member array; return false if no array exists
		bool display_all();

	private:
		//sets the max size for member arrays
		int MAX_LEN = 5;
		
		//copies argument object and inserts new object
		//into data structure
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
		bool display(char *name, int i);

		//recursively traverses and call display function for each
		//Activity object in array
		void display_all(int i);
/*
		//wrapper; calls function to set ptrs in array to null
		void set_null(Activity **array);

		//sets all ptrs in array to null
		void set_null(Activity **array, int i);
*/
		//deletes any object array points to
		void delete_array(int i);

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

		//finds Activity matching argument name; returns object
		//via argument pointer
		void retrieve(char *name, Activity *retrieved);

		//finds Activity matching argument name; deletes object
		bool remove(char *name);

		//deletes all objects matching argument priorty level
		//void remove_all_p(int p_lvl);

		//calls display function for all object of argument priority
		bool display_all_p();


	private:
		//deletes all nodes in DLL
		void remove_all();

		//finds Activity matching argument name; returns true if found
		bool display(char *name, Node *node);

		//finds Activity matching argument name; deletes object
		bool remove(Node *&node, char *name);

		//recursive function to find correct Node's array to insert to
		//void insert(const Activity &to_copy, Node *&node);

		//pointer to DLL of nodes; each node points to
		//array of Activity object pointers
		Node *activities;
};
