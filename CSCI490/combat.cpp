//
// Dylan Whitehead

// d823691w
// 
// CSCI 490
// FALL 2019
// COMBAT CLASS
//
// Narrative: This is a class designed to control all combat-based functionality during the runtime of the game. Mostly to be used by the Interface Class, though it is important
// in the proper execution of the BugNest and Bug sub-classes currently. All combat should be performed with proper PlayerClass ptrs being passed in through SameCellCombat. 
// Currently, no other functionality should be necessary in order to properly simulate and compute player-based attacks.
//
// Special Notes: All rolls currently checking to see if the players are in the same cell may seem redundant, but it is for possible future implementation of ranged attacks being
// added per the specifications of the original CSCI330 Game Doc. 
//

#include "combat.h"
#include <iostream>
#include <iomanip>

#include "board.h" 
#include "cell.h"
#include "gamespace.h"
#include "warrior.h"
#include "explorer.h"
#include "hornet.h"
#include "spider.h"
#include "killerAnt.h"
#include "barbarian.h"

using namespace std;

//*****METHODS*****

//*****TRANSFORMERS*****
void Combat::SameCellCombat(PlayerClass* p1, PlayerClass* p2)

{	
	if((p1 && p2) && (p1->IsActive() && p2->IsActive()))
	{
		cout << endl;
		
		while((p1->Row() == p2->Row()) && (p1->Col() == p2->Col()) && (p1->Health() > 0) && (p2->Health() > 0))	
		{
			cout << p1->Name() << " is battling " << p2->Name() << endl << endl;
			cin.ignore();
			HitScore(p1, p2);
			
			if((p2->Health() > 0) && (p1->Row() == p2->Row()) && (p1->Col() == p2->Col()))
			{
				cout << p2->Name() << " is hitting back at " << p1->Name() << endl << endl;
				cin.ignore();
				HitScore(p2, p1);
			}
		}
	}
}

void Combat::HitScore(PlayerClass* att, PlayerClass* target)

{
	int score = 0;

	score = att->HitScore();
	cout << endl << score << endl;
	switch(score)
	{
		case(2): RollTwo(att, target);
				break;
		case(3): RollThree(att, target);
				break;
		case(4): RollFour(att, target);
				break;
		case(5): RollFive(att, target);
				break;
		case(6): RollSix(att, target);
				break;
		case(7): RollSeven(att, target);
				break;
		case(8): RollEight(att, target);
				break;
		case(9): RollNine(att, target);
				break;
		case(10): RollTen(att, target);
				break;
		case(11): RollEleven(att, target);
				break;
		case(12): RollTwelve(att, target);
				break;
		default: RollTwo(att, target);
	}
}


void Combat::Battle(PlayerClass* att, PlayerClass* target)

{
	if(att && target)
	{
		//unused currently -- possible ranged combat 
	}
}


bool Combat:: Run(PlayerClass* target)

{
	bool wasSuccessful = false;
	GameSpace::DirType prevDir = target->Dir();
	Board::Board* bd = Board::GetBd();
	
	target->SetDir(GameSpace::NORTH);
	
	if(bd->MoveCost(target, 1))
	{
		bd->MoveForward(target, 1);
		wasSuccessful = true;
		cout << target->Name() << " has run to the north!" << endl << endl;
	}
	else
	{
		target->SetDir(prevDir);
	}
	
	return wasSuccessful;
}


void Combat:: RollTwo(PlayerClass* att, PlayerClass* target)

{
	int dmg = att->HitDamage() - target->Defense();

	cout << att->Name() << " has " << att->Health() << " health" << endl;
	cout << target->Name() << " has " << target->Health() << " health" << endl << endl;
	
	target->Wounded(dmg);
	target->CriticalWound();

	cout << target->Name() << " has taken " << dmg << " damage." << endl;
	cout << target->Name() << " has suffered a critical wound!" << endl;
	cout << att->Name() << " now has " << att->Health() << " health" << endl;
	cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
}


void Combat:: RollThree(PlayerClass* att, PlayerClass* target)

{
	int dmg = att->HitDamage() - target->Defense();
	
	cout << att->Name() << " has " << att->Health() << " health" << endl;
	cout << target->Name() << " has " << target->Health() << " health" << endl << endl;
	
	if((att->Row() == target->Row()) && (att->Col() == target->Col()))
	{	
		target->Wounded(dmg);
		cout << target->Name() << " has taken " << dmg - target->Defense() << " damage." << endl;
		cout << att->Name() << " now has " << att->Health() << " health" << endl;
		cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
	}
}


void Combat:: RollFour(PlayerClass* att, PlayerClass* target)

{
	cout << "It missed!" << endl;
}


void Combat:: RollFive(PlayerClass* att, PlayerClass* target)

{
	int dmg = att->HitDamage() - target->Defense();
	
	cout << att->Name() << " has " << att->Health() << " health" << endl;
	cout << target->Name() << " has " << target->Health() << " health" << endl << endl;	
	target->Wounded(dmg);
	target->CriticalWound();

	cout << target->Name() << " has taken " << dmg << " damage." << endl;
	cout << target->Name() << " has suffered a critical wound!" << endl;
	cout << att->Name() << " now has " << att->Health() << " health" << endl;
	cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
}


void Combat:: RollSix(PlayerClass* att, PlayerClass* target)

{
	Human* h = dynamic_cast<Human*>(att);
	int dmg = 0;

	if(h && h->WeaponSkill() >= 5)
	{
		if((att->Row() == target->Row()) && (att->Col() == target->Col()))
		{	
			cout << att->Name() << " has " << att->Health() << " health" << endl;
			cout << target->Name() << " has " << target->Health() << " health" << endl << endl;
			dmg = att->HitDamage() - target->Defense();
			target->Wounded(dmg);
			cout << target->Name() << " has taken " << dmg << " damage." << endl;
			cout << att->Name() << " now has " << att->Health() << " health" << endl;
			cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
		}
	}
}


void Combat:: RollSeven(PlayerClass* att, PlayerClass* target)

{
	if((att->Row() == target->Row()) && (att->Col() == target->Col()))
	{	
		Run(target);
	}
}


void Combat:: RollEight(PlayerClass* att, PlayerClass* target)

{
	int dmg = 0;

	if(!Run(target))
	{
		cout << att->Name() << " has " << att->Health() << " health" << endl;
		cout << target->Name() << " has " << target->Health() << " health" << endl << endl;	
		dmg = att->HitDamage() - target->Defense();
		target->Wounded(dmg);
		target->CriticalWound();

		cout << target->Name() << " has taken " << dmg << " damage." << endl;
		cout << target->Name() << " has suffered a critical wound!" << endl;
		cout << att->Name() << " now has " << att->Health() << " health" << endl;
		cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
	}
}


void Combat:: RollNine(PlayerClass* att, PlayerClass* target)

{
	int dmg = 0;
	
	if(target->CurrentSpeed() < 8)
	{
		cout << att->Name() << " has " << att->Health() << " health" << endl;
		cout << target->Name() << " has " << target->Health() << " health" << endl << endl;		
		dmg = att->HitDamage() - target->Defense();
		target->Wounded(dmg);
		cout << target->Name() << " has taken " << dmg << " damage." << endl;
		cout << att->Name() << " now has " << att->Health() << " health" << endl;
		cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
	}
}


void Combat:: RollTen(PlayerClass* att, PlayerClass* target)

{
	if((att->Row() == target->Row()) && (att->Col() == target->Col()))
	{	
		Run(target);
	}
}


void Combat:: RollEleven(PlayerClass* att, PlayerClass* target)

{
	Human* h = dynamic_cast<Human*>(att);
	int dmg = 0;
	
	cout << att->Name() << " has " << att->Health() << " health" << endl;
	cout << target->Name() << " has " << target->Health() << " health" << endl << endl;		
	
	if(h && h->WeaponSkill() >= 9)
	{
		target->CriticalWound();
		cout << target->Name() << " has suffered a critical wound!" << endl;
	} 
	else 
	{
		dmg = att->HitDamage() - target->Defense();
		target->Wounded(dmg);
		cout << target->Name() << " has taken " << dmg << " damage." << endl;
	}
		cout << att->Name() << " now has " << att->Health() << " health" << endl;
		cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
}


void Combat:: RollTwelve(PlayerClass* att, PlayerClass* target)

{
	int dmg = 0;
	
	cout << att->Name() << " has " << att->Health() << " health" << endl;
	cout << target->Name() << " has " << target->Health() << " health" << endl << endl;		
	
	if((att->Row() == target->Row()) && (att->Col() == target->Col()))
	{	
		if(!Run(target))
		{
			dmg = att->HitDamage() - target->Defense();
			target->Wounded(dmg);
			cout << target->Name() << " has taken " << dmg << " damage." << endl;
		}
		cout << att->Name() << " now has " << att->Health() << " health" << endl;
		cout << target->Name() << " now has " << target->Health() << " health" << endl << endl;
	}
}


