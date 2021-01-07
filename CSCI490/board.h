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


#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <iostream>
#include <vector>

using namespace std;

class Board
{
	
	public:
	
//*****PUBLIC METHODS*****
		
	//*****CONSTRUCTORS & DESTRUCTORS*****
		
		~Board();
		//Narrative: The default destructor for the board class. Will deallocate all pointers used to comprise the board.
		//
		//Pre-condition: none
		//
		//Post-condition: board is deallocated.
		//
		
	//*****OBSERVERS*****
		
		vector<PlayerClass*> Occupants(PlayerClass* player) const;
		//Narrative: Return a list of occupants across the board.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: Vector returned
		//
		
		vector<PlayerClass*> Enemies(PlayerClass* player) const;
		//Narrative: Return a list of players across the board that are considered enemies by the player passed in.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: Vector returned
		//
	
		vector<PlayerClass*> Friends(PlayerClass* player) const;
		//Narrative: Return a list of players across the board that are considered friendly by the player passed in.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: Vector returned
		//
	
		int MoveCost(PlayerClass* player, int units) const;
		//Narrative: Returns the cost for a player to move to a cell based on the number of units passed in. The movement cost will only 
		//be calculated assuming the player walks along a straight path to get there.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: An integer denoting the cost is returned.
		//		
	
		void Display(ostream& out) const;
		//Narrative: Rotates through the board and ouputs a simple view of all cells per row.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition:
		//
		
		void PrintBoard(ostream& out, PlayerClass* player) const;
		//Narrative: Prints the board based on whatever output is passed in. Shows a full breakdown of all cells as well as all the player
		//passed in, where that player is on the board, and which cells have friends and which have enemies.
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: The board's cells are output based on what ostream was passed in.
		//
		
		int NumRow() const;
		//Narrative: Returns the number of rows in the board
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: Number returned
		//
		
		
		int NumCol() const;
		//Narrative: Returns the number of rows in the board
		//
		//Pre-condition: Board should be already created via GetBd()
		//
		//Post-condition: Number returned
		//
	
	//*****TRANSFORMERS*****
	
		static Board* GetBd();
		//Narrative: The only way to get a copy of the board during runtime of the program. Returns a pointer to the board's
		//vector of cells. If none exists, it will create one based on the default dimensions.
		//
		//Pre-condition: none
		//
		//Post-condition: If no board currently exists, a board is created and a pointer to that board is returned, otherwise just
		//the pointer is returned.
		//
		
		static vector<PlayerClass*> CreateBoard(int row = GameSpace::NUMROWS, int col = GameSpace::NUMCOLS);
		//Narrative: The only way to create a board with custom dimensions. Will return a vector of all players currently
		//occupying the game board.
		//
		//Pre-condition: none
		//
		//Post-condition: As long as no board has been created, a board is created and a vector of all players in the board is returned.
		//
		
		static void DeleteBd();
		//Narrative: The board is deallocated
		//
		//Pre-condition: The board should have already been created or else nothing will happen
		//
		//Post-condition: The board has been deallocated and is ready to be created again.
		//
	
		bool MoveForward(PlayerClass* player, int units);
		//Narrative: The player passed in is moved forward in the direction they are facing as long as the cost doesn't exceed their 
		//momentum. Will move forward x amount of cells where x is the units passed in however they will only pay the cost of the cell
		//x amount of distance away.
		//
		//Pre-condition: none 
		//
		//Post-condition: Player exits their old cell/enters a new one if they have enough momentum to pay the cost, otherwise
		//they stay where they are.
		//
		
		bool PlacePlayer(PlayerClass* player, int row, int col);
		//Narrative: If the player is currently at cell (-1, -1) and the cell that they are trying to be placed in is not a mountain
		//then they are added to the occupancy of the cell.
		//
		//Pre-condition: Player passed in should not be null and the row/col passed in should be within the dimenions of the board.
		//
		//Post-condition: If all conditions are met, the player is added to the occupancy of the cell at the given coordinate.
		//
		
		
	private:
	
//*****PRIVATE METHODS*****
	
	//*****CONSTRUCTORS*****
	
		Board();
		//Narrative: The default constructor for the Board class. Made private as it is never to be used.
		//
		//Pre-condition: None
		//
		//Post-condition: Exception thrown.
		//
		
		Board(int row, int col);
		//Narrative: The parameterized constructor for the board class. If no values are passed for the parameters
		//the default will be used instead. Only ever created from GetBd() or CreateBoard().
		//
		//Pre-condition: none
		//
		//Post-condition: A new instance of the board is used and ready to be shared during the runtime of the program.
		//
		
		Board(const Board& b);
		//Narrative: Copy constructor for the cell class. Made private as it's not to be used/accessed.
		//
		//Pre-condition: none
		//
		//Post-condition: throw triggered.
		//

		Board& operator=(const Board* b);
		//Narrative: Assignment operator for the cell class. Made private as it's not to be used/accessed.
		//
		//Pre-condition: none
		//
		//Post-condition: throw triggered.
		//
		
	
	//*****TRANSFORMERS*****
	
		vector<PlayerClass*> LoadBoard();
		//Narrative: Loads a board from boardTest.txt. Full breakdown of the format this file needs to be in is located
		//in the GameDoc. Upon loading the board,
		//
		//Pre-condition: Should only ever be called upon construction of the board at the beginning of the program.
		//
		//Post-condition: The board's 2d vector boardCells is populated with cells of varying types.
		//
	
//*****PRIVATE VARIABLES*****
	
	static Board* bd; //Singleton pointer setup
	const int ROW_SIZE;
	const int COL_SIZE;
	static const int DISPLAY_SIZE;
	static const int PRINT_SIZE;

	vector<vector <Cell::Cell*> > boardCells;
};

#endif