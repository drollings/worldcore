//
// C++ Implementation: editing
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "editing.hpp"
#include "constraints.hpp"
#include "permissions.hpp"
#include "properties.hpp"


using namespace std;

namespace Editing
{
    #if 0
    ErrorCodes::Code	Editable::Print(int offset, String &feedback)
    {
    	Ptr p = GetPointer(offset);
     	if (!p)		return ErrorCodes::InvalidOffset;
    	const Constraint *constraint;
		GetAccessor(offset, p, constraint);
		constraint->Print(p, feedback);
		return ErrorCodes::None;
	};
	#endif
	
	Flags Editable::GetRelativePermsFor(const Editable *)
	{	return CODER_VIEW;		}

	bool Editable::CheckReadPermissions(const Accessor &table, const Editable *e)
	{	return (table.permissions & Permissions::READ_MASK & GetRelativePermsFor(e) ? true : false);	}

	bool Editable::CheckWritePermissions(const Accessor &table, const Editable *e)
	{	return (table.permissions & Permissions::WRITE_MASK & GetRelativePermsFor(e) ? true : false);		}

	bool Editable::CheckDerivePermissions(const Accessor &table, const Editable *e)
	{	return (table.permissions & Permissions::DERIVE_MASK & GetRelativePermsFor(e) ? true : false);		}
	
	#if 0
	void				Editable::SetAccessor(const char *key, const Flags &permissions, const Accessor &access)
	{
		AccessorTable &table = GetAccessorTable();
	}
	#endif

}
