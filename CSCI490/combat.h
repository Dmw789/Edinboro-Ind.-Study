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


#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"

using namespace std;

class Combat
{
	public:
	
//*****PUBLIC METHODS*****
	
	//*****PUBLIC VARIABLES*****
		enum HitEnum{MISS, RUN, FW, CW};
	
	
	//*****TRANSFORMERS*****
		static void SameCellCombat(PlayerClass* p1, PlayerClass* p2);
		//Narrative: Begins and computes a simulation of combat between two players. Depending on the rolls, various outcomes are possible including
		//one player running, inflicting damage, or inflicting a critical wound on the other player. If both players are still active and in the same cell, 
		//the target player will retaliate with their own attack. This process repeats until either one player runs or dies.
		//
		//Pre-condition: Both players passed in should be valid playerclasses
		//
		//Post-condition: The combat is computed, and either one player has run or died as a result depending on what they rolled.
		//
		

	private:
	
//*****PRIVATE METHODS*****
	//*****CONSTRUCTORS*****
		Combat(); //Default Constructor, not to be used
	
	//*****TRANSFORMERS*****
		static void HitScore(PlayerClass* att, PlayerClass* target);
		//Narrative: Roll the hitscore that determines the effect of a player's attack. Depending on the result, one of 11 functions will be called.
		//
		//Pre-condition: Either the rolls should be set for the dice class using WriteRolls or that should be disabled so that random rolls can be 
		//properly generated when passed in.
		//
		//Post-condition: Control is passed to the appropriate corresponding method
		//
	
		static void Battle(PlayerClass* att, PlayerClass* target);
		//Narrative: To be used possible in the future for ranged battle - Currently underdeveloped and thus set to private to be unaccessible.
		//
		//Pre-condition:
		//
		//Post-condition:
		//		
		
		static bool Run(PlayerClass* target);
		//Narrative: Computes if a player is able to run to the north. Returns true or false depending on if the move was completed.
		//
		//Pre-condition: none
		//
		//Post-condition: If the player is able to move to the north, they move up one, otherwise no move is completed and they stay where they were
		//
		
		static void RollTwo(PlayerClass* att, PlayerClass* target); //Wound and CriticalWound called on target
		static void RollThree(PlayerClass* att, PlayerClass* target); //Wound called on target
		static void RollFour(PlayerClass* att, PlayerClass* target); //nothing -- attack misses
		static void RollFive(PlayerClass* att, PlayerClass* target); //Wound and CriticalWound called on target
		static void RollSix(PlayerClass* att, PlayerClass* target); //Wound inflicted if wepSkill is >= 5
		static void RollSeven(PlayerClass* att, PlayerClass* target); //Target runs
		static void RollEight(PlayerClass* att, PlayerClass* target); //If unable to run, Wound and CriticalWound called on target
		static void RollNine(PlayerClass* att, PlayerClass* target); //If target's currentSpeed < Wound is called on target
		static void RollTen(PlayerClass* att, PlayerClass* target); //Target runs
		static void RollEleven(PlayerClass* att, PlayerClass* target); 
		static void RollTwelve(PlayerClass* att, PlayerClass* target);
};

#endif