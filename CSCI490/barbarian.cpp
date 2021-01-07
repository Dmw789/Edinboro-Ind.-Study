//
// Dylan Whitehead
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: A derived child class of Human. Assumes all methods and variables publicly from Human, and therefor from PlayerClass.
// One of the player types used throughout the game that is reusable and replicatable.
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes:
//
//


#include "barbarian.h"
#include <math.h> //used for ceil in Hit Damage

using namespace std;

//ASSIGN STATIC CONSTS
const int Barbarian::INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE] = {100, 11, 4, 4, 11, 10, -1, -1};
const int Barbarian::INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE] = {100, 4, 6, 4};
const string Barbarian:: TYPE_STR = "BARBARIAN";
const int Barbarian:: BARBARIAN_HEAL_AMOUNT = 5;

//*****METHODS*****

//*****CONSTRUCTORS*****


Barbarian::Barbarian(): Human("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Barbarian::Barbarian(string name): Human(name, INIT_CONST_STATS, INIT_VAR_STATS)

{

}


//*****OBSERVERS*****

string Barbarian::TypeStr() const

{
	return TYPE_STR;
}
	

int Barbarian:: HitDamage() const

{
	int damage = 0;
	
	if(IsActive())
	{
		damage = (Human::HitDamage() * (floor(WillPower()/2) + WillPower()%2));
	}
	
	return damage;
}


bool Barbarian:: IsMyEnemyCheck(const PlayerClass* p) const
	
{
	return(p && p != this);
}


bool Barbarian::Heal()

{
	bool healed = false;

	if(IsActive() && IsAlive())
	{
		ResetCurrentSpeed();
		Invigorate(BARBARIAN_HEAL_AMOUNT);
		healed = true;
	}

	return healed;
}
	
			
void Barbarian::Write(ostream& out) const

{
	out << TypeStr() << "#";
	Human::Write(out);
}


Barbarian* Barbarian:: Clone() const

{
	return new Barbarian(*this);
}