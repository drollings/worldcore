//
// C++ Implementation: world
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "worlds.hpp"
#include "properties.hpp"

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;
using namespace Base;
using namespace Things;

namespace Worlds
{
	class Location;
	class World;

	class ProximityLocation : public Proximity
	{
	public:
								ProximityLocation(const char *n)  : Proximity(n) {};
		virtual 				~ProximityLocation(void) {};

		#if 0
		virtual SInt32			Add(Base::Holds &host, Base::Element &obj)
		{
			if (Proximity::Add(host, obj)) {
				// FIXME - Need coordinate information being filled in here.
			} else {
				return 0;
			}
			return 1;
		};

		virtual SInt32			Remove(Base::Holds &host, Base::Element &obj)
		{
			if (Proximity::Remove(host, obj)) {
				// FIXME - Need coordinate information being filled in here.
			} else {
				return 0;
			}
			return 1;
		};
		#endif
		
		friend class Location;
	};
	
	const Proximity *	Location::DefaultProximity(void) const	
	{
		return proximityLocation;
	}
	
	const Proximity *	Location::InProximity(void) const
	{
		return proximityLocation;
	}



	//########################################################################
	// For the Location class
	
	Location::Location(const char *name, IDNum id) : Element(), HasID(id), _parent(NULL), _zone(NULL), _prox(NULL) {}
	Location::~Location(void) {}
	
	void Location::Extract(void)
	{
		LocationVector::iterator	iter;
		if (_parent && _children.size() > 0) {
			iter = _children.begin();

			while (iter != _children.end()) {
				(*iter)->From();
				(*iter)->To(*_parent);
				iter = _children.begin();
			}
		}

		if (_parent) {
			LocationVector				&lp = _parent->_children;
			iter = lp.begin();

			while (iter != lp.end()) {
				if (*iter == this) {
					lp.erase(iter);
					break;
				}
				++iter;
			}
		}
		
	}
	
	const Location *	Location::InLocation(void) const	{	return _parent ? _parent : this;			}
	// Base::Entity::Element * Location::InZone(void) const	{	return inside->InZone();	}
	UInt8				Location::GetGenus(void) const			{	return ::Genus::LOCATION;		}

	Element *	Location::Clone(void) const
	{
		Location *l = new Location;
		l->_zone = _zone;
		l->_locationState = _locationState;
		return l;
	}

	//########################################################################
	// For the World class
	World::World(void) : Location("The World"), lastPulse(0), numBeats(0), rootNode(new Location("The center of the universe"))
	{
	}
	
	World::~World(void) 
	{
		delete rootNode;
		rootNode = NULL;
	}

	UInt8				World::GetGenus(void) const			{	return Genus::WORLD;		}
	IDNum				World::GetSpecies(void) const		{	return 0;					}
	
	void	World::Initialize(void)
	{
		// FIXME
	}

	void	World::Pulse(void)
	{
		// FIXME
	}

	Thing *	World::Find(Flags f, const char *arg) const
	{
		// FIXME
		return NULL;
	}

	Thing *	World::Find(IDNum idnum) const
	{
		// FIXME
		return NULL;
	}
	
	int	Init(void)
	{
		proximityLocation = new ProximityLocation("Location");

		return 1;
	}

	World world;	
	
}

