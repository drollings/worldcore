#ifndef __STRING_HPP__
#define __STRING_HPP__

//
// C++ Interface: typedefs
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <string>
#include <map>
#include <list>


class String;
typedef		std::list<String>				StringTable;
typedef		std::list<String>				StringList;
typedef		std::map<String, String>		StringMap;



class String : public std::string
{
public:
	
};


#endif	// __STRING_HPP__
