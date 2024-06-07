#ifndef __MATERIALS_HPP__
#define __MATERIALS_HPP__

//
// C++ Interface: materials
//
// Description: 
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


//####################################################################
// 
namespace Material
{
	
	class Material
	{
	private:
		float				temperature;
		
	public:
		virtual 			~Material() = 0;
		
		bool				IsMetallic(void);
		bool				IsOrganic(void);
		bool				IsStone(void);
	};

}
	
	
#endif	// __MATERIALS_HPP__
