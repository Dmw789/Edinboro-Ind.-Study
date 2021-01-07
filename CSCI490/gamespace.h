// gamespace.h
// game specific types and functions
// game: Insurgence of the Predator Bugs

#ifndef _GAMESPACE
#define _GAMESPACE

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

namespace GameSpace
{

//*****************************************************************************  
// Named constants  

//Input Files
  const string ARSENAL_FILE = "arsenal.in";
  const string BOARD_FILE = "board.in";
  const string DICE_FILE = "dice.in";
  const string MELEE_WPNS_FILE = "melee.in";
  const string RANGE_WPNS_FILE = "range.in";
  const string PLAYERS_FILE = "players.in";

//Output Files
  const string COMBAT_OUTFILE = "combat.out";
  const string MOVE_OUTFILE = "move.out";
  const string TEST_OUTFILE = "tests.out";

//Board constants
  const int NUMROWS = 12;
  const int NUMCOLS = 8;
  const bool KEYBD = true;

//Output constants
  const string LINE1 = "*************************************************\n";
  const char DEL = '#';

//*****************************************************************************  
// enum for dice  
  
  enum RollType {HITSCORE, DAMAGE, IMPACT, WOUND};
    // HITSCORE - HITSCORE value for player in combat
    // DAMAGE - Damage value for player or wpn
    // IMPACT - Impact value for IMPACT table
    // WOUND - Wound value for WOUND table

  const int NUM_ROLLTYPE = 4;
  const string ROLL_STR[NUM_ROLLTYPE] ={"HITSCORE", "DAMAGE", "IMPACT", "WOUND"};

  RollType StrToRoll(string str);
  // Converts the string RollType to RollType enum


//**********************************************************************
// enum for direction

  enum DirType {NORTH, EAST, SOUTH, WEST};

  const int NUM_DIRTYPE = 4;
  const string DIR_STR[NUM_DIRTYPE] = {"NORTH", "EAST", "SOUTH", "WEST"};
  const char DIR_CHAR[NUM_DIRTYPE] = {'N', 'E', 'S', 'W'};

  DirType StrToDir(string str);
  // Converts string to DirType

  DirType CharToDir(char c);
  // Converts char to Dirtype

  
//*****************************************************************************  
// Enum for exception handling

  enum ExceptionType {INVALID_MISC, INVALID_NAME, INVALID_PTYPE, INVALID_WPN,
			INVALID_DIR, INVALID_CELL, INVALID_ROLL}; 

  const int NUM_EXCEPTIONS = 7;
  const string EXCEPTION_STR[NUM_EXCEPTIONS] = {"INVALID MISC", "INVALID NAME", 
                                                "INVALID PLAYER TYPE", "INVALID WEAPON",
						"INVALID DIR", "INVALID_CELL",
						"INVALID ROLL"}; 

//*****************************************************************************  
// Function creating uppercase string  
  
  string Ucase(string str);
  // Converts str to uppercase
  // pre: str is a string
  // post: returns the uppercase version of str

  string TrimStr(string str);
  // Trims leading and trailing whitespace and removes extra
  //    whitespace in the middle
  // pre: str is a string
  // post: returns the trimmed string

  bool Cmp(string s1, string s2);
  // Compares 2 strings(non-case sensitive) to determine sorted order
  // pre:
  // post: returns true if s1<=s2

  void Sort(vector<string>& vec);
  // Sorts a vector of strings (not case-sensitive sort)
  // pre:
  // post: vector is in sorted order


  
//*****************************************************************************  
// File I/O for dice

  void WriteDel(ostream& stream);
  // Writes the delimiter to the output stream
  // pre: stream is open and in good condition
  // post: delimiter has been written
  
  bool ReadNum(istream& stream, int& num,int min,int max);
  // Reads a number, validates range, if valid reads del and returns true
  // pre: stream is open and in good cond, min and max indicate boundaries for num
  // post: valid: returns num, reads passed delimiter (includes \n), returns true
  //       invalid: stops reading and returns false
   
  bool ReadStr(istream& stream, string& str);    
  // Reads string through del, returns true if string length>0 && stream
  // pre: stream is open and in good cond.
  // post: reads str and delimiter (includes \n).  if string length >0 return true
  //		otherwise returns false
  
  bool ReadDel(istream& stream);
  // Reads Del (includes '\n')
  // pre: stream is open and in good cond.
  // post: delimiter is read and stream status is returned


//*****************************************************************************  
// Functions for Game Play  

  void PrintTest(ostream & out, string test="");
  // Prints the test label
  // pre:  out is open and test is prefix for test
  //       if test is new then testnumber is reset
  // post: test label is printed

  string ConvertInt(int num);
  // converts an int to a string
  // pre : num is integer value
  // post: returns as string of num: num = 5, "5"

  void PrintMove(string name, int row, int col, int mom, bool first = false);
    // Prints the move to a file move.out
    // pre:  none
    // post: prints a line to the move.out with the move data
    //
    //   LineNum:PlayerName(Row,Col) Momentum
    //  a line of asterisks is printed when a new player is encountered

  void NewMoveFile( );
    // Removes the move file


  
}


#endif

