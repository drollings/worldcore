//
// C++ Implementation: affects
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "affects.hpp"
#include "properties.hpp"
#include "things.hpp"
#include "Templates/WeakRef.hpp"

using namespace std;
using namespace Base;
using namespace Events;
using namespace Things;

namespace Affects
{
	class EventAffect : public Affect
	{
	protected:
		Events::Event *event;

	public:
						EventAffect(Events::Event *e) : event(e) {};
						~EventAffect(void) {};

		virtual ::Events::Event *	GetEvent(void) const	{	return event;	}
	};
	
	class PropertyAffect : public Affect
	{
	protected:
		SInt16	offset;
		SInt16	modifier;
		Flags	flags;

	public:
						PropertyAffect(SInt16 o, SInt16 m, Flags f) : offset(o), modifier(m), flags(f) {};
						~PropertyAffect(void) {};

		virtual SInt16				GetOffset(void) const	{	return offset;	}
		virtual SInt16				GetModifier(void) const	{	return modifier;	}
	};


	class SourcedPropertyAffect : public PropertyAffect
	{
	protected:
		std::weak_ptr<Things::Thing>	causedBy;
		IDNum				species;

	public:
						SourcedPropertyAffect(Things::Thing *t, IDNum s, SInt16 o, SInt16 m, Flags f) : PropertyAffect(o, m, f), causedBy(t), species(s) {};
						~SourcedPropertyAffect(void) {};

		virtual ::Things::Thing *	GetCausedBy(void) const	{	return (causedBy ? *causedBy : NULL);	}
	};

	class FullAffect : public SourcedPropertyAffect
	{
	protected:
		Events::Event *event;

	public:
						FullAffect(Things::Thing *t, IDNum s, SInt16 o, SInt16 m, Flags f, Events::Event *evt) : SourcedPropertyAffect(t, s, o, m, f), event(evt) {};
						~FullAffect(void) {};

		virtual ::Events::Event *	GetEvent(void) const	{	return event;	}
	};


	Affect *				Affect::Generate(SInt16 off, SInt16 mod, const Flags &f, ::Events::Event *evt, ::Things::Thing *source, IDNum spe)
	{
		if (off || mod || f.any()) {
			if (spe || source) {
				if (evt) {
					return new FullAffect(source, spe, off, mod, f, evt);
				}
				return new SourcedPropertyAffect(source, spe, off, mod, f);
			}
			return new PropertyAffect(off, mod, f);
		} else if (evt) {
			return new EventAffect(evt);
		}
		return NULL;
	}
}
