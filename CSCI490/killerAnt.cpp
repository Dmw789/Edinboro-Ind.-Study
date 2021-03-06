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
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes: 
//
//


#include "killerAnt.h"
#include <typeinfo>
#include "combat.h"
#include "board.h"

using namespace std;

//ASSIGN STATIC CONSTS
const int KillerAnt::INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE] = {20, 7, 2, 2, 5, 10, -1, -1};
const int KillerAnt::INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE] = {20, 2, 6, 2};
const string KillerAnt:: TYPE_STR = "KILLERANT";
const int KillerAnt:: MOVE_AMOUNT = 4;

//*****METHODS*****

//*****CONSTRUCTORS*****


KillerAnt::KillerAnt(): Bug("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


KillerAnt::KillerAnt(string name): Bug(name, INIT_CONST_STATS, INIT_VAR_STATS)

{

}


//*****OBSERVERS*****

string KillerAnt::TypeStr() const

{
	return TYPE_STR;
}


bool KillerAnt::IsMyEnemyCheck(const PlayerClass* p) const
	
{
	return(p && (typeid(*p) != typeid(KillerAnt)));
}
	
	
void KillerAnt::Write(ostream& out) const

{
	out << TypeStr() << "#";
	Bug::Write(out);
}


//*****TRANSFORMERS*****

bool KillerAnt::Move()

{
	bool moved = false;
	bool wasSuccessful = false;
	int dirAmount = 0;
	Board* bd = Board::GetBd();	
	vector<PlayerClass*> enemies;
	vector<PlayerClass*>:: iterator iter;
	
	
	for(int i = 0; i <= CurrentSpeed() && Momentum() != 0; ++i)
	{
		wasSuccessful = MoveUnits(1);
		
		if(wasSuccessful && i == CurrentSpeed() && Momentum() == 0)
		{
			moved = true;
		}
		else if(!wasSuccessful && Momentum() > 0)
		{
			switch(Dir())
			{
				case(GameSpace::NORTH): SetDir(GameSpace::EAST);
							break;
				case(GameSpace::EAST): SetDir(GameSpace::SOUTH);
							break;
				case(GameSpace::SOUTH): SetDir(GameSpace::WEST);
							break;
				case(GameSpace::WEST): SetDir(GameSpace::NORTH);
							break;
			}
		}
		
		enemies = bd->Enemies(this);
		for(iter = enemies.begin(); iter != enemies.end(); ++iter)
		{
			Combat::SameCellCombat(this, *iter);
		}
	}
	
	return moved;
}















