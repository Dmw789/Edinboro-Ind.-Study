// wpn.cpp
// Weapon Class

#include "wpn.h"


//*************************************************************************
map<string, Weapon::WeaponRec> Weapon::wpns;
const int Weapon::NUM_DIFF_WPNS;
const string Weapon::WPNTYPE_STR[NUM_DIFF_WPNS] = {"BALLISTIC", "BLUDGEONING", "ENERGY",
                                    "PIERCING", "SLASHING"};
int Weapon::count = 0;

Weapon::WpnType Weapon::StrToWpnType(string str)
{
  str = Ucase(TrimStr(str));
  bool found = false;
  int ret_val = 0;
  for (int i = 0; i<NUM_DIFF_WPNS && !found; i++)
   {
     if (WPNTYPE_STR[i] == str)  
     { 
          ret_val = i;
          found = true;
       }
   }
   return WpnType(ret_val);
}



// these are not called
   Weapon::Weapon( )
   {
     //cout << "Weapon::Default called"<<endl;
     throw INVALID_WPN;
   }
    
/*   Weapon::Weapon(const Weapon & w )
   {
     //cout << "Weapon::Copy const called"<<endl;
     throw INVALID_WPN;
   }
    
   Weapon& Weapon::operator=(const Weapon & w )
   {
     //cout << "Weapon::Assignment called"<<endl
     throw INVALID_WPN;
   }
*/

//*********************************Constructors
Weapon::Weapon(string n)
{
  string un = Ucase(TrimStr(n));

  Load( );
//  cout << "in constr - new weapon:" << n <<"\t" <<un <<endl;
  if (wpns.count(un) > 0)
  {
      name = n;
      serialNum = ++count;
  }
  else
      throw INVALID_WPN;
}


//*********************************Getters methods

string Weapon::Name( ) const
{
 return name;
}

string Weapon::NameAndNum( ) const
{
 return name+"-"+ConvertInt(serialNum);
}

int Weapon::Cost( ) const
{
  return wpns[Ucase(Name())].cost;
}

int Weapon::Wt( ) const
{
  return wpns[Ucase(Name())].wt;
} 

int Weapon::Range( ) const
{
  return wpns[Ucase(Name())].range;
}
    
int Weapon::RollWeaponDamage(string pname ) const
{
    //numRolls = data.damRolls;
    //faces = data.damFaces;

  string n = Ucase(Name());
  int num = wpns[n].damRolls;
  int faces = wpns[n].damFaces;
  int roll = Dice::Roll(pname,GameSpace::DAMAGE,num,faces);

  return roll;
}

int Weapon::Power( ) const
{
  return wpns[Ucase(Name())].power;
}

Weapon::WpnType Weapon::Style( ) const
{
  return wpns[Ucase(Name())].style;
}

bool Weapon::IsMelee( ) const
{
  return wpns[Ucase(Name())].strength;
}

bool Weapon::IsRange( ) const
{
  return !wpns[Ucase(Name())].strength;
}



bool Weapon::IsMelee(string name)
{
  bool melee=false;

  Load( );

  if ( (wpns.count(Ucase(name))> 0))
    melee = wpns[Ucase(name)].strength;
  return melee;
}


bool Weapon::IsRange(string name)
{
  bool range=false;

  Load( );

  if ( (wpns.count(Ucase(name))> 0))
    range = !wpns[Ucase(name)].strength;
  return range;
}



//*********************************File methods

void Weapon::Load( )
{
  bool valid;
  string name;
  ifstream fin;
  WeaponRec data;
  
  if (wpns.size()>0) return;
  
  
    fin.open(RANGE_WPNS_FILE.c_str());
    valid = Read(fin, name, data);
    while (fin && valid )
    {
      name = Ucase(name);
      wpns[name] = data;
      wpns[name].strength = false;
      valid = Read(fin,name,data);
    }
    fin.close();

    fin.open(MELEE_WPNS_FILE.c_str());
    valid = Read(fin, name, data);
    while (fin && valid )
    {
      name = Ucase(name);
      wpns[name] = data;
      wpns[name].strength = true;
      valid = Read(fin,name,data);
    }
    
    fin.close();
    

/*    
    map<string, WeaponRec>::iterator i;
    for (i = wpns.begin(); i != wpns.end(); i++)
    {
      cout<<i->first <<DEL 
      << i->second.cost <<DEL
      << i->second.wt <<DEL 
      << i->second.range <<DEL
      << i->second.damRolls <<DEL
      << i->second.damFaces <<DEL
      << i->second.power <<DEL
//      << WeaponToStr(i->second.style)<<DEL
      << i->second.strength<<endl;
    }
    cout << "size:" <<wpns.size()<<endl<<endl;
*/
}


bool Weapon::Read(istream& stream, string& name, WeaponRec& data)
{
  string str;
  bool valid = true;
  valid = ReadStr(stream, name);
  if (valid)
    valid = ReadNum(stream, data.cost,0,INT_MAX);
  if (valid)
    valid = ReadNum(stream, data.wt,0,INT_MAX);
  if (valid)
    valid = ReadNum(stream, data.range,INT_MIN,INT_MAX);
  if(valid)
    valid = ReadNum(stream, data.damRolls,1,INT_MAX);
  if(valid)
    valid = ReadNum(stream, data.damFaces,1,INT_MAX);
  if (valid)
    valid = ReadNum(stream, data.power,0,INT_MAX);
  if (valid)
    valid = ReadStr(stream,str);
  if (valid)
    data.style = StrToWpnType(str);
  return valid;    
}
         
void Weapon::Write(ostream& stream) const
{
  string wname = Ucase(Name());
  stream << NameAndNum( );
  stream << DEL;
  stream << wpns[wname].cost;
  stream << DEL;
  stream << wpns[wname].wt;
  stream << DEL;
  stream << wpns[wname].range;
  stream << DEL;
  stream << wpns[wname].damRolls;
  stream << "d";
  stream << wpns[wname].damFaces;
  stream << DEL;
  stream << wpns[wname].power;
  stream << DEL;
  stream << WPNTYPE_STR[wpns[wname].style];
  stream <<DEL;
  if (IsMelee())
      stream << "MELEE";
  else
      stream << "RANGE";
            
}

ostream & operator<<(ostream& out, const Weapon & w)
{
    w.Write(out);
    return out;
}

//*******relational operators
//     compare the name of the weapon ONLY

bool Weapon::operator == (const Weapon & w) const
{
    return (Ucase(name) == Ucase(w.name));
}

bool Weapon::operator != (const Weapon & w) const
{
    return (Ucase(name) != Ucase(w.name));
}

bool Weapon::operator < (const Weapon & w) const
{
    return (Ucase(name) < Ucase(w.name));
}

bool Weapon::operator <= (const Weapon & w) const
{
    return (Ucase(name) <= Ucase(w.name));
}

bool Weapon::operator > (const Weapon & w) const
{
    return (Ucase(name) > Ucase(w.name));
}

bool Weapon::operator >= (const Weapon & w) const
{
    return (Ucase(name) >= Ucase(w.name));
}




/*
Weapon::~Weapon( )
{
    map<string, WeaponRec>::iterator i;
    for (i = wpns.begin(); i != wpns.end(); i++)
    {
      cout<<i->first <<" "<< i->second.range <<" " << i->second.power<<endl;
    }
}
*/
//***************************************
//**  Testing area
/*
#include <vector>
int main( )
{
  const int NUM_WPNS_IN_FILE = 6;
  ifstream fin;
  ofstream fout;  // file stream for tests
  string str;
  vector<string> wNames;
  int num;
  int i;
  fin.open(RANGE_WPNS_FILE.c_str());
  cout <<"Reading weapons from File:\n";
  while(fin)
  {
    ReadStr(fin,str);
    cout << str<<endl;
    wNames.push_back(str);
    fin.ignore(256,'\n');
  }
  fin.clear();
  fin.close();
  
  Weapon* e[NUM_WPNS_IN_FILE];

  for (i=0; i<NUM_WPNS_IN_FILE; i++)
  {
      cout <<"NEW:"<< wNames[i]<<endl;
         e[i]  = new Weapon(wNames[i]);
  }
  cout << "Write the weapons:"<<endl;
  for (i=0;i<NUM_WPNS_IN_FILE;i++)
  {
    e[i]->Write(cout);

    cout<<endl<<setw(21)<<" ";
    cout << e[i]->Name( ) <<DEL
         << e[i]->Cost( ) <<DEL
         << e[i]->Wt( ) <<DEL
         << e[i]->Range( ) <<DEL
         << e[i]->RollWeaponDamage(e[i]->Name() ) <<DEL
         << e[i]->Power( )<< DEL
         << e[i]->Style( ) <<DEL
         << e[i]->IsMelee( ) <<endl;
  }
  cout <<endl <<endl;
  
  Weapon f(*e[0]);
  Weapon g(*e[1]);
  f.Write(cout);
  cout <<endl;
  g.Write(cout);
  cout <<endl;
  

  if (f == g) cout<<"\t== ";
  if (f != g) cout<<"\t!= ";
  if (f < g) cout<<"\t< ";
  if (f <= g) cout<<"\t<= ";
  if (f > g) cout<<"\t> ";
  if (f >= g) cout<<"\t>= ";
  
cout <<endl<<endl<<"flip them around:"<<endl;
  if (g == g) cout<<"\t== ";
  if (g != g) cout<<"\t!= ";
  if (g < g) cout<<"\t< ";
  if (g <= g) cout<<"\t<= ";
  if (g > g) cout<<"\t> ";
  if (g >= g) cout<<"\t>= ";
cout <<endl;
  return 0;
  
}

*/


