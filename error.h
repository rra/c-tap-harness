/* error.h -- Error reporting (possibly fatal). */
/* $Id$ */

#ifndef ERROR_H
#define ERROR_H 1

#ifndef CONFIG_H
# include "config.h"
#endif

/* This feature is available in gcc versions 2.5 and later, but only with
   gcc 2.7 could you use the __format__ form of the attributes, which is
   what we use (to avoid confusion with other macros). */
#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7) || __STRICT_ANSI__
#  define __attribute__(spec)   /* empty */
# endif
#endif

/* If non-NULL, called before exit and its return value passed to exit. */
extern int (*error_fatal_cleanup)(void);

/* If non-NULL, prepended (followed by ": ") to all error messages. */
extern const char *error_program_name;

#if STDC_HEADERS || HAVE_STDARG_H
extern void warn(const char *, ...)
    __attribute__((__format__(printf, 1, 2)));
extern void syswarn(const char *, ...)
    __attribute__((__format__(printf, 1, 2)));
extern void die(const char *, ...)
    __attribute__((__noreturn__, __format__(printf, 1, 2)));
extern void sysdie(const char *, ...)
    __attribute__((__noreturn__, __format__(printf, 1, 2)));
#else
extern void warn();
extern void syswarn();
extern void die();
extern void sysdie();
#endif

/* If the system doesn't have strerror, we provide a replacement. */
#if !HAVE_STRERROR
extern const char *strerror(int error);
#endif

#endif /* !ERROR_H */
