
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


#include "gurpsskills.hpp"
#include "things.hpp"
#include "properties.hpp"
#include "functions.hpp"
#include "things.hpp"
#include "stringfunctions.hpp"
#include <vector>
#include <algorithm>

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;
using namespace Base;
using namespace Things;

const int stat_cost_table[] = {
	-100,
	-80,
	-70,
	-60,
	-50,
	-40,
	-30,
	-20,
	-15,
	-10,
	0,				// 10 is norm!
	10,
	20,
	30,
	45,
	60,
	80,
	100,
	125,
	150,
	175
};


// Returns cost of a given stat level
int stat_cost(int level)
{
	int cost;

	if (level < 0)		level = 0;
	if (level > 20) 	cost = stat_cost_table[20] + (25 * (level - 20));
	else				cost = stat_cost_table[level];

	return (cost);
}

// Returns stat for a given number of points
int stat_ptlevel(int cost)
{
	int level = 0;

	while (stat_cost(level + 1) < cost)
		++level;

	return (level);
}

// This routine used to calculate the cost given a level
int generic_cost(int level, SInt16 start, SInt16 mod)
{
	int cost;

	if (level == 0) {
		return 0;
	}

	if (level < 0)		cost = ((level + 1) * mod) - start;
	else				cost = ((level - 1) * mod) + start;

	return (cost);
}

// This routine used to calculate the level given a cost
int generic_ptlevel(int cost, SInt16 start, SInt16 mod)
{
	if (cost == 0)
		return 0;

	int level = 0;
	bool negative = false;

	if (cost < 0) {
		cost = -cost;
		negative = true;
	}

	if (cost > start) {
		cost -= start;
		level = 1;
	} else {
		return 0;
	}

	level += (cost / mod);

	if (negative)
		level = -level;

	return (level);
}


namespace Skills
{
    vector < Skill >		skills;
    vector < string >		sortedSkillStrings;
    vector < SInt32 >		sortedSkillNums;

	const char *skillFlagsStrings[] = {
		"LEARNABLE",
		"STAT",
		"SKILL",
		"PRAYER",
		"COMBATMOVE",
		"WEAPONPROF",
		"LANGUAGE",
		"STEALTH",
		"MAGICROOT",
		"MAGICMETHOD",
		"MAGICTECHNIQUE",
		"MAGICSPELL",
		"ORDINATION",
		"SPHERE",
		"VOW",
		"PSI",
		"DEFAULT",
		"\n"
	};
	
	const char *skillBaseStrings[] = {
		"STR",
		"INT",
		"DEX",
		"CON",
		"VISION",
		"HEARING",
		"MOVE",
		"\n"
	};

	inline bool		ValidPosition(Thing &ch, const Skill &skill) 
	{
		const Properties::Stats	*statsPtr = GET_PROPERTY((&ch), Stats);

		if (statsPtr) {
			if (!IS_SET(statsPtr->state, skill._stateFlags))			return false;
			if (!IS_SET(statsPtr->position, skill._positionFlags))		return false;
		}
		
		return true;
	}


	class ProximitySkillStore : public ::Base::Proximity
	{
	private:
								ProximitySkillStore(const char *n)  : ::Base::Proximity(n) {};
		virtual 				~ProximitySkillStore(void) {};

	public:
		virtual SInt32			Add(Base::Holds &host, Base::Element &obj) const
		{
			Thing				*b = dynamic_cast<Thing *>(&host);
			if (!b)						return Proximity::Add(host, obj);

			SkillStore					*skillStore = dynamic_cast<SkillStore *>(&obj);
			if (!skillStore)			return 0;

			Properties::Stats			*statsPtr = GET_PROPERTY(b, Stats);
			if (!statsPtr)				return 0;

			if (statsPtr->skills)		delete statsPtr->skills;
			statsPtr->skills = skillStore;
			
			#ifdef UNITTEST
			cout << "Putting " << &obj << " in proximityID " << GetID() << endl;
			#endif
			return 1;
		};

		virtual SInt32			Remove(Base::Holds &host, Base::Element &obj) const
		{
			Thing					*b = dynamic_cast<Thing *>(&host);
			if (!b)							return Proximity::Remove(host, obj);
			Properties::Stats				*statsPtr = GET_PROPERTY(b, Stats);
			if (!statsPtr)					return 0;

			if (statsPtr->skills == static_cast<SkillStore *>(&obj))	statsPtr->skills = NULL;
			#ifdef UNITTEST
			cout << "Removing " << &obj << " in proximityID " << GetID() << endl;
			#endif
			return 1;
		};
		
		friend class SkillStore;
	};


	Base::Proximity *		SkillStore::InProximity(void) const
	{
		//FIXME
		static ProximitySkillStore *proxSkillStore = new ProximitySkillStore("proximitySkillStore");
		
		return proxSkillStore;
	}


	class SkillStoreVector : protected vector< SkillKnown >, public SkillStore
	{
	public:
		virtual void FindSkill(const Skill &, SkillKnown **) const;
		
		virtual Element *		Clone(void) const;

		virtual void AddSkill(const Skill &, SkillKnown * = NULL, UInt8 = 1, UInt8 = 0);
		virtual void RemoveSkill(const Skill &);

		virtual int TotalPoints(int = STAT | SKILL | PRAYER | COMBATMOVE | WEAPONPROF | LANGUAGE | STEALTH | MAGICROOT | MAGICMETHOD | MAGICTECHNIQUE | MAGICSPELL | ORDINATION | SPHERE | VOW | PSI);
		virtual int TotalTheory(int = STAT | SKILL | PRAYER | COMBATMOVE | WEAPONPROF | LANGUAGE | STEALTH | MAGICROOT | MAGICMETHOD | MAGICTECHNIQUE | MAGICSPELL | ORDINATION | SPHERE | VOW | PSI);
		// int LoadSkills(FILE *infile, int nr);
		// int SaveSkills(FILE *outfile);
	};


	// Rolls 3d6 for a given skill at a given chance.
	// Returns the difference between the chance and the result of the roll.
	// Returns SKILL_CRIT_SUCCESS (120) for critical successes, 
	// SKILL_CRIT_FAILURE (-120) for critical failures, 
	inline SInt8 DiceRoll(SInt8 chance)
	{
		int roll;

		Dice::Roll3d6(roll);
		
		switch (roll) {
		case 3: 
		case 4: 
			return (SKILL_CRIT_SUCCESS);		// Critical success.	We assume dumb luck.
		case 5: 
		case 6:
			return MAX(MIN(chance - roll, 100), -100);
		case 17: 
		case 18:
			return (SKILL_CRIT_FAILURE);
		}
		
		return MAX(MIN(chance - roll, 9), -9);
	}

	//####################################################################
    Skill::Skill(const char *name) : Named(name), 
		_ID(0), _typeFlags(0), _statFlags(0), _targetFlags(0), _positionFlags(0), 
		_routines(0), _delay(0), _lag(0), _mana(0), _violence(0), _helpfulness(0),
		_numPrereqs(0), _maxincr(4), _startMod(-3)
    {
        int i = 0;
        for (i = 0; i < SKILL_MAX_DEFAULTS; ++i)
        	defaults[i].skillNum = 0;
        for (i = 0; i < SKILL_MAX_PREREQS; ++i)
        	prereq[i].skillNum = 0;
        for (i = 0; i < SKILL_MAX_ANREQS; ++i)
        	anreq[i].skillNum = 0;
    }

    Skill::~Skill(void)                         {                   }
    
    // Ptr	Skill::GetPointer(int)					{	return NULL;	} //FIXME

    // const ::Editing::Constraints *
    // Skill::GetConstraints(int) const			{	return NULL; 	} //FIXME
    

	Skill *			GetSkill(int skillnum)
	{
		if (skillnum < 0 || skillnum >= skills.size())		{	return NULL;	}
		return &(skills[skillnum]);
	}
    

	//####################################################################
    inline void BarPoints(const int &chance3d6, int &result)
    {
        switch (chance3d6)
        {
        case 3:
        case 4:		result =  1; return;
        case 5:
        case 6:		result =  2; return;
        case 7:
        case 8:		result =  3; return;
        case 9:		result =  4; return;
        case 10:	result =  5; return;
        case 11:	result =  6; return;
        case 12:	result =  7; return;
        case 13:
        case 14:	result =  8; return;
        case 15:
        case 16:	result =  9; return;
        case 17:
        case 18:	result =  10; return;
        }
        result = 0; return;
    }
        
    const char *GraphSkill(int percent, int theory)
    {
        static char buf[64];
        char *pos = 0;
        int barLearned, barKnown, barRemainder, i;
        
        strcpy(buf, "&cy[");
        BarPoints(percent, barLearned);
        BarPoints(theory, barKnown);
        
        if (barLearned > barKnown) {	
        	barKnown = 0;
	} else {	
		barKnown = MAX(0, barKnown - barLearned);	
	}
        
        barRemainder = MAX(0, 10 - barLearned + barKnown);
        
	    if (barLearned) {
	        strcat(buf, "&cm");
	        pos = buf + strlen(buf);
	        for (i = barLearned;
	             i-- > 0;
	             *pos++ = '*');
	        *pos = '\0';
	    }
	
	    if (barKnown) {
	        strcat(buf, "&cb");
	        pos = buf + strlen(buf);
	        for (i = barKnown;
	             i-- > 0;
	             *pos++ = '+');
	        *pos = '\0';
	    }
	     
	    if (barRemainder) {
	        strcat(buf, "&cb");
	        pos = buf + strlen(buf);
	
	        for (i = barRemainder;
	         i-- > 0;
	         *pos++ = '-');
	        *pos = '\0';   
	    }

		strcat(buf, "&cy&c0");
		return buf;
    }

    SInt8 modToPoints2[8] = {
        1, 2, 4, 6, 8, 10, 12, 14
    };
    SInt8 pointsToMod2[24] = {
        0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11 
    };

    SInt8 modToPoints4[8] = {
        1, 2, 4, 8, 12, 16, 20, 24
    };
    SInt8 pointsToMod4[24] = {
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6
    };

    SInt8 modToPoints8[8] = {
        1, 2, 4, 8, 16, 24, 32, 40
    };
    SInt8 pointsToMod8[24] = {
        0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4
    };

	int PointsToMod(const Skill &skill, UInt8 points)
	{
	    SInt16		maxincr, mod, cost = 0;
	    
        if (points == 0)            {   return -50; }

	    maxincr = skill._maxincr;
	    mod = skill._startMod;
	    if (points == 1) 			{	return mod;	}
	    
	    switch (maxincr)
	    {
		case 2:
			if (points < 24)		{	return mod + pointsToMod2[points];	}
			points -= 24;
			mod += 12 + (points / 2);
			return mod;
			
		case 4:
			if (points < 24)		{	return mod + pointsToMod4[points];	}
			points -= 24;
			mod += 7 + (points / 4);
			return mod;
			
		case 8:
			if (points < 24)		{	return mod + pointsToMod8[points];	}
			points -= 24;
			mod += 5 + (points / 8);
			return mod;
		
		// These are for stats
		case 10:					return points / 10;
		case 20:					return points / 20;

		default:
			while ((cost += RANGE(1, cost, maxincr)) <= points)
            	mod = MIN(++mod, 120);   
	    }
	    
        return mod;	    
	}
	
	int ModToPoints(const Skill &skill, SInt8 mod)
	{
	    SInt32		maxincr, startmod, points, cost;
	    
	    #if 0
		#ifdef UNITTEST
		cout << "ModToPoints: " << int(mod) << endl;
		#endif
		#endif

	    maxincr = skill._maxincr;
	    startmod = skill._startMod;
	    if (startmod > mod)				{	return 0;	}
	    if (startmod == mod)			{	return 1;	}


	    switch (maxincr)
	    {
		case 2:
			mod -= startmod;
			if (mod < 8)		{	return modToPoints2[mod];	}
			// This is a case where we have to compute beyond eight levels of modifier
			points = modToPoints2[7] + ((mod - 7) * 2);
			break;
			
		case 4:
			mod -= startmod;
			if (mod < 8)		{	return modToPoints4[mod];	}
			// This is a case where we have to compute beyond eight levels of modifier
			points = modToPoints4[7] + ((mod - 7) * 4);
			break;
			
		case 8:
			mod -= startmod;
			if (mod < 8)		{	return modToPoints8[mod];	}
			// This is a case where we have to compute beyond eight levels of modifier
			points = modToPoints8[7] + ((mod - 7) * 8);
			break;
			
		case 10:		return mod * 10;
		case 20:		return mod * 20;

		default:
			points = 1;
			for( int i = startmod; i < mod; ++i) {
				points += MIN(points, maxincr);
			}
			break;
	    }
	    
	    return points;
	}
	

	int AverageBaseChance(Thing &ch, const Skill &skill)
	{
		IDNum chance = 0, bases = 0; 
		const Properties::Stats		*statsPtr = GET_PROPERTY((&ch), Stats);
		
		if (skill.IsBasedOn(SKLBASE_STR)) {
			if (!statsPtr) 			return SKILL_NOCHANCE;
			chance += statsPtr->strength;
			++bases;
		}
		if (skill.IsBasedOn(SKLBASE_INT)) {
			if (!statsPtr) 			return SKILL_NOCHANCE;
			chance += statsPtr->intellect;
			++bases;
		}
		if (skill.IsBasedOn(SKLBASE_AGI)) {
			if (!statsPtr) 			return SKILL_NOCHANCE;
			chance += statsPtr->agility;
			++bases;
		}
		if (skill.IsBasedOn(SKLBASE_HT)) {
			if (!statsPtr) 			return SKILL_NOCHANCE;
			chance += statsPtr->health;
			++bases;
		}
	
		if (bases)		chance /= bases;				// Average out skill bases
	
		return chance;
	}
	
	//####################################################################
	Base::Element *	SkillStoreVector::Clone(void) const
	{
		SkillStore	*clone = new SkillStoreVector(*this);
		// FIXME - copy the elements?
		return clone;
	}
	

	//####################################################################
	// Sets pointer i to a given skill.	Returns 1 if skill found, 0 if not.
	void	SkillStoreVector::FindSkill(const Skill &skill, SkillKnown **known) const
	{
		int					lower, upper, mid;
		const SkillKnown	*ptr;

		upper = size();
		if (upper == 0)		{	return;	}

		lower = 0;
		
		while (lower <= upper) {
			mid = (lower + upper) / 2;
			ptr = &(operator[](mid));
			if (skill._ID > ptr->skillNum) {
				lower = mid + 1;
			} else if (skill._ID < ptr->skillNum) {
				upper = mid - 1;
			} else {
				*known = (SkillKnown *) ptr;
			}
		}
	}
		
	// Gets the character's default modifier on a skill.	Returns -20 if not learned.
	int SkillStore::GetSkillMod(const Skill &skill, SkillKnown *known) const
	{
		if (skill.IsLearnable()) {
			if (!known)		{	FindSkill(skill, &known);					}
			if (known)		{	return PointsToMod(skill, known->proficient);	}
		}
		return SKILL_NOCHANCE;
	}

	// Gets the character's point investment on a skill.	Returns 0 if not learned.
	int SkillStore::GetSkillPts(const Skill &skill, SkillKnown *i) const
	{
		if (skill.IsLearnable()) {
			if (!i)		{	FindSkill(skill, &i);					}
			if (i)		{	return PointsToMod(skill, i->proficient);	}
		}
		return 0;
	}

	// Gets the character's point investment on a skill.	Returns 0 if not learned.
	int SkillStore::GetSkillTheory(const Skill &skill, SkillKnown *i) const
	{
		if (skill.IsLearnable()) {
			if (!i)		{	FindSkill(skill, &i);					}
			if (i)		{	return PointsToMod(skill, i->theory);	}
		}
		return 0;
	}

	int SkillStore::CheckSkillPrereq(Thing &ch, const Skill &skill) const
	{
		int skillChance = 0, i, numValid = 0;
		
		// Prerequisite check.  The .chance variable represents the points allocated
		// to the skill. -DR
		if (skill._numPrereqs) {
			for (i = 0; i < SKILL_MAX_PREREQS; ++i) {
				skillChance = GetSkillChance(ch, skill, NULL, false);
				if (skillChance >= skill.prereq[i].chance) {
					++numValid;
					if (numValid == skill._numPrereqs)				return true;
				}
			}
			return false;
		} else {
			for (i = 0; i < SKILL_MAX_PREREQS; ++i) {
				skillChance = GetSkillChance(ch, skill, NULL, false);
				if (skillChance < skill.prereq[i].chance)
					return false;
			}
		}
		
		// Anrequisite check.	
		for (i = 0; i < SKILL_MAX_ANREQS; ++i) {
			skillChance = GetSkillChance(ch, skill, NULL, false);
			if (skillChance >= skill.anreq[i].chance)
				return false;
		}
		
		return true;
	}

	// Gets a number to roll against on 3d6.	Returns SKILL_NOCHANCE if there's not a
	// snowball's chance in hell of the character using the skill.
	int SkillStore::GetSkillChance(Thing &ch, const Skill &skill, SkillKnown *known, SInt8 chkdefault) const
	{
		int chance = SKILL_NOCHANCE, temp = SKILL_NOCHANCE;
		SInt8 bases = 0, j = 0, tempmodifier = 0;
		IDNum tempnum = 0, points = 0;
		
		const Properties::Stats		*statsPtr = NULL;
		
		// Special cases, these.
		if (skill.IsStat()) {
			switch (skill._ID) {
			case STAT_STR:
			case STAT_AGI:
			case STAT_HT:
			case STAT_INT:
				statsPtr = GET_PROPERTY((&ch), Stats);
				if (!statsPtr)		return SKILL_NOCHANCE;
				break;
			}
			
			#if 0
			case SKILL_WEAPON:
			case STAT_VISION:
			case STAT_HEARING:
			case STAT_MOVEMENT:
			case SKILL_WEAPON_R:
			case SKILL_WEAPON_L:
			case SKILL_WEAPON_3:
			case SKILL_WEAPON_4:
			#endif

			switch (skill._ID) {
			// Cases for rolling against a character's stats.
			case STAT_STR: chance = statsPtr->strength; break;
			case STAT_INT: chance = statsPtr->intellect; break;
			case STAT_AGI: chance = statsPtr->agility; break;
			case STAT_HT: chance = statsPtr->health; break;

			#if 0
			case SKILL_WEAPON: chance = SKILLCHANCE(ch, GET_WEAPONSKILL(ch, 0), NULL); break;
			case STAT_VISION: chance = GET_INT(ch); break;
			case STAT_HEARING: chance = GET_INT(ch); break;
			case STAT_MOVEMENT: chance = GET_MOVEMENT(ch); break;
			case SKILL_WEAPON_R: chance = SKILLCHANCE(ch, GET_WEAPONSKILL(ch, WEAR_HAND_R), NULL); break;
			case SKILL_WEAPON_L: chance = SKILLCHANCE(ch, GET_WEAPONSKILL(ch, WEAR_HAND_L), NULL); break;
			case SKILL_WEAPON_3: chance = SKILLCHANCE(ch, GET_WEAPONSKILL(ch, WEAR_HAND_3), NULL); break;
			case SKILL_WEAPON_4: chance = SKILLCHANCE(ch, GET_WEAPONSKILL(ch, WEAR_HAND_4), NULL); break;
			#endif
			}
			
			return chance;
		}
		
		if (!CheckSkillPrereq(ch, skill))		return SKILL_NOCHANCE;	// Skill roll is not possible.
		if (!skill.IsLearnable())				return SKILL_NOCHANCE;
		
		// Here we do actual skill lookup.  The SkillStore object 
		if (!known) {
			if (!statsPtr)		statsPtr = GET_PROPERTY((&ch), Stats);
			FindSkill(skill, &known);
		}
		points = GetSkillPts(skill, known);
		
		if (points && skill._statFlags) {
			chance = AverageBaseChance(ch, skill) + PointsToMod(skill, points);
		}
		
		if (!(skill.IsLearnable()))		chkdefault = 1;
	
		// Check the skill's defaults, setting chance if one is found that is better.
		if (chkdefault) {		// Skip if this is already a default check
	
			if (skill.IsLearnable())
				--chkdefault;	// Decrement chkdefault.	If it's 0, this skill is
								// considered a dead end for default checks.
	
			for (j = 0; j < SKILL_MAX_DEFAULTS; ++j) {
				tempnum = skill.defaults[j].skillNum;
	
				if (tempnum) {
					Skill *skillPtr = GetSkill(tempnum);
					if (skillPtr) {
						temp = GetSkillChance(ch, *skillPtr, known, chkdefault);
						tempmodifier = skill.defaults[j].chance;
						if (temp != SKILL_NOCHANCE)		temp += tempmodifier;
						if (chance < temp)				chance = temp;
					}
				}
			}
		}

		return chance;
	}

    // void            SkillStore::Purge(void) {}
    // void            SkillStore::Extract(void) {}
	UInt8			SkillStore::Genus(void) const			{	return Genus::SKILLSTORE;	}
	IDNum			SkillStore::Species(void) const			{	return 1;	}

	void 			SkillStore::FindBestRoll(Thing &ch, const Skill &skill, const Skill **defaultSkill, SInt8 &chance, SInt8 &mod, int type)
	{
		SInt8 tmpchance = SKILL_NOCHANCE, tmpmod = 0, j;
		IDNum tmpdefault = 0;
		int size;
		Skill *defaultPtr;
		
		if (skill.IsStat())		return;
			
		if (!CheckSkillPrereq(ch, skill)) {
			chance = SKILL_NOCHANCE;	// We failed!	Skillroll is not possible.
			return;
		}
	
		size = SKILL_MAX_DEFAULTS;
		for (j = 0; j < size; ++j) {
			tmpdefault = skill.defaults[j].skillNum;
			if (!tmpdefault)	continue;

			tmpmod = skill.defaults[j].chance;
			defaultPtr = GetSkill(tmpdefault);
			
			if (type && !(defaultPtr->IsType(type)))	continue;

			tmpchance = GetSkillChance(ch, *defaultPtr, NULL, !(skill.IsLearnable()));
			if (tmpchance == SKILL_NOCHANCE)			continue;
			tmpchance += tmpmod;
	
			if (tmpchance > chance) {
				*defaultSkill = defaultPtr;
				chance = tmpchance;
				mod = tmpmod;
			}
		}
	}
	
	void 			SkillStore::SetSkill(const Skill &skill, SkillKnown *known, UInt8 proficient, UInt8 theory)
	{
		if (!known)									FindSkill(skill, &known);
		if (!known)									AddSkill(skill, NULL, proficient, theory);
		else {
			known->proficient = proficient;
			known->theory = theory;
		}
	}

	void 			SkillStoreVector::AddSkill(const Skill &skill, SkillKnown *known, UInt8 proficient, UInt8 theory)
	{
		resize(size() + 1);
		SkillKnown &ref = operator[](size() - 1);
		
		ref.skillNum = skill._ID;
		ref.proficient = proficient;
		ref.theory = theory;
		
		sort(begin(), end());
	}
	
	void 			SkillStoreVector::RemoveSkill(const Skill &skill) 
	{
		SInt16				lower, upper, mid;
		const SkillKnown	*ptr;
		SkillStoreVector::iterator iter = begin();

		upper = size();
		if (upper == 0)		{	return;	}

		lower = 0;
		
		while (lower <= upper) {
			mid = (lower + upper) / 2;
			ptr = &(operator[](mid));
			if (skill._ID > ptr->skillNum)			lower = mid + 1;
			else if (skill._ID < ptr->skillNum)		upper = mid - 1;
			else {
				iter += mid;
				erase(iter);
			}
		}
	}

	int 			SkillStore::RollSkill(Thing &ch, const Skill &skill)
	{
		SInt8		chance = SKILL_NOCHANCE, mod = 0;
		const Skill	*defaultSkill = NULL;
		
		if (!(skill.IsStat()) && !ValidPosition(ch, skill)) {
			return -1;
		}
		
		FindBestRoll(ch, skill, &defaultSkill, chance, mod);
		if (chance == SKILL_NOCHANCE)		return chance;
		
		/* if (!skill.IsLearnable() && defaultSkill) {
			return DiceRoll(chance);
		} */
		return DiceRoll(chance);
	}

	int 			SkillStore::RollSkill(Thing &ch, const Skill &skill, SInt8 chance)
	{
		if (!(skill.IsStat()) && !ValidPosition(ch, skill)) {
			return -1;
		}
		
		if (chance == SKILL_NOCHANCE)		return chance;

		return DiceRoll(chance);
	}

	int 			SkillStore::RollSkill(Thing &ch, const Skill &skill, const Skill *defaultSkill, SInt8 chance)
	{
		if (!(skill.IsStat()) && !ValidPosition(ch, skill)) {
			return -1;
		}
		
		if (chance == SKILL_NOCHANCE)		return chance;

		/* if (!skill.IsLearnable() && defaultSkill) {
			return DiceRoll(chance);
		} */
		return DiceRoll(chance);
	}
	
	int 		SkillStore::RollToLearn(Thing &ch, const Skill &skill, int roll, SkillKnown *known)
	{
		int pts = 0;
		bool higherTheory = false;
		const Properties::Stats		*statsPtr = GET_PROPERTY((&ch), Stats);
		
		if (!statsPtr)				return 0;
		
		// An internal enum for skill gain/loss.  Make sure all Losses come after Learns.
		enum {
			None,
			Learn,
			LearnByBotch,
			LearnByLesson,
			LoseByBotch
		} critical = None;
		
		if (skill.IsLearnable()) {
			if (!known)		FindSkill(skill, &known);
			
			if (known) {
				pts = known->proficient;
				if (known->theory > known->proficient)
					higherTheory = true;
			}
		} else {
			return 0;
		}
		
		switch (roll) {
		case 3:		if ((GetSkillChance(ch, skill, known, true) < roll) && (statsPtr->intellect >= Dice::Roll3d6())) {
       					critical = Learn;
					}
					// break;	// Yes, we want the fallthrough
		case 4:		if (higherTheory)							critical = LearnByLesson;	break;
		case 17:	if (statsPtr->intellect >= Dice::Roll3d6())	critical = LearnByBotch;
					else										critical = LoseByBotch;
					break;
		}
				
		switch (critical) {
		case LearnByBotch: 
			LearnSkill(skill, known, pts + 1);
			// AlterMana(ch, pts);
			// ch.Sendf("&cW&bbThat didn't work!  "
			// 			"You'll not botch %s like that again!&b0&c0\r\n",
			// 			Skill::Name(skillnum));
			break;
		case LearnByLesson:
			LearnSkill(skill, known, pts + 1);		 // Critical success.	Learn from it!
			// ch.Sendf("&cW&bbBrilliant move!  "
			// 			"Your lessons in %s are paying off!&b0&c0\r\n",
			// 			Skill::Name(skillnum));
			// AlterMana(ch, pts);
			break;
		case Learn:
			LearnSkill(skill, known, pts + 1);		 // Critical success.	Learn from it!
			// ch.Sendf("&cW&bbBrilliant move!  "
			// 			"Your skill in %s is increasing!&b0&c0\r\n",
			// 			Skill::Name(skillnum));
			// AlterMana(ch, pts);
			break;
		case LoseByBotch:
			LearnSkill(skill, known, -1); // Uh oh, they lost confidence.
			// ch.Sendf("&cY&brThat didn't work!  "
			// 		"You feel less confident in your skill in %s!&b0&c0\r\n",
			// 		Skill::Name(skillnum));
			break;
		default:
			break;
		}
		return critical;
	}
	
	void			SkillStore::LearnTheory(const Skill &skill, SkillKnown *known, SInt8 pts)
	{
		int change = 0;

		if (!pts)				return;
		if (!known)				FindSkill(skill, &known);
		if (!known)				AddSkill(skill, NULL, 0, pts);
		else					known->theory = MIN(known->theory + pts, 250);
	}

	void			SkillStore::LearnSkill(const Skill &skill, SkillKnown *known, SInt8 pts)
	{
		int change = 0;

		if (!pts)				return;
		if (!known)				FindSkill(skill, &known);
		if (!known)				AddSkill(skill, NULL, pts, 0);
		else					known->proficient = MIN(known->proficient + pts, 250);
	}

	void			SkillStore::SkillContest(
						Thing &c, const Skill &cSkill, SInt8 cMod, 
						Thing &v, const Skill &vSkill, SInt8 vMod, 
						SInt8 &offence, SInt8 &defence, int &cCode, int &vCode)
	{
		const Skill	*cDefault, *vDefault;
		int			scaledown;
		SInt8		cChance, vChance;
		
		FindBestRoll(c, cSkill, &cDefault, cChance, cMod);
		FindBestRoll(v, vSkill, &vDefault, vChance, vMod);

		// If both skill chances are 15 or more, this kicks in to lower the numbers
		// for a faster contest.
		if ((cChance > 14) && (vChance > 14)) {
			if (cChance > vChance)			 	scaledown = cChance - 14; 			 
			else					 			scaledown = vChance - 14;
		}
		
		if (cChance != SKILL_NOCHANCE) {
			offence = DiceRoll(cChance) + cMod - scaledown;
		}
	
		if (vChance != SKILL_NOCHANCE) {
			// Either the victim has no chance or has no available skill for defence.
			defence = DiceRoll(vChance) + vMod - scaledown;
		}
	
		if (offence == defence) {	// Equal success rolls mean failure for both.
			offence = -1;
			defence = -1;
		}
	}

	int			SkillStoreVector::TotalPoints(SInt32 flags)
	{
		int sum = 0;
		SkillStoreVector::iterator i;
		const Skill *skill;
		
		i = begin();
		
		while (i != end()) {
			skill = GetSkill((*i).skillNum);

			if (!skill)					continue;
			if (!skill->IsType(flags))	continue;
			
			sum += (*i).proficient;
		}		
		return sum;
	}


	int			SkillStoreVector::TotalTheory(SInt32 flags)
	{
		int sum = 0;
		SkillStoreVector::iterator i;
		const Skill *skill;
		
		i = begin();
		
		while (i != end()) {
			skill = GetSkill((*i).skillNum);

			if (!skill)					continue;
			if (!skill->IsType(flags))	continue;
			
			sum += (*i).theory;
		}		
		return sum;
	}


	#if 0
	void 			SkillStoreVector::ClearSkills();
	IDNum 			SkillStoreVector::FindBestDefault(Thing &ch, SInt16 &skillnum, int chance, Int8 &mod, SInt8 chkdefault);
	#endif

	SkillStore *	SkillStore::Generate(int species) 
	{
		return new SkillStoreVector;
	}
		
}

