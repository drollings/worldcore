#ifndef __CONSTRAINTS_HPP__
#define __CONSTRAINTS_HPP__

//
// C++ SInterface: constraints
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "typedefs.hpp"
#include "editing.hpp"
#include "stringfunctions.hpp"
#include "base.hpp"

namespace Editing
{
    // The accessor is a singleton object looked up from a vtable-like vector.  It should not be used directly;
    // it gets looked up by an editable that itself determines the base address of the object being edited,
    // and the address of the targetted member variable.  The accessor manages the type-safety of the input.

    class CString : public Constraint
    {
    protected:
                                    unsigned int _minLen_, _maxLen_;
    public:
                                    CString(UInt32 min, UInt32 max) : Constraint(), _minLen_(min), _maxLen_(max) {}

        virtual void                Set(Ptr &p, const char *input) const
        {
            int len = strlen(input);
            if (len < _minLen_ || len > _maxLen_)        return;

            char **ptr = static_cast<char **>(p);
            *ptr = strdup(input);
        }

        virtual void                Get(Ptr &p, String &output) const
        {
            char **ptr = static_cast<char **>(p);
            output = *ptr;
        }

        virtual void                Get(Ptr &p, int &output) const
        {
            char **ptr = static_cast<char **>(p);
            output = strlen(*ptr);
        }

    };
    

    class CPPString : public Constraint
    {
    protected:
                                    unsigned int _minLen_, _maxLen_;
    public:
                                    CPPString(UInt32 min, UInt32 max) : Constraint(), _minLen_(min), _maxLen_(max) {}

        virtual void                Set(Ptr &p, const char *input) const
        {
            int len = strlen(input);
            if (len < _minLen_ || len > _maxLen_)        return;

            String *ptr = static_cast<String *>(p);
            *ptr = input;
        }

        virtual void                Get(Ptr &p, String &output) const
        {
            String *ptr = static_cast<String *>(p);
            output = *ptr;
        }

        virtual void                Get(Ptr &p, int &output) const
        {
            String *ptr = static_cast<String *>(p);
            output = ptr->length();
        }

    };
    

    template < class _T_ >
    class IntConstraintTemplate : public Constraint
    {
    public:
                                    IntConstraintTemplate(void) : Constraint()    {}
        virtual                        ~IntConstraintTemplate(void) {};

        virtual void                Set(Ptr &p, const char *input) const
        {
            _T_ *ptr = (_T_ *)p;
            *ptr = _T_(atoi(input));
        }

        virtual void                Get(Ptr &p, String &output) const
        {
            _T_ *ptr = static_cast< _T_ *>(p);
            output = *ptr;
        }

        virtual void                Get(Ptr &p, int &output) const
        {
            _T_ *ptr = static_cast< _T_ *>(p);
            output = *ptr;
        }
    };

    
    template < class _T_ >
    class FloatConstraintTemplate : public Constraint
    {
    public:
                                    FloatConstraintTemplate(void) : Constraint()    {}
        virtual                        ~FloatConstraintTemplate(void) {};

        virtual void                Set(Ptr &p, const char *input) const
        {
            _T_ *ptr = (_T_ *)p;
            *ptr = _T_(atof(input));
        }

        virtual void                Get(Ptr &p, String &output) const
        {
            _T_ *ptr = static_cast< _T_ *>(p);
            output = *ptr;
        }

        virtual void                Get(Ptr &p, int &output) const
        {
            _T_ *ptr = static_cast< _T_ *>(p);
            output = (int) *ptr;
        }
    };

    
    template < class _T_ >
    class IntNumericRange : public IntConstraintTemplate< _T_ >
    {
    protected:
                                    _T_    _low_, _high_;
    public:
                                    IntNumericRange(_T_ lo, _T_ hi) : IntConstraintTemplate<_T_>(), _low_(lo), _high_(hi) {}

        virtual void                Set(Ptr &p, const char *input) const
        {
            _T_ *ptr = (_T_ *)p;
            *ptr = _T_(atoi(input));
            if (*ptr > _high_)        *ptr = _high_;
            else if (*ptr < _low_)    *ptr = _low_;
        }

    };

    
    template < class _T_ >
    class FloatNumericRange : public FloatConstraintTemplate< _T_ >
    {
    protected:
                                    _T_    _low_, _high_;
    public:
                                    FloatNumericRange(_T_ lo, _T_ hi) : FloatConstraintTemplate<_T_>(), _low_(lo), _high_(hi) {}

        virtual void                Set(Ptr &p, const char *input) const
        {
            _T_ *ptr = (_T_ *)p;
            *ptr = _T_(atof(input));
            if (*ptr > _high_)        *ptr = _high_;
            else if (*ptr < _low_)    *ptr = _low_;
        }

    };

    
    template < class _T_ >
    class Values : public IntConstraintTemplate< _T_ >
    {
    protected:
                                    const char ** _sValues_;
    public:
                                    Values(const char **val) : IntConstraintTemplate<_T_>(), _sValues_(val) {}

        virtual void                Set(Ptr &p, const char *input) const
        {
            int offset = search_block(input, _sValues_, false);
            if (offset != -1) {
                _T_ *ptr = (_T_ *)p;
                *ptr = static_cast<_T_>(offset);
            }
        }

        virtual void                Get(Ptr &p, String &output) const
        {
            _T_ *ptr = (_T_ *)p;
            output = (*_sValues_)[*ptr];
        }

    };

    
    template < class _T_ >
    class Masked : public Values< _T_ >
    {
    protected:
                                    _T_    _mask_;
    public:
                                    Masked(const char **val, _T_ m) : Values<_T_>(val), _mask_(m) {}

    };
}

#endif    // __CONSTRAINTS_HPP__
