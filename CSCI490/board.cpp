//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// BOARD CLASS
//
// Narrative: A class designed to hold all cells and control all movement during the runtime of the program.
// At the beginning of using this class, you should call CreateBoard. Before the program ends, DeleteBd should be called.
//
// Special Notes: The board is a singleton class, being so the only way to access the board is via GetBd(). If a board is not created before GetBd() is called,
// then one will be created with the default dimensions.
//


//*****CHANGE TO A HEADER FILE ONCE ALL IS COMPLETED*****
#include "board.h" 
#include "gamespace.h"
#include "warrior.h"
#include "explorer.h"
#include "hornet.h"
#include "spider.h"
#include "killerAnt.h"
#include "barbarian.h"
#include "cell.h"
#include "bugNest.h"
#include "sinkHole.h"
#include "landMine.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


Board* Board::bd = NULL;
const int Board::DISPLAY_SIZE = 8;
const int Board::PRINT_SIZE = 11;


//*****CONSTRUCTORS AND DESTRUCTORS*****


Board::Board() : ROW_SIZE(0),
			     COL_SIZE(0)

{
	throw GameSpace:: INVALID_MISC;
}


Board::Board(int row, int col) : ROW_SIZE(row),
								 COL_SIZE(col)

{
	
}


Board:: ~Board()

{
	for(int i = 0; i < COL_SIZE; ++i)
	{
		for(int j = 0; j < ROW_SIZE; ++j)
		{
			delete boardCells.at(i).at(j);
		}
	}
	
	boardCells.clear();
}


vector<PlayerClass*> Board:: Occupants(PlayerClass* player) const

{
	bool found = false;
	vector<PlayerClass*> tempVec;
	
	for(int i = 0; i < COL_SIZE && found == false; ++i)
	{
		for(int j = 0; j < ROW_SIZE; ++j)
		{
			if(boardCells.at(i).at(j)->InCell(player))
			{
				tempVec = boardCells.at(i).at(j)->Occupants();
				found = true;
			}
		}
	}
	return tempVec;
}


vector<PlayerClass*> Board:: Enemies(PlayerClass* player) const

{
	//Search for occupants inside of the same cell as the player sent in
	//first find which cell the player is in if even at all, then call the enemies for that cell
	
	vector<PlayerClass*> tempVec;
	
	if(player)
	{
		
		tempVec = boardCells.at(player->Row()).at(player->Col())->Enemies(player);
	}

	return tempVec;
}


vector<PlayerClass*> Board:: Friends(PlayerClass* player) const

{
	//Search for occupants inside of the same cell as the player sent in
	//first find which cell the player is in if even at all, then call the friends function for that cell
	
	vector<PlayerClass*> tempVec;
	
	if(player)
	{
		tempVec = boardCells.at(player->Row()).at(player->Col())->Friends(player);
	}

	return tempVec;
}


int Board:: MoveCost(PlayerClass* player, int units) const

{
	//calculate the cost of moving however many units in the direction the player is facing
	//do a whole bunch of moveForwards if the player is facing in the correct direction(?)
	//and if terrain allows it
	
	int num = 0;
	int row = 0;
	int col = 0;
	int rowAdd = 0;
	int colAdd = 0;
	
	if(player)
	{
		row = player->Row();
		col = player->Col();
		
		for(int i = 0; i < units; ++i)
		{	

			switch(player->Dir())
			{
				case NORTH: rowAdd = -1;
							break;
				case SOUTH: rowAdd = 1;
							break;
				case EAST: colAdd = 1;		
							break;		
				case WEST: colAdd = -1;
							break;					
			}
			
			row += rowAdd;
			col += colAdd;

			if(row < 0)
			{
				row = ROW_SIZE;
			}
			else if(row > ROW_SIZE)
			{
				row = 0;
			}
			
			if(col < 0)
			{
				col = COL_SIZE;
			}
			else if(col > COL_SIZE)
			{
				col = 0;
			}
			
			num += boardCells.at(row).at(col)->EnterCost();
			rowAdd = 0;
			colAdd = 0;
		}
	}
	
	return num;
}


void Board:: Display(ostream& out) const

{
	//rotate through board and print all cells per row
	
	out << setfill('*') << setw(DISPLAY_SIZE*(COL_SIZE+1)) << "*" << endl;
	
	for(int i = 0; i <= ROW_SIZE; ++i)
	{
		for(int j = 0; j <= COL_SIZE; ++j)
		{
			boardCells.at(i).at(j)->Display(out);
		}
		out << endl << setfill('*') << setw(DISPLAY_SIZE*(COL_SIZE+1)) << "*" << endl;
	}
}


int Board:: NumRow() const

{
	return ROW_SIZE;
}

		
int Board:: NumCol() const

{
	return COL_SIZE;
}

void Board:: PrintBoard(ostream& out, PlayerClass* player) const

{
	char terr = 'C';
	vector<PlayerClass*> friendVec;
	vector<PlayerClass*> enemyVec;
	
	if(!player)
	{
		throw GameSpace::INVALID_PTYPE;
	}
	
	out << setfill('*') << setw(PRINT_SIZE*(COL_SIZE+1) + 1) << "*" << endl; //****** SET THE SET FILL AMOUNT TO A CONSTANT!!*****
	
	for(int i = 0; i <= ROW_SIZE; ++i)
	{
		out << "*";
		for(int j = 0; j <= COL_SIZE; ++j)
		{
			out << "[";
			
			if(boardCells.at(i).at(j)->InCell(player))
			{
				switch(player->Dir())
				{
					case(NORTH): out << "^";
								break;
					case(EAST): out << ">";
								break;
					case(SOUTH): out << "v";
								break;
					case(WEST): out << "<";
								break;
				}
			}
			else
			{
				out << " ";
			}
			
			out << boardCells.at(i).at(j)->Terrain();

			friendVec = boardCells.at(i).at(j)->Friends(player);
			out << " F" << friendVec.size();

			enemyVec = boardCells.at(i).at(j)->Enemies(player);
			out << " E" << enemyVec.size();
			
			out << "]*";
		}
		out << endl << setfill('*') << setw(PRINT_SIZE*(COL_SIZE+1) + 1) << "*" << endl;
	}
}



//*****TRANSFORMERS*****


Board* Board::GetBd()

{
	if(!bd)
	{
		bd = new Board(GameSpace::NUMROWS-1, GameSpace::NUMCOLS-1);
	}
	return bd;
}


vector<PlayerClass*> Board:: CreateBoard(int row, int col)

{	
	if(!bd)
	{
		bd = new Board(row-1, col-1);
	}

	return bd->LoadBoard();
}


void Board:: DeleteBd()

{
	bd = NULL;
}


bool Board:: MoveForward(PlayerClass* player, int units)
{
	bool moveSuccess = false;
	int rowAdd = 0;
	int colAdd = 0;
	int rowGoTo = 0;
	int colGoTo = 0;
	
	if(player)
	{
		switch(player->Dir())
		{
			case NORTH: rowAdd = -1 * units;
						break;
			case SOUTH: rowAdd = 1 * units ;
						break;
			case EAST: colAdd = 1 * units;		
						break;
			case WEST: colAdd = -1 * units;
						break;			
		}
		
		rowGoTo = player->Row() + rowAdd;
		colGoTo = player->Col() + colAdd;

		if(rowGoTo < 0)
		{
			rowGoTo = ROW_SIZE;
		}
		else if(rowGoTo > ROW_SIZE)
		{
			rowGoTo = 0;
		}
		
		if(colGoTo < 0)
		{
			colGoTo = COL_SIZE;
		}
		else if(colGoTo > COL_SIZE)
		{
			colGoTo = 0;
		}
		
		if(player->Momentum() - boardCells.at(rowGoTo).at(colGoTo)->EnterCost() >= 0) //can possibly shorten to make more efficient
		{
			moveSuccess = true;
			
			boardCells.at(player->Row()).at(player->Col())->ExitCell(player);
			
			boardCells.at(rowGoTo).at(colGoTo)->EnterCell(player);
			player->SetCell(rowGoTo, colGoTo);
		}
	}
	
	return moveSuccess;
}


bool Board:: PlacePlayer(PlayerClass* player, int row, int col)

{
	bool placed = false;
	
	if(player)
	{
		if(row <= ROW_SIZE && col <= COL_SIZE && player->Row() == -1 && player->Col() == -1)
		{
			boardCells[row][col]->EnterCell(player);
			placed = player->SetCell(row, col);
		}

	}
	return placed;
}


vector<PlayerClass*> Board:: LoadBoard()

{
	ifstream fin;
	vector<PlayerClass*> nest;
	vector<PlayerClass*> nestCollect;
	PlayerClass* bugType;
	char terr, type, bType;
	int num;
	Cell:: TerrainType terrain;
	
	fin.open("boardTest.txt");
	
	if(bd)
	{
		for(int i = 0; i <= ROW_SIZE; ++i) //for the max number of rows to be used
		{
			vector<Cell*> tempVec; //create new vector, this will be the full row
			Cell* c;
			for(int j = 0; j <= COL_SIZE; ++j)
			{
					
				fin >> terr;
				
				switch(terr)
				{
					case 'C' : terrain = Cell:: CLEAR;
							   break;

					case 'M' : terrain = Cell:: MOUNTAIN;
							   break;		
				
					case 'R' : terrain = Cell:: ROCKY;
							   break;		

					case 'S' : terrain = Cell:: SWAMP;
							   break;		
				}
				
				fin >> type;
				
				switch(type)
				{
					
					case 'N' : c = new Cell(terrain, i, j);
							   break;
					
					case 'B' : fin >> num;
							   fin >> bType;
							   switch(bType) //ADD ANOTHER FIN FOR BTYPE -- TEST THIS --
							   {
									case 'H' : bugType = new Hornet("HORNET");
											   break;
									
									case 'K' : bugType = new Spider("KILLERANT");
											   break;
								
									case 'S' : bugType = new Spider("SPIDER");
											   break;
							   }
			
								for(int m = 0; m < num; ++m)
								{
									nest.push_back(bugType);
								}
							   nestCollect.insert(nestCollect.end(), nest.begin(), nest.end());
							   c = new BugNest(terrain, i, j, nest);
							   break;
							   
					case 'L' : fin >> num;
							   c = new LandMine(terrain, i, j, num);
							   break;
					
					case 'S' : fin >> num;
							   c = new SinkHole(terrain, i, j, num);
							   break;
				}
				tempVec.push_back(c);
			}
			
			boardCells.push_back(tempVec);
		}
	}
	
	fin.close();
	
	return nestCollect;
}
