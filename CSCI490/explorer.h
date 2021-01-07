//
// Dylan Whitehead
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: A derived child class of Human. Assumes all methods and variables publicly from Human, and therefor from PlayerClass.
// One of the player types used throughout the game that is reusable and replicatable.
// 
// Special Notes: The default constructor is set to private and should never be used. Will always throw an exception.
//
//


#ifndef EXPLORER_H
#define EXPLORER_H

#include "human.h"
using namespace std;


class Explorer : public Human
{
	public:
	
//*****PUBLIC VARIABLES*****

	static const string TYPE_STR;

//*****PUBLIC METHODS*****

	//*****CONSTRUCTORS*****
	
	Explorer(string name);
	//Narrative: Parameterized constructor for the Explorer class. Takes a name and creates a new instance of the class with
	//the appropriate stats. As a child class of Human, all methods and variables of Human and PlayerClass are assigned as well.
	//
	//Pre-condition: The name passed in is of type string and is not empty, else an exception will be thrown.
	//
	//Post-condition: A new instance of Explorer is created.
	//	

	//*****OBSERVERS*****
	
	string TypeStr() const;
	//Narrative: Returns the type of the class as a string. 
	//
	//Pre-condition: none
	//
	//Post-condition: TYPE_STR returned
	//
	
	virtual void Write(ostream& out) const;
	//Narrative: Writes all of the values of the class to an output stream by passing it to the Write() function inside 
	//of the Human class.
	//
	//Pre-condition: output stream passed in
	//
	//Post-condition: control is passed to the method in Human class, output occurs with stream passed in.
	//

	virtual Explorer* Clone() const;
	//Narrative: Returns a pointer of own class type. Helps to determine of what type the pointer is during runtime.
	//
	//Pre-condition: none
	//
	//Post-condition: pointer returned
	//


	private:

//*****PRIVATE METHODS*****

	//*****CONSTRUCTORS*****
	
	Explorer();
	//Narrative: A private constructor for the Explorer class. Set to private and should never be called. 
	//
	//Pre-condition: none
	//
	//Post-condition: Exception thrown
	//		

	
//*****PRIVATE VARIABLES*****
	
	static const int INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE];
	static const int INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE];
};

#endif