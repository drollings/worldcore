#ifndef __BINARYBLOCK_HPP__
#define __BINARYBLOCK_HPP__

//
// C++ interface: binaryblock
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
#include "Templates/sorted_node_vector.hpp"

// The idea behind this is to provide blocks of data that can be written directly
// from memory to disk, and read back with extra parsing to restore the state of
// things rapidly.


namespace Block
{
	struct BlockHeader
	{
					BlockHeader(void) : genus(0), size(0), revision(0) {}

		SInt32		genus;
		UInt32		size;
		UInt32		revision;
	};
	
	template < class _T_ >
	struct BlockNode
	{
					BlockNode(void) : _block_ID(0) {}

		IDNum		_block_ID;
		_T_			_block;
	};

	template < class _T_ >
	class BlockVector : public < BlockNode <_T_> >
	{
	public:
												BlockVector(void) : _empty(NULL) {};
												~BlockVector(void) {};
												
	private:
		BlockNode<_T_>							*_empty;

	public:
		BlockNode<_T_> *						_GetNewNode(void) 
		{
			BlockNode<_T_> *	retval = NULL;
			int n;
			
			if (_empty) {
				retval = _empty;
				_empty = NULL;
			} else {
				n = this->size();
				this->resize(n + 1000);
				return &((*this)[n]);
			}
			return retval;
		}
		
		void									_SetEmpty(BlockNode<_T_> *n)
		{
			if (_empty && _empty > n)			_empty = n;
		}
	};

	
	struct BlockFile
	{
					BlockFile(void) {}
		
		BlockHeader	fileHeader;
	};


	template < class _T_ >
	class BlockSavedPtr
	{
	public:
												BlockSavedPtr(void) : _blockNode(NULL)	{}
		virtual 								~BlockSavedPtr(void)
												{	if (_blockNode)		_blockNode->_block_ID = 0;	}

	protected:
		BlockNode<_T_>							*_blockNode;		// To point to a binaryblock

	public:
		inline _T_ *							operator->(void) const	
		{	
			return &((*_blockNode)._block);
		}

		BlockSavedPtr<_T_> &					operator=(::Block::BlockNode<_T_> &n)	
		{	
			if (_blockNode && _blockNode != n)	_blockNode->_block_ID = 0;
			_blockNode = &n;	
			return *this;
		}

		BlockSavedPtr<_T_> &					operator=(::Block::BlockNode<_T_> *n)	
		{	
			if (_blockNode && _blockNode != n)	_blockNode->_block_ID = 0;
			_blockNode = n;	
			return *this;
		}
	};
}



#endif
