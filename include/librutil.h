/* librutil.h -- Interface to the random utility library. */
/* $Id$ */

/* Note that this header file assumes support for ANSI C stdargs in your
   compiler.  It will not compile with varargs support (to avoid a
   dependency on any particular config.h). */

#ifndef LIBRUTIL_H
#define LIBRUTIL_H 1

#include <stdarg.h>             /* va_list */
#include <sys/types.h>          /* size_t and ssize_t */

/* Forward declaration rather than including sys/uio.h. */
struct iovec;

/* BEGIN_DECLS is used at the beginning of declarations so that C++
   compilers don't mangle their names.  END_DECLS is used at the end. */
#undef BEGIN_DECLS
#undef END_DECLS
#ifdef __cplusplus
# define BEGIN_DECLS    extern "C" {
# define END_DECLS      }
#else
# define BEGIN_DECLS    /* empty */
# define END_DECLS      /* empty */
#endif

/* __attribute__ is available in gcc 2.5 and later, but only with gcc 2.7
   could you use the __format__ form of the attributes, which is what we use
   (to avoid confusion with other macros). */
#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7)
#  define __attribute__(spec)   /* empty */
# endif
#endif

/* Used for unused parameters to silence gcc warnings. */
#define UNUSED  __attribute__((__unused__))

BEGIN_DECLS

/* Additional log function takes the length of the resulting message, the
   format, the arguments, and the errno if any. */
typedef void (*error_log_t)(int, const char *, va_list, int);

/* If non-NULL, called after printing to stderr and passed the message. */
extern error_log_t error_log_function;

/* If non-NULL, called before exit and its return value passed to exit. */
extern int (*error_fatal_cleanup)(void);

/* If non-NULL, prepended (followed by ": ") to all error messages. */
extern const char *error_program_name;

/* Failure handler takes the function, the size, the file, and the line. */
typedef void (*xmalloc_handler_t)(const char *, size_t, const char *, int);

/* Assign to this variable to choose a handler other than the default, which
   just calls sysdie. */
extern xmalloc_handler_t xmalloc_error_handler;

/* Function prototypes. */
extern void *concat(const char *, ...);
extern void warn(const char *, ...)
    __attribute__((__format__(printf, 1, 2)));
extern void syswarn(const char *, ...)
    __attribute__((__format__(printf, 1, 2)));
extern void die(const char *, ...)
    __attribute__((__noreturn__, __format__(printf, 1, 2)));
extern void sysdie(const char *, ...)
    __attribute__((__noreturn__, __format__(printf, 1, 2)));
ssize_t xwrite(int fd, const void *buffer, size_t size);
ssize_t xwritev(int fd, const struct iovec iov[], int iovcnt);

/* The xmalloc, xrealloc, and xstrdup functions are actually macros so that
   we can pick up the file and line number information for debugging error
   messages without the user having to pass those in every time. */
#define xmalloc(size)           x_malloc((size), __FILE__, __LINE__)
#define xrealloc(p, size)       x_realloc((p), (size), __FILE__, __LINE__)
#define xstrdup(p)              x_strdup((p), __FILE__, __LINE__)

/* Last two arguments are always file and line number.  These are internal
   implementations that should not be called directly.  ISO C99 says that
   identifiers beginning with _ and a lowercase letter are reserved for
   identifiers of file scope, so while the position of libraries in the
   standard isn't clear, it's probably not entirely kosher to use _xmalloc
   here.  Use x_malloc instead. */
extern void *x_malloc(size_t, const char *, int);
extern void *x_realloc(void *, size_t, const char *, int);
extern char *x_strdup(const char *, const char *, int);

END_DECLS

#endif /* !LIBRUTIL_H */
