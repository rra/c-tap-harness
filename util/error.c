/* $Id$

   Error reporting (possibly fatal).

   Copyright 2000 Russ Allbery <rra@stanford.edu>

   This program is free software under an MIT-style license.  See the file
   LICENSE which should have accompanied this file for exact terms and
   conditions.

   warn prints an error followed by a newline to stderr.  die does the same
   but then exits, normally with a status of 1.  The sys* versions do the
   same, but append a colon, a space, and the results of strerror(errno) to
   the end of the message.  All functions accept printf-style formatting
   strings and arguments.

   If error_fatal_cleanup is non-NULL, it is called before exit by die and
   sysdie and its return value is used as the argument to exit.  If
   error_program_name is non-NULL, the string it points to, followed by a
   colon and a space, is prepended to all error messages.

   Honoring error_program_name and printing to stderr is just the default
   handler; with warn_set_handlers or die_set_handlers the handlers for warn
   and die can be changed.  These functions take a count of handlers and
   then that many function pointers, each one to a function that takes a
   message length, a format, an argument list as a va_list, and the
   applicable errno value (or 0 if none).

   Three handlers are provided:  one that prints to stderr and two that log
   to syslog (one at LOG_ERR and the other at LOG_WARNING). */

#include "config.h"
#include "librutil.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#if STDC_HEADERS
# include <string.h>
#endif
#include <syslog.h>

/* The default handler list. */
static error_handler_t default_handlers[2] = { error_log_stderr, NULL };

/* The list of logging functions currently in effect. */
static error_handler_t *die_handlers  = default_handlers;
static error_handler_t *warn_handlers = default_handlers;

/* If non-NULL, called before exit and its return value passed to exit. */
int (*error_fatal_cleanup)(void) = NULL;

/* If non-NULL, prepended (followed by ": ") to all error messages. */
const char *error_program_name = NULL;


void
warn_set_handlers(int count, ...)
{
    va_list args;
    int i;

    if (warn_handlers != default_handlers) free(warn_handlers);
    warn_handlers = xmalloc(sizeof(error_handler_t) * (count + 1));
    va_start(args, count);
    for (i = 0; i < count; i++)
        warn_handlers[i] = (error_handler_t) va_arg(args, error_handler_t);
    va_end(args);
    warn_handlers[count] = NULL;
}

void
die_set_handlers(int count, ...)
{
    va_list args;
    int i;

    if (die_handlers != default_handlers) free(die_handlers);
    die_handlers = xmalloc(sizeof(error_handler_t) * (count + 1));
    va_start(args, count);
    for (i = 0; i < count; i++)
        die_handlers[i] = (error_handler_t) va_arg(args, error_handler_t);
    va_end(args);
    die_handlers[count] = NULL;
}


void
error_log_stderr(int len, const char *fmt, va_list args, int error)
{
    fflush(stdout);
    if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
    vfprintf(stderr, fmt, args);
    if (error) fprintf(stderr, ": %s", strerror(error));
    fprintf(stderr, "\n");
}


void
error_log_syslog(int pri, int len, const char *fmt, va_list args, int err)
{
    char *buffer;
    int oerrno;

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        if (error_program_name) fprintf(stderr, "%s: ", error_program_name);
        fprintf(stderr, "failed to malloc %lu bytes at %s line %d: %s",
                len + 1, __FILE__, __LINE__, strerror(errno));
        exit(1);
    }
    vsnprintf(buffer, len, fmt, args);
    oerrno = errno;
    errno = err;
    syslog(pri, err ? "%s: %m" : "%s", buffer);
    if (errno == err) errno = oerrno;
    free(buffer);
}

void
error_log_syslog_warning(int len, const char *fmt, va_list args, int err)
{
    error_log_syslog(LOG_WARNING, len, fmt, args, err);
}

void
error_log_syslog_err(int len, const char *fmt, va_list args, int err)
{
    error_log_syslog(LOG_ERR, len, fmt, args, err);
}


void
warn(const char *format, ...)
{
    va_list args;
    error_handler_t *log;
    int length;

    va_start(args, format);
    length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) return;
    for (log = warn_handlers; *log; log++) {
        va_start(args, format);
        (**log)(length, format, args, 0);
        va_end(args);
    }
}

void
syswarn(const char *format, ...)
{
    va_list args;
    error_handler_t *log;
    int length;
    int error = errno;

    va_start(args, format);
    length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) return;
    for (log = warn_handlers; *log; log++) {
        va_start(args, format);
        (**log)(length, format, args, error);
        va_end(args);
    }
}

void
die(const char *format, ...)
{
    va_list args;
    error_handler_t *log;
    int length;

    va_start(args, format);
    length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length >= 0)
        for (log = die_handlers; *log; log++) {
            va_start(args, format);
            (**log)(length, format, args, 0);
            va_end(args);
        }
    exit(error_fatal_cleanup ? (*error_fatal_cleanup)() : 1);
}

void
sysdie(const char *format, ...)
{
    va_list args;
    error_handler_t *log;
    int length = 0;
    int error = errno;

    va_start(args, format);
    length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length >= 0)
        for (log = die_handlers; *log; log++) {
            va_start(args, format);
            (**log)(length, format, args, error);
            va_end(args);
        }
    exit(error_fatal_cleanup ? (*error_fatal_cleanup)() : 1);
}
