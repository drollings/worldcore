#ifndef __SKILLS_HPP__
#define __SKILLS_HPP__

//
// C++ SInterface: skills
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

#include "macros.hpp"
#include "things.hpp"
#include "Templates/sorted_node_vector.hpp"
#include "gen-cpp/skills_types.h"

#define SKILL_NOCHANCE -120
#define SKILL_CRIT_SUCCESS 100
#define SKILL_CRIT_FAILURE -100
#define SKILL_MAX_DEFAULTS 8
#define SKILL_MAX_PREREQS 8
#define SKILL_MAX_ANREQS 4

namespace Skills
{
	class Skill;
	

	//####################################################################
	struct SkillRef
	{
		SInt16					skillNum;
		SInt8					chance;
	};
	// This macro declares ge/lt/eq functions for the above based on skillNum
	DECLARE_KEY_COMPARISON_OPERATORS(SkillRef, SInt16, skillNum)	

	//####################################################################
	struct SkillKnown
	{
		SInt16					skillNum;
		SInt8					proficient;
		SInt8					theory;
	};
	// This macro declares ge/lt/eq functions for the above based on skillNum
	DECLARE_KEY_COMPARISON_OPERATORS(SkillKnown, SInt16, skillNum)	

	//####################################################################
	class Skill : public ::Base::Named
	{
	public:
										Skill(const char *);
		virtual 						~Skill(void);

		// static const char *				Name(IDNum);
    	// static IDNum        			Number(const char *name, int type = 0xFFFFFFF);

	public:
		IDNum							_ID;

		SInt32	   						_typeFlags;
		SInt32		   					_statFlags;		 //  Stats Used   
		SInt32							_targetFlags;	   //  Valid Targets
		SInt32	   						_positionFlags;
		SInt32	   						_stateFlags;
		SInt32		   					_routines;

		UInt16  						_delay;
		UInt16	  						_lag;
		UInt16				  			_mana;
		UInt8							_violence;
		UInt8							_helpfulness;
		UInt8							_numPrereqs;		// How many of the prerequisites must be satisfied
		
		UInt8							_maxincr;			// For stats, this is the cost of each point
		SInt8							_startMod;
		
		SkillRef						defaults[SKILL_MAX_DEFAULTS];
		SkillRef						prereq[SKILL_MAX_PREREQS];
		SkillRef						anreq[SKILL_MAX_ANREQS];
		
	public:
		inline bool						IsLearnable(void) const		{	return IS_SET(_typeFlags, LEARNABLE);	}
		inline bool						IsStat(void) const			{	return IS_SET(_typeFlags, STAT);		}
		inline bool						IsType(SInt32 f) const		{	return IS_SET(_typeFlags, f);			}
		inline bool						IsValid(void) const			{	return _typeFlags != 0;						}
		inline bool						IsBasedOn(SInt32 f) const	{	return IS_SET(_statFlags, f);			}
	};


	extern Base::Proximity * proximitySkillStore;

	class SkillStore : public Base::Element
	{
	public:
		// Functions to acquire
		virtual void FindSkill(const Skill &, SkillKnown **) const = 0;
		int GetSkillMod(const Skill &, SkillKnown *) const;
		int GetSkillPts(const Skill &, SkillKnown *) const;
		int GetSkillTheory(const Skill &, SkillKnown *) const;
		int CheckSkillPrereq(Things::Thing &, const Skill &) const;
		int GetSkillChance(Things::Thing &, const Skill &, SkillKnown *, SInt8 = 0) const;
		
        // virtual void            Purge(void);
        // virtual void            Extract(void);

		virtual UInt8			Genus(void) const;
		virtual IDNum			Species(void) const;

		virtual Base::Proximity *		InProximity(void) const;
		
		// virtual bool						HasProperty(int) const		{	return 0;		}
		// virtual const Properties::Property *	GetProperty(int) const		{	return NULL;	}
		// virtual Properties::Property *		IsolateProperty(int)		{	return NULL;	}

		void SetSkill(const Skill &, SkillKnown * = NULL, UInt8 = 1, UInt8 = 0);
		virtual void AddSkill(const Skill &, SkillKnown * = NULL, UInt8 = 1, UInt8 = 0) = 0;
		virtual void RemoveSkill(const Skill &) = 0;
		void LearnSkill(const Skill &, SkillKnown * = NULL, SInt8 = 1);
		void LearnTheory(const Skill &, SkillKnown * = NULL, SInt8 = 1);
		// int LearnSkill(Things::Thing &, const Skill &, SkillKnown *i = NULL, SInt16 = 1);
		// int SetSkill(Things::Thing &, IDNum = 0, SkillKnown *i = NULL, UInt8 = 0, UInt8 = 0);

		void FindBestRoll(Things::Thing &, const Skill &, const Skill **, SInt8 &, SInt8 &, int = 0);
		int RollSkill(Things::Thing &, const Skill &);
		int RollSkill(Things::Thing &, const Skill &, SInt8);
		int RollSkill(Things::Thing &, const Skill &, const Skill *, SInt8);
		int RollSkill(Things::Thing &, SkillKnown *);
		void SkillContest(Things::Thing &, const Skill &, SInt8, Things::Thing &, const Skill &, SInt8, SInt8 &, SInt8 &, int &, int &);
		// int LoadSkills(FILE *infile, int nr);
		// int SaveSkills(FILE *outfile);
		virtual int TotalPoints(SInt32) = 0;
		virtual int TotalTheory(SInt32) = 0;
		void ClearSkills();
		IDNum FindBestDefault(Things::Thing &, SInt16 &,SInt8 &, SInt8 &, SInt8 chkdefault);
		int RollToLearn(Things::Thing &, const Skill &, int, SkillKnown * = NULL);
		
		static SkillStore *	Generate(int = 0);
	};
	
	
	class SkillStoreKnown : public SkillStore
	{
	private:
		Templates::sorted_node_vector<SInt16, SkillKnown>	lSkillsKnown;
		
	public:
		virtual void FindSkill(const Skill &skl, SkillKnown **ptr) const {
			*ptr = const_cast<SkillKnown *>(lSkillsKnown.GetByKey(skl._ID));
		}
		virtual void AddSkill(const Skill &, SkillKnown * = NULL, UInt8 = 1, UInt8 = 0) {
		}
		virtual int TotalPoints(SInt32);
		virtual int TotalTheory(SInt32);
	};




	#define GETBODYSTAT(_ch, _stat) \
	{ \
		const Properties::Animate	*bodyPtr = GET_PROPERTY(_ch, Animate); \
		if (bodyPtr)		return (bodyPtr->_stat); \
	}
	
	#define GETMINDSTAT(_ch, _stat) \
	{ \
		const Properties::Mind	*mindPtr = GET_PROPERTY(_ch, Mind); \
		if (mindPtr)		return (mindPtr->_stat); \
	}
	
	inline Skill *			GetSkill(int skillnum);

	int 			PointsToMod(const Skill &, UInt8 );
	int 			ModToPoints(const Skill &, SInt8 );

	// extern std::vector < Skill >		skills;
}


#endif	// __SKILLS_HPP__
