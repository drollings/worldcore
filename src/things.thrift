 namespace cpp Things

enum Offsets {
	NAME,
	PROTO,
	INSIDE,
	PROXIMITY,
	GENUS,
	MASS,
	TEMPERATURE,
	QUANTITY,

	KEY,
	OPENSKILL,
	OPENDIFFICULTY,
	
	TO_THING,
	FROM_THING,
	METERSWIDE,
	THETA,
	
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
	WILLPOWER,
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
	HITRANGE,
	
	TOP
}

enum Position {
	Limp,
	Prone,
	Upright,
	Sitting,
	Kneeling,
	Crouching,
	Crawling,
	Standing,
	Floating,
	NUM_POSITIONS
}

enum State {
	Dead,
	Dying,
	MortallyWounded,
	Incapacitated,
	Asleep,
	Stunned,
	Immobile,
	Resting,
	Fighting,
	Riding,			// USE THIS FOR COMMAND CHECKS ONLY!  This is a recipe for bugs otherwise.
	Audible,		// See above.
	Okay,
	NUM_STATES
}

enum ThingFlag {
	DELETED			= 1,		// Allowed to interact with regular players
	APPROVED		= 2,		// Allowed to interact with regular players
	NPC				= 4, 		// Is a NPC
	MALE			= 8, 		// Is male
	FEMALE			= 16, 		// Is female
	PLURAL			= 32,		// Referred to in a plural sense
	HIDDEN			= 64,		// Has hide aspects on it
	FROZEN			= 128,		// In a frozen state; will not respond to triggers or commands
	OPENABLE		= 256,
	OPEN			= 512,
	SEETHRU			= 1024,
	INVSTART		= 2048,

	NUM_THINGFLAGS
}
