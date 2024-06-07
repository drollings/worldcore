//
// C++ Implementation: mixins
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "macros.hpp"
#include "typedefs.hpp"
#include "mixins.hpp"

#define	OPENABLE_OPENABLE		(1 << 0)
#define	OPENABLE_LOCKABLE		(1 << 1)
#define	OPENABLE_PICKABLE		(1 << 2)
#define	OPENABLE_OPEN			(1 << 3)
#define	OPENABLE_LOCKED			(1 << 4)
#define	OPENABLE_SEETHRU		(1 << 5)


namespace Mixins
{
#if 0
	//########################################################################
	// For the Openable class
	Openable::Openable(void) : _flOpenableStates(0)	{}

	bool Openable::IsOpenable(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_OPENABLE);	}
	bool Openable::IsLockable(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_LOCKABLE);	}
	bool Openable::IsPickable(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_PICKABLE);	}
	bool Openable::IsOpen(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_OPEN);	}
	bool Openable::IsLocked(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_LOCKED);	}
	bool Openable::IsSeeThru(void) const	{	return IS_SET(_flOpenableStates, OPENABLE_SEETHRU);	}

	void Openable::SetOpen(void)		{	SET_BIT(_flOpenableStates, OPENABLE_OPEN);		}
	void Openable::SetClosed(void)		{	REMOVE_BIT(_flOpenableStates, OPENABLE_OPEN);		}
	void Openable::SetLocked(void)		{	SET_BIT(_flOpenableStates, OPENABLE_LOCKED);		}
	void Openable::SetUnlocked(void)	{	REMOVE_BIT(_flOpenableStates, OPENABLE_LOCKED);		}
#endif

}
