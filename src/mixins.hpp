#ifndef __MIXINS_HPP__
#define __MIXINS_HPP__

//
// C++ Interface: mixins
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

namespace Mixins
{
#if 0
	//####################################################################
	//
	class Openable
	{
	public:
								Openable(void);
		virtual 				~Openable(void) = 0;

		virtual bool			IsOpenable(void) const = 0;
		virtual bool			IsLockable(void) const = 0;
		virtual bool			IsPickable(void) const = 0;
		virtual bool			IsOpen(void) const = 0;
		virtual bool			IsLocked(void) const = 0;
		virtual bool			IsSeeThru(void) const = 0;

		virtual void			SetOpenable(void) = 0;
		virtual void			SetLockable(void) = 0;
		virtual void			SetOpen(void) = 0;
		virtual void			SetClosed(void) = 0;
		virtual void			SetLocked(void) = 0;
		virtual void			SetUnlocked(void) = 0;
	};
#endif

}


#endif	// __MIXINS_HPP__
