/***************************************************************************\
[*]    __     __  ___                ___  | LexiMUD is a C++ MUD codebase [*]
[*]   / /  ___\ \/ (_) /\/\  /\ /\  /   \ |        for Sci-Fi MUDs        [*]
[*]  / /  / _ \\  /| |/    \/ / \ \/ /\ / | Copyright(C) 1997-2005        [*]
[*] / /__|  __//  \| / /\/\ \ \_/ / /_//  | All rights reserved           [*]
[*] \____/\___/_/\_\_\/    \/\___/___,'   | Chris Jacobson (FearItself)   [*]
[*]      A Creation of the AvP Team!      | fearitself@avpmud.com         [*]
[-]---------------------------------------+-------------------------------[-]
[*] Advanced Buffer System by George Greer, Copyright (C) 1998-99         [*]
[-]-----------------------------------------------------------------------[-]
[*] File : buffer.h                                                       [*]
[*] Usage: Advanced Buffer System                                         [*]
\***************************************************************************/

#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__


#include "typedefs.hpp"
#include <stdlib.h>


//	CONFIGURABLES (aka, The place to shoot your own foot.) :)
//	---------------------------------------------------------
#define BUFFER_THREADED				0	//	Use threads
#define MAX_BUFFER_LENGTH	65536
#define MAX_STRING_LENGTH	8192

class Buffer {
public:
	enum Type {			//	Types for the memory to allocate.
		tBuffer,		//	Stack type memory.
		tPersist,		//	A buffer that doesn't time out.
		tMalloc			//	A malloc() memory tracker.
	};
	
//protected:
					Buffer(size_t size, Type type);
					~Buffer(void);
	
	Type			Clear(void);
	void			Remove(void);
	int				Used(void);
	int				Magnitude(void);
	
	char			magic;			//	Have we been trashed?
	Type			type;			//	What type of buffer are we?
	size_t			req_size;		//	How much did the function request?
	const size_t	size;			//	How large is this buffer realy?
	char *			data;			//	The buffer passed back to functions
public:
	Buffer *		next;			//	Next structure
	
#if BUFFER_THREADED
	enum tLock {
		lockNone		= 0,
		lockAcquire		= 1 << 0,
		lockWillClear	= 1 << 1,
		lockWillFree	= 1 << 2,
		lockWillRemove	= 1 << 3
	} locked;						//	Don't touch this item, we're locked.
	
	void Lock(tLock type, const char *func, int line);
	void Unlock(const char *func, int line);
	
	static void *ThreadFunc(void *);
	static void ListLock(const char *func, int line);
	static void ListUnlock(const char *func, int line);
#endif
	
public:
	union {
		int			life;		//	An idle counter to free unused ones.	(B)
		const char *	var;		//	Name of variable allocated to.			(M)
	};
	int			line;			//	What source code line is using this.
	const char	*	who;			//	Name of the function using this
	
	void			Check(void);
	
public:
	static void		Init(void);
	static void		Exit(void);
	
	static void		Reboot(void);
	
	static Buffer **Head(Type type);
//	static void		Lock(Type type);
//	static void		Unlock(Type type);
	
	static Buffer *	Find(const char *given, Type type);
	static Buffer *	FindAvailable(size_t size);
	static void		Detach(const char *data, Type type, const char *func, const int line_n);
	void			Detach(const char *func, const int line_n);
	static char *	Acquire(size_t size, Type type, const char *varname, const char *who, int line);
	static Buffer *	AcquireBuffer(size_t size, Type type, const char *varname, const char *who, int line);
	
	static void		ReleaseAll(void);
	
	static Buffer **buf;
	static Buffer **mem;
	
	static Flags	options;
	static const char *const optionsDesc[];
	
private:
	static void		Decrement(void);
	static void		ReleaseOld(void);
	static void		FreeOld(void);
};


inline Buffer **Buffer::Head(Buffer::Type type) {
	return (type == Buffer::tMalloc ? mem : buf);
}


/*
 * These macros neatly pass the required information without breaking the
 * rest of the code.  The 'get_buffer()' code should be used for a temporary
 * memory chunk such as the current CircleMUD 'buf,' 'buf1,' and 'buf2'
 * variables.  Remember to use 'release_buffer()' to give up the requested
 * buffer when finished with it.  'release_my_buffers()' may be used in
 * functions with a lot of return statements but it is _not_ encouraged.
 * 'get_memory()' and 'release_memory()' should only be used for memory that
 * you always want handled here regardless of BUFFER_MEMORY.
 */
#define get_buffer(a)		Buffer::Acquire((a), Buffer::tBuffer, NULL, __PRETTY_FUNCTION__, __LINE__)
#define get_memory(a)		Buffer::Acquire((a), Buffer::tMalloc, NULL, __PRETTY_FUNCTION__, __LINE__)
#define release_buffer(a)	do { Buffer::Detach((a), Buffer::tBuffer, __PRETTY_FUNCTION__, __LINE__); (a) = NULL; } while(0)
#define release_memory(a)	do { Buffer::Detach((a), Buffer::tMalloc, __PRETTY_FUNCTION__, __LINE__); (a) = NULL; } while(0)
#define release_my_buffers()	detach_my_buffers(__PRETTY_FUNCTION__, __LINE__)


class BufferWrapper
{
public:
	BufferWrapper(int size, const char *var, const char *func, int line) : m_Buffer(Buffer::AcquireBuffer(size, Buffer::tBuffer, var, func, line)), m_Function(func), m_Line(line) { }
	~BufferWrapper() { if (m_Buffer) m_Buffer->Buffer::Detach(m_Function, m_Line); }
	
	char *		Get() { return m_Buffer->data; }
private:
	Buffer *	m_Buffer;
	const char *m_Function;
	int			m_Line;
	
	BufferWrapper();
	BufferWrapper(const BufferWrapper &);
	BufferWrapper &operator=(const BufferWrapper &);
};
/*
#define BUFFER(n, l) \
	char *n = Buffer::Acquire((l), Buffer::tBuffer, #n, __PRETTY_FUNCTION__, __LINE__); \
	BufferWrapper	Buffer_##n(n, __PRETTY_FUNCTION__, __LINE__)
*/
#define BUFFER(NAME, SZ) \
	BufferWrapper	Buffer_##NAME((SZ), #NAME, __PRETTY_FUNCTION__, __LINE__); \
	char *NAME = Buffer_##NAME.Get()

void show_buffers(Things::Thing *ch, Buffer::Type type, int display_type);

#endif
