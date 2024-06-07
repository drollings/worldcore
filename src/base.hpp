#ifndef __BASE_HPP__
#define __BASE_HPP__

//
// C++ Interface: base
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


// This file provides the basic APIs for the MUD core.  The abstract classes appear here,
// with the guts of their APIs implemented elsewhere.  A major design objective is to make
// things accessible to the Python scripting layer while handling all the CPU-intense
// parts here.

// One benefit to using abstract classes here is that the individual cpp files can
// make their own derived classes without requiring a recompile of everything else.


// ************************************************************************************
// Base classes:
// Named - has a string name
// HasKeywords - has a number of strings to match

// Proximity - defines sparse relationships with a broker object pointed to
// Methods - Polymorphic virtual tables of member objects
// Properties - Small stubs of member data contained in unions

#include "macros.hpp"
#include "typedefs.hpp"
#include "properties.hpp"
#include "Templates/sorted_node_vector.hpp"
#include "gen-cpp/base_types.h"


namespace Base
{
	extern const char *sNullString;

	extern const Proximity *proximityInside;
	extern const Proximity *proximityPeople;
	extern const Proximity *proximityEquipped;
	extern const Proximity *proximityLocation;
	extern const Proximity *proximityPropertyOf;
	extern const Proximity *proximitySought;
	extern const Proximity *proximityRemembered;
	extern const Proximity *proximityTargeted;
	extern const Proximity *proximityAffecting;
	extern const Proximity *proximityConcentrating;
	extern const Proximity *proximityFollowing;
	extern const Proximity *proximityStalking;
	extern const Proximity *proximityMemberOf;
	extern const Proximity *proximityListener;

	extern std::vector<const Proximity *>	proximityList;

	//########################################################################
	// Generic base class for Named objects
	class Named
	{
	public:
											Named(const char * = NULL)			{										}
		virtual								~Named(void) 						{										}
		
		virtual const char *				GetName(void) const					{	return (GetClassName());			}
		virtual void 						SetName(const char *s)				{	return;								}
		virtual bool						Match(const char *s)				{	return strcmp(s, GetClassName());	}

	private:
		// Prevent cross-assignment between incompatible types.
		Named &								operator=(const Named &);
	
	protected:
		virtual const char *				GetClassName(void) const			{	return "Named";		}
	};
	
	//########################################################################
	// Generic base class for Named objects
	class HasKeywords
	{
	public:
											HasKeywords(const char * = NULL) {}
		virtual								~HasKeywords(void) {}
		
		virtual const char *				GetKeywords(void) const				{	return "";		}
		virtual void						SetKeywords(const char *s)			{					}	// FIXME
		virtual bool						MatchKeywords(const char *s)		{	return false;	}

	private:
		// Prevent cross-assignment between incompatible types.
		HasKeywords &						operator=(const Named &);
	};
	
	class HasID
	{
	public:
											HasID(void)	{}
											HasID(IDNum id)	: m_ID(id) {}
		virtual								~HasID(void) {}
		
	public:
		virtual void						SetID(IDNum id)				{	m_ID = id;	}
		IDNum								GetID(void) const			{	return m_ID;	}
	
	private:
		// Prevent cross-assignment between incompatible types.
		HasID &								operator=(const HasID &);

		IDNum								m_ID;

		DECLARE_MEMBER_COMPARISON_OPERATORS(HasID, IDNum, m_ID)	
	};

	//########################################################################
	// Base interface for lazy-evaluated objects.
	class LazyEval
	{
	public:
											LazyEval(time_t t) : m_lastAccess(t) {};
		virtual 							~LazyEval(void) = 0;
		virtual void						LazyEvaluation(UInt32 &) = 0;
		
	private:
		time_t								m_lastAccess;
	};
	
	//####################################################################
	// Generic middleman for relationships between Holds and Elements.
	// The proximity object handles the actual insertion into data structures,
	// not the Holds, because proximities can vary.
	class Proximity : public Named, public HasID
	{
	public:
											Proximity(const char * = "Unnamed proximity", IDNum = 0);
		virtual 							~Proximity(void);

		virtual ElementList *				GetElementList(const Holds &) const;
		virtual ThingList *					GetThingList(const Holds &) const;
		
		virtual SInt32						Add(Holds &, Element &) const;
		virtual SInt32						Remove(Holds &, Element &) const;

		virtual const char *				GetClassName(void) const			{	return "Proximity";		}

	private:
		// Prevent cross-assignment between incompatible types.
		Proximity &							operator=(const Proximity &);
	};
	

	//########################################################################
	// The Element is a generic interface for containable objects.
	class Element : public Named
	{
	public:
											Element(void);
											Element(const char *);
		virtual 							~Element(void);

		// virtual Element *					Clone(void) const = 0;


		virtual void						Purge(void);
		virtual void						Extract(void);

		virtual const Proximity *			DefaultProximity(void) const;
		virtual const Proximity *			InProximity(void) const { return DefaultProximity(); }

		virtual SInt32						To(Holds &, const Proximity * = NULL);
		virtual SInt32						From(Holds * = NULL, const Proximity * = NULL); 

		virtual UInt8						GetGenus(void) const { return 0; }
		virtual IDNum						GetSpecies(void) const { return 0; }

		virtual const char *				GetClassName(void) const			{	return "Element";		}

		// This generator method allows creation of objects with the Genus, the IDNum of the ancestor, and an optional int switch parameter.
		static Element *					Generate(IDNum = 0, IDNum = 0, int = 0);

	private:
		// Prevent cross-assignment between incompatible types.
		Element &							operator=(const Element &);
	};


	//####################################################################
	// The Holds is a generic interface for objects that can contain other objects.
	class Holds
	{
	private:
		ProximityElementMap					m_dElements;

	public:
											Holds(void) {};
		virtual 							~Holds(void) {};

		virtual SInt32						Receive(Element &, const Proximity *);
		virtual SInt32						Remove(Element &, const Proximity *);
		virtual void						Extract(void);

		virtual ElementList *				GetElementsInProximity(const Proximity *);
		virtual ThingList *					GetThingsInProximity(const Proximity *);
		// virtual const Element *				Has(int, const char *);
		
		friend class						Proximity;
	};

	extern const char 						*genusStrings[];

	class Method : public HasID, public Element
	{
	public:
											Method(void);
		virtual								~Method(void);

		virtual const char *				GetName(void) const					{	return m_Name.c_str();				}
		virtual void 						SetName(const char *s)				{	m_Name = s;					}
		virtual bool						Match(const char *s)				{	return strcmp(s, m_Name.c_str());		}
		
	private:
		String								m_Name;
	public:
		virtual const ::Base::Proximity *	DefaultProximity(void) const;
		Method &							operator=(const Method &);
	};
	

	typedef Templates::sorted_node_vector<IDNum, Method>	MethodList;
	typedef Templates::sorted_node_vector<IDNum, Properties::PropertyData> PropertyList;

	class Propertied
	{
	private:
		// PropertyList						_lProperties_;		// The compact structs of properties
		Flags								_property_flags_;
		Properties::PropertyStruct			*_lProperties_;
		
	public:
											Propertied(void) : _lProperties_(new Properties::PropertyStruct) {};
											~Propertied(void) {	delete _lProperties_;	};

		inline bool							HasProperty(IDNum f) const		{	return IS_SET(_property_flags_, (1 << f));	};
		Properties::PropertyData *			GetProperty(IDNum) const;
	};


	extern int	Init(void);
}

namespace Signal
{
	//####################################################################
	class Signal
	{
	public:
		virtual								~Signal(void) = 0;

											// Parameters:  To, Flags, From, To Location, From Location, integer modifier, string modifier
		virtual int							Send(Things::Thing *, Flags, Things::Thing * = NULL, Worlds::Location * = NULL, Worlds::Location * = NULL, int = 0, const char * = NULL) = 0;
	};

	class Listener : public ::Base::Element
	{
	public:
											Listener(void) {};
		virtual								~Listener(void) = 0;
	};

}

#endif	// __BASE_HPP__
