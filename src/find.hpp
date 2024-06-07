#ifndef __FIND_HPP__
#define __FIND_HPP__

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

#include "base.hpp"

Base::Element *			Find(ElementList &, const char *);

Things::Thing *			Find(ThingList &, const char *);
Things::Thing *			FindByID(ThingList &, IDNum);
Things::Thing *			FindBySpecies(ThingList &, IDNum);
Things::Thing *			FindByProperty(ThingList &, IDNum);
Things::Thing *			FindByFlag(ThingList &, Flags);
Things::Thing *			FindByPredicateThing(ThingList &, PredicateThing);
Things::Thing *			FindByPredicateThingThing(ThingList &, PredicateThingThing, Things::Thing &);
Things::Thing *			FindByStringThing(ThingList &, const char *, Things::Thing &);

inline Things::Thing *	Find(ThingList *l, const char *c)				{	return (l ? Find(*l, c) : NULL);	}
inline Things::Thing *	FindByID(ThingList *l, IDNum n)					{	return (l ? FindByID(*l, n) : NULL);	}
inline Things::Thing *	FindBySpecies(ThingList *l, IDNum n)			{	return (l ? FindBySpecies(*l, n) : NULL);	}
inline Things::Thing *	FindByProperty(ThingList *l, IDNum n)			{	return (l ? FindByProperty(*l, n) : NULL);	}
inline Things::Thing *	FindByFlag(ThingList *l, Flags f)				{	return (l ? FindByFlag(*l, f) : NULL);	}
inline Things::Thing *	FindByPredicateThing(ThingList *l, PredicateThing f)		{	return (l ? FindByPredicateThing(*l, f) : NULL);	}
inline Things::Thing *	FindByPredicateThingThing(ThingList *l, PredicateThingThing f, Things::Thing &t)		{	return (l ? FindByPredicateThingThing(*l, f, t) : NULL);	}
inline Things::Thing *	FindByStringThing(ThingList *l, const char *c, Things::Thing &t)		{	return (l ? FindByStringThing(*l, c, t) : NULL);	}

inline Things::Thing *	Find(Base::Holds &h, Base::Proximity &p, const char *c)				{	return Find(p.GetThingList(h), c);	}
inline Things::Thing *	FindByID(Base::Holds &h, Base::Proximity &p, IDNum n)				{	return FindByID(p.GetThingList(h), n);	}
inline Things::Thing *	FindBySpecies(Base::Holds &h, Base::Proximity &p, IDNum n)			{	return FindBySpecies(p.GetThingList(h), n);	}
inline Things::Thing *	FindByProperty(Base::Holds &h, Base::Proximity &p, IDNum n)			{	return FindByProperty(p.GetThingList(h), n);	}
inline Things::Thing *	FindByFlag(Base::Holds &h, Base::Proximity &p, Flags f)				{	return FindByFlag(p.GetThingList(h), f);	}
inline Things::Thing *	FindByPredicateThing(Base::Holds &h, Base::Proximity &p, PredicateThing f)	{	return FindByPredicateThing(p.GetThingList(h), f);	}
inline Things::Thing *	FindByPredicateThingThing(Base::Holds &h, Base::Proximity &p, PredicateThingThing &f, Things::Thing &t)		{	return FindByPredicateThingThing(p.GetThingList(h), f, t);	}
inline Things::Thing *	FindByStringThing(Base::Holds &h, Base::Proximity &p, const char *c, Things::Thing &t)	{	return FindByStringThing(p.GetThingList(h), c, t);	}


#if 1
Things::Thing *	get_obj(const char *name);
Things::Thing *	get_obj_num(VNum nr);
Things::Thing *	get_obj_vis(Things::Thing *ch, const char *name, int *number = NULL);
Things::Thing *	get_obj_by_char(Things::Thing * ch, const char *name);
Things::Thing *	get_obj_in_list(const char *name, int *number, ThingList &list);
Things::Thing *	get_obj_in_list_vis(Things::Thing *ch, const char *name, ThingList &list, int *number = NULL);
Things::Thing *	get_obj_in_list_num(VNum num, ThingList &list);
Things::Thing *	get_obj_in_list_type(int type, ThingList &list);
Things::Thing *	get_obj_in_list_flagged(int flag, ThingList &list);
Things::Thing *	get_obj_in_equip(const char *arg, int *number, Things::Thing * equipment[], int *j);
Things::Thing *	get_obj_in_equip_vis(Things::Thing * ch, const char *arg, Things::Thing * equipment[], int *j, int *number = NULL);
Things::Thing *	get_obj_in_equip_type(int type, Things::Thing * equipment[]);
Things::Thing *	get_obj_by_obj(Things::Thing *obj, const char *name);
Things::Thing *	get_obj_by_room(Things::Thing *room, const char *name);
Things::Thing *	find_vehicle_by_vid(VNum vnum);

int	get_num_chars_on_obj(Things::Thing * obj);
Things::Thing *	get_char_on_obj(Things::Thing *obj);

Things::Thing *	get_char(const char *name);
Things::Thing *	get_char_room(const char *name, Things::Thing *room, int *number = NULL);
Things::Thing *	get_char_num(VNum nr);
Things::Thing *	get_char_by_obj(Things::Thing *obj, const char *name);

/* find if character can see */
Things::Thing *	get_char_room_vis(Things::Thing *ch, const char *name, int *number = NULL);
Things::Thing *	get_char_world_vis(Things::Thing *ch, const char *name, int *number = NULL);
Things::Thing *	get_char_other_room_vis(Things::Thing * ch, const char *name, Things::Thing *room, int *number = NULL);
Things::Thing *	get_player_vis(Things::Thing *ch, const char *name, Flags where = 0, int *number = NULL);
Things::Thing *	get_player(const char *name, int *number = NULL);
Things::Thing *	get_char_vis(Things::Thing *ch, const char *name, Flags where, int *number = NULL);
Things::Thing *	get_char_by_char(Things::Thing *ch, const char *name);

Things::Thing *get_char_by_room(Things::Thing *room, const char *name);

Things::Thing *get_room(const char *name, Hash zone = 0);

//ShipData *find_ship(IDNum n);

/* find all dots */

int	find_all_dots(char *arg);

#define FIND_INDIV	0
#define FIND_ALL	1
#define FIND_ALLDOT	2


/* Generic Find */

int	generic_find(const char *arg, int bitvector, Things::Thing *ch, Things::Thing **tar_ch, Things::Thing **tar_obj);

#define FIND_CHAR_ROOM     1
#define FIND_CHAR_WORLD    2
#define FIND_OBJ_INV       4
#define FIND_OBJ_ROOM      8
#define FIND_OBJ_WORLD    16
#define FIND_OBJ_EQUIP    32



#endif

#endif	// __FIND_HPP__
