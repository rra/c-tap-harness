/* $Id$

   malloc routines with failure handling.

   Copyright 2000 Russ Allbery <rra@stanford.edu>

   This program is free software under an MIT-style license.  See the file
   LICENSE which should have accompanied this file for exact terms and
   conditions.

   %AUTOCONF%
   AC_C_CONST
   AC_HEADER_STDC
   AC_CHECK_FUNCS(memcpy)
   AC_TYPE_SIZE_T
   %%

   Usage:

        #include <stdlib.h>
        #include "xmalloc.h"

        extern xmalloc_handler_t memory_error;
        extern const char *string;
        char *buffer;

        xmalloc_error_handler = memory_error;
        buffer = xmalloc(1024);
        xrealloc(buffer, 2048);
        free(buffer);
        buffer = xstrdup(string);

   xmalloc, xrealloc, and xstrdup behave exactly like their C library
   counterparts without the leading x except that they will never return
   NULL.  Instead, on error, they call xmalloc_error_handler, passing it the
   name of the function whose memory allocation failed, the amount of the
   allocation, and the file and line number where the allocation function
   was invoked (from __FILE__ and __LINE__).  This function may do whatever
   it wishes, such as some action to free up memory or a call to sleep to
   hope that system resources return.  If the handler returns, the
   interrupted memory allocation function will try its allocation again
   (calling the handler again if it still fails).

   The default error handler, if none is set by the caller, prints an error
   message to stderr and exits with exit status 1.  An error handler must
   take a const char * (function name), size_t (bytes allocated), const
   char * (file), and int (line). */

#include "config.h"
#include "xmalloc.h"

#include <stdlib.h>
#include <sys/types.h>

#if STDC_HEADERS
# include <string.h>
#else
# if !HAVE_MEMCPY
#  define memcpy(d, s, n)       bcopy((s), (d), (n))
# endif
#endif

#include "error.h"

/* The default error handler. */
static void
xmalloc_fail(const char *function, size_t size, const char *file, int line)
{
    sysdie("failed to %s %lu bytes at %s line %d", function,
           (unsigned long) size, file, line);
}

/* Assign to this variable to choose a handler other than the default. */
xmalloc_handler_t xmalloc_error_handler = xmalloc_fail;

void *
_xmalloc(size_t size, const char *file, int line)
{
    void *p;

    p = malloc(size);
    while (!p) {
        (*xmalloc_error_handler)("malloc", size, file, line);
        p = malloc(size);
    }
    return p;
}

void *
_xrealloc(void *p, size_t size, const char *file, int line)
{
    void *newp;

    newp = realloc(p, size);
    while (!newp) {
        (*xmalloc_error_handler)("remalloc", size, file, line);
        newp = realloc(p, size);
    }
    return newp;
}

char *
_xstrdup(const char *s, const char *file, int line)
{
    char *p;
    size_t len;

    len = strlen(s) + 1;
    p = malloc(len);
    while (!p) {
        (*xmalloc_error_handler)("strdup", len, file, line);
        p = malloc(len);
    }
    memcpy(p, s, len);
    return p;
}
