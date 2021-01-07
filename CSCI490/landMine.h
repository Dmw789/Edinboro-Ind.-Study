//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// LANDMINE CLASS
//
// Narrative: A child of the Cell class that handles all behaviour regarding the holding of and location of players during the game.
// As a child of the cell class, this counts as as "TRAP" during the game that will activate a special effect upon a player entering 
// the cell. This particular trap will trigger a damage penalty upon entry unless already triggered.
//
// Special Notes:
//

#ifndef LANDMINE_H
#define LANDMINE_H

#include "cell.h"
using namespace std;

class LandMine : public Cell
{
	public: 
	
	//*****PUBLIC METHODS*****
		
	//*****CONSTRUCTORS/DESTRUCTORS/HELPERS*****
		
		LandMine(TerrainType terrain,  int row, int col, int wound);
		//Narrative: The only constructor for the LandMine class, passed in is the amount of damage taken upon
		//entering the cell as well as the coordinates.
		//
		//Pre-condition: none
		//
		//Post-condition: A new instance of a LandMine is created
		//
	
	
	//*****OBSERVERS*****
		
		virtual void Display(ostream& out) const;
		//Narrative: Displays all information regarding the coordinates and occupants of the cell.
		//
		//Pre-condition: none
		//
		//Post-condition: Cell info output
		//
		
		
	//*****TRANSFORMERS*****
	
		virtual bool EnterCell(PlayerClass* player);
		//Narrative: Adds a pointer to the player class to the occupancy of the cell. Will only enter if they meet
		//the necessary momentum requirement.
		//
		//Pre-condition: none
		//
		//Post-condition: A player is added to the occupancy vector
		//
		
		
	private:
	
	//*****PRIVATE METHODS*****
		
	//*****CONSTRUCTORS/DESTRUCTORS/HELPERS*****
	
		LandMine();
		//Narrative: The default constructor for the LandMine class. Made private so as to make it inaccessible.
		//
		//Pre-condition: Should not be able to be called at any point.
		//
		//Post-condition: Error is thrown
		//
		
		bool Trigger(PlayerClass* player);
		//Narrative: The effect of the LandMine class is triggered upon entry of a player unless the effect has already
		//been triggered.
		//
		//Pre-condition: none
		//
		//Post-condition: The player who entered the cell has their health decreased by the amount set upon creation.
		//
		

	//*****PRIVATE VARIABLES*****
		bool triggered;
		int woundAmt;
};

#endif
