//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// KILLERANT CLASS
// 
// Narrative: A derived child class of Bug. Assumes all methods and variables publicly from Bug, and therefor from PlayerClass.
// One of the player types used throughout the game that is reusable and replicatable.
// 
// Special Notes: The default constructor is set to private and should never be used. Will always throw an exception.
//
//


#ifndef KILLERANT_H
#define KILLERANT_H

#include "bug.h"
using namespace std;


class KillerAnt : public Bug
{
	public:

//*****PUBLIC METHODS*****

	//*****CONSTRUCTORS*****
	KillerAnt(string name);
	//Narrative: Parameterized constructor for the KillerAnt class. Takes a name and creates a new instance of the class with
	//the appropriate stats. As a child class of Bug, all methods and variables of Bug and PlayerClass are assigned as well.
	//
	//Pre-condition: The name passed in is of type string and is not empty, else an exception will be thrown.
	//
	//Post-condition: A new instance of KillerAnt is created.
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
	//of the Bug class.
	//
	//Pre-condition: output stream passed in
	//
	//Post-condition: control is passed to the method in Bug class, output occurs with stream passed in.
	//	
	
	//*****TRANSFORMERS*****
	virtual bool Move();
	//Narrative: 
	//
	//Pre-condition: 
	//
	//Post-condition: 
	//


	private:

//*****PRIVATE METHODS*****

	//*****CONSTRUCTORS*****
	KillerAnt();
	//Narrative: A private constructor for the KillerAnt class. Set to private and should never be called. 
	//
	//Pre-condition: none
	//
	//Post-condition: Exception thrown
	//
	
	//*****OBSERVERS*****
	virtual bool IsMyEnemyCheck(const PlayerClass* p) const;
	//Narrative: Returns true if the player (p) is an enemy of this player 
	//class, false otherwise
	//
	//Pre-condition: 
	//
	//Post-condition: Returns true unless the playerClass passed in is of the same class.
	//

	
//*****PRIVATE VARIABLES*****
	
	static const int INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE];
	static const int INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE];
	static const int MOVE_AMOUNT;
	static const string TYPE_STR;
};

#endif