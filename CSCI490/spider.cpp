//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// SPIDER CLASS
// 
// Narrative: A derived child class of Bug. Assumes all methods and variables publicly from Bug, and therefor from PlayerClass.
// One of the player types used throughout the game that is reusable and replicatable.
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes: 
//
//


#include "spider.h"
#include "board.h"
#include "combat.h"
#include <typeinfo>

using namespace std;

//ASSIGN STATIC CONSTS
const int Spider::INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE] = {50, 8, 15, 15, 11, 7, -1, -1};
const int Spider::INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE] = {50, 15, 6, 2};
const string Spider:: TYPE_STR = "SPIDER";
const int Spider:: MOVE_AMOUNT = 4;


//*****METHODS*****

//*****CONSTRUCTORS*****


Spider::Spider(): Bug("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Spider::Spider(string name): Bug(name, INIT_CONST_STATS, INIT_VAR_STATS)

{

}


//*****OBSERVERS*****

string Spider::TypeStr() const

{
	return TYPE_STR;
}


bool Spider::IsMyEnemyCheck(const PlayerClass* p) const
	
{
	return(p && (typeid(*p) != typeid(Spider)));
}


void Spider::Write(ostream& out) const

{
	out << TypeStr() << "#";
	Bug::Write(out);
}


//*****TRANSFORMERS*****

bool Spider::Move()

{
	Board* gameBd = Board::GetBd();
	bool moved = false;
	bool wasSuccessful = false;
	bool moveDone = false;
	bool firstPass = true;
	vector<PlayerClass*> enemies;
	vector<PlayerClass*>:: iterator iter;
	
	for(int i = 0; i <= CurrentSpeed() && Momentum() != 0 && !moveDone; ++i)
	{
		if(Dir() == GameSpace::NORTH)
		{
			if(firstPass)
			{
				SetDir(GameSpace::EAST);
				firstPass = false;
				wasSuccessful = MoveUnits(1);
			}
			else
			{
				moveDone = true;
			}
		}
		else
		{
			switch(Dir())
			{
				case(GameSpace::EAST): SetDir(GameSpace::SOUTH);
							break;
				case(GameSpace::SOUTH): SetDir(GameSpace::WEST);
							break;
				case(GameSpace::WEST): SetDir(GameSpace::NORTH);
							break;
			}
		
			wasSuccessful = MoveUnits(1);
		}
		
		if(wasSuccessful && i == CurrentSpeed() && Momentum() == 0 || wasSuccessful && moveDone)
		{
			moved = true;
		}
		
		enemies = gameBd->Enemies(this);
		for(iter = enemies.begin(); iter != enemies.end(); ++iter)
		{
			Combat::SameCellCombat(this, *iter);
		}
	}
	
	return moved;
}

