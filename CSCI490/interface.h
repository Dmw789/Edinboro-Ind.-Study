//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// INTERFACE CLASS
//
// Narrative: A class designed to handle all output generated to propmt the player for all necessary information during the runtime of the game.
// This class also acts as a medium between the implementation of the player, combat, and board to the GameMaster for ease of use. All player control
// done by the players during runtime should be done inside of this class only.
//
// Special Notes: Currently has little documentation as interface is very subject to change soon
//


#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

class Interface
{
	public:
//*****PUBLIC METHODS*****
	  
	//*****TRANSFORMERS*****
		static bool StartMenu();
		
		static vector<PlayerClass*> SetDifficulty();

		static vector<PlayerClass*> CreatePlayers();
		
		static void BeginPlayerTurn(PlayerClass* p);
		
		static void BeginAITurn(PlayerClass* p);
		
		static bool IsGameOver(vector<PlayerClass*> allPlayers);
	  
 		static void DisplayBoardState(PlayerClass* p);
		
	private:
//*****PRIVATE METHODS*****
	//*****CONSTRUCTORS*****
		Interface(); //Default constructor, made private as not to be used
	
	//*****TRANSFORMERS*****
		static bool PlayerMove(PlayerClass* p);
		
		static void PlayerChangeDir(PlayerClass* p);
		
		static bool PlayerHeal(PlayerClass* p);
		
		static void PlayerCheckStats(PlayerClass* p);
};
	
#endif

