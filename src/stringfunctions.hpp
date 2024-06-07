#ifndef __STRINGFUNCTIONS_HPP__
#define __STRINGFUNCTIONS_HPP__

#include "typedefs.hpp"

#define str_cmp(a, b)   strcasecmp(a, b)
#define strn_cmp(a, b, c) strncasecmp(a, b, c)

/* public functions in utils.c */
char *  str_dup(const char *source);
char *str_str(char *cs, const char *ct);
// inline const char *str_str(const char *cs, const char *ct) { return (char *) str_str((char *)cs, ct); }


#if defined(_WIN32)
char *  strsep(char **sp, char *sep);
#endif

int			cstr_cmp(const char *a, const char *b);
unsigned int      cstrlen(const char *str);
unsigned int      cstrnlen(const char *str, unsigned int n);
unsigned int      cstrnlen_for_sprintf(const char *str, unsigned int n);
// const char *strip_color (const char *txt);
// int     touch(char *path);
int     Number(int from, int to);
void    sprintbit(Flags vektor, const char *names[], char *result);
void    sprinttype(int type, const char *names[], char *result);   
const char *findtype(int type, char **names);
int     get_line(FILE *fl, char *buf);
int     get_any_line(FILE * fl, char *buf, int length);
int     get_filename(const char *orig_name, char *filename);
int     replace_str(char **string, char *pattern, char *replacement, int rep_all, int max_size);
// void    format_text(char **ptr_string, int mode, DescriptorData *d, int maxlen);
void    core_dump_func(const char *who, int line);
#define core_dump() core_dump_func(__PRETTY_FUNCTION__, __LINE__)

int		search_block(const char *arg, const char **list, bool exact);
inline int search_block(const char *arg, char **list, bool exact) { return search_block(arg, (const char **)list, exact); }
int		search_chars(const char arg, const char *list);

char *	one_argument(const char *argument, char *first_arg);
char *	one_word(const char *argument, char *first_arg);
char *	any_one_arg(const char *argument, char *first_arg);
char *	any_one_name(const char *argument, char *first_arg);
char *	two_arguments(const char *argument, char *first_arg, char *second_arg);
char *	three_arguments(const char *argument, char *first_arg, char *second_arg, char *third_arg);
bool	fill_word(const char *argument);
void	half_chop(const char *string, char *arg1, char *arg2);
bool	is_abbrev(const char *arg1, const char *arg2);
bool	is_number(const char *str);
bool	is_float(const char *str);
int		find_command(const char *command);
void	skip_spaces(const char * &string);
void	skip_spaces(char *&string);
char *	delete_doubledollar(char *string);
int		sprintf_cat(char *str, const char *format, ...);

enum STR_TYPE
{
	STR_TYPE_STRING = 0,
	STR_TYPE_INTEGER = 1,
	STR_TYPE_FLOAT = 2
};
STR_TYPE	str_type(const char *str);
void		fix_float(char *str);


#define YESNO(a) ((a) ? "YES" : "NO")
#define ONOFF(a) ((a) ? "ON" : "OFF")

// IS_UPPER and IS_LOWER added by dkoepke
#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')

#define LOWER(c)   (IS_UPPER(c) ? ((c)+('a'-'A')) : (c))
#define UPPER(c)   (IS_LOWER(c) ? ((c)+('A'-'a')) : (c))

#define ISNEWL(ch) ((ch) == '\n' || (ch) == '\r') 
//#define CAP(st)  (*(st) = UPPER(*(st)), st)
extern char *CAP(char *in);

/*
 * Escape character, which indicates that the name is
 * a unique id number rather than a standard name.
 * Should be nonprintable so players can't enter it.
 */
const char UID_CHAR = 0x1b; /* '\e' */

#define AN(string) (strchr("aeiouAEIOU", *string) ? "an" : "a")

#define END_OF(buffer)		((buffer) + strlen((buffer)))

#endif
