#ifndef __TYPEDEFS_HPP__
#define __TYPEDEFS_HPP__

//
// C++ Interface: typedefs
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <cstring>
#include <string>
#include <map>
#include <list>
#include <list>
#include <stdint.h>

#include "gen-cpp/typedefs_types.h"

#include "Templates/SharedPtr.h"	// For now we're using Chris Jacobson's SharedPtr

//	Basic Types
typedef signed char SInt8;         /* 8 bit signed */
typedef unsigned char UInt8;      /* 8 bit unsigned */
typedef short SInt16;              /* 16 bit signed */ 
typedef unsigned short UInt16;    /* 16 bit unsigned */
typedef int SInt32;                /* 32 bit signed */  
typedef unsigned int UInt32;      /* 32 bit unsigned */

// typedef signed long long SInt64;      /* 64 bit unsigned */
typedef unsigned long long UInt64;      /* 64 bit unsigned */

// These are general-purpose typedefs.
typedef		void *						Ptr;
typedef		UInt32						IDNum;
typedef		SInt32						VNum;
typedef		SInt32						Flags;

typedef 	unsigned long				CRC32;
typedef 	unsigned long				Hash;
typedef 	unsigned short				Hash16;

typedef		std::string					String;
typedef		std::shared_ptr<String>		SString;


#ifndef NULL
#define NULL							nullptr
#endif	// NULL

#include "gen-cpp/base_types.h"
#include "gen-cpp/genus_types.h"
#include "gen-cpp/pronouns_types.h"
#include "gen-cpp/proximities_types.h"


//########################################################################
// Class forward declarations

namespace Base
{
    class Named;
    class HasKeywords;
    class HasID;
    class Element;
	class Holds;
	class Proximity;
	class Method;
	class Propertied;
}

namespace Affects
{
    class Affect;
}

namespace Things
{
	class Thing;
}

namespace Editing
{
	class Editor;
    class Editable;
    class Accessor;
	class Constraint;
}

namespace Events
{
	class Event;
}

namespace Worlds
{
	class Location;
	class World;
}

namespace Properties
{
	class Property;
	union PropertyData;
	struct PropertyStruct;
}

namespace Skills
{
	class SkillStore;
	class Skill;
}

class Path;

// These typedefs are based on above declarations, and need to be at the end.

typedef		std::list< Affects::Affect *>	AffectList;
typedef		std::list< Events::Event *>		EventList;
typedef		std::list< Base::Element * >	ElementList;
typedef		std::map< int, ElementList >			ProximityElementMap;	// genus to elementlist
typedef		std::list< Things::Thing *>		ThingList;
typedef		ThingList *								ThingListPointer;
typedef		std::map< int, ThingList >				ProximityThingMap;
typedef		std::map< IDNum, Things::Thing * >		IDThingMap;

typedef 	bool (*PredicateElement)(Base::Element *);
typedef 	bool (*PredicateNamedString)(Base::Named *, const char *);
typedef 	bool (*PredicateHasKeywordsString)(Base::HasKeywords *, const char *);
typedef 	bool (*PredicateThing)(Things::Thing *);
typedef 	bool (*PredicateThingThing)(Things::Thing *, Things::Thing *);
typedef 	bool (*PredicateThingThingString)(Things::Thing *, Things::Thing *, const char *);


#endif	// __TYPEDEFS_HPP__
