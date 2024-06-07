#ifndef __PERMISSIONS_HPP__
#define __PERMISSIONS_HPP__

//
// C++ Interface: permissions
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "typedefs.hpp"
#include "gen-cpp/permissions_types.h"

namespace Permissions
{
	const int READ_MASK = CODER_VIEW | CREATOR_VIEW | STAFF_VIEW | WORLD_VIEW | SCRIPT_VIEW | PLAYER_VIEW;
	const int WRITE_MASK = CREATOR_WRITE | STAFF_WRITE | WORLD_WRITE | SCRIPT_WRITE | PLAYER_WRITE;
	const int DERIVE_MASK = CREATOR_DERIVE | STAFF_DERIVE | WORLD_DERIVE | SCRIPT_DERIVE | PLAYER_DERIVE;
	
	extern const char *			memberPermissionsFlagsStrings[];
	
	extern const Flags	permCoder;
	extern const Flags	permCreator;
	extern const Flags	permStaff;
	extern const Flags	permWorld;
	extern const Flags	permScript;
	extern const Flags	permPlayer;
}


int			GetTrust(const ::Things::Thing *);

#define GET_TRUST(ch)	(GetTrust((ch)))
#define IS_STAFF(ch)	(GET_TRUST(ch) >= TRUST_STAFF)
#define STF_FLAGGED(ch, flag)		(IS_STAFF(ch) && IS_SET(STF_FLAGS(ch), (flag)))



#endif	// __PERMISSIONS_HPP__	
