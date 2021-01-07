//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// GAME MASTER
//
// Narrative: This file serves as the ultimate controller for what happens during the runtime of the program. All board allocation, player prompts, and various event triggers
// are first intiated here inside of a while loop that will repeat until the end of game state is triggered. Once the end of game state is achieved, the winner of the game
// is determined (either human-controlled players or AI ones), and the program ends.
//
// GAME END STATE: Currently, the end state of the game is determined when all human players that are active run through the entirety of the player list and find whether there are more
// enemies or not. If enemies are still found, then the game continues. The reason for this implementation was because we do not care if the AI Bug players still have enemies left on the board
// after all humans have been defeated, since they can be enemies of AI-controlled bug types. Considering that only bugs would be left to fight eachother, this would both further extend the playtime
// of the game needlessly, and can only result in one endstate, which is that the player loses regardless of which bug wins.
//
// Special Notes: Any further implementation of the gameMaster relies heavily on what can be considered appropriate for it to control. If it is implementation that has to do with
// previously constructed classes, it should be created in such a way to fit in those classes first, and controlled here second, not the other way around. 
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
	bool won = false;
	vector<PlayerClass*> players;
	vector<PlayerClass*> bugs;
	vector<PlayerClass*>:: iterator iter;
	Human* e;
	
	bugs = Board::CreateBoard(4,5);
	Board* gameBd = Board::GetBd();
	gameOver = Interface::StartMenu();
	if(!gameOver)
	{
		bugs = Interface::SetDifficulty();
		players = Interface::CreatePlayers();
	
		players.insert(players.end(), bugs.begin(), bugs.end());
	}
	
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
			gameOver = Interface::IsGameOver(players);
		}

	}
	
	for(iter = players.begin(); iter != players.end(); ++ iter)
	{
		e = dynamic_cast<Human*>(*iter);
		
		if(e && e->IsActive())
		{
			won = true;
		}
	}
	
	for(iter = players.begin(); iter != players.end(); ++ iter)
	{
		delete (*iter);
	}
	
	
	if(won)
	{
		cout << endl << endl << "Congratulations!!! The humans have won!" << endl << endl; 
	}
	else
	{
		cout << endl << endl << "GAMEOVER" << endl;
		cout << endl << endl << "Oh no!!! The bugs have taken over!" << endl << endl;
	}
	
	Board::DeleteBd();
	
	return 0;
};