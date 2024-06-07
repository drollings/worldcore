#ifndef __THINGS_HPP__
#define __THINGS_HPP__

//
// C++ SInterface: things
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
#include "editing.hpp"
#include "affects.hpp"
#include "gurpsskills.hpp"
#include "gen-cpp/materials_types.h"
#include "gen-cpp/things_types.h"


extern ThingList                thing_list;

namespace Things
{
    extern const char *                            offsetStrings[];

    extern const char *materialStrings[];
    extern const char *engineStrings[];
    extern const char *flagsStrings[];
    extern const char *positionStrings[];
    extern const char *stateStrings[];
    
    class AnimateStats : public Editing::Editable
    {
                        AnimateStats(void) :
                        strength(10), health(10), agility(10), position(10), movement(10), vision(10), hearing(10),
                        scent(10), state(10), hunger(0), thirst(0), drunk(0), bodyType(10), intellect(10), will(10),
                        awareness(10), focus(10), m_ActFlags(0),
                        skills(NULL), following(NULL) {}
    public:
    
        SInt8                    strength;
        SInt8                    health;
        SInt8                    agility;
        UInt8                    position;

        SInt8                    movement;
        SInt8                    vision;
        SInt8                    hearing;
        SInt8                    scent;

        UInt8                    state;
        SInt8                    hunger;
        SInt8                    thirst;
        SInt8                    drunk;

        IDNum                    bodyType;

        SInt8                    intellect;
        SInt8                    will;
        SInt8                    awareness;
        SInt8                    focus;

        Flags                    m_ActFlags;
        Skills::SkillStore        *skills;
        Thing                    *following;

        virtual const Editing::Accessor    **    GetAccessorTable(void) const;
        virtual Ptr                            GetPointer(int offset) const;
    };
    

    class MobData
    {
    public:
                                MobData() : m_MobFlags(0), courage(10), disposition(10), mood(10), erratic(10) {}
        
        Flags                    m_MobFlags;
        SInt8                    courage;
        SInt8                    disposition;
        SInt8                    mood;
        SInt8                    erratic;

        #if 0
        Opinion                    m_Hates;
        Opinion                    m_Fears;
        #endif
    };


    //####################################################################
    class Thing : 
        public Base::HasID, public Base::Element, public Base::Holds, public Base::HasKeywords, 
        public Base::Propertied, public Editing::Editable
    {
    private:
        const Base::Proximity *                m_Proximity;
    
    public:
        Thing *                                inside;
        ::Events::Event    *                    action;
        Events::Event *                        points_event[3];

        SInt16                                temperature;
        UInt16                                quantity;

        UInt8                                position;
        UInt8                                state;
        UInt8                                genus;                // This will allow a little run-time polymorphism between objects and creatures
        UInt8                                material;            // An enumeration type will determine material, and hence PD/DR

        UInt8                                condition;            // We're just going to abstract hit points to a percentile
        UInt8                                energy;                // A percentile of energy
        SInt8                                hidden;

        float                                mass;

        AnimateStats                        *stats;
        MobData                                *m_MobileData;
        Path                                *path;
        
        Flags                                m_ThingFlags;
        String                                m_Name;
        String                                m_Keywords;

        String                                m_RoomDescription;
        String                                m_Description;

        ThingList                            contents;            //    Head of list
        ThingList                            people;                //    Head of list
        
        std::list<Affects::Affect *>        m_Affects;            //    affects
        Affects::AffectFlags                m_AffectFlags;
        std::weak_ptr<Thing>                targeting;
        std::vector<Thing *>                equipment;

        // DescriptorData *    desc;                //    NULL for mobiles
        
                                            Thing(void);
                                            Thing(const Thing &);
                                            Thing(const char *);
                                            ~Thing(void) {};

        virtual const char *                GetName(void) const                    {    return m_Name.c_str();        }
        virtual void                         SetName(const char *s)                {    m_Name = s;                    }
        virtual const char *                GetAlias() const { return m_Keywords.c_str(); }
        virtual bool                        Match(const char *s)                {    return m_Name == s;    }
        
        virtual const char *                GetClassName(void) const            {    return "Thing";        }

        virtual UInt8                        GetGenus(void) const                {    return genus;            }
        virtual Thing *                        Inside(void)                        {    return inside;            }
        virtual const Thing *                Inside(void) const                    {    return inside;            }
        Pronouns::Pronouns                    GetSex() const { return (IS_SET(m_ThingFlags, Things::MALE) ? Pronouns::MALE : (IS_SET(m_ThingFlags, Things::FEMALE) ? Pronouns::FEMALE : Pronouns::NEUTER)); }
        void                                SetSex(int s) { 
            switch (s) {
                case Pronouns::MALE:    SET_BIT(m_ThingFlags, Things::MALE);    REMOVE_BIT(m_ThingFlags, Things::FEMALE);    return;
                case Pronouns::FEMALE:    SET_BIT(m_ThingFlags, Things::FEMALE);    REMOVE_BIT(m_ThingFlags, Things::MALE);    return;
            }
            REMOVE_BIT(m_ThingFlags, Things::FEMALE);    
            REMOVE_BIT(m_ThingFlags, Things::MALE);
        }

        virtual const Base::Proximity *        InProximity(void) const                {    return m_Proximity;        }

        // virtual void                        AddOrReplaceEvent(Events::Event *event);

        // virtual void                        Save();                    //    Redirector
        // virtual bool                        Load(const char *name);    //    Redirector
    
        virtual const Editing::Accessor    **    GetAccessorTable(void) const;
        virtual Ptr                            GetPointer(int offset) const;

        const ThingList &                    GetContents(void) const                {    return contents;    }
        ThingList &                            GetContents(void)                    {    return contents;    }
        virtual const ThingList &                    GetPeople(void) const                {    return people;    }
        virtual ThingList &                            GetPeople(void)                        {    return people;    }
        
        // virtual void                        Extract(void);
        // virtual void                        Appear(Affects::Flags flags = Affects::AFF_STEALTH_FLAGS);
        virtual Base::Element *                Clone(void) const;
        virtual const ::Base::Proximity *    DefaultProximity(void) const;
        
        virtual AnimateStats *                GetAnimate(void)                    {    return stats;    }
        virtual const AnimateStats *        GetAnimate(void) const                {    return stats;    }
        // virtual void                        SetAnimate(AnimateStats *s = NULL);
        // virtual    Flags                        GetActFlags(void) const                {    if (stats)    return stats->m_ActFlags;    return 0;        }
        // virtual    Things::Thing *                GetFollowing(void) const            {    if (stats)    return stats->following;    return NULL;    }
        // virtual    void                        SetFollowing(Things::Thing *);
        virtual    int                            RollSkill(const Skills::Skill *s);

        // virtual int                            To(Holds &, const Base::Proximity * = NULL);
        // virtual int                            From(Holds * = NULL, const Base::Proximity * = NULL); 
        virtual SInt32                        To(Holds &, const Base::Proximity * = NULL);
        virtual SInt32                        From(Holds * = NULL, const Base::Proximity * = NULL); 
        // virtual int                            To(Worlds::Location &, const Base::Proximity * = NULL);
        // virtual int                            From(Worlds::Location * = NULL, const Base::Proximity * = NULL); 
        // virtual int                            ToEquip(Thing &, int slot);
        // virtual int                            FromEquip(Thing &, int slot); 

        virtual void                         ToWorld(void);

        virtual float                        GetMass(void) const;
        virtual void                        SetMass(float);
        virtual void                        ChangeMass(float);

        // virtual bool                        IsAwake(void) const;
        // virtual bool                        CanSense(Thing *target, bool ignoreLight = false);
        // virtual int                            GetCondition(void) const;
        // virtual int                            GetEnergy(void) const;

        Position                            GetPosition(void) const        {    return static_cast<Position>(position);    }
        void                                SetPosition(Position p)        {    position = static_cast<UInt8>(p);    }
        State                                GetState(void) const        {    return static_cast<State>(state);    }
        void                                SetState(State s)            {    state = static_cast<UInt8>(s);    }
        // virtual void                        Update(void);

        // virtual int                            Send(const char *messg);
        // virtual int                            Sendf(const char *messg, ...) __attribute__ ((format (printf, 2, 3)));

        static Thing *                        Find(IDNum id);

        // PlayerData *                        GetPlayer();
        // const PlayerData *                    GetPlayer() const;

    public:
        String                                GetFilename() const { return GetFilename(GetName()); }
        String                                GetObjectFilename() const { return GetObjectFilename(GetName()); }
        
        static Things::Thing *        Create(Things::Thing *obj = NULL);

        static String    GetFilename(const char *name);
        static String    GetObjectFilename(const char *name);

    };

    extern int    Init(void);
}

extern ThingList        character_list;
extern ThingList        object_list;
extern ThingList        combat_list;

#define CURRENT_VERSION                        14
const int    EXDSCR_LENGTH        = 480;
const int    MAX_NAME_LENGTH        = 12;
#define GET_POINTS_EVENT(ch, i) ((ch)->points_event[i])

#endif

