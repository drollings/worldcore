namespace cpp Base

enum EngineFlags {
	PURGED			= 1,		// Flagged for removal
	DIRTY			= 2,		// Flagged for serializtion
	SUPER			= 4,		// Flagged to perform maximally
	AFFECTED		= 8,		// Has Affects on it
	BUSY			= 16		// Works like PLR_MAILING or PLR_EDITING, this object is busy with something
}


