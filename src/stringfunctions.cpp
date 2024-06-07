//
// C++ Implementation: stringfunctions
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//


#include "stringfunctions.hpp"

using namespace std;

const char *fill_words[] =
{
  "in"	,
  "from",
  "with",
  "the"	,
  "on"	,
  "at"	,
  "to"	,
  "\n"
};

const char *reserved_words[] =
{
  "a",
  "an",
  "self",
  "me",
  "all",
  "room",
  "someone",
  "something",
  "\n"
};


// FIXME - This is CircleMUD code and I need to rewrite - DR

/*
 * searches an array of strings for a target string.  "exact" can be
 * 0 or non-0, depending on whether or not the match must be exact for
 * it to be returned.  Returns -1 if not found; 0..n otherwise.  Array
 * must be terminated with a '\n' so it knows to stop searching.
 */
int search_block(const char *arg, const char **list, bool exact) {
    SInt32      i, l;

    //  Make into lower case, and get length of string
//  for (l = 0; *(arg + l); l++)
//      *(arg + l) = LOWER(*(arg + l));
    l = strlen(arg);  

    if (exact) {
        for (i = 0; **(list + i) != '\n'; i++)
            if (!str_cmp(arg, *(list + i)))
                return (i);
    } else {
        if (!l)
            l = 1;  //  Avoid "" to match the first available string
        for (i = 0; **(list + i) != '\n'; i++)
            if (!strn_cmp(arg, *(list + i), l))
                return (i);
    }

    return -1;
}

int search_chars(char arg, const char *list) {
	int i;

	for (i = 0; list[i]; ++i)
		if (arg == list[i])
			return (i);
	return -1;
}


/*
bool is_number(char *str) {
	if (!str || !*str)		return false;
	if (*str == '-')		str++;		
	while (*str)
		if (!isdigit(*(str++)))
			return false;
	return true;
}
*/
bool is_number(const char *str)
{
	char c = *str;
	if (!c)	return false;
	if (c == '-' || c == '+')		c = *(++str);
	if (!c)	return false;
/*	if (c == '0')
	{
		c = *(++str);
		if (c == 'x' || c == 'X')
		{
			c = *(++str);
			while (isxdigit(c))			c = *(++str);
			return (!c || isspace(c));
		}
	}
*/	while (isdigit(c))				c = *(++str);
	return (!c || isspace(c));
}


bool is_float(const char *str)
{
	char c = *str;
	if (!c)	return false;
	if (c == '-' || c == '+')		c = *(++str);
	if (!c)	return false;
	while (isdigit(c))				c = *(++str);
	if (c == '.')
	{
		c = *(++str);
		while (isdigit(c))			c = *(++str);
	}
	return (!c || isspace(c));
}


STR_TYPE str_type(const char *str)
{
	bool	bIsFloat = false;
	bool	bIsNumber = false;
	bool	bIsHexadecimal = false;
	
	if (!str)						return STR_TYPE_STRING;
	char c = *str;
	if (c == '-' || c == '+')		c = *(++str);
	if (c == '0')	//	Supports octal and hex
	{
		bIsNumber = true;
		c = *(++str);
		if (tolower(c) == 'x')	//	hex
		{
			c = *(++str);
			bIsHexadecimal = true;
		}
	}
	
	if (bIsHexadecimal)
	{
		while (isxdigit(c))
		{
			bIsNumber = true;
			c = *(++str);
		}
	}
	else
	{
		while (isdigit(c))
		{
			bIsNumber = true;
			c = *(++str);
		}
		if (c == '.')
		{
			c = *(++str);
			if (isdigit(c))
			{
				bIsFloat = bIsNumber = true;
				do { c = *(++str); } while (isdigit(c));
			}
		}
		if (bIsNumber && (c == 'e' || c == 'E'))
		{
			c = *(++str);
			if (c == '-' || c == '+')		c = *(++str);
			if (isdigit(c))
			{
				bIsFloat = true;	
				do { c = *(++str); } while (isdigit(c));
			}
		}
	}
	
	if (bIsNumber
		&& (!c || isspace(c)))		return bIsFloat ? STR_TYPE_FLOAT : STR_TYPE_INTEGER;
	else							return STR_TYPE_STRING;
}


void	fix_float(char *str)
{
#if 0		//	Strlen work backwards removing every 0 then re-add the last 0 if at .0
	int n = strlen(str) - 1;
	
	for (; n > 1 && str[n] == '0'; --n)
		str[n] = '\0';
	
	if (str[n] == '.')
	{
		str[n+1] = '0';
		str[n+2] = '\0';
	}
#elif 1		//	Find the first zero in the last string of zeroes
	//	Find the decimal
	bool	bFoundDigit = false;
	
	char c = *str;
	while (c && c != '.')
	{
		if (c != '0')	bFoundDigit = true;
		c = *++str;	
	}
	
	if (!c)	return;
	
	//	str is at the period so skip it
	c = *++str;
	
	//	We might have a non-zero digit...
	if (!bFoundDigit)	bFoundDigit = c != '0';
	
	c = *++str;	//	We want at least one digit after the period!
	
	char *	firstZero = NULL;
	while (c && !isspace(c))
	{
		if (c == '0')
		{
			if (!firstZero)	firstZero = str;
		}
		else
		{
			firstZero = NULL;
		}
		
		c = *++str;
	}
	
	if (firstZero)	*firstZero = '\0';
#else		//	Find the first zero in a series of zeroes with max of 5 in a row terminate there

	//	Find the decimal
	bool	bFoundDigit = false;
	
	char c = *str;
	while (c && c != '.')
	{
		if (c != '0')	bFoundDigit = true;
		c = *++str;	
	}
	
	if (!c)	return;
	
	//	str is at the period so skip it
	c = *++str;
	
	//	We might have a non-zero digit...
	if (!bFoundDigit)	bFoundDigit = c != '0';
	
	c = *++str;	//	We want at least one digit after the period!
	
	char *	firstZero = NULL;
	int		numZeroes = 0;
	while (c && !isspace(c))
	{
		if (c == '0')
		{
			if (!firstZero)
			{
				firstZero = str;
				numZeroes = 0;	
			}
			else if (bFoundDigit && ++numZeroes == 4)
				break;
		}
		else
		{
			firstZero = NULL;
			bFoundDigit = true;
		}
		
		c = *++str;
	}
	
	if (firstZero)	*firstZero = '\0';
#endif
}


void skip_spaces(const char * &string) {
	while (isspace(*string))	++string;
}

void skip_spaces(char * &string) {
	while (isspace(*string))	++string;
}


char *delete_doubledollar(char *string) {
	char *read, *write;

	if ((write = strchr(string, '$')) == NULL)
		return string;

	read = write;

	while (*read)
		if ((*(write++) = *(read++)) == '$')
			if (*read == '$')
				read++;

	*write = '\0';

	return string;
}


/*
 * copy the first non-fill-word, space-delimited argument of 'argument'
 * to 'first_arg'; return a pointer to the remainder of the string.
 */
char *one_argument(const char *argument, char *first_arg) {
	char *begin = first_arg;
	
	if (!argument) {
		*first_arg = '\0';
		return NULL;
	}
	
	do {
		skip_spaces(argument);

		first_arg = begin;
		while (*argument && !isspace(*argument)) {
			*(first_arg++) = LOWER(*argument);
			argument++;
		}

		*first_arg = '\0';
	} while (fill_word(begin));

	skip_spaces(argument);
	
	return const_cast<char *>(argument);
}


/*
 * one_word is like one_argument, except that words in quotes ("") are
 * considered one word.
 */
char *one_word(const char *argument, char *first_arg)
{
  char *begin = first_arg;

	if (!argument) {
		*first_arg = '\0';
		return NULL;
	}

  do {
    skip_spaces(argument);

    first_arg = begin;

    if (*argument == '\"') {
      argument++;
      while (*argument && *argument != '\"') {
        *(first_arg++) = LOWER(*argument);
        argument++;
      }
      argument++;
    } else {
      while (*argument && !isspace(*argument)) {
        *(first_arg++) = LOWER(*argument);
        argument++;
      }
    }

    *first_arg = '\0';
  } while (fill_word(begin));

  return const_cast<char *>(argument);
}


/* same as one_argument except that it doesn't ignore fill words */
char *any_one_arg(const char *argument, char *first_arg)
{
  skip_spaces(argument);

  while (*argument && !isspace(*argument)) {
    *(first_arg++) = tolower(*argument); //LOWER(*argument);
    ++argument;
  }

  *first_arg = '\0';

  skip_spaces(argument);

  return const_cast<char *>(argument);
}



/* same as any_one_arg except that it stops at punctuation */
char *any_one_name(const char *argument, char *first_arg) {
    char* arg;
  
    /* Find first non blank */
//    while(isspace(*argument))
//		argument++;
	skip_spaces(argument);	
	  
    /* Find length of first word */
    for(arg = first_arg ;
			*argument && !isspace(*argument) &&
	  		(!ispunct(*argument) || *argument == '#' || *argument == '-');
			arg++, argument++)
		*arg = LOWER(*argument);
    *arg = '\0';

    return const_cast<char *>(argument);
}


/*
 * Same as one_argument except that it takes two args and returns the rest;
 * ignores fill words
 */
char *two_arguments(const char *argument, char *first_arg, char *second_arg) {
	return one_argument(one_argument(argument, first_arg), second_arg);
}


char *three_arguments(const char *argument, char *first_arg, char *second_arg, char *third_arg) {
	return one_argument(two_arguments(argument, first_arg, second_arg), third_arg);  
}


/*
 * determine if a given string is an abbreviation of another
 * returns 1 if arg1 is an abbreviation of arg2
 */
bool is_abbrev(const char *arg1, const char *arg2) {
	if (!*arg1 || !*arg2)
		return false;

	for (; *arg1 && *arg2; arg1++, arg2++)
		if (LOWER(*arg1) != LOWER(*arg2))
			return false;

	if (!*arg1)	return true;
	else		return false;
}

/* return first space-delimited token in arg1; remainder of string in arg2 */
void half_chop(const char *string, char *arg1, char *arg2)
{
  char *temp;

  temp = any_one_arg(string, arg1);
  skip_spaces(temp);
  strcpy(arg2, temp);
}



/***************************************************************************
 * Various other parsing utilities                                         *
 **************************************************************************/

bool fill_word(const char *argument) {
	return (search_block(argument, fill_words, true) >= 0);
}


bool reserved_word(const char *argument) {
	return (search_block(argument, reserved_words, true) >= 0);
}


/* Return pointer to first occurrence of string ct in */
/* cs, or NULL if not present.  Case insensitive */
const char *str_str(const char *cs, const char *ct)
{
	const char *s;
	const char *t;

	if (!cs || !ct)
		return NULL;

	while (*cs) {
		t = ct;

		while (*cs && (LOWER(*cs) != LOWER(*t)))
			cs++;

		s = cs;

		while (*t && *cs && (LOWER(*cs) == LOWER(*t))) {
			t++;
			cs++;
		}
    
		if (!*t)
			return s;
	}

	return NULL;
}
