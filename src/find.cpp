//
// C++ Implementation: find
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "find.hpp"
#include "properties.hpp"
#include "things.hpp"


#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;
using namespace Base;
using namespace Things;


	Element *			Find(ElementList &l, const char * c) 
	{
		ElementList::iterator i;
		Element *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (e->GetName() == c) {
				return e;
			}
			return e;
		}
		return NULL;
	}

	Thing *			Find(ThingList &l, const char *c)
	{
		ThingList::iterator i;
		Thing *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (e->GetName() == c) {
				return e;
			}
			return e;
		}
		return NULL;
	}

	Thing *			FindByID(ThingList &l, IDNum n)
	{
		ThingList::iterator i;
		Thing *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (e->GetID() == n)	return e;
		}
		return NULL;
	}

	Thing *			FindBySpecies(ThingList &l, IDNum n)
	{
		ThingList::iterator i;
		Thing *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (e->GetSpecies() == n)	return e;
		}
		return NULL;
	}

	Thing *			FindByProperty(ThingList &l, IDNum n)
	{
		ThingList::iterator i;
		Thing *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (e->HasProperty(n))	return e;
		}
		return NULL;
	}

	Thing *			FindByThingFlag(ThingList &l, Flags f)
	{
		ThingList::iterator i;
		Thing *e;
		
		for (i = l.begin(); i != l.end(); ++i) {
			e = *i;
			if (IS_SET(e->m_ThingFlags, f))	return e;
		}
		return NULL;
	}

	Thing *			FindByPredicateThing(ThingList &l, PredicateThing f)
	{
		ThingList::iterator i;
		
		for (i = l.begin(); i != l.end(); ++i) {
			if ((*f)(*i))	return *i;
		}
		return NULL;
	}


	Thing *			FindByPredicateThingThing(ThingList &l, PredicateThingThing f, Thing &t)
	{
		ThingList::iterator i;
		
		for (i = l.begin(); i != l.end(); ++i) {
			if ((*f)(*i, &t))	return *i;
		}
		return NULL;
	}


