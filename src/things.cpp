//
// C++ Implementation: thing
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "things.hpp"
#include "constraints.hpp"
#include "properties.hpp"

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;
using namespace Base;
using namespace Editing;

namespace Materials
{
    const char *                            materialStrings[] = {
        "UNDEFINED",
        "WATER",
        "VEGETABLE",
        "FLESH",
        "PAPER",
        "CLOTH",
        "LEATHER",
        "WOOD",
        "BONE",
        "METAL",
        "PLASTIC",
        "GLASS," 
        "GEMSTONE",
        "MINERAL",
        "CERAMIC",
        "\n"
    };
}

namespace Things
{
    //########################################################################
    // For the Thing class
    const char * engineStrings[] = {
        "PURGED",
        "DIRTY",
        "SUPER",
        "AFFECTED",
        "BUSY",
        "\n"
    };
    const char * flagsStrings[] = {
        "DELETED",
        "APPROVED",
        "NPC",
        "MALE",
        "FEMALE",
        "PLURAL",
        "HIDDEN",
        "FROZEN",
        "OPENABLE",
        "OPEN",
        "SEETHRU",
        "\n"
    };

    const char *positionStrings[] = {
        "limp",
        "prone",
        "upright",
        "sitting",
        "kneeling",
        "crouching",
        "crawling",
        "standing",
        "floating",
        "\n"
    };
    
    const char *stateStrings[] = {
        "dead",
        "dying",
        "mortally wounded",
        "incapacitated",
        "asleep",
        "stunned",
        "immobile",
        "resting",
        "fighting",
        "riding",
        "audible",
        "nothing",    
        "\n"
    };


    Thing::Thing(void) : Base::HasID(), Base::Element(), HasKeywords(), 
        m_Proximity(NULL), inside(NULL), action(NULL), 
        temperature(25.0), quantity(1), 
        position(Standing), state(Okay), genus(Genus::THING), material(0), 
        condition(100), energy(100), hidden(0), 
        mass(1.0), stats(NULL),    m_MobileData(NULL), path(NULL)
        {};
    Thing::Thing(const Thing &other) : Base::HasID(), Base::Element(), HasKeywords(), 
        m_Proximity(NULL), inside(NULL), action(NULL), 
        temperature(other.temperature), quantity(other.quantity), 
        position(Standing), state(Okay), genus(other.genus), material(other.material), 
        condition(100), energy(100), hidden(0), 
        mass(other.mass), stats(other.stats), m_MobileData(other.m_MobileData), path(NULL)
        {};
    Thing::Thing(const char *s) : Base::HasID(), Base::Element(s), HasKeywords(), 
        m_Proximity(NULL), inside(NULL), action(NULL), 
        temperature(25.0), quantity(1), 
        position(Standing), state(Okay), genus(Genus::THING), material(0), 
        condition(100), energy(100), hidden(0), 
        mass(1.0), stats(NULL),    m_MobileData(NULL), path(NULL)
        {};

    Base::Element *    Thing::Clone(void) const
    {    
        Thing *t = new Thing(*this);
        return static_cast<Element *>(t);    
    }
    
    const Base::Proximity *    Thing::DefaultProximity(void) const    
    {
        switch (GetGenus()) {
        case Genus::CREATURE:    return Base::proximityPeople;
        default:                break;
        };
        return Base::proximityInside;
    }
    
    float        Thing::GetMass(void) const            {    return mass;        }
    void        Thing::SetMass(float m)                {    mass = m;            }
    void        Thing::ChangeMass(float m)            {    mass += m;            }

    /* enter a character in the world (place on lists) */
    void Thing::ToWorld() {
        switch (genus) {
        case Genus::CREATURE:    
            // if (Lexi::IsInContainer(character_list, this))    return; //FIXME
            // character_list.push_front(this);
            break;
        default:        
            // if (Lexi::IsInContainer(object_list, this))    return;
            // object_list.push_front(this);
            break;
        }
        
        #if 0
        // IDManager::Register(this);    // FIXME
    
        if (IS_MOB(this))        /* if mobile */
            ++GetPrototype()->m_Count;
        
        // FIXME - what to do with this?
        if (!IS_NPC(this) && GET_CLAN(this))
        {
            GET_CLAN(this)->OnPlayerToWorld(this);
        }
        
        FOREACH(Lexi::List<Affects::Affect *>, m_Affects, affect)
        {
            (*affect)->ResumeTimer(this);
        }
        #endif
    }

    SInt32    Thing::To(Holds &host, const Base::Proximity *prox)
    {
        int retval;

        if (!prox)    prox = DefaultProximity();
        retval = host.Receive(*this, prox);
        if (retval) {
            m_Proximity = prox;
            Thing *hostThing = NULL;
            hostThing = dynamic_cast<Thing *>(&host);
            if (hostThing) {
                inside = hostThing;
            }
        }
        return retval;
    }

    SInt32    Thing::From(Holds *holds, const Base::Proximity *prox)
    {
        int retval;
        
        if (!holds)        holds = inside;
        if (!holds)        return 0;    // Failure
        if (!prox)        prox = InProximity();

        retval = holds->Remove(*this, prox);
        if (retval) {
            if (holds == inside)    inside = NULL;
            if (prox == InProximity())    m_Proximity = NULL;
        }
        return retval;
    }

    
    Ptr            Thing::GetPointer(int offset) const
    {
        Properties::PropertyData *p = NULL;
        switch (offset) {
        case NAME:        return ((Ptr) &m_Name);
        // case PROTO:        return ((Ptr) &m_Prototype);
        case INSIDE:        return ((Ptr) &inside);
        case PROXIMITY:        return ((Ptr) &m_Proximity);
        case GENUS:        return ((Ptr) &genus);
        case MASS:        return ((Ptr) &mass);
        case TEMPERATURE:        return ((Ptr) &temperature);
        case QUANTITY:        return ((Ptr) &quantity);

        #if 0
        case KEY:            
        case OPENSKILL:        
        case OPENDIFFICULTY:
            p = GetProperty(PropertyTypes::Openable);
            if (!p)    return NULL;
            switch (offset) {
            case KEY:        return &(((Properties::Openable *) p)->key);
            }
        
        case TO_THING:        return ((Ptr) &);
        case FROM_THING:        return ((Ptr) &);
        case METERSWIDE:        return ((Ptr) &);
        case THETA:        return ((Ptr) &);
        
        MODHUNGER,
        MODTHIRST,
        MODDRUNK,
        
        SEVERITY,
        DURATION,
        
        HOURS,
        ALIGHT,
        
        USEHOW,
        TOOLSKILL,
        CHARGES,
        
        STRENGTH,
        HEALTH,
        AGILITY,
        POSITION,
        MOVEMENT,
        VISION,
        HEARING,
        SCENT,
        INTELLECT,
        WILL,
        AWARENESS,
        FOCUS,
        COURAGE,
        DISPOSITION,
        MOOD,
        ERRATIC,
        STATE,
        HUNGER,
        THIRST,
        DRUNK,
        
        CONC_INTERVAL,
        COST_HIT,
        COST_MANA,
        COST_MOVEMENT,
        
        DECAYTIME,
        
        CONTAINERFLAGS,
        MAXWEIGHT,
        PICK_MODIFIER,
        SCABBARDOF,
        CORPSEOF,
        
        MOUNTABLEFLAGS,
        MAXCARRY,
        
        ARMORCHART,
        SHIELDBONUS,
        
        PROFICIENCY,
        TOHIT,
        DAMBONUS,
        DAMTYPE,
        AMMO,
        MAXAMMO,
        SHOOTRANGE,
        SHOOTSPEED,
        
        WEAPONSKILL,
        SWINGMESSAGE,
        THRUSTMESSAGE,

        SWINGTOHIT,
        SWINGBONUS,
        SWINGDAMTYPE,
        SWINGSPEED,

        THRUSTTOHIT,
        THRUSTBONUS,
        THRUSTDAMTYPE,
        THRUSTSPEED,

        PARRYSPEED,
        PARRYBONUS,
        RANGE,
        #endif


        };
        return NULL;
    }

    const Accessor **        Thing::GetAccessorTable(void) const
    {
        static const Accessor *_thingAccessors[9] = {
            new Accessor("name", NAME, new CPPString(1, 40), CODER_VIEW | CODER_WRITE),
            new Accessor("proto", PROTO, new IntConstraintTemplate<IDNum>, CODER_VIEW | CODER_WRITE),
            new Accessor("inside", INSIDE, new Values<UInt8>(genusStrings), CODER_VIEW | CODER_WRITE),
            new Accessor("proximity", PROXIMITY, new Values<UInt8>(genusStrings), CODER_VIEW | CODER_WRITE),
            new Accessor("genus", GENUS, new Values<UInt8>(genusStrings), CODER_VIEW | CODER_WRITE),
            new Accessor("mass", MASS, new FloatNumericRange<float>(0.0, 10000.0), CODER_VIEW | CODER_WRITE),
            new Accessor("temperature", TEMPERATURE, new FloatNumericRange<float>(-273.0, 900000000.0), CODER_VIEW | CODER_WRITE),
            new Accessor("quantity", QUANTITY, new IntNumericRange<float>(1, 2000000000), CODER_VIEW | CODER_WRITE),
            NULL
        };
        return _thingAccessors;
    }

    // PlayerData *                        Thing::GetPlayer() { return (desc ? desc->m_pPlayer : NULL); }
    // const PlayerData *                    Thing::GetPlayer() const { return (desc ? desc->m_pPlayer : NULL); }

    int                                    Thing::RollSkill(const Skills::Skill *s)    {
        if (!stats || !s || !(stats->skills))    return SKILL_NOCHANCE;
        return stats->skills->RollSkill(*this, *s);
    }


    int    Init(void)
    {
        return 0;
    }
}