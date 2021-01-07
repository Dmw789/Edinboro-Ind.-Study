//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// PLAYER CLASS
// 
// Narrative: Class designed to hold a series of stats that appropriately describe the state of a player at any given moment
// during the  game's runtime. Every instance of the player class created holds values for current and max health, willpower, 
// current and max speed, momentum, power, physdam, defense, row, col, and direction. They are also given names, which can be
// passed and set during construction using the second constructor.
//
// Special Notes: 
//
//

#include "player.h"
#include "board.h"
#include <math.h>
using namespace std;


//ASSIGN STATIC CONSTS
const string PlayerClass:: DEFAULT_NAME = "DEFAULT";
const GameSpace:: DirType PlayerClass::DEFAULT_DIR = GameSpace:: NORTH;
const int PlayerClass::MAX_WILLPOWER = 12;
const int PlayerClass::MIN_WILLPOWER = 0;
const int PlayerClass::NUM_HUMAN_TYPES = 1; // Total num - 1 for enum
const int PlayerClass::NUM_BUG_TYPES = 2; // Total num - 1 for enum
const int PlayerClass::HEAL_AMOUNT = 10;
const int PlayerClass::CRIT_WOUND_AMOUNT = 10;

const int PlayerClass::DEFAULT_HITSCORE_DIE = 2;
const int PlayerClass::DEFAULT_HITSCORE_FACE = 6;
const int PlayerClass::DEFAULT_IMPACT_DIE = 2;
const int PlayerClass::DEFAULT_IMPACT_FACE = 6;
const int PlayerClass::MAX_IMPACT_POWER = 12;
const int PlayerClass::MIN_IMPACT_POWER = 2;
const int PlayerClass::DEFAULT_CRIT_DIE = 2;
const int PlayerClass::DEFAULT_CRIT_FACE = 6;
int PlayerClass:: playerNumTotal = 0;


//ASSIGN 2D ARRAYS

const int PlayerClass:: IMPACT_TABLE[IMPACT_ROW][IMPACT_COL] = {
{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
{0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,  W},
{0,  0,  2,  3,  4,  5,  6,  7,  8,  9, 10,  W,  W},
{0,  0,  3,  4,  5,  6,  7,  8,  9, 10,  W,  W,  W},
{0,  0,  4,  5,  6,  7,  8,  9, 10,  W,  W,  W,  W},
{0,  0,  5,  6,  7,  8,  9, 10,  W,  W,  W,  W,  W},
{0,  0,  6,  7,  8,  9, 10,  W,  W,  W,  W,  W,  W},
{0,  0,  7,  8,  9, 10,  W,  W,  W,  W,  W,  W,  W},
{0,  0,  8,  9, 10,  W,  W,  W,  W,  W,  W,  W,  W},
{0,  0,  9, 10,  W,  W,  W,  W,  W,  W,  W,  W,  W},
{0,  0, 10,  W,  W,  W,  W,  W,  W,  W,  W,  W,  W}
};


const int PlayerClass:: CRITICAL_WOUND_TABLE[CRIT_ROW][CRIT_COL] = {
{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{0,  0,  K,  K,  K,  K,  K,  K,  K,  K,  K,  K, -1},
{0,  0,  K,  K,  K,  K,  K,  K,  K,  K,  K, -1, -1},
{0,  0,  K,  K,  K,  K,  K,  K,  K,  K, -1, -1, -1},
{0,  0,  K,  K,  K,  K,  K,  K,  K, -1, -1, -1, -1},
{0,  0,  K,  K,  K,  K,  K,  K, -1, -1, -1, -1, -1},
{0,  0,  K,  K,  K,  K,  K, -1, -1, -1, -1, -1, -1},
{0,  0,  K,  K,  K,  K, -1, -1, -1, -1, -1, -1, -1},
{0,  0,  K,  K,  K, -1, -1, -1, -1, -1, -1, -1, -1},
{0,  0,  K,  K, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0,  0,  K, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};


//*****METHODS*****


//*****CONSTRUCTORS*****


PlayerClass::PlayerClass(): NAME(DEFAULT_NAME),
							STATS(NULL)

{
	throw GameSpace:: INVALID_MISC;
}


PlayerClass::PlayerClass(string sName, const int C_STATS[], const int V_STATS[]): NAME(ValidateName(sName)),
																			      STATS(C_STATS)

{	
	//Set stats
	//iterator that sets every stat for a type
	for(int i = 0; i < END_STAT_TYPE; ++i)
	{
		stats[i] = V_STATS[i];
	}
	
	//Set remaining variables
	dir = DEFAULT_DIR;
	active = false;
	playerNumTotal += 1;
	playerNum = playerNumTotal;
}


//*****DESTRUCTORS*****


PlayerClass:: ~PlayerClass()

{
	
}


//*****OBSERVERS*****


string PlayerClass::Name() const

{
	return NAME;
}


int PlayerClass::Row() const

{
    return stats[ROW];
}


int PlayerClass::Col() const

{
    return stats[COL];
}


GameSpace:: DirType PlayerClass:: Dir() const

{
    return dir;
}


int PlayerClass::MaxHealth() const

{
    return STATS[MAX_HEALTH];
}


int PlayerClass::Health() const

{
    return stats[CURR_HEALTH];
}


int PlayerClass:: WillPower() const

{
   	return stats[WILLPOWER];
}


int PlayerClass:: MaxSpeed() const

{
	return STATS[MAX_SPEED];
}


int PlayerClass:: CurrentSpeed() const

{
   	return stats[CURR_SPEED];
}


int PlayerClass:: Momentum() const

{
   	return stats[MOMENTUM];
}


int PlayerClass:: Power() const

{
	return stats[POWER];
}


int PlayerClass:: RollPhysDam() const

{
	return Dice::Roll(Name(), GameSpace::RollType(DAMAGE), STATS[PHYS_DAM_DICE], STATS[PHYS_DAM_FACE]);
}


int PlayerClass:: Defense() const

{
    return stats[DEFENSE];
}


bool PlayerClass:: IsAlive() const

{
	return stats[CURR_HEALTH] > 0;
}


int PlayerClass:: PlayerNum() const

{
	return playerNum;
}


bool PlayerClass:: IsDead() const

{
	return stats[CURR_HEALTH] <= 0;
}


bool PlayerClass:: IsActive() const

{
	return active;
}


int PlayerClass:: HitScore() const

{
	int roll = 0;
	
	if(IsActive())
	{
		roll = RollDie(GameSpace::HITSCORE, DEFAULT_HITSCORE_DIE, DEFAULT_HITSCORE_FACE);
	}
	
	
	return roll;
}


int PlayerClass:: HitDamage() const

{
	int damage = 0;
	
	if(IsActive())
	{
		damage = RollPhysDam() + Power();
	}
	
	return damage;
}


int PlayerClass:: Impact() const

{
	int impactAmount = 0;
	int roll = 0;
	
	if(IsActive())
	{	
		roll = RollDie(GameSpace:: IMPACT, DEFAULT_IMPACT_DIE, DEFAULT_IMPACT_FACE);
		
		if(Power() >= MIN_IMPACT_POWER && Power() < MAX_IMPACT_POWER)
		{
			impactAmount = LookupImpact(roll, Power());
		}
		else if(Power() >= MAX_IMPACT_POWER)
		{
			impactAmount = LookupImpact(roll, MAX_IMPACT_POWER);
		}
	}

	return impactAmount;
}


bool PlayerClass:: IsMyEnemy(const PlayerClass* p) const

{
	return(IsMyEnemyCheck(p) || (p && p->IsMyEnemyCheck(this)));
}


//*****TRANSFORMERS*****


bool PlayerClass:: MakeActive() 

{
	if(IsAlive())
	{
		active = true;
	}

	return IsAlive();
}


bool PlayerClass:: MakeInActive()

{
	active = false;
	
	return true;
}


bool PlayerClass:: MakeDead()

{
	stats[CURR_HEALTH] = 0;
	stats[WILLPOWER] = 0;
	stats[MOMENTUM] = 0;
	stats[CURR_SPEED] = 0;
	MakeInActive();
	
	return true;
}


int PlayerClass:: Wounded(int damage)

{
	if(IsActive() && damage > 0)
	{
		stats[CURR_HEALTH] -= damage;
		if(stats[CURR_HEALTH] <= 0)
		{
			MakeDead();
		}
	}
	
	return stats[CURR_HEALTH];
}


int PlayerClass:: Invigorate(int vigor)

{
	if(IsActive() && vigor > 0)
	{
		if(stats[CURR_HEALTH] + vigor >= STATS[MAX_HEALTH])
		{
			stats[CURR_HEALTH] = STATS[MAX_HEALTH];
		}
		else
		{
			stats[CURR_HEALTH] += vigor;
		}
	}

	return stats[CURR_HEALTH];
}


bool PlayerClass::Heal()

{
	bool healed = false;

	if(IsActive() && IsAlive())
	{
		ResetCurrentSpeed();
		Invigorate(HEAL_AMOUNT);
		healed = true;
	}

	return healed;
}


int PlayerClass:: SlowDown(int hazard)

{
	if(IsActive() && hazard > 0)
	{
		if(stats[CURR_SPEED] - hazard < 0)
		{
			stats[CURR_SPEED] = 0;
		}
		else
		{
			stats[CURR_SPEED] -= hazard;
		}
  
		if(stats[MOMENTUM] > stats[CURR_SPEED])
		{
			ResetMomentum();
		}
	}
	
	return stats[CURR_SPEED];
}


int PlayerClass:: ResetCurrentSpeed()

{
	if(IsActive())
	{
		stats[CURR_SPEED] = STATS[MAX_SPEED];
	}
	
	return stats[CURR_SPEED];
}


int PlayerClass:: ResetMomentum()

{
   	if(IsActive())
    	{
        	stats[MOMENTUM] = stats[CURR_SPEED];
    	}
    
	return stats[MOMENTUM];
}


int PlayerClass:: UseMomentum(int amount)

{
	if(IsActive() && amount > 0)
	{
		if(stats[MOMENTUM] - amount < 0)
		{
			stats[MOMENTUM] = 0;
		}
		else
		{
			stats[MOMENTUM] -= amount;
		}
	}

	return stats[MOMENTUM];
}


bool PlayerClass:: SetCell(int newRow, int newCol)

{
	bool cellSet = false;

	if(newRow >= 0 && newRow < GameSpace:: NUMROWS)
	{
		if(newCol >= 0 && newCol < GameSpace:: NUMCOLS)
		{
			stats[ROW] = newRow;
			stats[COL] = newCol;
			cellSet = true;
		}
	}
	else if(newRow == -1 && newCol == -1)
	{
		stats[ROW] = newRow;
		stats[COL] = newCol;
		cellSet = true;
	}
	
	return cellSet;
}


bool PlayerClass:: SetDir(GameSpace::DirType newDir)

{
	bool dirChange = false; 
	
	if(newDir >= GameSpace:: NORTH && newDir <= GameSpace:: WEST)
	{
		dir = newDir;
		dirChange = true;
	}
	
	return dirChange;
}


int PlayerClass:: Fortify(int boost)

{
	if(IsActive() && boost > 0)
	{
		stats[DEFENSE] += boost; 
	}

	return stats[DEFENSE];
}


int PlayerClass:: Expose(int decline)

{
	if(IsActive() && decline > 0)
	{
		if(stats[DEFENSE] - decline > 0)
		{
			stats[DEFENSE] -= decline;
		}
		else
		{
			stats[DEFENSE] = 0;
		}
	}
	return stats[DEFENSE];
}


int PlayerClass:: WillPowerAdj(int adjustment)

{
	if(IsActive())
	{
		stats[WILLPOWER] += adjustment;
		
		if(stats[WILLPOWER] > MAX_WILLPOWER)
		{
			stats[WILLPOWER] = MAX_WILLPOWER;
		}
		else if(stats[WILLPOWER] < MIN_WILLPOWER)
		{
			stats[WILLPOWER] = MIN_WILLPOWER;
		}
	}
	if(stats[WILLPOWER] <= 0)
	{
		MakeDead();
	}
	
	return stats[WILLPOWER];
}

bool PlayerClass:: CriticalWound()

{	
	int roll;
	int wound;
	
	if(IsActive())
	{
		if(Health() - CRIT_WOUND_AMOUNT > 0 && WillPower() - 1 > 0)
		{
			if(WillPower() >= 2)
			{
				roll = RollDie(GameSpace::WOUND, DEFAULT_CRIT_DIE, DEFAULT_CRIT_FACE);
				
				if(WillPower() > MAX_WILLPOWER)
				{
					stats[WILLPOWER] = MAX_WILLPOWER;
				}

				wound = LookupWound(roll, WillPower());
				
				if(wound == -1)
				{
					WillPowerAdj(wound);
					Wounded(CRIT_WOUND_AMOUNT);
					SlowDown(floor(CurrentSpeed()/2) + (CurrentSpeed()%2));
				}
				else 
				{
					MakeDead();
				}
			}
			else
			{
				MakeDead();
			}
		}
		else
		{
			MakeDead();
		}
	}
	
	return IsAlive();
}


//*****OUTPUT*****


void PlayerClass::Write(ostream& out) const

{
	out << IsActive() << "#";
	out << Name() << "#";
	out << "(" << stats[ROW] << "," << stats[COL] << "," << GameSpace:: DIR_CHAR[dir] << ")" << "#"; 
	out << STATS[MAX_HEALTH] << "#";
	out << stats[CURR_HEALTH] << "#";
	out << stats[WILLPOWER] << "#";
	out << stats[POWER] << "#";
	out << STATS[MAX_SPEED] << "#";
	out << stats[CURR_SPEED] << "#";
	out << stats[MOMENTUM] << "#";
	out << STATS[PHYS_DAM_DICE] << "d" << STATS[PHYS_DAM_FACE] << "#";
	out << stats[DEFENSE] << endl;
}


//*****OVERLOADED OPERATORS*****


PlayerClass& PlayerClass::operator=(const PlayerClass& player)
{	
	if(this != &player)
	{
		*(const_cast<const int**>(&STATS)) = player.STATS;
		*(const_cast<string*>(&NAME)) = player.Name();
		
		Copy(player);
	}
	return *this;
}


bool PlayerClass:: operator==(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) == GameSpace::Ucase(p.Name()));
}


bool PlayerClass:: operator!=(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) != GameSpace:: Ucase(p.Name()));
}


bool PlayerClass:: operator<(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) < GameSpace:: Ucase(p.Name()));
}


bool PlayerClass:: operator>(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) > GameSpace:: Ucase(p.Name()));
}


bool PlayerClass:: operator<=(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) <= GameSpace:: Ucase(p.Name()));
}


bool PlayerClass:: operator>=(const PlayerClass& p) const

{
	return(GameSpace:: Ucase(Name()) >= GameSpace:: Ucase(p.Name()));
}


//*****HELPER FUNCTIONS*****


string PlayerClass::ValidateName(string sName) const

{
	if(sName.length() > 1)
	{
		sName = GameSpace:: TrimStr(sName);
		if(sName.length() <= 1)
		{
			throw GameSpace:: INVALID_NAME;
		}
	}
	else
	{
		throw GameSpace:: INVALID_NAME;
	}
	
	if(sName.length() > 10)
	{
		sName.resize(10);
	}
		
	return sName;
}


void PlayerClass::Copy(const PlayerClass& player)

{
	active = player.IsActive();
	dir = player.Dir();
		
	for(int i = 0; i < END_STAT_TYPE; ++i)
	{
		stats[i] = player.stats[i];
	}
}


bool PlayerClass::MoveUnits(int units) //possibly better implementation would be to return a number? That way could know why exactly the move had failed

{
	bool moved = false;
	Board* myBd = Board::GetBd();

	if(IsActive() && myBd->MoveForward(this, units))
	{
		moved = true;
	}

	return moved;
}


int PlayerClass:: RollDie(GameSpace:: RollType what, int numDie, int numFace) const

{
	int roll = 0;
	
	roll = Dice::Roll(Name(), what, numDie, numFace);
	
	if(roll > (numFace * numDie) || roll < numDie)
	{
		throw GameSpace:: INVALID_ROLL;
	}
	
	return roll;
}


int PlayerClass::LookupImpact(int roll, int power) const

{
	return IMPACT_TABLE[roll][power];
}


int PlayerClass::LookupWound(int roll, int wPower) const

{
	return CRITICAL_WOUND_TABLE[roll][wPower];
}


//*****TOP-LEVEL FUNCTIONS*****


ostream& operator<<(ostream& out, const PlayerClass* p)

{
	if(p)
	{
		p->Write(out);
	}
	
	return out;
}
