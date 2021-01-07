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


#include "landMine.h"

using namespace std;


//*****CONSTRUCTORS AND DESTRUCTORS*****

LandMine:: LandMine() : Cell(Cell::CLEAR,0,0)

{
	throw GameSpace:: INVALID_MISC;
}

LandMine:: LandMine(TerrainType terrain,  int row, int col, int wound) : Cell(terrain, row, col),
																		 woundAmt(wound)				   
{

}


//*****OBSERVERS*****


void LandMine:: Display(ostream& out) const

{
	//Add anything else for display?
	Cell::Display(out);
}


//*****TRANSFORMERS*****


bool LandMine:: EnterCell(PlayerClass* player)

{
	if(!triggered && player)
	{
		Trigger(player);
	}
	return Cell::EnterCell(player);
}

bool LandMine:: Trigger(PlayerClass* player)
{
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}
	
	return player->Wounded(woundAmt);
}

