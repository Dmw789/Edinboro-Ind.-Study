//dice.cpp

#include "dice.h"


bool Dice::see = false;
bool Dice::write = false;
bool Dice::read = false;
vector<Dice::RollRec> Dice::rollData;
  
  

void Dice::HideRolls( )
{
	see = false;
}

void Dice::SeeRolls( )
{
	see = true;
}

void Dice::WriteRollsToFile( )
{
	write = true;
	read = false;
        ofstream fout;
        fout.open(DICE_FILE.c_str());
        fout.close();
}

void Dice::ReadRollsFromFile( )
{
  write = false;
  read = true;
  bool valid;
  string name;
  ifstream fin;
  RollRec data;
  
    fin.open(DICE_FILE.c_str());
    if (!fin) cout<<DICE_FILE<< " NOT FOUND! ROLLS WILL NOT BE READ"<<endl;
    //fin.open("die.out");
    valid = Read(fin, data);
    while (fin && valid )
    {
      data.name = Ucase(data.name);
      rollData.push_back(data);
      valid = Read(fin,data);
    }
    fin.close();

/*    vector<RollRec>::iterator i;
    for (i = rollData.begin(); i != rollData.end(); i++)
    {
      cout <<i->name <<DEL
           << i->what <<DEL
           <<i->numrolls<<"d"
           <<i->faces<<DEL
           << i->rollvalue<<endl;
    }
*/

}


bool Dice::Read(istream& stream, RollRec& data)
{
  string str;
  int num;
  bool valid = true;
  valid = ReadStr(stream, data.name);
  if (valid)
    valid = ReadNum(stream, num,0,INT_MAX);
  if (valid)
    data.what = RollType(num);
//  if (valid)
//    valid = ReadNum(stream, data.times,0,INT_MAX);
//  if (valid)
//    valid = ReadNum(stream, data.numrolls,0,INT_MAX);
  stream >> data.numrolls;
  stream.ignore(1);
  if(valid)
    valid = ReadNum(stream, data.faces,0,INT_MAX);
  if (valid)
    valid = ReadNum(stream, data.rollvalue,0,INT_MAX);
  data.used = false;
  stream.ignore(256,'\n');
  return valid;    
}

Dice::Dice( )
{

}

int Dice::Roll(string who, RollType what, int num_dice, int num_dice_faces)
{
	
	int tot;
	who = TrimStr(who);
	who = Ucase(who);
	if (who.length()==0) who = "?";
	if (read)
	{
	 tot = Find (num_dice,num_dice_faces,who,what);
	}
	else
	{
	  tot = Roll(num_dice,num_dice_faces);
        }
        
	if (see) 
	{
	  Write(cout,num_dice,num_dice_faces, who,what,tot);
	}
	
	if ((!read) && (write))
	{
	  ofstream fout;
	  fout.open(DICE_FILE.c_str(),ios::app);
	  fWrite(fout,num_dice,num_dice_faces, who,what,tot);
	  fout.close();
	}
	
	return tot;
}	

int Dice::Roll(int n, int f)
{
	int roll;
	int tot = 0;
	for (int i = 0; i< n ; i++)
	{
		roll = (rand( ) % f) + 1;
		tot +=roll;
	}
	return tot;
}

int Dice::Find(int n, int f, string who, RollType what)
{
	
	unsigned int tot = 0;
	unsigned int i;
	bool found;
//cout << who<<DEL<<what<<endl;
	for (i = 0, found = false; i < rollData.size() && !found;i++)
	{
//		cout << rollData[i].name<<DEL<<rollData[i].what<<endl;
		if ((rollData[i].name == who) &&
		    (rollData[i].what == what) &&
		    (rollData[i].numrolls == n) &&
		    (rollData[i].faces == f) &&
		    (!rollData[i].used))
		    {
		        found = true;
		    	rollData[i].used = true;
		    	tot = rollData[i].rollvalue;
//		    	cout << "set value from vector"<<endl;
		    }
          }
        // not yet found
	for (i = 0; i < rollData.size() && !found;i++)
	{
          
		if ((rollData[i].name == who) &&
		    (rollData[i].what == what) &&
		    (!rollData[i].used))
		    {
		    	cout << "error:found in file, but wrong dice:"
		    	    <<who<<DEL<<what<<DEL<<n<<"d"<<f<< "[" << ROLL_STR[what]<<"]"<<endl;
		    	//error
		        found = true;
		    	rollData[i].used = true;
		    	tot = rollData[i].rollvalue;
		    }
	}
	// still not found
	if (!found) 
	{
            cout << "error:not found in file random roll:"
                 <<who<<DEL<<what<<DEL<<n<<"d"<<f<< "[" << ROLL_STR[what]<<"]"<<endl;
		    	//error
	    tot = Roll(n,f);
	}	
//	if (found) cout <<"found\n"; else cout <<"NOT\n";
	return tot;	
}


void Dice::fWrite(ostream& stream, int n, int f, string who, 
                 RollType what, int tot)
{
//        if (who.length( ) == 0)
//          who=who+"?";
          
	stream << who<<"#"<<what<<"#"<<n<< "d" << f<<"#"<<tot<<"#";

        stream << "[" << ROLL_STR[what]<<"]"<<endl;
        
}

void Dice::Write(ostream& stream, int n, int f, string who, 
                 RollType what, int tot)
{
	stream << who<<"["<<setw(4)<<ROLL_STR[what]<<"]:";
	stream <<n<< "d" << f<<"="<<tot;
        cout <<endl;
}
/*
//***************************************
//**  Testing area


int main( )
{
  //Dice::WriteRollsToFile( );
  Dice::ReadRollsFromFile( );
	int tot = 0;
	
	
     for (int f = 1; f<5; f++)
      for(int n=1; n<5; n++)
      {
	Dice::SeeRolls( );
	tot =Dice::Roll("Joe",RollType(f+n),n,f);
	cout <<"\t"<<tot<<"----";

	Dice::HideRolls( );
	tot =Dice::Roll("Joe",RollType(f+n), n, f);
	cout <<tot<<endl;;
      }

	cout <<endl <<endl;

  return 0;

}
*/





