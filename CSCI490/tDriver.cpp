//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// TEST DRIVER
//
// Narrative:
//
// Special Notes:
//

#include <iostream>
#include <string>
#include "hornet.h"
#include "killerAnt.h"
#include "spider.h"
#include "warrior.h"
#include "explorer.h"
#include "barbarian.h"
#include "cell.h"
#include "bugNest.h"
#include "board.h"
#include "combat.h"
#include "dice.h"
#include "interface.h"

using namespace std; 

int main()

{
	bool gameOver = false;
	vector<PlayerClass*> players;
	vector<PlayerClass*> bugs;
	vector<PlayerClass*>:: iterator iter;
	Human* e;
	
	bugs = Board::CreateBoard(4,5);
	Board* gameBd = Board::GetBd();
	gameOver = Interface::StartMenu();
	bugs = Interface::SetDifficulty();
	players = Interface::CreatePlayers();
	
	players.insert(players.end(), bugs.begin(), bugs.end());
	
	gameOver = Interface::IsGameOver(players);
	
	while(!gameOver)
	{
		for(iter = players.begin(); iter != players.end(); ++iter)
		{
			if((*iter)->IsActive())
			{
				e = dynamic_cast<Human*>(*iter);
				
				if(e)
				{
					Interface::DisplayBoardState(*iter);
					Interface::BeginPlayerTurn(*iter);
				}
				else
				{
					Interface::BeginAITurn(*iter);
				}
			}
		}
		
		gameOver = Interface::IsGameOver(players);
	}
	
	Board::DeleteBd();
	
	return 0;
};