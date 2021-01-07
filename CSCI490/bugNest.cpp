//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// CELL CLASS
//
// Narrative:
//
// Special Notes:
//


#include "bugNest.h"

using namespace std;


//*****CONSTRUCTORS AND DESTRUCTORS*****

BugNest:: BugNest() : Cell(Cell::CLEAR,0,0)

{
	throw GameSpace:: INVALID_MISC;
}

BugNest:: BugNest(TerrainType terrain,  int row, int col, vector<PlayerClass*> bugs) : Cell(terrain, row, col),
																					   bugVec(bugs)
{
	
}


//*****OBSERVERS*****


void BugNest:: Display(ostream& out) const

{
	//Add anything else for display?
	Cell::Display(out);
}


//*****TRANSFORMERS*****


bool BugNest:: EnterCell(PlayerClass* player)

{
	if(!triggered && player)
	{
		Trigger(player);
	}
	return Cell::EnterCell(player);
}

bool BugNest:: Trigger(PlayerClass* player)
{
	
	vector<PlayerClass*>:: const_iterator iter;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}
	
	
	for(iter = bugVec.begin(); iter != bugVec.end(); ++iter)
	{
		Cell::EnterCell(*iter);
	}	
	
	//NEEDED -- BUGS ATTACK PLAYER WHEN THEY ARE SPAWNED IN --
	
	return true;
}