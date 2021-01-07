//
// Dylan Whitehead
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: A derived child class of Human. Assumes all methods and variables publicly from Human, and therefor from PlayerClass.
// One of the player types used throughout the game that is reusable and replicatable.
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes: 
//
//


#include "warrior.h"

using namespace std;

//ASSIGN STATIC CONSTS
const int Warrior::INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE] = {81, 9, 5, 5, 9, 8, -1, -1};
const int Warrior::INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE] = {81, 5, 6, 3};
const string Warrior:: TYPE_STR = "WARRIOR";

//*****METHODS*****

//*****CONSTRUCTORS*****


Warrior::Warrior(): Human("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Warrior::Warrior(string name): Human(name, INIT_CONST_STATS, INIT_VAR_STATS)

{

}


//*****OBSERVERS*****

string Warrior::TypeStr() const

{
	return TYPE_STR;
}
	
	
void Warrior::Write(ostream& out) const

{
	out << TypeStr() << "#";
	Human::Write(out);
}


Warrior* Warrior:: Clone() const

{
	return new Warrior(*this);
}
