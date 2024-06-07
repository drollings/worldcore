//
// C++ Implementation: base
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
#include "properties.hpp"
#include "editing.hpp"
#include "constraints.hpp"
#include "events.hpp"
#include "things.hpp"
#include "worlds.hpp"


#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;


namespace Pronouns
{
    const char *                            pronounStrings[] = {
        "UNDEFINED",
        "NEUTER",
        "MALE",
        "FEMALE",
        "PLURAL",
        "\n"
    };
};


namespace Base
{
    const char *    sNullString = "null";
    
    const Proximity *proximityInside;
    const Proximity *proximityPeople;
    const Proximity *proximityEquipped;
    const Proximity *proximityLocation;
    const Proximity *proximityPropertyOf;
    const Proximity *proximitySought;
    const Proximity *proximityRemembered;
    const Proximity *proximityTargeted;
    const Proximity *proximityAffecting;
    const Proximity *proximityFollowing;
    const Proximity *proximityStalking;
    const Proximity *proximityMemberOf;
    extern const Proximity *proximityListener;

    std::vector<const Proximity *>    proximityList;
    
    //########################################################################
    // For the Named class
    #if 0
                    Named::Named(const char *s) : m_Name(s) {}
                    Named::~Named(void) {}

    const char *    Named::GetName(void) const                    {    return m_Name.c_str();        }
    void            Named::SetName(const char *s)                {    m_Name = s;                    }
    bool            Named::Match(const char *s)                    {    return m_Name.compare(s);    }
    #endif

    //########################################################################
    // For the HasKeywords class
    #if 0
                    HasKeywords::HasKeywords(const char *s) {}
                    HasKeywords::~HasKeywords(void) {}
    #endif


    //########################################################################
    // For the Proximity class
    Proximity::Proximity(const char *n, IDNum id) : Named(n), HasID() 
    {
        SetID(id);
        if (proximityList.size() <= id) {
            proximityList.push_back(this);
        } else {
            proximityList[id] = this;
        }
    }
    Proximity::~Proximity() {}

    int Proximity::Add(Holds &host, Element &obj) const
    {
        #ifdef UNITTEST
        cout << "Putting " << &obj << " in host " << &host << " with proximityID " << GetID() << " with addr " << this << endl;
        #endif
        host.m_dElements[GetID()].push_back(&obj);
        return 1;
    }

    int Proximity::Remove(Holds &host, Element &obj) const
    {
        int proximityID = GetID();
        host.m_dElements[proximityID].remove(&obj);
        if (host.m_dElements[proximityID].size() == 0) {
            host.m_dElements.erase(proximityID);
        }
        #ifdef UNITTEST
        cout << "Removing " << &obj << " from host " << &host << " in proximityID " << proximityID << " with addr " << this << endl;
        #endif
        return 1;
    }

    ElementList *    Proximity::GetElementList(const Holds &host) const
    {
        ProximityElementMap::const_iterator iter = host.m_dElements.find(GetID());
        if (iter == host.m_dElements.end())        return NULL;
        else {
            Holds &h = const_cast<Holds &>(host);
            return &(h.m_dElements[GetID()]);
        }
    }

    ThingList *        Proximity::GetThingList(const Holds &) const
    {
        return NULL;
    }



    //########################################################################
    // For the Element class
    Element::Element(void) {}
    Element::Element(const char *n) : Named(n) {}
    Element::~Element(void)    
    {                    
        #ifdef UNITTEST
        cout << "Deleting Element " << this << endl;
        #endif
    }
    Element &    Element::operator=(const Element &)                {    return *this;    }
    void        Element::Purge(void)                             {}
    const Proximity *    Element::DefaultProximity(void) const    {    return proximityInside;    }
    // const Holds *    Element::Inside(void) const        {    return inside;                    }

    SInt32    Element::To(Holds &host, const Proximity *prox)
    {
        if (!prox)    prox = DefaultProximity();
        return host.Receive(*this, prox);
    }

    SInt32    Element::From(Holds *holds, const Proximity *prox)
    {
        if (!holds)        return 0;    // Failure
        if (!prox)        prox = DefaultProximity();

        return holds->Remove(*this, prox);
    }

    void    Element::Extract(void) {}


    //########################################################################
    // For the Holds class
    int        Holds::Receive(Element &obj, const Proximity *prox) {    
        #ifdef UNITTEST
        cout << "Receiving " << &obj << "!" << endl; 
        #endif
        return prox->Add(*this, obj);        
    }

    int        Holds::Remove(Element &obj, const Proximity *prox)    {    return prox->Remove(*this, obj);    }

    void    Holds::Extract(void)
    {
        ProximityElementMap::iterator i;
        ElementList::iterator j;
        Element *e;
        
        for (i = m_dElements.begin(); i != m_dElements.end(); ++i) {
            for (j = i->second.begin(); j != i->second.end(); ++j) {
                e = *j;
                e->Extract();
            }
        }
    }

    ElementList *    Holds::GetElementsInProximity(const Proximity *prox)
    {
        int g = prox->GetID();
        if (m_dElements.count(g)) {
            return &(m_dElements[g]);
        }

        return NULL;
    }

    ThingList *    Holds::GetThingsInProximity(const Proximity *prox)
    {
        int g = prox->GetID();
        if (m_dElements.count(g)) {
            return (ThingList *) &(m_dElements[g]);
        }

        return NULL;
    }

    #if 0
    const PropertyData *    ::Base::Propertied::GetProperty(IDNum num) const
    {
        const PropertyData *data = NULL;
        if (HasProperty(num))    {
            data = (const_cast<::Base::Propertied *>(this))->_lProperties_.GetByKey(num);
            if (data)        return data;
            else {            
                const ::Base::Propertied *propertied = GetProto();
                if (propertied) {
                    return propertied->GetProperty(num);
                }
            }
        }
        return NULL;
    }

    ::Properties::PropertyData *            Propertied::GetProperty(IDNum num)
    {
        ::Properties::PropertyData *data = NULL;

        if (HasProperty(num))    {
            data = _lProperties_.GetByKey(num);
            if (data)        return data;
            #if 0
            else {
                data = const_cast<Properties::PropertyData *>(GetProperty(num));
                if (data) {
                    _lProperties_.Insert(num, *data);
                    return data;
                }
            }
            #endif
        }
        return NULL;
    }
    #endif

    Properties::PropertyData *    ::Base::Propertied::GetProperty(IDNum num) const
    {
        const Properties::PropertyData *data = NULL;
        if (HasProperty(num))    {
            switch (num) {
            case PropertyTypes::Exit:    return ((Properties::PropertyData *) &(_lProperties_->_Exit_));
            case PropertyTypes::Ingestable:    return ((Properties::PropertyData *) &(_lProperties_->_Ingestable_));
            case PropertyTypes::Poison:    return ((Properties::PropertyData *) &(_lProperties_->_Poison_));
            case PropertyTypes::Light:    return ((Properties::PropertyData *) &(_lProperties_->_Light_));
            case PropertyTypes::Weapon:    return ((Properties::PropertyData *) &(_lProperties_->_Weapon_));
            case PropertyTypes::FireWeapon:    return ((Properties::PropertyData *) &(_lProperties_->_FireWeapon_));
            case PropertyTypes::Missile:    return ((Properties::PropertyData *) &(_lProperties_->_Missile_));
            case PropertyTypes::Armor:    return ((Properties::PropertyData *) &(_lProperties_->_Armor_));
            case PropertyTypes::Container:    return ((Properties::PropertyData *) &(_lProperties_->_Container_));
            case PropertyTypes::Mountable:    return ((Properties::PropertyData *) &(_lProperties_->_Mountable_));
            case PropertyTypes::Decay:    return ((Properties::PropertyData *) &(_lProperties_->_Decay_));
            case PropertyTypes::Money:    return ((Properties::PropertyData *) &(_lProperties_->_Money_));
            case PropertyTypes::Stats:    return ((Properties::PropertyData *) &(_lProperties_->_Stats_));
            }
        }
        return NULL;
    }




    //########################################################################
    // For the Trigger class
    // Trigger::Trigger(void)                {}
    // Trigger::~Trigger(void)                {}


    const char *genusStrings[] = {
        "UNDEFINED",
        "INT",
        "TYPE",
        "FLAGS",
        "STRING",
        "SSTRING",
        "LEXISTRING",
        "CONSTRAINT",
        "EDITABLE",
        "ELEMENT",
        "THING",
        "LOCATION",
        "VEGETABLE",
        "CREATURE",
        "WORLD",
        "AFFECT",
        "EVENT",
        "CONCENTRATION",
        "PROPERTY",
        "ACTION",
        "EXIT",
        "MIND",
        "\n"
    };

    int    Init(void)
    {
        proximityInside = new Proximity("Inside");
        proximityPeople = new Proximity("People");
        proximityEquipped = new Proximity("Equipped");
        proximityPropertyOf = new Proximity("PropertyOf");
        proximitySought = new Proximity("Sought");
        proximityRemembered = new Proximity("Remembered");
        proximityTargeted = new Proximity("Targeted");
        proximityAffecting = new Proximity("Affecting");
        proximityFollowing = new Proximity("Following");
        proximityStalking = new Proximity("Stalking");
        proximityMemberOf = new Proximity("MemberOf");
        
        ::Worlds::Init();

        return 1;
    }
    
}

namespace Signal
{
    const char                         *signalTypeStrings[] = 
    {
        "GLOBAL",
        "RANDOM",
        "COMMAND",
        "SPEECH",
        "GREET",
        "LEAVE",
        "DOOR",
        "DROP",
        "GET",
        "ACT",
        "DEATH",
        "FIGHT",
        "HITPRCNT",
        "SIT",
        "GIVE",
        "WEAR",
        "CONSUME",
        "REMOVE",
        "LOAD",
        "TIMER",
        "START",
        "QUIT",
        "ATTACK",
        "INSTALL",
        "CALL",
        "ENTER",
        "DESTROYREPAIR",
        "ATTACKED",
        "KILL",
        "PUT",
        "MOTION",
        "RESET",
        "\n"
    };
}