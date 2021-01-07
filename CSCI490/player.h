//
// Dylan Whitehead
// d823691w
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: Class designed to hold a series of stats that appropriately describe the state of a player at any given moment
// during the  game's runtime. Every instance of the player class created holds values for current and max health, willpower, 
// current and max speed, momentum, power, physdam, defense, row, col, and direction. They are also given names, which can be
// passed and set during construction using the second constructor.
// 
// Special Notes: If statsType or ConstStatsType are changed in any way the child classes will have to change their stat arrays accordingly.
// The default constructor is set to private and should never be used. Will always throw an exception.
//
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "gamespace.h"
#include "dice.h"

using namespace std;

class PlayerClass
{
	public:
//*****PUBLIC CONSTANT VARIABLES*****
	
	//Special Notes: The arrays are publicly declared so all child classes can use the END_STAT_TYPE and END_CONST_STAT_TYPE to index 
	//their own individual stat arrays.
	//The alternative is to either hard-code in the values to the child classes or create a NUM_STATS for the size of those child stat arrays,
	//though both of those would add extra variables that would need to be changed if added/deleting stats from the StatsType or ConstStatsType

	enum StatsType{CURR_HEALTH, WILLPOWER, CURR_SPEED, MOMENTUM, POWER, DEFENSE, ROW, COL, END_STAT_TYPE};
	enum ConstStatsType{MAX_HEALTH, MAX_SPEED, PHYS_DAM_FACE, PHYS_DAM_DICE, END_CONST_STAT_TYPE};
	
	//*****CONSTRUCTORS/DESTRUCTORS*****
	
	virtual ~PlayerClass();
	//Narrative: A destructor for the PlayerClass. Deallocates all dynamic data used by the class.
	//
	//Pre-condition: none
	//
	//Post-condition: PlayerClass instance is destructed.
	//
	
	
	//*****GETTERS*****
	
	virtual string Name() const;
	//Narrative: returns the player's name
	//
	//Pre-condition: none
	//
	//Post-condition: NAME returned
	//
	
	int Row() const;
	//Narrative: Returns the row of the cell the player is on
	//
	//Pre-condition: none
	//
	//Post-condition: stats[ROW] returned
	//
	
	int Col() const;
	//Narrative: Returns the column of the cell the player is on
	//
	//Pre-condition: none
	//
	//Post-condition: stats[COL] returned
	//

	GameSpace:: DirType Dir() const;
	//Narrative: Returns the direction of the player
	//
	//Pre-condition: none
	//
	//Post-condition: dir returned
	//	
	
	int MaxHealth() const;
	//Narrative: Returns the maximum health of the player
	//
	//Pre-condition: none
	//
	//Post-condition: STATS[MAX_HEALTH] returned
	//
	
	int Health() const;
	//Narrative: Returns the current health of the player
	//
	//Pre-condition: none
	//
	//Post-condition: stats[HEALTH] returned
	//
	
	int WillPower() const;
	//Narrative: Returns the player's willpower
	//
	//Pre-condition: none
	//
	//Post-condition: stats[WILLPOWER] returned
	//

	int MaxSpeed() const;
	//Narrative: Returns the player's maximum speed
	//
	//Pre-condition: none
	//
	//Post-condition: STATS[MAX_SPEED] returned
	//
	
	int CurrentSpeed() const;
	//Narrative: Returns the player's current speed
	//
	//Pre-condition: none
	//
	//Post-condition: stats[CURR_SPEED] returned
	//
	
	int Momentum() const;
	//Narrative: Returns the player's momentum
	//
	//Pre-condition: none
	//
	//Post-condition: stats[MOMENTUM] returned
	//

	int Power() const;
	//Narrative: Returns the player's power
	//
	//Pre-condition: none
	//
	//Post Condition: stats[POWER] returned
	//
	
	virtual int RollPhysDam() const;
	//Narrative: Return the player's physical damage
	//
	//Pre-condition: none
	//
	//Post Condition: Physical damage rolled and amount returned
	//
	
	int Defense() const;
	//Narrative: Return the player's defense value
	//
	//Pre-condition: none
	//
	//Post-condition: stats[DEFENSE] returned
	//
	
	virtual bool IsAlive() const;
	//Narrative: Returns true if player is alive, otherwise returns false
	//
	//Pre-condition: none
	//
	//Post-condition: If HP > 0, return true, else false
	//

	virtual bool IsDead() const; 
	//Narrative: Returns true if player is dead, otherwise returns false
	//
	//Pre-condition: none
	//
	//Post-condition: If HP == 0, return true, else false
	//
	
	virtual bool IsActive() const;
	//Narrative: Returns true if the player is active, otherwise returns false
	//
	//Pre-condition: none
	//
	//Post-condition: If active, return true, else false
	//
	
	int PlayerNum() const;
	//Narrative: Returns the numbered ID of the Player.
	//
	//Pre-condition: none
	//
	//Post-condition: ID number is returned
	//
	
	virtual int HitScore() const;
	//Narrative: If the player is active the hit score is rolled and returned, otherwise 0 is returned
	//
	//Pre-condition: none 
	//
	//Post-condition: Returns the hitscore rolled if active, otherwise returns 0 if inactive
	//
	
	virtual int HitDamage()  const;
	//Narrative: If the player is active, the damage inflicted is returned, otherwise 0 is returned. Damage is calculated by using the player’s power.
	//
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, damage inflicted is returned, else 0 is returned. 
	//
	
	virtual int Impact() const;
	//Narrative: If the player is active, the impact of a critical wound inflicted is returned, otherwise 0 is returned. The return value is determined from the Impact Table using the 
	//player’s power. A player can inflict no critical wound if they are not active or player power is less than 2. 
	//Return -1 if the wound is a mortal wound (‘w’ in the strike table).
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, critical wound inflicted is returned, else 0 is returned.
	//
	
	virtual bool IsMyEnemy(const PlayerClass* p) const;
	//Narrative: Returns true if the player (p) is an enemy of this player OR if the player passed in 
	//considers this player an enemy.
	//
	//Pre-condition: PlayerClass passed in has to be passed by address and cannot be null or else
	//nothing will happen.
	//
	//Post-condition: If player is a human type, returns true if p is a bug 
	//type, otherwise returns true.
	//If player is a bug, then returns true unless p is a bug of the same type.
	//
	
	
	//*****SETTERS*****

	virtual bool MakeActive();
	//Narrative: Makes a player active unless they are dead
	//
	//Pre-condition: Player cannot be dead or nothing will change.
	//
	//Post-condition: If isAlive is true, then active set to true and return 
	//true, else return false
	//

	virtual bool MakeInActive();
	//Narrative: Makes a player inactive
	//
	//Pre-condition: none
	//
	//Post-condition: Set active to false and return true
	//
    
	virtual bool MakeDead();
	//Narrative: Sets player in to a "dead" state. Health, willpower, momentum, 
	//and currrent speed are all set to zero and player is now inactive
	//
	//Pre-condition: none
	//
	//Post-condition: stats[CURR_HEALTH], stats[WILLPOWER], stats[MOMENTUM], and
	//stats[CURR_SPEED] all set to zero. Active set to false. Returns true
	//
    
	int Wounded(int damage);
	//Narrative: If player is active and damage is more than 0, damage deducted 
	//from health. If the player's health drops below zero, then the player is
	//dead and no longer active. Returns Health.
	//
	//Pre-condition: damage passed in
	//
	//Post-condition: if damage > 0, health reduced by damage. If health <= 0, 
	//then active = false. Health returned.
	//
    
	int Invigorate(int vigor);
	//Narrative: If player is active and vigor is greater than zero, the vigor 
	//is added to health. Health is then returned.
	//
	//Pre-condition: vigor passed in
	//
	//Post-condition: If active and vigor > 0, health = health + vigor, health 
	//returned
	//
 
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
    
	int SlowDown(int hazard);
	//Narrative: If player is active and hazard is more than zero, hazard is 
	//deducted from the current speed. Current speed cannot drop below zero
	//and if momentum would be higher than current speed after the change,
	//momentum is reduced to the value of current speed.
	//
	//Pre-condition: Hazard passed in
	//
	//Post-condition: If active is true and hazard > 0, stats[CURR_SPEED]
	//reduced by hazard. If stats[MOMENTUM] > stats[CURR_SPEED], 
	//stats[MOMENTUM] == stats[CURR_SPEED]
	//
    
 	int ResetCurrentSpeed();
	//Narrative: If player is active then current speed is reset to max speed,
	//then current speed is returned.
	//
	//Pre-condition: none
	//
	//Post-condition: if active is true, stats[CURR_SPEED] == stats[MAX_SPEED],
	//else if active is false, stats[CURR_SPEED] remains unchanged. 
	//stats[CURR_SPEED] returned.
	//

	int ResetMomentum();
	//Narrative: If player is active, momentum reset to the current speed, then
	//momentum is returned.
	//
	//Pre-condition: none
	//
	//Post-condition: If active is true, stats[MOMENTUM] == stats[CURR_SPEED],
	//else if active is false, stats[MOMENTUM] remains unchanged.
	//stats[MOMENTUM] returned.
	//
    
	int UseMomentum(int amount);
	//Narrative: If player is active and amount is greater than zero, then the 
	//amount is deducted from the momentum, unless momentum would go below zero
	//in which case it is set to zero.
	//
	//Pre-condition: Amount passed in. Should be higher than zero or else no change will take place.
	//
	//Post-condition: if active is true and amount > 0 and stats[MOMENTUM] - 
	//amount > 0, stats[MOMENTUM] is reduced by amount. If stats[MOMENTUM] would
	//be < 0, it then is set to zero. Momentum Returned either way.
	//
    
	bool SetCell(int newRow, int newCol);
	//Narrative: Changes player's current coordinates. If both newRow and newCol
	// > -1 then the coordinates are set. If they are equal to -1, then the 
	//coordinates are set as well though now the player is off the board. 
	//Otherwise the coordinates are not set. If set, return true, otherwise
	//return false.
	//
	//Pre-condition: NewRow passed and newCol cannot be higher than NUM_COL and NUM_ROW respectively
	//or lower than -1 for any change to take place.
	//
	//Post-condition: if coordinates set, return true, else false.
	//
    
	bool SetDir(GameSpace:: DirType newDir);
	//Narrative: Change player's current direction
	//
	//Pre-condition: newDir passed
	//
	//Post-condition: dir equal to new value
	//
    
    int Fortify(int boost);
	//Narrative: If the player is active and boost is greater than zero, the boost is added to the defense. Return the defense.
	//
	//Pre-condition: int boost passed in must be more than zero in order for a change to occur. 
	//
	//Post-condition:  If boost passed in is greater than zero, boost is added to defense. Defense is returned.
	//
	
	int Expose(int decline);
	//Narrative: If the player is active and decline is greater than zero, the decline is deducted from the defense. If the player’s defense drops below zero, set it to zero indicating
	//the player cannot defend itself. Defense is returned.
	//
	//Pre-condition: int decline passed in must be more than zero in order for a change to occur.
	//
	//Post-condition: If decline passed in is greater than zero, decline is deducted from defense. If defense would otherwise be less than zero, it is equal to zero.
	//
	
	int WillPowerAdj(int adjustment);
	//Narrative: Adjusts the WillPower of the player by whatever is passed in. If passed a negative value, that number is subtracted, if passed
	//a positive value that number is added to the overall total. If Willpower is higher than the max, or lower than the minimum, it will be set to those values
	//
	//
	//Pre-condition: none
	//
	//Post-condition: Willpower is adjusted and the new value is returned.
	//

	virtual bool CriticalWound();
	//Narrative: Applies the outcome of a critical wound on an active player. The player’s health is reduced by 10 points and the current speed is decreased by half (round down). 
	//If player is still alive then consult the Critical Wound Table for the damage to the willpower or the life ending damage. Return true if player is still alive and false if player is dead.
	//
	//Pre-condition: none
	//
	//Post-condition: If IsAlive returns true, then return true, else false.
	//
	
	
	//*****PURE VIRTUAL METHODS*****
	
	virtual string TypeStr() const = 0;
	//Narrative: Returns the type of the class as a string. 
	//
	//Pre-condition: none
	//
	//Post-condition: TYPE_STR returned
	//
		
	virtual bool Move() = 0;
	//Narrative: 
	//
	//Pre-condition: 
	//
	//Post-condition: 
	//
	
	
	//*****OUTPUT*****

	virtual void Write(ostream& out) const;
	//Narrative: Writes all of the values of the class to an output stream in the following order:
	//active#name#(row,col,dir)#maxH#health#willPow#power#maxSp#currSp#mom#pDam#defVal<lf>
	//
	//
	//Pre-condition: output stream has to be either opened or output to terminal
	//
	//Post-condition: All data from the class has been output via the output stream
	//
	
	//*****OVERLOADED COMPARISON OPERATORS*****
	bool operator==(const PlayerClass& p) const;
	bool operator!=(const PlayerClass& p) const;
	bool operator<(const PlayerClass& p) const;
	bool operator>(const PlayerClass& p) const;
	bool operator<=(const PlayerClass& p) const;
	bool operator>=(const PlayerClass& p) const;
	
	//*****OVERLOADED ASSIGNMENT OPERATOR*****
	PlayerClass& operator=(const PlayerClass& player);
	//Narrative: Assignment operator for PlayerClass. Deep copies all data from one player to another.
	//
	//Pre-condition: none
	//
	//Post-condition: All data is copied.
	//
	

	private:
	
//*****PRIVATE METHODS*****

	PlayerClass();
	//Narrative: The default construtor for the PlayerClass. Creates an instance of PlayerClass with default values
	//correlating to the DEFAULT_TYPE. Direction set to DEFAULT_DIR and both column and row are set to -1.
	//
	//Pre-condition: N/A
	//
	//Post-condition: A new instance of PlayerClass is created wtih default values.
	//
	
	//*****HELPER METHODS*****
	
	string ValidateName(string sName) const;
	//Narrative: Validates a name to be no longer than 10 digits long and to delete any unncessecary whitespace.
	//
	//Pre-condition: N/A
	//
	//Post-condition: A string is returned with a name that fits the given specifications
	//

	void Copy(const PlayerClass& player);
	//Narrative: Copies all class data from class passed in to this class.
	//
	//Pre-condition: None
	//
	//Post-condition: All data has been copied and proper memory has been allocated
	//
	
	
	//*****PURE VIRTUAL***** 
	
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

//*****PRIVATE VARIABLES*****

	const string NAME; //Name of player
	GameSpace:: DirType dir; //Direction player is facing 
	bool active; //Whether or not the player is active
	
	int stats[END_STAT_TYPE]; //Stat array that holds all integer values of stats.
	const int* const STATS; //pointer to an array of all constant stat values
	
	static int playerNumTotal;
	int playerNum;
	
	static const string DEFAULT_NAME;
	static const GameSpace:: DirType DEFAULT_DIR;
	static const int MIN_WILLPOWER;
	static const int MAX_WILLPOWER;
	static const int NUM_HUMAN_TYPES; // Total num - 1 for enum
	static const int NUM_BUG_TYPES; // Total num - 1 for enum
	static const int HEAL_AMOUNT;
	static const int CRIT_WOUND_AMOUNT;

	//Intialization of all tables and their variables	
	static const int IMPACT_ROW = 13;
	static const int IMPACT_COL = 13;
	static const int CRIT_ROW = 13;
	static const int CRIT_COL = 13;
	static const int W = -1;
	static const int K = 2;
	static const int IMPACT_TABLE[IMPACT_ROW][IMPACT_COL];
	static const int CRITICAL_WOUND_TABLE[CRIT_ROW][CRIT_COL];
	
	//Dice && Roll variables
	static const int DEFAULT_HITSCORE_DIE;
	static const int DEFAULT_HITSCORE_FACE;
	static const int DEFAULT_IMPACT_DIE;
	static const int DEFAULT_IMPACT_FACE;
	static const int MAX_IMPACT_POWER;
	static const int MIN_IMPACT_POWER;
	static const int DEFAULT_CRIT_DIE;
	static const int DEFAULT_CRIT_FACE;
	
	
	protected: 
	
//*****PROTECTED METHODS*****

	PlayerClass(string sName, const int C_STATS[], const int V_STATS[]);
 	//Narrative: A constructor for the PlayerClass that creates an instance of PlayerClass with values correlating
	//to the initPType passed in. Name is set to the name passed in, trimming any whitespace and capitalizing
	//all letters. If name passed is blank, name is set to DEFAULT instead. Direction set to DEFAULT_DIR and both 
	//column and row are set to -1.
	//
	//Pre-condition: Name of player passed in, PlayerType passed in.
	//
	//Post-condition: A new instance of PlayerClass is created with default values.
	//
	
	int RollDie(GameSpace:: RollType what, int numDie, int numFace) const;
	//Narrative: Returns number rolled from the dice class roll function with the dice passed in. If result goes out of bounds,
	//an exception will be thrown.
	//
	//Pre-condition: None
	//
	//Post-condition: Roll returned if dice passed boundaries, else INVALID_ROLL exception was thrown.
	//
	
	int LookupImpact(int roll, int power) const;
	//Narrative: Helper function to be used in derived classes to look up values for impact
	//
	//Pre-condition: none
	//
	//Post-condition: int returned
	//
	
	int LookupWound(int roll, int wPower) const;
	//Narrative: Helper function to be used in derived classes to look up values for critical wound
	//
	//Pre-condition: none
	//
	//Post-condition: int returned
	//
	
	bool MoveUnits(int units);
	//Narrative:
	//
	//Pre-condition: 
	//
	//Post-condition:
	//
};


//*****TOP-LEVEL*****

//Narrative: Writes all of the values of the class to an output stream in the following order:
//active#name#(row,col,dir)#maxH#health#willPow#power#maxSp#currSp#mom#pDam#defVal<lf>
//
//Pre-condition: output stream has to be either opened or output to terminal. Pointer passed cannot be null or else 
//nothing will be output.
//
//Post-condition: All data from the class has been output via the output stream
//
ostream& operator<<(ostream& out, const PlayerClass* p);

#endif
