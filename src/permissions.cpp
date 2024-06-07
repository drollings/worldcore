//
// C++ Implementation: permissions
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "permissions.hpp"

namespace Permissions
{
	const char *			memberPermissionsFlagsStrings[] = {
		"CODER_VIEW",
		"CREATOR_VIEW",
		"STAFF_VIEW",
		"WORLD_VIEW",
		"SCRIPT_VIEW",
		"PLAYER_VIEW",
		"CODER_WRITE",
		"CREATOR_WRITE",
		"STAFF_WRITE",
		"WORLD_WRITE",
		"SCRIPT_WRITE",
		"PLAYER_WRITE",
		"CODER_DERIVE",
		"CREATOR_DERIVE",
		"STAFF_DERIVE",
		"WORLD_DERIVE",
		"SCRIPT_DERIVE",
		"PLAYER_DERIVE",
		"\n",
	};
	
	const Flags	permCoder = CODER_VIEW;
	const Flags	permCreator = permCoder | CREATOR_VIEW | CREATOR_WRITE;
	const Flags	permStaff = permCreator | STAFF_VIEW | STAFF_WRITE;
	const Flags	permWorld = permStaff | WORLD_VIEW | WORLD_WRITE;
	const Flags	permScript = permWorld | SCRIPT_VIEW | SCRIPT_WRITE;
	const Flags	permPlayer = PLAYER_VIEW | PLAYER_WRITE;
	
}


