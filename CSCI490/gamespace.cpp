// gamespace.cpp

#include "gamespace.h"

//Game specific functions


GameSpace::RollType GameSpace::StrToRoll(string str)
{
  str = Ucase(TrimStr(str));
  bool found = false;
  int ret_val = -1;
  for (int i = 0; i<NUM_ROLLTYPE && !found; i++)
   {
     if (ROLL_STR[i] == str)  ret_val = i;
   }
   if (ret_val == -1)  throw INVALID_ROLL;
   return RollType(ret_val);

}

GameSpace::DirType GameSpace::StrToDir(string s)
{
   s = Ucase(TrimStr(s));
   bool found = false;
   int ret_val = -1;
   for (int i = 0; i<NUM_DIRTYPE && !found; i++)
   {
     if (DIR_STR[i] == s)  ret_val = i;
   }
   if (ret_val == -1)  throw INVALID_DIR;
   return DirType(ret_val);
}


GameSpace::DirType GameSpace::CharToDir(char c)
{
  c = toupper(c);
  int ret_val = 0;
  bool found = false;
   for (int i = 0; i<NUM_DIRTYPE && !found; i++)
   {
     if (DIR_CHAR[i] == c)  ret_val = i;
   }
   if (ret_val == -1)  throw INVALID_DIR;

   return DirType(ret_val);

}


string GameSpace::TrimStr(string str)
{
    unsigned int start = 0;;
    unsigned int end =str.length();
    unsigned int i = 0;
    string newstr = "";
    bool done = false;

    
    // remove front whitespace
    while((i < str.length( ))&& isspace(str[i]))
    {
     i++;
    }
    start = i;

    if (start < end) // characters left in string
    {
      // remove end whitespace
      i = str.length()-1;
    
      while ((i>0) && isspace(str[i]))
      {
        i--;
      }
      end = i;
    }
    else
      done = true;
    
    if (!done)
    {
   
      bool prev_ws=false,ws = false;
      for (i=start; i<=end;i++)
      {
        ws = isspace(str[i]);
        if (!ws)
        {
          if (prev_ws)
          {
            newstr = newstr+" ";
            //ws = false;
          }
          newstr = newstr+str[i];
        }
        prev_ws = ws;
       }
    }
    return newstr;
}


string GameSpace::Ucase(string s)
{
        unsigned int i;
	
        for (i=0; i<s.length(); i++)
        {
                s[i] = toupper(s[i]);
        }
        return s;
}


bool GameSpace::Cmp(string s1, string s2)
{
 return (Ucase(s1) <= Ucase(s2));
}


void GameSpace::Sort(vector<string>& s)
{
 sort(s.begin(), s.end(),Cmp);
}



bool GameSpace::ReadNum(istream& stream, int& num, int min, int max)
{
  bool valid = true;
  stream >> num;
  if (stream && (num >=min)&& (num<=max))
    valid = ReadDel(stream);
  else valid = false;
  return valid;  
}


bool GameSpace::ReadStr(istream& stream, string& str)
{
  str = "";
  char ch;
  stream.get(ch);
  //discard leading whitespace
  while (stream && isspace(ch))
     stream.get(ch);
     
  while (stream && (ch!='\n') &&(ch!=DEL))  
  {
    str=str+ch;
    stream.get(ch);
  }
  return stream && (str.length()>0) ;  
}


bool GameSpace::ReadDel(istream& stream)
{
  char ch='\0';
  stream.get(ch);
//cout << ch <<endl;
  return stream && ((ch=='\n') || (ch==DEL)|| (ch == 'd'));
}


void GameSpace::WriteDel(ostream& stream)
{
	stream<<DEL;
}


//**************************************************************OUTPUT


void GameSpace::PrintTest(ostream & out, string test)
{
  static string testch = "T";
  static int testnum = 1;
  if ((test != testch) && (test !=""))
  {
     testch = test;
     testnum = 1;
  }
  out << testch<<left<<setw(3)<< testnum++<<": ";
}

string GameSpace::ConvertInt(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
/*
using namespace GameSpace;
int main()
{
 string test = "";
 test = TrimStr(test);
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr(" ");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr("   ");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr("t");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr(" t");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr("t ");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr(" t ");
 cout << "string["<<test<<"]"<<endl;
 test = TrimStr("xx ");
 cout << "string["<<test<<"]"<<endl;

 test = "he\n\t   l    l   o";
 test = TrimStr(test);
 cout << "string["<<test<<"]"<<endl;
 return 0;
}
*/