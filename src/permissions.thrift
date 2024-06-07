enum Trust {
    TRUST_PLAYER    = 0,
	TRUST_IMMORT	= 1,
	TRUST_STAFF		= 2,
	TRUST_SRSTAFF	= 3,
	TRUST_ADMIN		= 4,
	TRUST_CODER		= 5,
	TOP,

	TRUST_FREEZE	= 4
}


enum MemberPermissions {
    CODER_VIEW				,			// Coders and no others can view this value at runtime
	CREATOR_VIEW			,			// Element's creator(s) can view this value
	STAFF_VIEW				,			// Other staff members can view this value
	WORLD_VIEW				,			// The outside world can view this value
	SCRIPT_VIEW				,			// Scripts are allowed to view, if above permissions check out
	PLAYER_VIEW				,			// Players can view this value (use with care!)
	CODER_WRITE				,			// Element's creator(s) can change this value
	CREATOR_WRITE			,			// Element's creator(s) can change this value
	STAFF_WRITE				,			// Other staff members can change this value
	WORLD_WRITE				,			// The outside world can change this value
	SCRIPT_WRITE			,			// Scripts are allowed to change, if above permissions check out
	PLAYER_WRITE			,			// Players can change this value (use with care!)
	CODER_DERIVE			,			// Element's creator(s) can derive this value
	CREATOR_DERIVE			,			// Element's creator(s) can derive this value
	STAFF_DERIVE			,		// Other staff members can derive this value
	WORLD_DERIVE			,		// The outside world can derive this value
	SCRIPT_DERIVE			,		// Scripts are allowed to derive, if above permissions check out
	PLAYER_DERIVE			,		// Players can derive this value (use with care!)
	NUM_MEMBER_PERMISSIONS
}
	
//  Staff Flags
enum StaffCommands {
    STAFF_GENERAL     ,	     //  General commands
    STAFF_ADMIN       ,	     //  Administration
    STAFF_SECURITY    ,	     //  Player Relations - Security
    STAFF_GAME        ,	     //  Game Control
    STAFF_OLC         ,	     //  Houses
    STAFF_CHARS       ,	     //  Player Relations - Character Maint.
    STAFF_CLANS       ,	     //  Clans
    STAFF_MOBILES     ,	     //  Medit
    STAFF_OBJECTS     ,	     //  Oedit
    STAFF_ROOMS       ,	     //  Redit
    STAFF_OLCADMIN    ,	    //  OLC Administration
    STAFF_SOCIALS     ,	    //  AEdit
    STAFF_HELP        ,	    //  HEdit
    STAFF_SHOPS       ,	    //  SEdit
    STAFF_SCRIPTS     ,    //  ScriptEdit
    STAFF_FORCE       ,    //  IMC Commands
    STAFF_CODER       ,
    STAFF_WIZNET      ,
    STAFF_INVULN      ,
    STAFF_ALLOW       ,    //  Administration
    STAFF_EXTRA       ,
    STAFF_SKILLED     ,
    STAFF_IMC         ,
    NUM_STAFF_COMMANDS
}
