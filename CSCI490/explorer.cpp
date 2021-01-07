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


#include "explorer.h"

using namespace std;

//ASSIGN STATIC CONSTS
const int Explorer::INIT_VAR_STATS[PlayerClass:: END_STAT_TYPE] = {42, 7, 8, 8, 6, 0, -1, -1};
const int Explorer::INIT_CONST_STATS[PlayerClass:: END_CONST_STAT_TYPE] = {42, 8, 6, 1};
const string Explorer:: TYPE_STR = "EXPLORER";

//*****METHODS*****

//*****CONSTRUCTORS*****


Explorer::Explorer(): Human("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Explorer::Explorer(string name): Human(name, INIT_CONST_STATS, INIT_VAR_STATS)

{

}


//*****OBSERVERS*****

string Explorer::TypeStr() const

{
	return TYPE_STR;
}
	
		
void Explorer::Write(ostream& out) const

{
	out << TypeStr() << "#";
	Human::Write(out);
}


Explorer* Explorer:: Clone() const

{
	return new Explorer(*this);
}