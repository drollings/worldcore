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

#include "properties.hpp"
#include "editing.hpp"
#include "worlds.hpp"

using namespace std;

namespace Properties
{
	const char * propertyNameStrings[] = {
		"Openable",
		"Exit",
		"Ingestable",
		"Poison",
		"Light",
		"Tool",
		"Weapon",
		"FireWeapon",
		"Missile",
		"WeaponContainer",
		"Armor",
		"Container",
		"Mountable",
		"Decay",
		"Money",
		"Stats",
		"\n"
	};

	class Property : public ::Base::Element
	{
	public:
											Property(void);
		virtual								~Property(void);

	private:
		// Prevent cross-assignment between incompatible types.
											Property(Property &) {};
		Property &							operator=(const Property &) {	return *this;	};

	public:
		virtual const char *				Name(void) = 0;
		virtual SInt32 						Type(void) = 0;
		
		virtual const Base::Proximity *		DefaultProximity(void) const	{	return Base::proximityPropertyOf;	}
	};


	void Init(IDNum type, PropertyData &data) 
	{
	}
	
	void Init(Stats &data) 
	{
		data.strength = 10;
		data.health = 10;
		data.agility = 10;
		data.position = 0;
		data.movement = 5;
		data.vision = 10;
		data.hearing = 10;
		data.scent = 10;
		data.intellect = 10;
		data.will = 10;
		data.awareness = 10;
		data.focus = 10;
		data.disposition = 50;
		data.mood = 50;
		data.erratic = 0;
		data.state = 0;
		data.hunger = 0;
		data.thirst = 0;
		data.drunk = 0;
		data.m_Mind = 0;
		data.bodyType = 0;
		data.skills = NULL;
	}


}

