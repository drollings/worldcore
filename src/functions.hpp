#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

//
// C++ SInterface: functions
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "typedefs.hpp"


namespace Random
{
	UInt32				Random(void);
	inline int			RandomSInt(int lo, int hi) {		return ((Random() % (hi - lo)) + lo);		}
}

namespace Dice
{
	extern UInt8		table_3d6[];
	extern UInt8		table_3d20[];
	inline void			Roll3d6(int &output)	{	output = table_3d6[Random::Random() % 200];	}
	inline void			Roll3d20(int &output)	{	output = table_3d20[Random::Random() % 206];	}
	inline int			Roll3d6(void)			{	return table_3d6[Random::Random() % 200];	}
	inline int			Roll3d20(void)			{	return table_3d20[Random::Random() % 206];	}

	inline int			Roll(UInt8 num, UInt16 size)	
	{
		int sum = 0;
		while (num > 0) {
			sum += Random::RandomSInt(1, size);
			--num;
		}
		return sum;
	}
}



#endif	// __FUNCTIONS_HPP__
