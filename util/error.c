/* $Id$

   Error reporting (possibly fatal).

   Copyright 2000 Russ Allbery <rra@stanford.edu>

   This program is free software under an MIT-style license.  See the file
   LICENSE which should have accompanied this file for exact terms and
   conditions.

   %AUTOCONF%
   AC_C_CONST
   AC_HEADER_STDC
   AC_CHECK_HEADERS(stdarg.h varargs.h)
   AC_CHECK_FUNCS(strerror)
   %%

   Usage:

        #include "error.h"

        extern int cleanup(void);

        error_fatal_cleanup = cleanup;
        error_program_name = argv[0];

        warn("Something horrible happened at %lu", time);
        syswarn("Couldn't unlink temporary file %s", tmpfile);

        die("Something fatal happened at %lu", time);
        sysdie("open of %s failed", filename);

   warn prints an error followed by a newline to stderr.  die does the same
   but then exits, normally with a status of 1.  The sys* versions do the
   same, but append a colon, a space, and the results of strerror(errno) to
   the end of the message.  All functions accept printf-style formatting
   strings and arguments.

   If error_fatal_cleanup is non-NULL, it is called before exit by die and
   sysdie and its return value is used as the argument to exit.  It is a
   pointer to a function taking no arguments and returning an int.

   If error_program_name is non-NULL, the string it points to, followed by a
   colon and a space, is prepended to all error messages.  It is a const
   char *. */

#include "config.h"
#include "error.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* FIXME: Assumes we have strerror.  Should provide a copy of we don't. */
#if STDC_HEADERS
# include <string.h>
#endif

/* varargs implementation based on Solaris 2.6 man page. */
#if STDC_HEADERS || HAVE_STDARG_H
# include <stdarg.h>
# define VA_PARAM(type, param)  (type param, ...)
# define VA_START(args, param)  (va_start(args, param))
#else
# if HAVE_VARARGS_H
#  include <varargs.h>
#  define VA_PARAM(type, param) (param, va_alist) type param; va_dcl
#  define VA_START(args, param) (va_start(args))
# else
#  error "No variadic argument mechanism available."
# endif
#endif

/* If non-NULL, called before exit and its return value passed to exit. */
int (*error_fatal_cleanup)(void) = 0;

/* If non-NULL, prepended (followed by ": ") to all error messages. */
const char *error_program_name = 0;

/* If we don't have strerror, assume that we do have sys_nerr and
   sys_errlist to use instead and provide a replacement. */
#if !HAVE_STRERROR
const char *
strerror(int error)
{
    extern int sys_nerr;
    extern char *sys_errlist[];
    static char buff[32];

    if (error >= 0 && error < sys_nerr) return sys_errlist[error];

    /* Paranoia.  If an int is very large (like 128 bytes) one could
       overflow the buffer here, so refuse to process particularly large
       values of error. */
    if (error > 30000) return "";
    sprintf(buff, "Error code %d", error);
    return buff;
}
#endif /* !HAVE_STRERROR */

void
warn VA_PARAM(const char *, format)
{
    va_list args;

    if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
    VA_START(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void
syswarn VA_PARAM(const char *, format)
{
    va_list args;
    int error = errno;

    if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
    VA_START(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, ": %s\n", strerror(error));
}

void
die VA_PARAM(const char *, format)
{
    va_list args;

    if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(error_fatal_cleanup ? (*error_fatal_cleanup)() : 1);
}

void
sysdie VA_PARAM(const char *, format)
{
    va_list args;
    int error = errno;

    if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, ": %s\n", strerror(error));
    exit(error_fatal_cleanup ? (*error_fatal_cleanup)() : 1);
}
