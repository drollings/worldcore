#ifndef __SORTED_NODE_VECTOR_HPP__
#define __SORTED_NODE_VECTOR_HPP__

//
// C++ Interface: templates
//
// Description:  
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <vector>

namespace Templates
{
	template < typename _KeyT_, typename _ValT_ >
	struct SortedNode
	{
		_KeyT_			key;
		_ValT_			val;

		inline SortedNode< _KeyT_, _ValT_ > & operator = (const _ValT_ *b)
	    {	
	    	val = b;
	    	return *this;
	    }	
		inline SortedNode< _KeyT_, _ValT_ > & operator = (_ValT_ *b)
	    {	
	    	val = b;
	    	return *this;
	    }	

	};

	template < typename _KeyT_, typename _ValT_ >
	inline bool operator < (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key < b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator > (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key > b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator == (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key == b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator <= (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key <= b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator >= (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key >= b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator != (const SortedNode< _KeyT_, _ValT_ > &a, const SortedNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key != b.key);	}	
    
	template < typename _KeyT_, typename _ValT_ >
	inline bool operator < (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key < n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator > (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key > n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator == (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key == n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator <= (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key <= n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator >= (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key >= n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator != (const SortedNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key != n);	}

	template < typename _KeyT_, typename _ValT_ >
	inline const _ValT_ & operator * (const SortedNode< _KeyT_, _ValT_ > &a)	
    {	return a.val;	}	

	template < typename _KeyT_, typename _ValT_ >
	inline _ValT_ & operator * (SortedNode< _KeyT_, _ValT_ > &a)	
    {	return a.val;	}	


	template < typename _KeyT_, typename _ValT_ >
	class sorted_node_vector : public std::vector< SortedNode< _KeyT_, _ValT_ > >
	{
	protected:
		bool				sorted;
		
		typedef				SortedNode< _KeyT_, _ValT_ >	_nodeType_;
		typedef				std::vector< SortedNode< _KeyT_, _ValT_ > > _vectorType_;
		
		inline void			BinarySearch(_KeyT_ &key, _KeyT_ &mid, const _nodeType_ **node) const
		{
			_KeyT_			lower, upper;
	
			assert (!sorted);
			
			upper = _vectorType_::size();
			if (upper == 0) {
				mid = -1;
				node = NULL;
				return;
			}
	
			lower = 0;
	
			while (lower <= upper) {
				mid = (lower + upper) / 2;
				*node = &(_vectorType_::operator[](mid));
	
				if (**node < key)		lower = mid + 1;
				else if (**node > key)	upper = mid - 1;
				else					return;
			}
			mid = -1;
			node = NULL;
		}

	public:
		const _ValT_ *			GetByKey(_KeyT_ key) const
		{
			_KeyT_					mid;
			const _nodeType_		*node;

			BinarySearch(key, mid, &node);

			if (node)		return &**node;
			return NULL;
		}
		
		int			IndexOf(_KeyT_ key) const
		{
			_KeyT_					mid;
			const _nodeType_		*node;
			
			BinarySearch(key, mid, &node);
			return mid;
		}

		void		Insert(_KeyT_ key, _ValT_ val)
		{
			sorted = false;
			_vectorType_::resize(_vectorType_::size() + 1);
			_nodeType_	* ref = &(operator[](_vectorType_::size() - 1));
			ref->key = key;
			ref->val = val;
		}
		
		void		Sort(void) {
			if (!sorted) {
				sort(_vectorType_::begin(), _vectorType_::end());
				sorted = true;
			}	
		}
		
	};





	template < typename _KeyT_, typename _ValT_ >
	struct SortedPtrNode
	{
		_KeyT_			key;
		_ValT_			*ptr;

		inline SortedPtrNode< _KeyT_, _ValT_ > & operator = (const _ValT_ *b)
	    {	
	    	ptr = b;
	    	return *this;
	    }	
		inline SortedPtrNode< _KeyT_, _ValT_ > & operator = (_ValT_ *b)
	    {	
	    	ptr = b;
	    	return *this;
	    }	

	};

	template < typename _KeyT_, typename _ValT_ >
	inline bool operator < (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key < b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator > (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key > b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator == (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key == b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator <= (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key <= b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator >= (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key >= b.key);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator != (const SortedPtrNode< _KeyT_, _ValT_ > &a, const SortedPtrNode< _KeyT_, _ValT_ > &b)	
    {	return (a.key != b.key);	}	
    
	template < typename _KeyT_, typename _ValT_ >
	inline bool operator < (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key < n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator > (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key > n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator == (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key == n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator <= (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key <= n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator >= (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key >= n);	}	
	template < typename _KeyT_, typename _ValT_ >
    inline bool operator != (const SortedPtrNode< _KeyT_, _ValT_ > &a, const _KeyT_ &n)	
    {	return (a.key != n);	}

	template < typename _KeyT_, typename _ValT_ >
	inline _ValT_ & operator * (const SortedPtrNode< _KeyT_, _ValT_ > &a)	
    {	return *(a.ptr);	}	



	template < typename _KeyT_, typename _ValT_ >
	class sorted_pointer_node_vector : public std::vector< SortedPtrNode< _KeyT_, _ValT_ > >
	{
	protected:
		bool				sorted;
		
		typedef				SortedPtrNode< _KeyT_, _ValT_ >	_nodeType_;
		typedef				std::vector< SortedPtrNode< _KeyT_, _ValT_ > > _vectorType_;
		
		inline void			BinarySearch(_KeyT_ &key, _KeyT_ &mid, const _nodeType_ **node) const
		{
			_KeyT_			lower, upper;
	
			assert (!sorted);
						
			upper = _vectorType_::size();
			if (upper == 0) {
				mid = -1;
				node = NULL;
				return;
			}
	
			lower = 0;
	
			while (lower <= upper) {
				mid = (lower + upper) / 2;
				*node = &(_vectorType_::operator[](mid));
	
				if (**node < key)		lower = mid + 1;
				else if (**node > key)	upper = mid - 1;
				else					return;
			}
			mid = -1;
			node = NULL;
		}

	public:
		_ValT_ *			GetByKey(_KeyT_ key) const
		{
			_KeyT_					mid;
			const _nodeType_		*node;

			BinarySearch(key, mid, &node);

			if (node)		return &**node;
			return NULL;
		}
		
		int			IndexOf(_KeyT_ key) const
		{
			_KeyT_					mid;
			const _nodeType_		*node;
			
			BinarySearch(key, mid, &node);
			return mid;
		}

		void		Insert(_KeyT_ key, _ValT_ val)
		{
			sorted = false;
			_vectorType_::resize(_vectorType_::size() + 1);
			_nodeType_	* ref = &(this->operator[](_vectorType_::size() - 1));
			ref->key = key;
			ref->ptr = &val;
		}
		
		void		Sort(void)
		{
			if (!sorted) {
				sort(_vectorType_::begin(), _vectorType_::end());
				sorted = true;
			}	
		}
		
	};


}


#endif
