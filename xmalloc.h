/* xmalloc.h -- malloc routines with failure handling. */
/* $Id$ */

#ifndef XMALLOC_H
#define XMALLOC_H 1

#ifndef CONFIG_H
# include "config.h"
#endif

#include <sys/types.h>

/* The xmalloc, xrealloc, and xstrdup functions are actually macros so that
   we can pick up the file and line number information for debugging error
   messages without the user having to pass those in every time. */
#define xmalloc(size)           _xmalloc((size), __FILE__, __LINE__)
#define xrealloc(p, size)       _xrealloc((p), (size), __FILE__, __LINE__)
#define xstrdup(p)              _xstrdup((p), __FILE__, __LINE__)

/* Failure handler takes the function, the size, the file, and the line. */
typedef void (*xmalloc_handler_t)(const char *, size_t, const char *, int);

/* Assign to this variable to choose a handler other than the default, which
   just calls sysdie. */
extern xmalloc_handler_t xmalloc_error_handler;

/* Last two arguments are always file and line number. */
extern void *_xmalloc(size_t, const char *, int);
extern void *_xrealloc(void *, size_t, const char *, int);
extern char *_xstrdup(const char *, const char *, int);

#endif /* !XMALLOC_H */
