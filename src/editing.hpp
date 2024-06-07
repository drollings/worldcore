#ifndef __EDITING_HPP__
#define __EDITING_HPP__

//
// C++ SInterface: editing
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
#include "permissions.hpp"

namespace Editing
{
	// An Accessor is an item that has a name, an offset from the beginning of a struct or object, a constraint, and permission flags.
	class Accessor
	{
	public:
                            Accessor(const char *s, UInt32 n, Constraint *c, Flags p = CODER_VIEW | CODER_WRITE) : name(s), offset(n), constraint(c), permissions(p) {};
		virtual				~Accessor(void) {};
		
		const char			*name;
		UInt32				offset;
		const Constraint	*constraint;
		Flags				permissions;
	};

	// A constraint simply has item-specific limits on the input.
    class Constraint
    {
    public:
                                    Constraint(void) {};
        virtual                     ~Constraint(void) {};
        
        virtual void				Set(Ptr &p, const char *input) const = 0;	// This is const because it's actually used to Set on the pointer
        virtual void				Get(Ptr &p, String &output) const = 0;
        virtual void				Get(Ptr &p, int &output) const = 0;
    };

	class Editable
	{
	public:
        virtual 						~Editable(void) {}

	protected:
	    // These abstract classes must be overridden by the inheriting class; this is a mixin.
		virtual const Accessor	**		GetAccessorTable(void) const = 0;
        virtual Ptr						GetPointer(int) const = 0;

        // By offset, get a void pointer to the structure and a pointer to the Constraint, and set an error code if anything goes wrong.
		inline void						GetAccessor(int offset, Ptr &ptr, const Constraint *&constraint) const
		{
		    Ptr tmp;
		    tmp = GetPointer(offset);
		    if (!tmp)	{	return;	}
		    
		    // FIXME - Permissions check here
		    
		    ptr = tmp;
		    const Accessor   **table = GetAccessorTable();
		    constraint = table[offset]->constraint;
		}

		// Get an offset for a string naming a member
		inline void						GetOffset(const char *searchName, int &offset) const
		{
		    const Accessor   **table = GetAccessorTable();
		    
		    for (int i = 0; table[i]; ++i) {
		        if (!strcmp(table[i]->name, searchName)) {	// FIXME - this needs a faster routine
		            offset = i;
		            return;
		        }
		    }
		}

	public:

    	Flags GetRelativePermsFor(const Editable *);
    	bool CheckReadPermissions(const Accessor &table, const Editable *e);
    	bool CheckWritePermissions(const Accessor &table, const Editable *e);
    	bool CheckDerivePermissions(const Accessor &table, const Editable *e);

    	// static void			Parse(Lexi::Parser &parser, VirtualID nr);
    	// virtual void		Write(Lexi::OutputParserFile &file);

        // virtual ErrorCodes::Code		Print(int offset, String &feedback);

    	void							Get(const char *key, String &output) const
    	{
	    	int offset;
	    	GetOffset(key, offset);
	    	if (offset != -1)	Get(offset, output);
        }
        
		void							Get(int offset, String &output) const
    	{
        	Ptr p = GetPointer(offset);
        	if (!p)		return;
        	const Constraint *constraint;
        	GetAccessor(offset, p, constraint);
        	constraint->Get(p, output);
        }

		void							Set(const char *key, const char *input)
		{
		    int offset;
	    	GetOffset(key, offset);
	    	if (offset != -1)	Set(offset, input);
		}

		void							Set(int offset, const char *input)
        {
        	Ptr p = GetPointer(offset);
        	if (!p)		return;
        	const Constraint *constraint;
        	GetAccessor(offset, p, constraint);
        	constraint->Set(p, input);
    	};
		
	};
}

#endif	// __EDITING_HPP__
