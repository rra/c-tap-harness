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

#ifdef STDC_HEADERS
# include <string.h>
#endif

/* If we're testing, use regular malloc. */
#ifdef TEST
# include <stdlib.h>
# undef xmalloc
# define xmalloc malloc
#endif

/* varargs implementation based on Solaris 2.6 man page. */
#if STDC_HEADERS || HAVE_STDARG_H
# include <stdarg.h>
# define VA_PARAM(type, param)  (type param, ...)
# define VA_START(args, param)  (va_start(args, param))
#else
# ifdef HAVE_VARARGS_H
#  include <varargs.h>
#  define VA_PARAM(type, param) (param, va_alist) type param; va_dcl
#  define VA_START(args, param) (va_start(args))
# else
#  error "No variadic argument mechanism available."
# endif
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
    for (string = first; string != 0; VA_NEXT(string, const char *))
        while (*string != '\0')
            *p++ = *string++;
    va_end(args);
    *p = '\0';

    return result;
}


/* Some simple testing code to create memory leaks. */
#ifdef TEST

#include <stdio.h>

int
main ()
{
#if STDC_HEADERS || HAVE_STDARG_H
    printf("Using stdargs:\n\n");
#else
    printf("Using varargs:\n\n");
#endif
    printf("a\t%s\n",     concat("a",                          (char *) 0));
    printf("ab\t%s\n",    concat("a", "b",                     (char *) 0));
    printf("ab\t%s\n",    concat("ab", "",                     (char *) 0));
    printf("ab\t%s\n",    concat("", "ab",                     (char *) 0));
    printf("\t%s\n",      concat("",                           (char *) 0));
    printf("abcde\t%s\n", concat("ab", "c", "", "de",          (char *) 0));
    printf("abcde\t%s\n", concat("abc", "de", (char *) 0, "f", (char *) 0));
    return 0;
}

#endif /* TEST */
