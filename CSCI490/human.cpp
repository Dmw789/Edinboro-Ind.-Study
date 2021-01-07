//
// Dylan Whitehead
//
// CSCI 330 Section 1
// Spring 2019
// Program # 5
// 
// Narrative: A derived child class of PlayerClass. Assumes all methods and data publicly from PlayerClass and adds a new version of Write(). 
// Meant to serve as a gateway parent class for any other player type that falls under the same category. Any and all functions/variables that 
// are consistently used by all Human types but not by all Human AND human types are to be put in this class to avoid redundancy.
// Almost all implementation currently revolves around passing the flow of control to PlayerClass. Any implementation added should first be checked
// against PlayerClass to see if it would be better used more abstractly or if it is too redundant.
// 
// Special Notes: 
//
//


#include "human.h"
using namespace std;

//ASSIGN STATIC CONSTS
const int Human::DEFAULT_SKILL = 1;
const int Human::DEFAULT_WT_MULTIPLIER = 10;
const int Human::MAX_HUMAN_IMPACT_POWER = 12;
const int Human::MIN_HUMAN_IMPACT_POWER = 2;
const int Human::DEFAULT_HUMAN_IMPACT_DIE = 2;
const int Human::DEFAULT_HUMAN_IMPACT_FACE = 6;


Human::Human() : PlayerClass("NAME", NULL, NULL),
				 PACK(new PackClass(0)),
				 currWeapon(NULL)

{
	throw GameSpace:: INVALID_MISC;
}


Human::Human(const string NAME, const int C_STATS[], const int V_STATS[]): PlayerClass(NAME, C_STATS, V_STATS),
																		   PACK(new PackClass(PackWeight())),
																		   currWeapon(NULL)

{
	
}


Human::Human(const Human& h): PlayerClass(h),
							  PACK(new PackClass(*h.PACK)),
							  currWeapon(NULL)

{
	Copy(h);
}


Human::~Human()

{
	delete currWeapon;
	currWeapon = NULL;
	delete PACK;
}


string Human:: WeaponName() const

{
	string wepName = "";
	if(HasWeapon())
	{
		wepName = GameSpace::Ucase(currWeapon->Name());
	}
	
	return wepName;
}


string Human:: WeaponNameAndNum() const

{
	string wepName = "";
	if(HasWeapon())
	{
		wepName = currWeapon->NameAndNum();
	}

	return wepName;
}


int Human:: WeaponSkill() const

{
	int wpnSkill = 0;
	
	if(HasWeapon())
	{
		wpnSkill = myWpns.find(WeaponName())->second;
	}
	
	return wpnSkill;
}


bool Human:: HasWeapon() const

{
	return currWeapon;
}


int Human:: PackWeight() const

{
	return(DEFAULT_WT_MULTIPLIER * RollPhysDam());
}


vector<string>Human::Pack() const

{
	return PACK->PackInventory();
}


int Human:: HitDamage() const

{
	int damage = 0;
	
	if(IsActive())
	{
		if(HasWeapon())
		{
			damage = currWeapon->RollWeaponDamage(Name()) + WeaponSkill();
		}
		else
		{
			damage = PlayerClass::HitDamage();
		}
	}
	
	return damage;
}


int Human:: Impact() const

{
	int impactAmount = 0;
	int roll = 0;
	
	if(IsActive())
	{	
		if(HasWeapon())
		{	
			roll = RollDie(GameSpace:: IMPACT, DEFAULT_HUMAN_IMPACT_DIE, DEFAULT_HUMAN_IMPACT_FACE);
			
			if(roll > 12 || roll < 2)
			{
				throw GameSpace::INVALID_ROLL;
			}
			
			if(currWeapon->Power() >= MAX_HUMAN_IMPACT_POWER)
			{
				impactAmount = LookupImpact(roll, MAX_HUMAN_IMPACT_POWER);
			}
			else if(currWeapon->Power() >= MIN_HUMAN_IMPACT_POWER)
			{
				impactAmount = LookupImpact(roll, currWeapon->Power());
			}
		}
		else
		{
			impactAmount = PlayerClass::Impact();
		}
	}

	return impactAmount;
}


Weapon::Weapon* Human:: GrabWeapon(Weapon* newWeapon)

{
	Weapon:: Weapon* prevWeapon = NULL;
	
	if(!newWeapon)
	{
		throw GameSpace::INVALID_WPN;
	}

	prevWeapon = newWeapon;
	
	if(IsActive())
	{
		if(currWeapon)
		{
			if(PACK->AddWeapon(currWeapon))
			{
				prevWeapon = NULL;
			}
			else
			{
				prevWeapon = currWeapon;
			}
		}
		else
		{
			prevWeapon = NULL;
		}
		
		currWeapon = newWeapon;
		
		if(myWpns.find(GameSpace::Ucase(newWeapon->Name())) == myWpns.end())
		{
			myWpns.insert(make_pair(GameSpace::Ucase(newWeapon->Name()), DEFAULT_SKILL));
		}
	}
	
	
	return prevWeapon;
}


Weapon:: Weapon* Human:: ChangeWeapon(string weaponName)

{
	Weapon:: Weapon* weaponToReturn = NULL;
	Weapon:: Weapon* changeWeaponTo = NULL;
	
	if(IsActive())
	{		
		if(PACK->InPack(GameSpace::Ucase(weaponName)) && GameSpace::Ucase(weaponName) != WeaponName())
		{
			changeWeaponTo = PACK->RemoveWeapon(weaponName);
			
            if(currWeapon && !PACK->AddWeapon(currWeapon))
            {
				weaponToReturn = currWeapon;
            }
			
			currWeapon = changeWeaponTo;
        }
	}
	
	return weaponToReturn;
}


Weapon:: Weapon* Human:: DropWeapon()

{
	Weapon::Weapon* weaponDrop = NULL;

	if(HasWeapon())
	{
		weaponDrop = currWeapon;
		currWeapon = NULL;
	}
	
	return weaponDrop;
}


bool Human:: ImprovedSkill(int improvement)

{
	bool improved = false;
	
	if(IsActive() && HasWeapon() && improvement > 0)
	{
		myWpns[WeaponName()] += improvement;
		improved = true;
	}
	
	return improved;
}


void Human:: Write(ostream& out) const

{
	PlayerClass::Write(out);
	
	if(HasWeapon() || !myWpns.empty())
	{
		out << '\t';
		out << WeaponNameAndNum() << "#";
		if(HasWeapon())
		{
			out << WeaponSkill();
		}
	}
	
	MapType:: const_iterator iter;
	if(!myWpns.empty())
	{
		for(iter = myWpns.begin(); iter != myWpns.end(); ++iter)
		{
			out << "#" << iter->first;
			out << "#" << iter->second;
		}
		out << endl;
	}
}


Human& Human::operator=(const Human& h)

{
	if(this != &h)
	{
		PlayerClass::operator=(h);
		*PACK = *h.PACK;
		Copy(h);
	}
	
	return *this;
}


bool Human:: IsMyEnemyCheck(const PlayerClass* p) const

{
	return(p && !(dynamic_cast<const Human*>(p)));
}


void Human:: Copy(const Human& h)

{
	if(currWeapon)
	{
		delete currWeapon;
		currWeapon = NULL;
	}
	
	if(h.currWeapon)
	{
		currWeapon = new Weapon(*(h.currWeapon));
	}
	myWpns = h.myWpns;
	
}


bool Human::Move()
{
	return MoveUnits(1);
}

