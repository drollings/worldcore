#ifndef __WEAKPTR_HPP__
#define __WEAKPTR_HPP__

//
// C++ SInterface: WeakPtr
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) December 3, 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

// This class is designed for ease of use over the alternatives, i.e. Boost's pointers.
// The one drawback is that it relies on WeakRefable<T> as a mixin for any class that this
// is going to work for.

template<class _T_>	class WeakRefNode;
template<class _T_>	class WeakRef;

#if 0
#include <iostream>
using namespace std;
#endif

template<class _T_>
class WeakRefable
{
public:
						// WeakRefable(void) : _pWeakRefNode(new WeakRefNode<_T_>((_T_ *)this)) {};
						WeakRefable(void) : _pWeakRefNode(NULL) {};
				virtual	~WeakRefable(void) { 
					DeleteWeakRefNode();
				}
				
				inline void DeleteWeakRefNode(void) {
					#if 0
					cout << "Deleting WeakRefable " << this << endl;
					#endif
					if (_pWeakRefNode) {
						_pWeakRefNode->_pWeakRefable = NULL; 
						if (_pWeakRefNode->_refcount == 0) {
							delete _pWeakRefNode;
						}
					}
				}
						
				// We're circumventing an aspect of const-ness here because this stuff is exclusive to this WeakRef scheme.
				inline void	MakeWeakRefNode(void) const 
				{	
					if (!_pWeakRefNode) {
						((_T_ *)this)->_pWeakRefNode = new WeakRefNode<_T_>((_T_ *) this);	
					}
				}

private:
	WeakRefNode<_T_>	*_pWeakRefNode;
	
	friend class WeakRef<_T_>;
};



template<class _T_>
class WeakRefNode
{
public:
						WeakRefNode(_T_ *o) : _pWeakRefable(o), _refcount(0) {};
						~WeakRefNode(void) 
						{
							#if 0
							cout << "Deleting WeakRefNode" << this << endl;
							#endif
						}
private:
	inline void Retain(void) {	++_refcount;	}

	inline void Release(void) {
		if (_pWeakRefable == NULL && _refcount <= 1) {
			delete this;
			return;
		}
		if (!_refcount)	return;
		--_refcount;
	}

	_T_					*_pWeakRefable;
	unsigned int		_refcount;
	
	friend class WeakRefable<_T_>;
	friend class WeakRef<_T_>;
};


template<class _T_>	
class WeakRef
{
public:
						WeakRef(void) : _pWeakRefNode(NULL) {};
						WeakRef(WeakRef<_T_> &other) : _pWeakRefNode(other._pWeakRefNode)	{	if (_pWeakRefNode) _pWeakRefNode->Retain();	}
						WeakRef(WeakRefable<_T_> *base) {	
							base->MakeWeakRefNode();
							_pWeakRefNode = base->_pWeakRefNode;
							if (_pWeakRefNode) _pWeakRefNode->Retain();	
						}
						~WeakRef(void) {	
							#if 0
							cout << "Deleting WeakRef " << this << endl;
							#endif
							if (_pWeakRefNode)	_pWeakRefNode->Release(); 
						}

	WeakRef<_T_> &		operator=(void *ptr) {	
		if (ptr && _pWeakRefNode && (void *)_pWeakRefNode == ((WeakRefable<_T_> *) ptr)->_pWeakRefNode)
		{
			#if 0
			cout << "Not setting weak ref " << this << " to " << ptr << " - already same." << endl;
			#endif
			return *this;	// They're already the same
		}
		
		if (_pWeakRefNode)	_pWeakRefNode->Release();
		((WeakRefable<_T_> *) ptr)->MakeWeakRefNode();
		_pWeakRefNode = ((WeakRefable<_T_> *) ptr)->_pWeakRefNode;
		if (_pWeakRefNode)	_pWeakRefNode->Retain();

		#if 0
		cout << "Setting weak ref " << this << " to " << ptr << " with reference count " << _pWeakRefNode->_refcount << endl;
		#endif
				
		return *this;
	}
	WeakRef<_T_> &		operator=(const WeakRefable<_T_> *other) {	
		if (_pWeakRefNode && _pWeakRefNode == other->_pWeakRefNode) {
			#if 0
			cout << "Not setting weak ref " << this << " to " << other << " ; already same." << endl;
			#endif
			return *this;	// They're already the same
		}
		
		if (_pWeakRefNode)	_pWeakRefNode->Release();
		other->MakeWeakRefNode();
		_pWeakRefNode = other->_pWeakRefNode;
		if (_pWeakRefNode)	_pWeakRefNode->Retain();

		#if 0
		cout << "Setting weak ref " << this << " to " << other << " with reference count " << _pWeakRefNode->_refcount << endl;
		#endif
		
		return *this;
	}
	WeakRef<_T_> &		operator=(const WeakRefable<_T_> &other) {	
		if (_pWeakRefNode && _pWeakRefNode == other._pWeakRefNode) {
			#if 0
			cout << "Not setting weak ref " << this << " to " << &other << " ; already same." << endl;
			#endif
			return *this;	// They're already the same
		}
		
		if (_pWeakRefNode)	_pWeakRefNode->Release();
		other.MakeWeakRefNode();
		_pWeakRefNode = other._pWeakRefNode;
		if (_pWeakRefNode)	_pWeakRefNode->Retain();

		#if 0
		cout << "Setting weak ref " << this << " to " << &other << " with reference count " << _pWeakRefNode->_refcount << endl;
		#endif
		
		return *this;
	}
	WeakRef<_T_> &		operator=(const WeakRef<_T_> &other) {	
		if (_pWeakRefNode == other._pWeakRefNode) {
			#if 0
			cout << "Not setting weak ref " << this << " to " << &other << " ; already same." << endl;
			#endif
			return *this;	// They're already the same
		}
		
		if (_pWeakRefNode)	_pWeakRefNode->Release();
		other.MakeWeakRefNode();
		_pWeakRefNode = other._pWeakRefNode;
		if (_pWeakRefNode)	_pWeakRefNode->Retain();
		
		#if 0
		cout << "Setting weak ref " << this << " to " << &other << " with reference count " << _pWeakRefNode->_refcount << endl;
		#endif
		
		return *this;
	}
	#if 0
	WeakRef<_T_> &		operator=(const WeakRefNode<_T_> &other) {	
		if (_pWeakRefNode == &other) {
			#if 0
			cout << "Not setting weak ref " << this << " to " << &other << " ; already same." << endl;
			#endif
			return *this;	// They're already the same
		}

		
		if (_pWeakRefNode)	_pWeakRefNode->Release();
		_pWeakRefNode = &other;
		other.Retain();
		
		#if 0
		cout << "Setting weak ref " << this << " to " << &other << " with reference count " << _pWeakRefNode->_refcount << endl;
		#endif
		
		return *this;
	}
	#endif

	inline bool			operator==(const WeakRef<_T_> &other) const { return _pWeakRefNode == other._pWeakRefNode; }
	inline bool			operator==(const WeakRefable<_T_> *object) const { return _pWeakRefNode == object->GetWeakRefNode(); }
	inline bool			operator==(const WeakRefable<_T_> &object) const { return _pWeakRefNode == object.GetWeakRefNode(); }
	inline bool			operator!=(const WeakRef<_T_> &other) const { return _pWeakRefNode != other._pWeakRefNode; }
	inline bool			operator!=(const WeakRefable<_T_> *object) const { return _pWeakRefNode != object->GetWeakRefNode(); }
	inline bool			operator!=(const WeakRefable<_T_> &object) const { return _pWeakRefNode != object.GetWeakRefNode(); }
	
	inline bool			valid(void) const			{ return (_pWeakRefNode != NULL && (_pWeakRefNode->_pWeakRefable));	}
	inline bool			operator!(void) const		{ return (_pWeakRefNode == NULL || !(_pWeakRefNode->_pWeakRefable));	}
	inline 				operator bool(void) const	{ return (_pWeakRefNode != NULL && (_pWeakRefNode->_pWeakRefable));	}
	
	inline _T_ *		operator*(void) const		{ return (_pWeakRefNode ? _pWeakRefNode->_pWeakRefable : NULL); }
	
	inline void			Clear(void) { 
		if (_pWeakRefNode) {
			#if 0
			cout << "Clearing weak ref " << this << " with reference count " << _pWeakRefNode->_refcount << endl;
			#endif
			_pWeakRefNode->Release();
		}
		_pWeakRefNode = NULL;
	}
	
	inline int			Count(void) {
		if (_pWeakRefNode) {
			return _pWeakRefNode->_refcount;
		}
		return 0;
	}

protected:
	
	WeakRefNode<_T_>	*_pWeakRefNode;
};


#endif	// __WEAKPTR_HPP__
