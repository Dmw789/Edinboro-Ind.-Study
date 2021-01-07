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


#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "human.h"
using namespace std;


class Barbarian : public Human
{
	public:
	
//*****PUBLIC VARIABLES*****

	static const string TYPE_STR;

//*****PUBLIC METHODS*****

	//*****CONSTRUCTORS*****
	
	Barbarian(string name);
	//Narrative: Parameterized constructor for the Barbarian class. Takes a name and creates a new instance of the class with
	//the appropriate stats. As a child class of Human, all methods and variables of Human and PlayerClass are assigned as well.
	//
	//Pre-condition: The name passed in is of type string and is not empty, else an exception will be thrown.
	//
	//Post-condition: A new instance of Barbarian is created.
	//	


	//*****OBSERVERS*****
	
	string TypeStr() const;
	//Narrative: Returns the type of the class as a string. 
	//
	//Pre-condition: none
	//
	//Post-condition: TYPE_STR returned
	//
	
	virtual int HitDamage()  const;
	//Narrative: If the player is active, the damage inflicted is returned, otherwise 0 is returned. Damage is calculated by using the player’s power.
	//
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, damage inflicted is returned, else 0 is returned. 
	//
	
	virtual Barbarian* Clone() const;
	//Narrative: Returns a pointer of own class type. Helps to determine of what type the pointer is during runtime.
	//
	//Pre-condition: none
	//
	//Post-condition: pointer returned
	//	

	
	//*****TRANSFORMERS******
	
	virtual bool Heal();
	//Narrative: If played is active, their health is updated by adding 
	//HEAL_AMOUNT to it. If their current health plus the heal amount being
	//added would be more than MAX, the health is set to MAX instead. Returns
	//true unless the player isn't active or dead.
	//
	//Pre-condition: none
	//
	//Post-condition: stats[CURR_HEALTH] updated if player is active and true
	//is returned, else stats[CURR_HEALTH] not updated and false returned.
	//
	
	//*****OUTPUT*****
	
	virtual void Write(ostream& out) const;
	//Narrative: Writes all of the values of the class to an output stream by passing it to the Write() function inside 
	//of the Human class.
	//
	//Pre-condition: output stream passed in
	//
	//Post-condition: control is passed to the method in Human class, output occurs with stream passed in.
	//

	private:

//*****PRIVATE METHODS*****

	//*****CONSTRUCTORS*****
	
	Barbarian();
	//Narrative: A private constructor for the Barbarian class. Set to private and should never be called. 
	//
	//Pre-condition: none
	//
	//Post-condition: Exception thrown
	//		

	virtual bool IsMyEnemyCheck(const PlayerClass* p) const;
	//Narrative: Returns true if the player (p) is an enemy of this player 
	//class, false otherwise
	//
	//Pre-condition: PlayerClass passed in has to be passed by address and cannot be null or else
	//nothing will happen.
	//
	//Post-condition: If player is a human type, returns true if p is a bug 
	//type, otherwise returns true.
	//If player is a bug, then returns true unless p is a bug of the same type.
	//

	
//*****PRIVATE VARIABLES*****
	
	static const int INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE];
	static const int INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE];
	static const int BARBARIAN_HEAL_AMOUNT;
};

#endif