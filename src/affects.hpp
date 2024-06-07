#ifndef __AFFECTS_HPP__
#define __AFFECTS_HPP__

//
// C++ SInterface: affects
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <bitset>
#include "typedefs.hpp"
#include "base.hpp"

enum AffectFlag
{
    AFF_BLIND,
    AFF_INVISIBLE,
    AFF_INVISIBLE_2,
    AFF_SENSE_LIFE,
    AFF_DETECT_INVIS,
    AFF_SANCTUARY,
    AFF_GROUP,
    AFF_FLYING,
    AFF_INFRAVISION,
    AFF_POISON,
    AFF_SLEEP,
    AFF_NOTRACK,
    AFF_SNEAK,
    AFF_HIDE,
    AFF_CHARM,
    AFF_MOTIONTRACKING,
    AFF_SPACESUIT,
    AFF_LIGHT,
    AFF_TRAPPED,
    AFF_STUNNED,
    AFF_ACIDPROOF,
    AFF_BLEEDING,
    AFF_NORECALL,
    AFF_GROUPTANK,
    AFF_COVER,
    AFF_TRAITOR,
    AFF_NOAUTOFOLLOW,
    AFF_DYING,
    AFF_DIDFLEE,
    AFF_DIDSHOOT,
    AFF_NOSHOOT,
    AFF_NOQUIT,
    AFF_RESPAWNING,
    NUM_AFF_FLAGS
};	


namespace Affects
{
	typedef std::bitset<NUM_AFF_FLAGS> AffectFlags;

    static const AffectFlags AFF_NO_FLAGS;
    static const AffectFlags AFF_INVISIBLE_FLAGS;
    static const AffectFlags AFF_STEALTH_FLAGS;

	//####################################################################
	// Paired with HasAccessors Bases, an affect provides a way to temporarily affect something
	class Affect : public Base::Element
	{
	protected:
		::Events::Event			*event;

	public:
						Affect(::Events::Event *evt = NULL) : event(evt) {};
						~Affect(void) {};

		// Base::Element overrides
		virtual const ::Base::Proximity *			DefaultProximity(void) const { return ::Base::proximityAffecting;	}
		virtual UInt8								GetGenus(void) const { return Genus::AFFECT; }
		virtual IDNum								GetSpecies(void) const { return 0; }
		
		virtual SInt16				GetOffset(void) const	{	return 0;		}
		virtual SInt16				GetModifier(void) const	{	return 0;		}
		virtual AffectFlags			GetFlags(void) const	{	return AFF_NO_FLAGS;	}
		
		virtual ::Events::Event *	GetEvent(void) const	{	return NULL;	}
		virtual ::Things::Thing *	GetCausedBy(void) const	{	return NULL;	}
		
    	void			PauseTimer();
    	void			ResumeTimer(Things::Thing *ch);

		static Affect *				Generate(SInt16 = 0, SInt16 = 0, const AffectFlags & = AFF_NO_FLAGS, ::Events::Event * = NULL, ::Things::Thing * = NULL, IDNum = 0);
	};
}

#endif
