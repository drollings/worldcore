#ifndef __PROPERTIES_HPP__
#define __PROPERTIES_HPP__

//
// C++ Interface: property
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "typedefs.hpp"
#include "macros.hpp"
#include "Templates/sorted_node_vector.hpp"

#include "gen-cpp/propertytypes_types.h"

#define GET_PROPERTY(thing, type)		(Properties:: type *)(thing->GetProperty(PropertyTypes:: type ))
#define HAS_PROPERTY(thing, type)		(thing->HasProperty(PropertyTypes:: type ))

namespace Base
{
	class Proximity;
}

namespace Properties
{
	struct Openable
	{
		IDNum		key;				// Individual
		IDNum		skill;
		int			difficulty;
	};

	struct Exit 
	{
		IDNum		toThing;			// Individual
		IDNum		fromThing;			// Individual
		SInt16		metersWide;
		SInt16		theta;
	};

	struct Ingestable 
	{
	 	SInt8 modHunger;
		SInt8 modThirst;
		SInt8 modDrunk;
	};

	struct Poison 
	{
		SInt8 severity;
		UInt8 duration;
		Flags affects;
	};

	struct Light 
	{
		SInt16	hours;					// Individual
		bool	lit;
	};

	struct Tool
	{
		Flags useHow;
		IDNum skill;
		SInt16 charges;					// Individual
	};

	struct Stats
	{
		SInt8			strength;
		SInt8			health;
		SInt8			agility;
		UInt8			position;

		SInt8			movement;
		SInt8			vision;
		SInt8			hearing;
		SInt8			scent;

		SInt8			intellect;
		SInt8			will;
		SInt8			awareness;
		SInt8			focus;

		SInt8			courage;
		SInt8			disposition;
		SInt8			mood;
		SInt8			erratic;

		UInt8			state;
		SInt8			hunger;
		SInt8			thirst;
		SInt8			drunk;

		Flags			m_Mind;
		IDNum			bodyType;
		Skills::SkillStore		*skills;
	};
	
	struct Living
	{
		Flags			genes[2];
	};

	struct Saving
	{
	};

	struct Misfire 
	{
		IDNum			vnum;		// 
	};

	struct Concentrate 
	{
		// Base::Message			* wearoff;
		// Base::Trigger			* trig;
		SInt16	interval;
		SInt16	costHit;
		SInt16	costMana;
		SInt16	costMovement;
	};

	struct Decay
	{
		UInt32 time;				// Individual
	};


	struct Money 
	{	
		double	value;
	};

	struct Container 
	{
		Flags	flags;
		SInt16	maxWeight;
		SInt8	pick_modifier;
		IDNum	scabbardOf;
	};

	struct Mountable 
	{
		Flags flags;
		SInt16 maxCarry;
	};

	struct Armor 
	{
		UInt8 chartnum;
		SInt8 shieldBonus;
	};


	struct Missile 
	{
		SInt8 proficiency;
		SInt8 toHit;
		SInt8 damBonus;
		SInt8 damType;
	};


	struct FireWeapon 
	{
		IDNum skill;
		SInt8 toHit;
		SInt8 damBonus;
		SInt8 damType;
		UInt16 ammo;	// Individual
		UInt16 maxAmmo;
		SInt8 range;
		SInt8 speed;
	};

	struct Weapon 
	{
		IDNum skill;

		SInt8 swingToHit;
		SInt8 swingBonus;
		SInt8 swingDamType;
		SInt8 swingSpeed;

		SInt8 thrustToHit;
		SInt8 thrustBonus;
		SInt8 thrustDamType;
		SInt8 thrustSpeed;

		SInt8 parrySpeed;
		SInt8 parryBonus;
		SInt8 range;
	};


	union PropertyData
	{
	public:
		Openable			_Openable_;
		Exit				_Exit_;
		Ingestable			_Ingestable_;
		Poison				_Poison_;
		Light				_Light_;
		Tool				_Tool_;
		Weapon				_Weapon_;
		FireWeapon			_FireWeapon_;
		Missile				_Missile_;
		Armor				_Armor_;
		Container			_Container_;
		Mountable			_Mountable_;
		Decay				_Decay_;
		Money				_Money_;
		Stats				_Stats_;
	};

	struct PropertyStruct
	{
	public:
		Openable			_Openable_;
		Exit				_Exit_;
		Ingestable			_Ingestable_;
		Poison				_Poison_;
		Light				_Light_;
		Tool				_Tool_;
		Weapon				_Weapon_;
		FireWeapon			_FireWeapon_;
		Missile				_Missile_;
		Armor				_Armor_;
		Container			_Container_;
		Mountable			_Mountable_;
		Decay				_Decay_;
		Money				_Money_;
		Stats				_Stats_;
	};

}


#endif	// __PROPERTIES_HPP__
