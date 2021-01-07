//
// Dylan Whitehead
// d823691w
// 
// CSCI 490
// FALL 2019
// BUG CLASS
// 
// Narrative: A derived child class of PlayerClass. Assumes all methods and data publicly from PlayerClass and adds a new version of Write(). 
// Meant to serve as a gateway parent class for any other player type that falls under the same category. Any and all functions/variables that 
// are consistently used by all bug types but not by all bug AND human types are to be put in this class to avoid redundancy.
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes: 
//
//


#include "bug.h"

using namespace std;


Bug::Bug() : PlayerClass("NAME", NULL, NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Bug::Bug(const string NAME, const int C_STATS[], const int V_STATS[]): PlayerClass(NAME, C_STATS, V_STATS)

{
	
}

string Bug::Name() const
	
{
	return PlayerClass::Name() + GameSpace::ConvertInt(PlayerNum());
}


void Bug:: Write(ostream& out) const

{
	PlayerClass::Write(out);
}
