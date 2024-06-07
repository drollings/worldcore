#ifndef __MACROS_HPP__
#define __MACROS_HPP__

//
// C++ Interface: macros
//
// Description: 
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#define PURGED(i)		((i)->IsPurged())
#define GET_ID(i)		((i)->GetID())

/* basic bitvector utils *************************************************/


#define IS_SET(flag,bit)  ((flag) & (bit))
#define SET_BIT(var,bit)  ((var) |= (bit))
#define REMOVE_BIT(var,bit)  ((var) &= ~(bit))
#define TOGGLE_BIT(var,bit) ((var) ^= (bit))

#ifdef MAX
#undef MAX
#endif
#ifdef MIN
#undef MIN
#endif

inline int MIN(int a, int b) {  return a < b ? a : b; }
inline int MAX(int a, int b) { return a > b ? a : b; }
inline int RANGE(int var, int low, int high) { return MAX(low, MIN(high, var)); }
inline unsigned int MIN(unsigned int a, unsigned int b) {   return a < b ? a : b; }
inline unsigned int MAX(unsigned int a, unsigned int b) { return a > b ? a : b; }
inline unsigned int RANGE(unsigned int var, unsigned int low, unsigned int high) { return MAX(low, MIN(high, var)); }
inline float MIN(float a, float b) { return a < b ? a : b; }
inline float MAX(float a, float b) { return a > b ? a : b; }
inline float RANGE(float var, float low, float high) { return MAX(low, MIN(high, var)); }
inline long long MIN(long long a, long long b) { return a < b ? a : b; }
inline long long MAX(long long a, long long b) { return a > b ? a : b; }
inline long long RANGE(long long var, long long low, long long high) { return MAX(low, MIN(high, var)); }

#define DECLARE_MEMBER_COMPARISON_OPERATORS(_strct, _keyType, _key) \
	inline bool operator < (const _strct &b)	{	return (_key < b._key);	}	\
    inline bool operator > (const _strct &b)	{	return (_key > b._key);	}	\
    inline bool operator == (const _strct &b)	{	return (_key == b._key);	}	\
    inline bool operator <= (const _strct &b)	{	return (_key <= b._key);	}	\
    inline bool operator >= (const _strct &b)	{	return (_key >= b._key);	}	\
    inline bool operator != (const _strct &b)	{	return (_key != b._key);	}	\
    \
	inline bool operator < (const _keyType &n)	{	return (_key < n);	}	\
    inline bool operator > (const _keyType &n)	{	return (_key > n);	}	\
    inline bool operator == (const _keyType &n)	{	return (_key == n);	}	\
    inline bool operator <= (const _keyType &n)	{	return (_key <= n);	}	\
    inline bool operator >= (const _keyType &n)	{	return (_key >= n);	}	\
    inline bool operator != (const _keyType &n)	{	return (_key != n);	}


#define DECLARE_KEY_COMPARISON_OPERATORS(_strct, _keyType, _key) \
	inline bool operator < (const _strct &a, const _strct &b)	{	return (a._key < b._key);	}	\
    inline bool operator > (const _strct &a, const _strct &b)	{	return (a._key > b._key);	}	\
    inline bool operator == (const _strct &a, const _strct &b)	{	return (a._key == b._key);	}	\
    inline bool operator <= (const _strct &a, const _strct &b)	{	return (a._key <= b._key);	}	\
    inline bool operator >= (const _strct &a, const _strct &b)	{	return (a._key >= b._key);	}	\
    inline bool operator != (const _strct &a, const _strct &b)	{	return (a._key != b._key);	}	\
    \
	inline bool operator < (const _strct &a, const _keyType &n)	{	return (a._key < n);	}	\
    inline bool operator > (const _strct &a, const _keyType &n)	{	return (a._key > n);	}	\
    inline bool operator == (const _strct &a, const _keyType &n)	{	return (a._key == n);	}	\
    inline bool operator <= (const _strct &a, const _keyType &n)	{	return (a._key <= n);	}	\
    inline bool operator >= (const _strct &a, const _keyType &n)	{	return (a._key >= n);	}	\
    inline bool operator != (const _strct &a, const _keyType &n)	{	return (a._key != n);	}

#endif	// __MACROS_HPP__
