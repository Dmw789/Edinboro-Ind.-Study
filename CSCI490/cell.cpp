//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// CELL CLASS
//
// Narrative: The Cell class handles all behaviour regarding the holding of and location of players during the game. 
// The parent of all other cell types to be used; this counts as the "CLEAR" cell which doesn't have any special effects
// triggered upon entry.
//
// Special Notes:
//
//

#include "cell.h"

using namespace std;


//*****CONSTRUCTORS AND DESTRUCTORS*****


Cell::Cell()

{
	throw GameSpace:: INVALID_MISC;
}


Cell::Cell(TerrainType inTerrain, int inRow, int inCol) : terrain(inTerrain),
														  row(inRow),
														  col(inCol)
{
	
}


Cell::Cell(const Cell& newcell)

{
	throw GameSpace:: INVALID_MISC;
}


Cell::~Cell()

{
	vector<PlayerClass*>:: const_iterator iter;

	for(iter = occupants.begin(); iter != occupants.end(); ++iter)
	{
		delete (*iter);
	}
	occupants.clear();
}


//*****OBSERVERS*****


vector<PlayerClass*> Cell:: Occupants() const

{
	return occupants;
}


vector<PlayerClass*> Cell:: Enemies(const PlayerClass* player) const

{
	vector<PlayerClass*> v_ret;
	vector<PlayerClass*>:: const_iterator iter;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}


	for(iter = occupants.begin(); iter != occupants.end(); ++iter)
	{
		if(player->IsMyEnemy(*iter) && (*iter)->IsActive())
		{
			v_ret.push_back(*iter);
		}
	}	

	return v_ret;
}


vector<PlayerClass*> Cell:: Friends(const PlayerClass* player) const

{		
	vector<PlayerClass*> v_ret;
	vector<PlayerClass*>:: const_iterator iter;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}	
	
	for(iter = occupants.begin(); iter != occupants.end(); ++iter)
	{
		if(!player->IsMyEnemy(*iter) && player != (*iter) && (*iter)->IsActive())
		{
			v_ret.push_back(*iter);
		}
	}
	
	return v_ret;
}


int Cell:: EnterCost() const

{
	int cost = 0;
	
	switch(terrain)
	{
		case CLEAR: 
				cost = 1;
				break;
		case MOUNTAIN: 
				cost = 99;
				break;
		case ROCKY: 
				cost = 2;
				break;
		case SWAMP:
				cost = 2;
				break;
	}
	
	return cost;
}


bool Cell:: InCell(PlayerClass* player) const

{
	bool found = false;
	vector<PlayerClass*>:: const_iterator iter;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}
	
	for(iter = occupants.begin(); found == false && iter != occupants.end(); ++iter)
	{
		if(*player == **iter)
		{
			found = true;
		}
	}
	
	return found;
}


int Cell:: Row() const

{
	return row;
}


int Cell:: Col() const

{
	return col;
}


char Cell:: Terrain() const

{
	char t = 'C';
	switch(terrain)
	{
		case CLEAR: 
				t = 'C';
				break;
		case MOUNTAIN: 
				t = 'M';
				break;
		case ROCKY: 
				t = 'R';
				break;
		case SWAMP:
				t = 'S';
				break;
	}
	
	return t;
}


bool Cell:: IsClear() const

{
	return(Terrain() == 'C');
}


bool Cell:: IsMtn() const

{
	return(Terrain() == 'M');
}


bool Cell:: IsRocky() const

{
	return(Terrain() == 'R');
}


bool Cell:: IsSwamp() const

{
	return(Terrain() == 'S');
}


void Cell:: Display(ostream& out) const

{
	bool first = true;
	vector<PlayerClass*>:: const_iterator iter;
	
	cout << "(" << Row() << "," << Col() << ")";
	
	for(iter = occupants.begin(); iter != occupants.end(); ++iter)
	{
		if(!first)
		{
			cout << ",";
		}
		else
		{
			first = false;
		}
		cout << (*iter)->Name();
	}
	
	cout << "[" << Terrain() << "]";
	
	return;
}


bool Cell:: EnterCell(PlayerClass* player)

{
	bool entered = false;
	
	vector<PlayerClass*>:: const_iterator iter;
	
	if(player)
	{
		if(!InCell(player) && (player->Momentum() - EnterCost() >= 0))
		{
			if(player->Row() == -1 && player->Col() == -1)
			{
				switch(Terrain())
				{
					case 'C': occupants.push_back(player);
							  entered = true;
							  break;
					
					case 'M': break;
					
					case 'R': occupants.push_back(player);
							  entered = true;
							  break; 
								
					case 'S': occupants.push_back(player);
							  entered = true;
							  break;
				}
			}
			else
			{
				switch(Terrain())
				{
					case 'C': player->UseMomentum(EnterCost());
							  occupants.push_back(player);
							  entered = true;
							  break;
					
					case 'M': break;
					
					case 'R': //player->SlowDown((player->CurrentSpeed())/2); **ASK ABOUT -- LISTED IN GAME DOC**
							  player->UseMomentum(EnterCost());
							  occupants.push_back(player);
							  entered = true;
							  break; 
								
					case 'S': //player->SlowDown((player->CurrentSpeed())/2);
							  player->UseMomentum(EnterCost()); 
							  occupants.push_back(player);
							  entered = true;
							  break;
				}
			}
		}
	}
	
	return entered;
}


bool Cell:: ExitCell(PlayerClass* player)

{
	bool found = false;
	bool exited = false;
	vector<PlayerClass*>:: iterator iter;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}
	
	if(InCell(player))
	{	
		for(iter = occupants.begin(); found == false && iter != occupants.end(); ++iter)
		{
			if(*player == **iter)
			{
				found = true;
				occupants.erase(iter);
				exited = true;
			}
		}
	}

	return exited;
}

Cell& Cell:: operator=(const Cell* cell)

{
	throw GameSpace:: INVALID_MISC;
}