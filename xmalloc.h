/* xmalloc.h -- malloc routines with failure handling. */
/* $Id$ */

#ifndef XMALLOC_H
#define XMALLOC_H 1

#include <sys/types.h>

/* The xmalloc, xrealloc, and xstrdup functions are actually macros so that
   we can pick up the file and line number information for debugging error
   messages without the user having to pass those in every time. */
#define xmalloc(size)           x_malloc((size), __FILE__, __LINE__)
#define xrealloc(p, size)       x_realloc((p), (size), __FILE__, __LINE__)
#define xstrdup(p)              x_strdup((p), __FILE__, __LINE__)

/* Failure handler takes the function, the size, the file, and the line. */
typedef void (*xmalloc_handler_t)(const char *, size_t, const char *, int);

/* Assign to this variable to choose a handler other than the default, which
   just calls sysdie. */
extern xmalloc_handler_t xmalloc_error_handler;

/* Last two arguments are always file and line number.  These are internal
   implementations that should not be called directly.  ISO C99 says that
   identifiers beginning with _ and a lowercase letter are reserved for
   identifiers of file scope, so while the position of libraries in the
   standard isn't clear, it's probably not entirely kosher to use _xmalloc
   here.  Use x_malloc instead. */
extern void *x_malloc(size_t, const char *, int);
extern void *x_realloc(void *, size_t, const char *, int);
extern char *x_strdup(const char *, const char *, int);

#endif /* !XMALLOC_H */
