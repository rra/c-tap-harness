/* $Id$

   Concatenate strings with dynamic memory allocation.

   Written by Russ Allbery <rra@stanford.edu>
   This work is hereby placed in the public domain by its author.

   %AUTOCONF%
   AC_C_CONST
   AC_HEADER_STDC
   AC_CHECK_HEADERS(stdarg.h varargs.h)
   AC_TYPE_SIZE_T
   %%

   Usage:

        #include "concat.h"

        string = concat(string1, string2, ..., (char *) 0);

   Dynamically allocates (using xmalloc) sufficient memory to hold all of
   the strings given and then concatenates them together into that allocated
   memory, returning a pointer to it.  Caller is responsible for freeing.
   Assumes xmalloc() is available.  The last argument must be a null pointer
   (to a char *, if you actually find a platform where it matters). */

#include "config.h"
#include "concat.h"
#include "xmalloc.h"

#if STDC_HEADERS
# include <string.h>
#endif

/* varargs implementation based on Solaris 2.6 man page. */
#if STDC_HEADERS || HAVE_STDARG_H
# include <stdarg.h>
# define VA_PARAM(type, param)  (type param, ...)
# define VA_START(args, param)  (va_start(args, param))
#elif HAVE_VARARGS_H
# include <varargs.h>
# define VA_PARAM(type, param)  (param, va_alist) type param; va_dcl
# define VA_START(args, param)  (va_start(args))
#else
# error "No variadic argument mechanism available."
#endif

/* Abbreviation for cleaner code. */
#define VA_NEXT(var, type)      ((var) = (type) va_arg(args, type))

/* ANSI C requires at least one named parameter. */
void *
concat VA_PARAM(const char *, first)
{
    va_list args;
    char *result, *p;
    const char *string;
    size_t length = 0;

    /* Find the total memory required. */
    VA_START(args, first);
    for (string = first; string != 0; VA_NEXT(string, const char *))
        length += strlen(string);
    va_end(args);
    length++;

    /* Create the string.  Doing the copy ourselves avoids useless string
       traversals of result, if using strcat, or string, if using strlen to
       increment a pointer into result, at the cost of losing the native
       optimization of strcat if any. */
    result = xmalloc(length);
    p = result;
    VA_START(args, first);
    for (string = first; string; VA_NEXT(string, const char *))
        while (*string != '\0')
            *p++ = *string++;
    va_end(args);
    *p = '\0';

    return result;
}
