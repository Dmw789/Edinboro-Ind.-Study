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


#include "sinkHole.h"

using namespace std;


//*****CONSTRUCTORS AND DESTRUCTORS*****

SinkHole:: SinkHole() : Cell(Cell::CLEAR,0,0)

{
	throw GameSpace:: INVALID_MISC;
}

SinkHole:: SinkHole(TerrainType terrain,  int row, int col, int reduce) : Cell(terrain, row, col),
																		  reduceAmt(reduce)				   
{

}


//*****OBSERVERS*****


void SinkHole:: Display(ostream& out) const

{
	//Add anything else for display?
	Cell::Display(out);
}


//*****TRANSFORMERS*****


bool SinkHole:: EnterCell(PlayerClass* player)

{
	if(!triggered && player)
	{
		Trigger(player);
	}
	return Cell::EnterCell(player);
}

bool SinkHole:: Trigger(PlayerClass* player)
{
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}


	return player->SlowDown(reduceAmt);
}

