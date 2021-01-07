// pack.cpp

#include "pack.h"

//***********************************************Constr/destr/assignment
PackClass::PackClass():MAX_WT(0)
{
  
}

PackClass::PackClass(int wt):MAX_WT(wt) // should validate >0
{
  if(wt <= 0)
  {
    throw GameSpace:: INVALID_MISC;
  }
}

PackClass::PackClass(const PackClass& p):MAX_WT(p.MAX_WT)
{
  CopyPack(p);
}

PackClass::~PackClass( )
{
  EmptyPack( );
}


PackClass& PackClass::operator=(const PackClass& p)
{
  if (this != &p)
    CopyPack(p);
    
  return *this;
}

void PackClass::CopyPack(const PackClass & p)
{
  // must create a FULL COPY of each weapon in p
  // add add to packVec
   
  //packVec = p.packVec; NOT DEEP copy

  EmptyPack();

  *const_cast<int *>(&MAX_WT) = p.MAX_WT;
  int length = p.packVec.size();
  Weapon* w = NULL;

  for(int i = 0; i < length; ++i)
  {
     w = new Weapon(*(p.packVec.at(i)));
     bool canAdd = AddWeapon(w);
     if(!canAdd)
	 {
       throw INVALID_MISC;
	 }
  }
}

//***********************************************Transformers

bool PackClass::AddWeapon(Weapon* w)
{
  // be sure weapon can be added 
  // add weapon ptr to the packVec
  // 
  bool canAdd = false;

  if(w == NULL)
  {
    throw INVALID_WPN;
  }

  int newWgt = Wt() + w->Wt();
  if(newWgt <= MAX_WT)
  {
    canAdd = true;
    packVec.push_back(w);
  }

  return canAdd;
}

Weapon * PackClass::RemoveWeapon(string wName)
{
  bool found;
  Weapon * ret_w = NULL;

  // i = find(pack.begin(), pack.end( ), wName);<-doesnt work - WHY?

  if(InPack(wName))
  {  
     ret_w = *(FindWeapon(wName));
     packVec.erase(FindWeapon(wName));
  }
  
  return ret_w;
}


void PackClass::EmptyPack( )  
{
  // Empty the packVec - 
  // be sure to actually deallocate all the weapons!!

  vector<Weapon *>:: iterator iter;

  for(iter = packVec.begin(); iter != packVec.end(); ++iter)
  {
    delete (*iter);
  }
  packVec.clear();
  
  
}  

//***********************************************Observers

bool PackClass::InPack(string wName) const
{
  bool found = false;
  vector<Weapon *>::const_iterator iter;

  // i = find(packVec.begin(), packVec.end( ), wName); // <- doesnt work - WHY?
  // Determine if the weapon is in the packVec

  for(iter = packVec.begin(); found == false && iter != packVec.end(); ++iter)
  {
    if(GameSpace::Ucase((*iter)->Name()) == GameSpace::Ucase(wName))
    {
      found = true;
    }
  }
 
  return (found);
}


vector<Weapon *>::iterator PackClass::FindWeapon(string wName)
{
  bool found = false;
  vector<Weapon *>::iterator iter, ret_iter;
  
  // i = find(packVec.begin(), packVec.end( ), wName); <-Doesnt work - WHY?
  // Find the weapon in the packVec and return 
  // the iterator to the first instance of that weapon
  //   if not found - return packVec.end()

  for(iter = packVec.begin(); found == false && iter != packVec.end(); ++iter)
  {
    if(GameSpace::Ucase((*iter)->Name()) == GameSpace::Ucase(wName))
    {
      ret_iter = iter;
      found = true;
    }
  }

  if(found == false)
  {
    ret_iter = packVec.end();
  }
 
  return (ret_iter); 
}

  
int PackClass::Size( ) const
{
  return packVec.size();
}


int PackClass::Wt( ) const
{
  int wgt = 0;
  // Calculate the weight of the pack
  int length = packVec.size();  

  for(int i = 0; i < length; ++i)
  {
     // wgt += packVec[i]->Wt();
     wgt += packVec.at(i)->Wt();
  }

  return wgt;
}


int PackClass::MaxWt( ) const
{
  return MAX_WT;
}

bool PackClass::IsEmpty( ) const
{
  return (packVec.size()==0);
}

bool PackClass::IsFull( ) const
{
  // pack is full if weight is at the MAX_WT
  return(Wt() == MAX_WT);
}

vector<string> PackClass::PackInventory( ) const
{
  // return a vector of weapon names in the pack
  vector<string> wpnNames;
  int length = packVec.size();

  for(int i = 0; i<length; ++i)
  {
    wpnNames.push_back(packVec.at(i)->NameAndNum());
  }
  
  return wpnNames;
}

void PackClass::Write(ostream & out ) const
{
  // outputs the weapons to the out ostream
  // uses Weapon::Write(out) - each on a new line.
	
  int length = packVec.size();

  for(int i = 0; i < length; ++i)
  {
    packVec.at(i)-> Write(out);
    out << endl; // may be removed
  }


}

/*

//Methods to add for iteration

Weapon& PackClass::operator[](int i)
{
  Weapon* retWep = NULL;  

  if(i <= packVec.size())
  {
    retWep = packVec.at(i);
  }
  else
  {
    retWep = *packVec.end();
  }

  return *retWep;
}

const Weapon& PackClass::operator[](int i) const
{
  Weapon* retWep = NULL;


  if(i <= packVec.size())
  {
    retWep = packVec.at(i);
  }
  else
  {
    retWep = *packVec.end();
  }

  return *retWep;
}
*/

/*

//***************************************
//**  Testing area

// loads weapons into wNames vector from input weapon files
void LoadFiles( ); 
void LoadFile(istream& fin,vector<string>& vec);
void PrintVector(ostream& fout, vector<string>&vec);

vector<string> wNames;  // stores all the range and melee weapons

int main( )
{
  const int MAXWT = 100;
  PackClass pack1(MAXWT);  
  int i;
  string wpn;
  Weapon* w;
  string tag = "";
  LoadFiles( );
  
  cout << "MaxWt:"<<pack1.MaxWt( )<<"  Wt:" <<pack1.Wt() <<endl;
  
  cout << "Size:" << pack1.Size()<<endl;
  for (int i = 0; i<wNames.size(); i++)
  {
	w = new Weapon(wNames[i]);
        tag = "";
	if (pack1.AddWeapon(w))
	   tag = "   Added";
        cout << setw(25) <<w->Name() << "  Wt:" <<setw(3)<<w->Wt() <<"\t";
	
        cout << "MaxWt:"<<pack1.MaxWt( )<<"  Wt:" <<setw(3)<<pack1.Wt() <<tag<<endl;
  }
  cout << "Wt( )=   " << pack1.Wt( ) <<endl;
  cout << "Size( )= " << pack1.Size()<<endl;

/*
// Test []
  for (int i=0; i<pack1.Size();i++)
  {
    pack1[i].Write(cout);
    cout <<endl;
  }  
  
  cout <<endl <<endl;
  
  for (int i=0; i<5;i++)
  {
    pack1[i]=Weapon(wNames[21+i]); 
  }  

  for (int i=0; i<pack1.Size();i++)
  {
    pack1[i].Write(cout);
    cout <<endl;
  }  


  cout<<endl;
  cout << "Processing removing a weapon... 5 tests"<<endl<<endl;
  
  for (int i = 0; i<5; i++)
  {
    cout << "What do you want to Remove? ";
    getline(cin,wpn);
  
    cout << "InPack(" << wpn<<")= "<< pack1.InPack(wpn)<<endl;
  
    w = pack1.RemoveWeapon(wpn);
    cout << "RemoveWeapon("<<wpn<<")= ";
    if (w == NULL) 
      cout <<"NULL - must not be in pack";
    else 
      cout <<"Removed "<< w->Name();
    cout << endl;
    cout << "Wt( )=   " << pack1.Wt( ) <<endl;
    cout << "Size( )= " << pack1.Size()<<endl;
    cout <<endl;
  }


  for (int i=0; i<pack1.Size();i++)
  {
    pack1[i].Write(cout);
    cout <<endl;
  }


  cout <<endl <<endl;
  return 0;
}


void LoadFiles( )
{
  ifstream fin;
  fin.open(RANGE_WPNS_FILE.c_str());
  LoadFile(fin, wNames);
  fin.close();
  fin.open(MELEE_WPNS_FILE.c_str());
  LoadFile(fin, wNames);
  fin.close();
  sort(wNames.begin(), wNames.end());
}

void LoadFile(istream& fin,vector<string>& vec)
{
  bool valid;
  string name;
  valid = ReadStr(fin, name);
  fin.ignore(256,'\n');
  while (fin && valid )
  {
      vec.push_back(Ucase(name));
      valid = ReadStr(fin,name);
      fin.ignore(256,'\n');
  }
}


void PrintVector(ostream& fout, vector<string>&vec)
{
  int i;
  for (i=0; i<vec.size();i++)
  {
    fout<<vec[i]<<DEL;
  }
  fout<<endl;
}
  

*/
