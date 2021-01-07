//
// Dylan Whitehead
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: A derived child class of PlayerClass. Assumes all methods and data publicly from PlayerClass and adds a new version of Write(). 
// Meant to serve as a gateway parent class for any other player type that falls under the same category. Any and all functions/variables that 
// are consistently used by all human types but not by all bug AND human types are to be put in this class to avoid redundancy.
// 
// Special Notes: The default constructor is set to private and should never be used. Will always throw an exception.
//
//


#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "wpn.h"
#include "pack.h"

using namespace std;


class Human : public PlayerClass
{
	public:
	
	//*****PUBLIC METHODS*****

	//*****CONSTRUCTORS/DESTRUCTORS*****
	
	Human(const Human& h);
	//Narrative: Copy constructor for the human class that deep copies all data from another Human to this one.
	//
	//Pre-condition: none
	//
	//Post-condition: A new instance of Human is created
	//

	virtual ~Human();
	//Narrative: Destructor for the Human class that deallocates all dynamic data.
	//
	//Pre-condition: none
	//
	//Post-condition: All dynamically allocated data has been deleted
	//
	
	
	//*****OBSERVERS*****
	
	bool HasWeapon() const;
	//Narrative: returns true if player has a weapon, false otherwise
	//
	//Pre-condition: none
	//
	//Post-condition: returns true if player's weapon is not null, false otherwise
	//
	
	string WeaponName() const;
	//Narrative: Return the name of the weapon. Return empty string if there is no weapon
	//
	//Pre-condition: Player needs to be holding a weapon or an empty string will be returned
	//
	//Post-condition: the weapon's name is returned
	//
	
	string WeaponNameAndNum() const;
	//Narrative: Return the name of the weapon name and serial number. Return empty string if there is no weapon.
	//
	//Pre-condition: Player needs to be holding a weapon or an empty string will be returned
	//
	//Post-condition: the weapon's name and number is returned in one string
	//
	
	int WeaponSkill() const;
	//Narrative: Return the skill of the current weapon Player has equipped. If no weapon is equipped, 0 is returned instead.
	//
	//Pre-condition: Weapon should not be null or else 0 will be returned.
	//
	//Post-condition: Either weapon skill is retrieved from map and returned or 0 is returned if not holding one.
	//

	int PackWeight() const;
	//Narrative: Returns the Player's initial maximum weight they can carry in their pack. This is calculated by
	//30 + (POWER * 5)
	//
	//Pre-condition: none
	//
	//Post-condition: An int of weight is returned
	//

	vector<string> Pack() const;
	//Narrative: Returns the Player's pack as a list of strings that include the Name and Serial Number
	//for the weapons in the pack.
	//
	//Pre-condition: none
	//
	//Post-condition: pack returned as a vector of strings
	//
	
	virtual int HitDamage() const;
	//Narrative: If the player is active, the damage inflicted is returned, otherwise 0 is returned. Damage is calculated by using the Weapon Skill for the weapon
	//or player’s power if no weapon; add the score from the Damage Value of the weapon used or roll the Physical Damage of player if no weapon.
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, damage inflicted is returned, else 0 is returned. 
	//

	virtual int Impact() const;
	//Narrative: If the player is active, the impact of a critical wound inflicted is returned, otherwise 0 is returned. The return value is determined from the Impact Table 
	//using either the weapon power (if the player has a weapon) or the player’s power. A player can inflict no critical wound if they are not active or have no weapon and
	//player power is less than 2. 
	//Return -1 if the wound is a mortal wound (‘w’ in the strike table).
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, critical wound inflicted is returned, else 0 is returned.
	//


	//*****TRANSFORMERS*****
	
	Weapon* GrabWeapon(Weapon* newWeapon);
	//Narrative: An active human grabs a new weapon. A human grabs the weapon sent in and returns the weapon they were using or returns NULL if there was not a weapon.
	//If the player is not active, no change is made and the weapon sent in is returned. If the player has skill with that weapon then that weapon skill is used. 
	//If the player has never used this weapon before then the skill is set to 1.
	//
	//Pre-condition: weapon being passed in should not be NULL
	//
	//Post-condition: Player's weapon is now set to newWeapon passed, if used before, previous skill for that weapon will be used, otherwise skill is added and set to 1.
	//
	
	Weapon* ChangeWeapon(string weaponName);
	//Narrative: An active human changes the weapon carried with a weapon in the pack. The weapon name passed in is the weapon the player wants as the current carried 
	//weapon. If the player does not have that weapon either in hand or in the pack, then no change is made. If there is a weapon swap then the discarded weapon is put into
	//the pack if possible, otherwise it is returned. If there is no extra weapon that weapon cannot fit in the pack, or the weapon is not available, then NULL is returned.
	//Only active players can change their weapon.
	//
	//Pre-condition: A weapon of the name passed in should already exist, and the player should be active or else no changes will be made.
	//
	//Post-condition: The weapon is either switched with one in the pack or if inactive or weapon passed in is false, nothing changes.
	//
	
	Weapon* DropWeapon();
	//Narrative: An active player drops their weapon and leaves the player with no weapon. The method returns weapon dropped, or NULL if the player is not active or 
	//there was no weapon to drop. 
	//
	//Pre-condition: Player should have a weapon already equipped in order for a change to occur.
	//
	//Post-condition: If IsActive and weapon isn't equal to NULL, then the weapon being dropped is returned, else null is returned.
	//
	
	bool ImprovedSkill(int improvement);
	//Narrative: An active player that has a weapon improves their skill with that weapon. Return true if the player can update the weapon skill, false otherwise.
	//Improvement should be greater than or equal to zero.
	//
	//Pre-condition: A player should already be equipped with a weapon or else no change will occur. Improvment should be greater than zero.
	//
	//Post-condition: True returned if improvement occured, else false returned.
	//

	virtual void Write(ostream& out) const;
	//Narrative: Writes all of the values of the class to an output stream by passing it to the Write() function inside 
	//of the PlayerClass
	//
	//Pre-condition: output stream passed in
	//
	//Post-condition: control is passed to the method in PlayerClass, output occurs with stream passed in.
	//

	
	//*****PURE VIRTUAL*****
	
	virtual bool Move();
	//Narrative: 
	//
	//Pre-condition: 
	//
	//Post-condition: 
	//
	
	
	//*****OVERLOADED ASSIGNMENT OPERATOR*****
	Human& operator=(const Human& h);
	//Narrative: Assignment operator for Human class. Deep copies all data from one human to another.
	//
	//Pre-condition: none
	//
	//Post-condition: All data is copied.
	//
	
	
	private:
	
	//*****PRIVATE METHODS*****
	
	Human();
	//Narrative: Default constructor for the Human class. Set to private and should never be used or accessible.
	//
	//Pre-condition: none
	//
	//Post-condition: exception thrown
	//
	
	
	//*****PURE VIRTUAL*****
	
	virtual bool IsMyEnemyCheck(const PlayerClass* p) const;
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
	
	
	//*****HELPER METHODS*****
	void Copy(const Human& h);

	//*****PRIVATE VARIABLES*****
	Weapon::Weapon* currWeapon; //current weapon pointer
	typedef map<string, int> MapType;
	MapType myWpns; //map of weapons with name as key
	static const int DEFAULT_SKILL;
	static const int DEFAULT_WT_MULTIPLIER; //Used for calculation in PackWeight()
	PackClass::PackClass* const PACK; //const pointer to a nonconstant pack. Not pointing to a constant instance of PackClass because we are adding/removing from it.	

	static const int DEFAULT_HUMAN_IMPACT_DIE;
	static const int DEFAULT_HUMAN_IMPACT_FACE;
	static const int MAX_HUMAN_IMPACT_POWER;
	static const int MIN_HUMAN_IMPACT_POWER;

	protected:
	
	Human(const string NAME, const int C_STATS[], const int V_STATS[]);
	//Narrative: Parameterized constructor for the Human class 
	//
	//Pre-condition: NAME passed in as well as two appropriately indexed const int arrays passed in.
	//
	//Post-condition: A new instance of Human class is created, passing the flow of control to PlayerClass and assuming
	//all of its methods and variables.
	//


};

#endif