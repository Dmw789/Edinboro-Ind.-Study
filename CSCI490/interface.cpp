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
// Special Notes:
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include "interface.h"

#include "board.h" 
#include "combat.h"
#include "gamespace.h"
#include "warrior.h"
#include "explorer.h"
#include "hornet.h"
#include "spider.h"
#include "killerAnt.h"
#include "barbarian.h"
#include "cell.h"

using namespace std;

//*****METHODS*****

//*****TRANSFORMERS*****

bool Interface:: StartMenu()

{
	bool gameOver = true;
	int choice;
	
	cout << endl;
	
	for(int i = 0; i < 10; ++i)
	{
		cout << setfill('*') << setw(49) << "*" << endl;
	}
	cout << "***** 1. START " << setfill('*') << setw(34) << " 2. EXIT *****";
	cout << endl << setfill('*') << setw(49) << "*" << endl;
	cout << endl;
	cin >> choice;
	cin.ignore();
	
	if(choice == 1)
	{
		gameOver = false;
	}
	
	return gameOver;
}


vector<PlayerClass*> Interface:: SetDifficulty()

{
	vector<PlayerClass*> players;
	PlayerClass* newPlayer;
	Board* bd = Board::GetBd();
	int numAnts = 0;
	int numHornets = 0;
	int numSpiders = 0;
	int randomRow = 0;
	int randomCol = 0;
	int rowLimit = bd->NumRow() - 1;
	int colLimit = bd->NumCol() - 1;
	char c;
	
	srand((unsigned)time(0)); 
	
	cout << endl;
	cout << "Please select a difficulty" << endl;
	cout << "1. Beginner" << endl; //3 total enemies
	cout << "2. Normal" << endl; //5 total enemies
	cout << "3. Hardcore" << endl << endl; //7 total enemies
	cin >> c;
	cin.ignore();
	
	switch(c)
	{
		case('1'): numAnts = 1;
				   numHornets = 1;
				   numSpiders = 1;
				break;
		case('2'): numAnts = 2;
				   numHornets = 1;
				   numSpiders = 2;
				break;
		case('3'): numAnts = 3;
				   numHornets = 2;
				   numSpiders = 2;
				break;
	}
	
	for(int i = 0; i < numAnts; ++i)
	{
		newPlayer = new KillerAnt("Ki");
		KillerAnt* k = dynamic_cast<KillerAnt*>(newPlayer);
		k->MakeActive();
		randomRow = rand()% rowLimit + 1;
		randomCol = rand() % colLimit + 1;
		
		bd->PlacePlayer(k, randomRow, randomCol);
		players.push_back(k);
	}
	
	for(int i = 0; i < numHornets; ++i)
	{
		newPlayer = new Hornet("Ho");
		Hornet* h = dynamic_cast<Hornet*>(newPlayer);
		newPlayer->MakeActive();
		randomRow = rand() % rowLimit + 1;
		randomCol = rand() % colLimit + 1;
		
		bd->PlacePlayer(h, randomRow, randomCol);
		players.push_back(h);
	}
	
	for(int i = 0; i < numSpiders; ++i)
	{
		newPlayer = new Spider("Sp");
		Spider* s = dynamic_cast<Spider*>(newPlayer);	
		newPlayer->MakeActive();
		randomRow = rand() % rowLimit + 1;
		randomCol = rand() % colLimit + 1;
		
		bd->PlacePlayer(s, randomRow, randomCol);
		players.push_back(s);
	}
	
	return players;
}


vector<PlayerClass*> Interface:: CreatePlayers()

{
	vector<PlayerClass*> players;
	PlayerClass* newPlayer;
	Board* bd = Board::GetBd();
	
	int num = 0;
	char p;
	string name;
	
	cout << endl << "How many players would you like to create?";
	cout << endl << "Number: ";
	cin >> num;
	cin.ignore();
	cout << endl;
	
	for(int i = 0; i < num; ++i)
	{
		cout << "Who would player #" << (i + 1) << " like to play as?" << endl;
		cout << "1. Explorer" << endl; 
		cout << "2. Warrior" << endl;
		cout << "3. Barbarian" << endl;
		cout << endl << "Choice: ";
		cin >> p;

		cout << endl;
		cout << "Name: ";
		cin.ignore();
		getline(cin, name);
		cout << endl;
		
		switch(p)
		{
			case('1'): newPlayer = new Explorer(name);
					break;
			case('2'): newPlayer = new Warrior(name);
					break;
			case('3'): newPlayer = new Barbarian(name);
					break;
			default: newPlayer = new Explorer(name);
					break;
		}
		
		newPlayer->MakeActive();
		bd->PlacePlayer(newPlayer, 0, 0);
		players.push_back(newPlayer);
	}
	
	return players;
}


void Interface:: BeginPlayerTurn(PlayerClass* p)

{
	char choice;
	bool turnOver = false;
	
	if(p)
	{
		p->ResetMomentum();
		
		while(!turnOver)
		{
			cout << endl << setfill('*') << setw(49) << "*" << endl;
			cout << p->Name() << " your turn starts now" << endl;
			cout << "What would you like to do?" << endl;
			cout << "1. Move" << endl;
			cout << "2. Change direction" << endl;
			cout << "3. Heal" << endl;
			cout << "4. Check stats" << endl;
			cout << endl << "Choice: ";
			
			cin >> choice;
			
			switch(choice)
			{
				case('1'): turnOver = PlayerMove(p);
					break;
				case('2'): PlayerChangeDir(p);
					break;
				case('3'): turnOver = PlayerHeal(p);
					break;
				case('4'): PlayerCheckStats(p);
					break;
			}
		}
	}
}


bool Interface:: PlayerMove(PlayerClass* p)

{
	int moveLimit = 0;
	int moveAmount = 0;
	bool moved = false;
	Board* bd = Board::GetBd();
	vector<PlayerClass*>:: iterator iter;	
	vector<PlayerClass*> enemies;
	
	if(p)
	{
		moveLimit = p->Momentum();
		while(!moved)
		{
			cout << "You can currently move " << p->Momentum() << " spaces" << endl;
			cout << "Please enter how much you would like to move: ";
			cin >> moveAmount;
			cin.ignore();
			cout << endl;
			
			if(moveAmount >= 0 && moveAmount <= p->Momentum())
			{
				moved = true;
			}
		}
		
		for(int i = 0; i < moveAmount; ++i)
		{
			p->Move();
			enemies = bd->Enemies(p);
			for(iter = enemies.begin(); iter != enemies.end(); ++iter)
			{
				Combat::SameCellCombat(p, *iter);
			}			
		}
	}
	return true;
}


void Interface:: PlayerChangeDir(PlayerClass* p)

{
	char dir;
	
	if(p)
	{
		cout << "Please enter the direction you'd like to face: "; 
		cin >> dir;
		cin.ignore();
		cout << endl;
		
		p->SetDir(GameSpace::CharToDir(dir));
	}
}


bool Interface:: PlayerHeal(PlayerClass* p)

{
	if(p)
	{
		p->Heal();
		cout << "You have taken a turn to rest" << endl;
		cout << "Your new current health is: " << p->Health();
		cout << endl;
	}
	
	return true;
}


void Interface:: PlayerCheckStats(PlayerClass* p)

{
	if(p)
	{
		p->Write(cout);
	}
}


void Interface:: BeginAITurn(PlayerClass* p)

{
	if(p)
	{
		p->ResetMomentum();	
		p->SetDir(GameSpace::EAST);
		p->Move();
	}
}


void Interface:: DisplayBoardState(PlayerClass* p)

{
	Board* bd = Board::GetBd();
	
	if(p)
	{
		bd->PrintBoard(cout, p);
	}
}


bool Interface:: IsGameOver(vector<PlayerClass*> allPlayers)

{
	Human* e;
	vector<PlayerClass*>:: iterator iterA;
	vector<PlayerClass*>:: iterator iterB;
	bool endState = true;


	for(iterA = allPlayers.begin(); iterA != allPlayers.end(); ++iterA)
	{
		e = dynamic_cast<Human*>(*iterA);
		if(e && (*iterA)->IsActive())
		{
			for(iterB = allPlayers.begin(); iterB != allPlayers.end(); ++iterB)
			{
				if((*iterA)->IsMyEnemy(*iterB) && (*iterB)->IsActive())
				{
					endState = false;
				}
			}
		}
	}
	
	return endState;
}