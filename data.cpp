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

	//if (prev) delete prev;

	if (activities) 
	{
		int i = 0;

		delete_array(i);
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



//finds Activity matching argument name; returns object
//via argument pointer
bool Node::retrieve(char *name, Activity *&retrieved)
{
	int i = 0;

	if (activities)
	{
		return retrieve(name, retrieved, i);
	}
	
	return false;
}



bool Node::retrieve(char *name, Activity *&retrieved, int i)
{
	if (i == MAX_LEN) return false;

	if (activities[i]->cmp_name(name) == 0)
	{
		retrieved = activities[i];

		return true;
	}

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
		bool val = remove(name, i);

		if (!activities[i])
		{
			delete [] activities;
			activities = NULL;
		}

		return val;
	}
	
	//else exit with fail
	else return false;
}



//recursively checks argument array for object matching name argument; if found
//removes object and calls function to shift objects in array
bool Node::remove(char *name, int i)
{
	if (i == MAX_LEN) return false;
	
	if (activities[i])
	{
		if (activities[i]->cmp_name(name) == 0)
		{
			delete activities[i];
			activities[i] = NULL;
			shuffle_left(i);

			return true;
		}
		
		else return remove(name, ++i);
	}

	return false;
}



//calls display function for all object of argument priority
bool Node::display_all()
{
	int i = 0;//set index tracker

	if (activities)
	{
		display_all(i);

		return true;
	}

	return false;
}



//calls display function for all object of argument priority
void Node::display_all(int i)
{
	//if end of array or empty index found, check next node's array
	//then exit
	if (i == MAX_LEN || !activities[i])
	{
		if (!get_next()) return;

		if (get_next()->cmp_lvl(*activities[0]) == 0)
		{
			get_next()->display_all();
			
		}

		return;
	}
	
	//call objects display function
	activities[i]->display();

	//traverse to next index
	display_all(++i);
}



int Node::cmp_lvl(const Activity &to_check)
{
	if (activities)
	{
		return activities[0]->cmp_lvl(to_check);
	}

	return -10;
}




int Node::cmp_name(const Activity &to_check)
{
	int i = 0;

	if (activities)
	{
		return cmp_name(to_check, i);
	}

	return -10;
}



int Node::cmp_name(const Activity &to_check, int i)
{
	if (!activities[i]) return -1;

	if (i == MAX_LEN-1)
	{
		return activities[i]->cmp_obj(to_check);
	}

	if (!activities[i+1])
	{
		return activities[i]->cmp_obj(to_check);
	}

	return cmp_name(to_check, ++i);
}


bool Node::is_empty()
{
	if (!activities) return true;

	return false;
}

		



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



void Data::delete_list(Node *&head)
{
	if (!head) return;

	Node *temp = head->get_next();

	delete head;

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

//copies argument object and inserts new object
//into data structure
bool Data::insert(const Activity &to_copy)
{
	if (!activities)
	{
		activities = new Node;
		return activities->insert(to_copy);
	}

	return insert(activities, to_copy);
}


bool Data::insert(Node *&node, const Activity &to_copy)
{
	int p_lvl = node->cmp_lvl(to_copy);

	if (p_lvl == 0)
	{
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

				//set temp's next's prev to temp
				if (temp->get_next())
				{
					temp->get_next()->set_prev(temp);
				}
				
				return temp->insert(to_copy);
			}

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
				
				return activities->insert(to_copy);
			}
			
		}

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

			return temp->insert(to_copy);
		}
	}

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



//finds Activity matching argument name; returns object
//via argument pointer
bool Data::retrieve(char *name, Activity *&retrieved)
{
	if (activities)
	{
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
	if (activities->retrieve(name, retrieved))
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
	
	//call recursive function to remove object
	return remove(activities, name);
}



//recursively checks each node in DLL to see if node's array holds object
//matching argument name; if found, call node remove function
bool Data::remove(Node *&node, char *name)
{
	if (!node) return false;

	if (node->remove(name)) 
	{
		if (node->is_empty())
		{
			if (node == activities)
			{

				if (activities->get_next())
				{
					Node * temp = node->get_prev();

					activities = node->get_next();

					delete activities->get_prev();

					activities->set_prev(temp);
				}

				else
				{
					delete activities;

					activities = NULL;
				}
			}

			else
			{
				Node *temp = node;

				Node *prev = &(*temp->get_prev());

				Node *next = &(*temp->get_next());

				prev->set_next(next);

				if (temp->get_next())
				{
					next->set_prev(prev);
				}
				
				delete node;

				node = NULL;
			}
		}

		return true;
	}

	Node *temp = node->get_next();

	return remove(temp, name);
}



//calls display function for all object of argument priority
bool Data::display_all_p()
{
	if (activities)
	{
		return activities->display_all();
	}

	return false;
}


