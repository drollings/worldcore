#ifndef __STRING_TYPE_TABLE_HPP__
#define __STRING_TYPE_TABLE_HPP__

//
// C++ Interface: StringTypeTable
//
// Description:  A series of preprocessor macros that can create templates.  Why this approach?  Speed.
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "sorted_node_vector.h"

namespace Templates
{
	template < typename _K_, typename _T_ >
	class StringTypeTable : public std::vector< _T_ >
	{
	public:
										TypeTable(void) {};
		virtual							~TypeTable(void) {};

		void							reset(void) 
		{
			m_KeysToOffsets.reset();
			_vectorType_::reset();
		}
		
		void							push_back( _T_ &val)
		{
		}
		
		void							push_front( _T_ &val)
		{
		}
		
		_T_ &							operator[]( size_t idx )
		{
		}
		
		_T_ &							operator[]( _K_ key )
		{
		}
		
		void							operator[]=( size_t idx, _T_ &val )
		{
		}
		
		void							operator[]=( _K_ &key, _T_ &val )
		{
		}
		
		
		
	protected:
		typedef std::vector< _T_ >		_vectorType_;
		Templates::sorted_node_vector < _K_, size_t >	m_KeysToOffsets;
	};


};

#endif