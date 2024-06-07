namespace cpp Skills

//########################################################################
enum Flags {
	LEARNABLE		= 1,
	STAT			= 2,
	SKILL			= 4,
	PRAYER			= 8,
	COMBATMOVE		= 16,
	WEAPONPROF		= 32,
	LANGUAGE		= 64,
	STEALTH			= 128,
	MAGICROOT		= 256,
	MAGICMETHOD		= 512,
	MAGICTECHNIQUE	= 1024,
	MAGICSPELL		= 2048,
	ORDINATION		= 4096,
	SPHERE			= 8192,
	VOW				= 16384,
	PSI				= 32768,
	DEFAULT			= 65536
}

enum Targets
{
	Ignore		= 1,		//  IGNORE TARGET
	CharRoom	= 2,		//  PC/NPC in room
	CharWorld   = 4,		//  PC/NPC in world
	FightSelf   = 8,		//  If fighting, and no argument, target is self
	FightVict   = 16,		//  If fighting, and no argument, target is opponent
	SelfOnly	= 32,		//  Flag: Self only
	NotSelf		= 64,		//  Flag: Anybody BUT self
	ObjInv		= 128,		//  Object in inventory
	ObjRoom		= 256,		//  Object in room
	ObjWorld	= 512,		//  Object in world
	ObjEquip	= 1024,		//  Object held
	ObjDest		= 2048,
	CharObj		= 4096,		//  Object character is holding
	IgnChar		= 8192,
	IgnObj		= 16384,
	Melee		= 32768,	//  Spell only hits at melee range
	Ranged		= 65536		//  Spell can hit targets in other rooms
}

enum Stats
{
	SKLBASE_STR			= 1,
	SKLBASE_INT			= 2,
	SKLBASE_AGI			= 4,
	SKLBASE_HT			= 8,
	SKLBASE_VISION		= 16,
	SKLBASE_HEARING		= 32,
	SKLBASE_MOVE		= 64
}

enum StatBases
{
	STAT_STR,
	STAT_INT,
	STAT_AGI,
	STAT_HT,
	STAT_VISION,
	STAT_HEARING,
	STAT_MOVE,
	STAT_MAX,
	TOP
}


//     enum {
// 		SKLBASE_STR	 = (1 << 0),
// 		SKLBASE_INT	 = (1 << 1),
// 		SKLBASE_AGI	 = (1 << 2),
// 		SKLBASE_HT	 = (1 << 3),
// 		SKLBASE_VISION	 = (1 << 4),
// 		SKLBASE_HEARING	 = (1 << 5),
// 		SKLBASE_MOVE	 = (1 << 6)
// 	};
// 	extern const char *					skillBaseStrings[];
// 	
//     enum {
// 		STAT_STR,
// 		STAT_INT,
// 		STAT_AGI,
// 		STAT_HT,
// 		STAT_VISION,
// 		STAT_HEARING,
// 		STAT_MOVE,
// 		STAT_MAX
// 	};
// 	extern const char *					skillStatStrings[];

