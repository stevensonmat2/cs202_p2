/*
Matt Stevenson
CS202 Program #2
4/22/2020

data.cpp

this file contains the function definitions for the Node and Data classes. 

the Data class managers a DLL of Nodes and is responsible for adding/deleting
nodes, retrieving objects from nodes, and deciding which node to insert a new
object into.

the Node class manages an array of ptrs to base class objects (Activity). each
node is responsible for adding/deleting objects to/from its array, as well as 
retrieving objects.

*/


#include "data.h"



//default constructor; sets member data to null values
Node::Node()
{
	next = NULL;
	prev = NULL;
	activities = NULL;
}



//destructor; deletes dynamic memory
Node::~Node()
{
	next = NULL;
	prev = NULL;
	
	//if Activity array exists
	if (activities) 
	{
		int i = 0;//index tracker
		
		//recursively delete objects in array
		delete_array(i);

		//delete array
		delete [] activities;

		activities = NULL;
	}
}



//returns next pointer's address
Node *& Node::get_next()
{
	return next;
}



//returns prev pointer's address
Node *& Node::get_prev()
{
	return prev;
}



//takes a Node and sets it to calling Node's next pointer
void Node::set_next(Node *&node)
{
	next = node;
}



//takes a Node and sets it to calling Node's prev pointer
void Node::set_prev(Node *&node)
{
	prev = node;
}



bool Node::insert(const Activity &to_copy)
{
	int i = 0;//create index tracker
	
	//if array exists
	if (activities)
	{
		//check last indes to see if array is full
		if (activities[MAX_LEN-1])
		{
			return false;
		}
		
		//call recursive insert function
		return insert(to_copy, i);
	}

	else//if array does not exist
	{
		//create new array; set each index to null
		activities = new Activity*[MAX_LEN]();
		
		//call recusrive insert function
		return insert(to_copy, i);
	}
}


//recursive insert function; checks all indicies of member array for
//place to insert. returns true if added, false if not or array is full
bool Node::insert(const Activity &to_copy, int i)
{
	//stopping condition; exit once end of array reached	
	if (i == MAX_LEN) return false;
	
	//if a blank index is found, add object to array
	if (!activities[i])
	{
		//try casting to three subclasses until argument object matches
		//
		//try Dining object
		const Dining *pt = dynamic_cast<const Dining*>(& to_copy);
		
		if (pt)//check if cast worked
		{
			//if so, copy argument data into new object;
			//save to array
			activities[i] = new Dining(to_copy);
			
			cout << "Dining event added" << endl
			     << endl;

			activities[i]->display();//display new object

			return true;
		}

		else//otherwise, try other classes
		{
			//try Nature object
			const Nature *pt = dynamic_cast<const Nature*>(& to_copy);

			if (pt)
			{
				activities[i] = new Nature(to_copy);
					
				cout << "nature event added" << endl
				     << endl;

				activities[i]->display();

				return true;
			}

			else
			{
				//try Entertainment object
				const Entertainment *pt = 
				dynamic_cast<const Entertainment*>(& to_copy);

				if (pt)
				{
					activities[i] = new Entertainment(to_copy);
					
					cout << "entertainment event added" << endl
					     << endl;

					activities[i]->display();

					return true;
				}
			}

			return false;//if none are true, exit
		}
	}
	
	//if index not empty, check argument's name against current index's;
	//if argument should be ordered after, traverse array recursively
	else if (activities[i]->cmp_obj(to_copy) < 0)
	{
		return insert(to_copy, ++i);
	}

	else//if argument name is ordred the same or before current index,
	//shift indicies down 1, empty current index, and recall function
	{
		shuffle_right(i);//call helper to shift array ptrs

		activities[i] = NULL;//free current index

		return insert(to_copy, i);//recall function to insert
	}	
}



//recursive helper to move objects in array to right (ie down)
void Node::shuffle_right(int i)
{
	//stopping condition; exit once last index reached	
	if (i == MAX_LEN-1) return;

	if (activities[i+1])//if next index not empty
	{
		//recall function to check next index
		shuffle_right(i+1);
	}
	
	//set next index's ptr to the object of current index's ptr
	activities[i+1] = &(*activities[i]);
}



//recursive helper to shift objects in array to left (ie up)
void Node::shuffle_left(int i)
{
	//stopping condition; exit once end of array reached	
	if (i == MAX_LEN-1) return;

	//set current index to next index object
	activities[i] = activities[i+1];

	//set next index to null
	activities[i+1] = NULL;

	//recall function to check next index
	shuffle_left(++i);
}



//wrapper; calls recursive function to find Activity matching argument
//and call its display function; return true if found, false if not
bool Node::display(char *name)
{
	//if no Acitivity objects in array exit with fail
	if (!activities) return false;
	
	int i = 0;//set index tracker
	
	//call and rerturn value of recursive display function passing in name,
	//Activity array and index tracker
	return display(name, i);
}



//recursive function to display member info of an Activity object; check's
//node's array for object matching argument name; if found, call object's
//display function and return true; else return false
bool Node::display(char *name, int i)
{
	//if end of array or empty index found, return false
	if (i == MAX_LEN || !activities[i]) return false;
	
	//if Activity name matches argument, call its display function
	if (activities[i]->cmp_name(name) == 0)
	{
		activities[i]->display();

		return true;
	}
	
	//traverse to next index
	return display(name, ++i);
}



//wrapper; if node has Activity array, calls recursive function to find object
//matching name argument and return it via argument pointer; returns false if 
//no array found, otherwise return value of recursive function
bool Node::retrieve(char *name, Activity *&retrieved)
{
	int i = 0;//index tracker
	
	//if Activity array exists
	if (activities)
	{
		//call recursive function
		return retrieve(name, retrieved, i);
	}
	
	return false;
}



//finds Activity matching argument name; returns object via argument pointer;
//return true if object found, false if not
bool Node::retrieve(char *name, Activity *&retrieved, int i)
{
	//if entire array checked with no match
	if (i == MAX_LEN) return false;
	
	//if current index object matches name
	if (activities[i]->cmp_name(name) == 0)
	{
		//set argument ptr to matching object
		retrieved = activities[i];

		return true;
	}
	
	//traverse array
	return retrieve(name, retrieved, ++i);
}



//wrapper; if member array exists, call recursive function to check
//array for object matching name argument. return value of recursive function
bool Node::remove(char *name)
{
	int i = 0;//set index tracker
	
	//if array exists, call recursive function 
	if (activities) 
	{
		//call recursive function; save return value
		bool val = remove(name, i);
		
		//check if array empty after removal; if so, delete array
		if (!activities[i])
		{
			delete [] activities;
			activities = NULL;
		}
		
		//return value of recursive function
		return val;
	}
	
	//else exit with fail
	else return false;
}



//recursively checks argument array for object matching name argument; if found
//removes object and calls function to shift objects in array
bool Node::remove(char *name, int i)
{
	//if entire array checked with no match
	if (i == MAX_LEN) return false;
	
	//if object at current index
	if (activities[i])
	{
		//if current object matches name argument
		if (activities[i]->cmp_name(name) == 0)
		{
			//delete object
			delete activities[i];
			activities[i] = NULL;

			//shift objects in array to fill gap
			shuffle_left(i);

			return true;
		}
		
		//traverse array
		else return remove(name, ++i);
	}

	return false;
}



//wrapper; calls recursive function to display all objects in array; returns
//false if no array exists, true otherwise
bool Node::display_all()
{
	int i = 0;//set index tracker
	
	//if array exists
	if (activities)
	{
		//call recursive display all function
		display_all(i);

		return true;
	}

	return false;
}



//recursively traverses Activity array and calls display function on all objects
void Node::display_all(int i)
{
	//if end of array or empty index found, check next node's array
	//for priority lvl match
	if (i == MAX_LEN || !activities[i])
	{
		//if no next node, exit
		if (!get_next()) return;
		
		//if next node's array matches current priority lvl
		if (get_next()->cmp_lvl(*activities[0]) == 0)
		{
			//call ndext node's display all
			get_next()->display_all();
		}

		return;
	}
	
	//call objects display function
	activities[i]->display();

	//traverse to next index
	display_all(++i);
}




//checks argument objects priorty lvl against first object in node's array;
//returns value of comparison; 0 = match, > 0 argument is lower priority
int Node::cmp_lvl(const Activity &to_check)
{
	//if array exists
	if (activities)
	{
		//check argument lvl against first object in arrays';
		//return the value of comparison
		return activities[0]->cmp_lvl(to_check);
	}
	
	//impossible condition to reach returns -1
	return -1;

	//check argument lvl against first object in arrays';
	//return the value of comparison
	//return activities[0]->cmp_lvl(to_check);
}



//wrapper; calls recursive function to compare name of argument to name of
//first of last object in Activity array; return integer result of comparison;
//0 = same, > 0 if array object name comes before arguments, < 0 otherwise 
int Node::cmp_name(const Activity &to_check)
{
	int i = 0;//index tracker
	//if array exists
	if (activities)
	{
		//call recursive function
		return cmp_name(to_check, i);
	}

	return -10;
}



//compares last object in arrays' name to argument's name and returns result
//of comparison
int Node::cmp_name(const Activity &to_check, int i)
{
	//if (!activities[i]) return -1;
	
	//if last index in array contains an object
	if (i == MAX_LEN-1)
	{
		//compare argument object to index object and return result
		return activities[i]->cmp_obj(to_check);
	}
	
	//if current object last in array
	if (!activities[i+1])
	{
		//compare argument object to index object and return result
		return activities[i]->cmp_obj(to_check);
	}
	
	//traverse until last object in array found
	return cmp_name(to_check, ++i);
}



//checks if node's array is empty; return if so, false otherwise
bool Node::is_empty()
{
	if (!activities) return true;

	return false;
}

		
//ERASE ERASE ERASE
//recursive function to delete all Activity objects in member array
void Node::delete_array(int i)
{
	//if end of array reached, exit
	if (i == MAX_LEN) return;
	
	//if current index not null
	if (activities[i])
	{
		//delete object being pointed to and set to null
		delete activities[i];
		activities[i] = NULL;
	}
	
	//traverse to next index
	delete_array(++i);
}



//DATA FUNCTIONS/////////////////////////////////////////////////////////////// 



//constructor
Data::Data()
{
	activities = NULL;
}



//destructor
Data::~Data()
{
	if (activities) 
	{
		delete_list(activities);
	}
}



//recursive function to delete all nodes in DLL
void Data::delete_list(Node *&head)
{
	//if end of list, exit
	if (!head) return;
	
	//save current node's next object
	Node *temp = head->get_next();
	
	//delete currnt node
	delete head;
	
	//traverse to next node
	delete_list(temp);
}

/*
//copies argument object and inserts new object
//into data structure
bool Data::insert(const Activity &to_copy)
{
	if (!activities)
	{
		activities = new Node;
	}

	//insert(to_copy, activities);
	return activities->insert(to_copy);
}
*/



//wrapper; if no nodes exist, create one; call recursive function to insert
//new object into a node's array; returns value of recursive function
bool Data::insert(const Activity &to_copy)
{
	//if no node exists
	if (!activities)
	{
		//create one at activities ptr
		activities = new Node;

		//call recursive insert function
		return activities->insert(to_copy);
	}

	//call recursive insert function
	return insert(activities, to_copy);
}



//checks priority of new object and then compares against each node's in DLL;
//if a match is found, attempts to insert new object into node's array. 
//if array is full, checks node array's last object's name against new object,
//then creates a new node either ahead or after current node and inserts new
//object there.
//otherwise, traverses DLL for appropriate place in insert new object
bool Data::insert(Node *node, const Activity &to_copy)
{
	//compare priority lvl of current object to current array
	int p_lvl = node->cmp_lvl(to_copy);
	
	//if matching
	if (p_lvl == 0)
	{
		//if array is full
		if (!node->insert(to_copy))
		{
			//if new object's name should be ordered after 
			//current node's array's last item
			if (node->cmp_name(to_copy) < 0)
			{
				//create new node
				Node *temp = new Node;

				//set new node's next to current node's next
				temp->set_next(node->get_next());

				//set current node's next to temp
				node->set_next(temp);

				//set temp's prev to current node
				temp->set_prev(node);
				
				//if temp's next not null
				if (temp->get_next())
				{
					//set temp's next's prev to temp
					temp->get_next()->set_prev(temp);
				}
				
				//call wrapper insert function to create new
				//array and insert new object
				return temp->insert(to_copy);
			}
			
			//if new object should go before current node
			else
			{
				//create new node
				Node *temp = new Node;
				
				//set new node's next to current node
				temp->set_next(node);
				
				//set current node's prev to new node
				node->set_prev(temp);
				
				//set activities ptr to new node
				activities = node->get_prev();
				
				//call wrapper insert function to create new
				//array and insert new object
				return activities->insert(to_copy);
			}
			
		}
		
		//if insertion successful, return true
		return true;
	}
	
	//if new object lower priority than current node
	else if (p_lvl > 0)
	{
		//check for next node
		if (node->get_next())
		{
			//if found, call node's insert function
			return insert(node->get_next(), to_copy);
		}
		
		//if next not found, create new node, insert into DLL,
		//and call its insert function
		else
		{
			Node *temp = new Node;
			node->set_next(temp);
			temp->set_prev(node);

			//call wrapper insert function to create new
			//array and insert new object
			return temp->insert(to_copy);
		}
	}
	
	//if new object higher priority than current node
	else
	{
		//if curret node is top priority
		if (!node->get_prev())
		{
			//create new node
			Node *temp = new Node;
			
			//set new node's next to current node
			temp->set_next(node);
			
			//set current node's prev to new node
			node->set_prev(temp);
			
			//set activities ptr to new node
			activities = node->get_prev();

			//call wrapper insert function to create new
			//array and insert new object
			return activities->insert(to_copy);
		}
		
		else
		{
			//insert new node before current node
			Node *temp = new Node;

			//set new node next to current node
			temp->set_next(node);

			//set new node prev to current node's prev
			temp->set_prev(node->get_prev());

			//set current node's prev's next to new node
			node->get_prev()->set_next(temp);

			//set current node's prev to new node
			node->set_prev(temp);

			//call wrapper insert function to create new
			//array and insert new object
			return temp->insert(to_copy);
		}
	}
}

//wrapper; calls recursive function to display object matching argument name
//if no Activity objects have been made, returns false; returns result of
//recusrive function otherwise
bool Data::display(char *name)
{
	//if list of Activity objects exists, call recursive display function
	if (activities) return display(name, activities);

	return false;
}



//recursively finds Activity matching argument name; checks each node in
//DLL for a match to name argument and returns true if found, false if not
bool Data::display(char *name, Node *node)
{
	//if no DLL or end of list reached, exit with fail
	if (!node) return false;
	
	//if match is found, return true
	if (node->display(name)) return true;
	
	//else, traverse to next node
	return display(name, node->get_next());
}



//wrapper; if activites exist, call recursive function to find and return
//object matching argument name. returns value of recursive function
bool Data::retrieve(char *name, Activity *&retrieved)
{
	//if activities exist
	if (activities)
	{
		//call recursive function
		return retrieve(name, retrieved, activities);
	}

	return false;
}



//recursively checks each node in DLL for Activity object that matches
//argument name; returns true if found, false otherwise
bool Data::retrieve(char *name, Activity *&retrieved, Node *node)
{
	//stopping condition
	if (!node) return false;
	
	//check current node
	if (node->retrieve(name, retrieved))
	{
		return true;//return true if retrieval successful
	}

	//if next node found, recall function with next node
	return retrieve(name, retrieved, node->get_next());
}



//finds Activity matching argument name; deletes object
bool Data::remove(char *name)
{
	//if no Activity objects added yet, exit with fail
	if (!activities) return false;
	
	//try removal from head of DLL
	if (activities->remove(name))
	{
		//if removal succeeds, check if array is empty
		if (activities->is_empty())
		{
			//save head node
			Node *temp = activities;

			//set head to next
			activities = activities->get_next();
			
			//if head not null
			if (activities)
			{
				//set prev to node to be deleted
				activities->set_prev(temp);
			}
			
			//delete old head node
			delete temp;

			//set current head's prev to null
			temp = NULL;
		}

		return true;
	}

	//call recursive function to remove object
	return remove(activities->get_next(), name);
}



//recursively checks each node in DLL to see if node's array holds object
//matching argument name; if found, call node remove function
bool Data::remove(Node *node, char *name)
{
	//if DLL empty of or end of list reached with no match
	if (!node) return false;
	
	//if object successfully removed
	if (node->remove(name)) 
	{
		//check if node array is empty
		if (node->is_empty())
		{
			//connect node's prev to node's next
			node->get_prev()->set_next(node->get_next());
			
			//node node's next not null
			if (node->get_next())
			{
				//set node's next's prev to node's prev
				node->get_next()->set_prev(node->get_prev());
			}
			
			//delete curret node
			delete node;
		}
		
		//if node not empty, exit with sucess
		return true;
	}
	
	//traverse to next node to look for match
	return remove(node->get_next(), name);
}



//calls display function for all object of argument priority
bool Data::display_all_p()
{
	//if activities exist
	if (activities)
	{
		//call node's display all function
		return activities->display_all();
	}

	return false;
}


