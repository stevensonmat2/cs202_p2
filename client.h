#include "data.h"



//client class. provides interface for user to work with Activity objects
class Client {

	public:
		//constructor
		Client();
		
		//destructor
		~Client();

		//main menu; provides command interface for working 
		//with Activity objects
		void menu();

		//allows user to add new Activity
		void add();

		//allows user to remove an Activity
		void remove();

		//allows user to display info of an Activity
		void display();

		//allows user to display all Activity objects
		//with the highest priority
		void display_top_p();

	private:
		//prompts user to input all data for new Activity object
		void build(Activity *&temp);

		//pointer to Data object; enables access to data structure
		Data *activities;
};
