/* concat.h -- Concatenate strings with dynamic memory allocation. */
/* $Id$ */

#ifndef CONCAT_H
#define CONCAT_H 1

#ifndef CONFIG_H
# include "config.h"
#endif

#if STDC_HEADERS || HAVE_STDARG_H
extern void *concat(const char *, ...);
#else
extern void *concat();
#endif

#endif /* !CONCAT_H */
