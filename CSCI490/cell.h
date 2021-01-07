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


#ifndef CELL_H
#define CELL_H

#include <iostream>
#include "player.h"

using namespace std;

class Cell
{
	public:
	
	//*****PUBLIC VARIABLES*****
		enum TerrainType{CLEAR, MOUNTAIN, ROCKY, SWAMP};
		
	
	//*****PUBLIC METHODS*****
				
	//*****CONSTRUCTORS & DESTRUCTORS*****
		Cell(TerrainType terrain, int row, int col);
		//Narrative: The constructor to be used for the Cell Class. This creates a "clear" cell that doesn't have any special effect
		//triggered upon entry minus the potential terrain movement cost. 
		//
		//Pre-condition: terrainType, an int for row and an int for col are passed in appropriately.
		//
		//Post-condition: A new instance of a clear cell is created.
		//
				
		virtual ~Cell();
		//Narrative: The default constructor for the Cell class. Virtual for all possible children
		//that might inherit the Cell class.
		//
		//Pre-condition: none 
		//
		//Post-condition: An instance of the cell class is deallocated.
		//
			
	//*****OBSERVERS*****
		vector<PlayerClass*> Occupants() const;
		//Narrative: Returns a list of all players currently inside of the cell. This list is in no particular order.
		//
		//Pre-condition: none
		//
		//Post-condition: Vector returned, filled with pointers to player instances.
		//
		
		vector<PlayerClass*> Enemies(const PlayerClass* player) const;
		//Narrative: Returns a list of all players currently inside of the cell that are considered enemies by the player passed in.
		//This list is in no particular order.
		//
		//Pre-condition: none
		//
		//Post-condition: Vector returned, filled with pointers to player instances that are of an enemy type.
		//
		
		vector<PlayerClass*> Friends(const PlayerClass* player) const;
		//Narrative: Returns a list of all players currently inside of the cell that are considered friendly by the player passed in.
		//This list is in no particular order.
		//
		//Pre-condition: none
		//
		//Post-condition: Vector returned, filled with pointers to player instances that are not of an enemy type.
		//
		
		int EnterCost() const;
		//Narrative: Returns the cost to enter this cell. Cost is calculated via the terrain that was passed in during construction.
		//
		//Pre-condition: none
		//
		//Post-condition: Cost to enter returned.
		//
		
		bool InCell(PlayerClass* player) const;
		//Narrative: Returns whether or not the player is listed in the occupants for this cell.
		//
		//Pre-condition: none
		//
		//Post-condition: Returns true if player is found, else false is returned.
		//
		
		int Row() const;
		//Narrative: A number representing the row is returned.
		//
		//Pre-condition: none
		//
		//Post-condition: Row returned.
		//
		
		int Col() const;
		//Narrative: A number representing the col is returned.
		//
		//Pre-condition: none
		//
		//Post-condition: Col returned.
		//
		
		char Terrain() const;
		//Narrative: A single character representing the type of terrain is returned.
		//
		//Pre-condition: none
		//
		//Post-condition: Terrain returned.
		//
		
		bool IsClear() const;
		//Narrative: Returns whether or not the terrain is of type clear.
		//
		//Pre-condition: none
		//
		//Post-condition: True returned if cell is of type clear, otherwise false is returned.
		//
		
		bool IsMtn() const;
		//Narrative: Returns whether or not the terrain is of type mountain.
		//
		//Pre-condition: none
		//
		//Post-condition: True returned if cell is of type mountain, otherwise false is returned.
		//
		
		bool IsRocky() const;
		//Narrative: Returns whether or not the terrain is of type rocky.
		//
		//Pre-condition: none
		//
		//Post-condition: True returned if cell is of type rocky, otherwise false is returned.
		//
		
		bool IsSwamp() const;
		//Narrative: Returns whether or not the terrain is of type swamp.
		//
		//Pre-condition: none
		//
		//Post-condition: True returned if cell is of type swamp, otherwise false is returned.
		//
		
		virtual void Display(ostream& out) const;
		//Narrative: Prints all important information for the cell.
		//
		//Pre-condition: none
		//
		//Post-condition: All information output to whatever is passed in.
		//
			
		
	//*****TRANSFORMERS*****
		virtual bool EnterCell(PlayerClass* player);
		//Narrative: Primary way to make a player enter the cell. Left virtual for potential
		//child classes to trigger events/change variables upon entry.
		//
		//Pre-condition: none
		//
		//Post-condition: If player passed in is not null and is able to enter the cell, that player 
		//pointer is added to the occupants list and then true is returned, else false is returned.
		//
		
		bool ExitCell(PlayerClass* player);
		//Narrative: Primary way to make a player exit the cell. Left virtual for potential
		//child classes to trigger events/change variables upon exit.
		//
		//Pre-condition: none
		//
		//Post-condition: If player passed in is not null and is currently in the occupants list, that player 
		//pointer is removed from the occupants list and then true is returned, else false is returned.
		//
		
	private: 
	
	//*****PRIVATE METHODS*****
	
	
	//*****CONSTRUCTORS & DESTRUCTORS*****
		Cell();	
		//Narrative: Default constructor for the cell class. Made private as it's not to be used/accessed.
		//
		//Pre-condition: none
		//
		//Post-condition: throw triggered.
		//
		
		
		Cell(const Cell& newcell);
		//Narrative: Copy constructor for the cell class. Made private as it's not to be used/accessed.
		//
		//Pre-condition: none
		//
		//Post-condition: throw triggered.
		//

	
		Cell& operator=(const Cell* cell);
		//Narrative: Assignment operator for the cell class. Made private as it's not to be used/accessed.
		//
		//Pre-condition: none
		//
		//Post-condition: throw triggered.
		//
		
	//*****PRIVATE VARIABLES*****
		int row;
		int col;
		TerrainType terrain;
		vector<PlayerClass*> occupants;
	
};

#endif