//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// BUG CLASS
// 
// Narrative: A derived child class of PlayerClass. Assumes all methods and data publicly from PlayerClass and adds a new version of Write(). 
// Meant to serve as a gateway parent class for any other player type that falls under the same category. Any and all functions/variables that 
// are consistently used by all bug types but not by all bug AND human types are to be put in this class to avoid redundancy.
// 
// Special Notes: The default constructor is set to private and should never be used. Will always throw an exception.
//
//


#ifndef BUG_H
#define BUG_H

#include "player.h"
using namespace std;


class Bug : public PlayerClass
{
	public:
	virtual void Write(ostream& out) const;
	//Narrative: Writes all of the values of the class to an output stream by passing it to the Write() function inside 
	//of the PlayerClass
	//
	//Pre-condition: output stream passed in
	//
	//Post-condition: control is passed to the method in PlayerClass, output occurs with stream passed in.
	//

	//*****PURE VIRTUAL METHODS*****
	
	virtual bool Move() = 0;
	//Narrative: 
	//
	//Pre-condition: 
	//
	//Post-condition: 
	//
	
	virtual string Name() const;
	//Narrative: returns the player's name
	//
	//Pre-condition: none
	//
	//Post-condition: NAME returned
	//


	private:

	Bug();
	//Narrative: Default constructor for the Bug class. Set to private and should never be used or accessible.
	//
	//Pre-condition: none
	//
	//Post-condition: exception thrown
	//

	virtual bool IsMyEnemyCheck(const PlayerClass* p) const = 0;
	//Narrative: Returns true if the player (p) is an enemy of this player 
	//class, false otherwise. ONLY returns if the player passed in considered an enemy by this class, does not factor if the enemy
	//passed in considers this player an enemy. Needed for IsMyEnemy to calculate it's result.
	//
	//Pre-condition: PlayerClass passed in has to be passed by address and cannot be null or else
	//nothing will happen.
	//
	//Post-condition: If player is a human type, returns true if p is a bug 
	//type, otherwise returns true.
	//If player is a bug, then returns true unless p is a bug of the same type.
	//
	

	protected:
	Bug(const string NAME, const int C_STATS[], const int V_STATS[]);
	//Narrative: Parameterized constructor for the Bug class 
	//
	//Pre-condition: NAME passed in as well as two appropriately indexed const int arrays passed in.
	//
	//Post-condition: A new instance of Bug class is created, passing the flow of control to PlayerClass and assuming
	//all of its methods and variables.
	//


};

#endif