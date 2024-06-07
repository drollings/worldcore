#ifndef __WORLDS_HPP__
#define __WORLDS_HPP__

//
// C++ Interface: world
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "base.hpp"
#include "things.hpp"
#include <vector>

namespace Worlds
{
	typedef		std::vector< Location * >			LocationVector;

#if 0
/* 
class RadiusPlacerDef(Placer):
	singleton = None
	
	def __init__(self, scale = 1.0):
		self.scale = scale

	def __call__(self, kCenterPoint, distance, d = None):
		if not distance:
			return kCenterPoint

		fHypotenuse = distance * self.scale
		fHypotenuseSqr = fHypotenuse * fHypotenuse
		
		# Randomly determine the opposite and adjacent lengths to fit the hypotenuse of orbit distance + planet radius
		X = fHypotenuseSqr * randint(0, 100) * 0.01
		Y = sqrt(fHypotenuseSqr - X)
		X = sqrt(X)

		# Now randomize the quadrants along the X and Z axes
		if randint(0, 100) > 50:	X = X * -1.0
		if randint(0, 100) > 50:	Y = Y * -1.0

		# point.SetXYZ(X + kCenterPoint.x, Y + kCenterPoint.y, Z + kCenterPoint.z)
		point = Units.Point()
		point.x = X + kCenterPoint.x
		point.y = Y + kCenterPoint.y
		# point.z = Z + kCenterPoint.z
		point.z = kCenterPoint.z

		return point
*/
#endif

	class Zone;
	
	extern ::Base::Proximity				*proximityToWorld;
	extern ::Base::Proximity				*proximityLocationToLocation;

	struct LocationState
	{
												LocationState(void) : inside(0), species(0)  {}
		IDNum									inside;
		IDNum									species;
	};

	
	class Location : public Base::Element, public Base::Holds, public Base::HasID
	{
	private:
		Location								*_parent;
		LocationVector							_children;
		LocationState							_locationState;
		Zone									*_zone;
		Base::Proximity							*_prox;
		
	public:
	
												Location(const char * = "Unnamed location", IDNum = 0);
		virtual									~Location(void);

		::Base::Element *						Clone(void) const;

		virtual UInt8							GetGenus(void) const;
		virtual IDNum							GetSpecies(void) const		{	return _locationState.species;	}

		virtual void							Extract(void);

		virtual const ::Base::Proximity *		InProximity(void) const;
		virtual const Location *				InLocation(void) const;
		virtual const ::Base::Proximity *		DefaultProximity(void) const;
	};


	class Zone : public Location
	{
	public:
		std::list<IDNum>						owners;
		bool									approved;
	};


	class World : public Location
	{
	private:
		unsigned long long						lastPulse;
		UInt32									numBeats;
		IDNum									maxID;
		Location								*rootNode;

	public:
												World(void);
												~World(void);

		virtual UInt8							GetGenus(void) const;
		virtual IDNum							GetSpecies(void) const;

		// virtual SInt32						Receive(Base::Element &, Base::Proximity * = proximityToWorld);
		// virtual SInt32						Remove(Base::Element &, Base::Proximity * = proximityToWorld);
		// virtual void							Extract(void);

		virtual void							Initialize(void);
		virtual void							Pulse(void);

		virtual Things::Thing *					Find(Flags, const char *) const;
		virtual Things::Thing *					Find(IDNum) const;

		IDThingMap								hCreatures;
		IDThingMap								hObjects;
		IDThingMap								hRooms;
	};

	extern int	Init(void);
	
	extern	World world;	
}

#endif	// __WORLD_HPP__
