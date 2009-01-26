/*
 * Basic utility routines for the TAP protocol.
 *
 * Copyright 2006, 2007, 2008
 *     Board of Trustees, Leland Stanford Jr. University
 * Copyright (c) 2004, 2005, 2006
 *     by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1991, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001,
 *     2002, 2003 by The Internet Software Consortium and Rich Salz
 *
 * See LICENSE for licensing terms.
 */

#ifndef TAP_BASIC_H
#define TAP_BASIC_H 1

#include <sys/types.h>          /* pid_t */

/*
 * BEGIN_DECLS is used at the beginning of declarations so that C++
 * compilers don't mangle their names.  END_DECLS is used at the end.
 */
#undef BEGIN_DECLS
#undef END_DECLS
#ifdef __cplusplus
# define BEGIN_DECLS    extern "C" {
# define END_DECLS      }
#else
# define BEGIN_DECLS    /* empty */
# define END_DECLS      /* empty */
#endif

BEGIN_DECLS

/* Print out the number of tests and set standard output to line buffered. */
void plan(int count);

/* Basic reporting functions. */
void ok(int n, int success);
void skip(int n, const char *reason);

/* Report the same status on, or skip, the next count tests. */
void ok_block(int n, int count, int success);
void skip_block(int n, int count, const char *reason);

/* Check an expected value against a seen value. */
void is_int(int n, int wanted, int seen);
void is_double(int n, double wanted, double seen);
void is_string(int n, const char *wanted, const char *seen);

END_DECLS

#endif /* LIBTEST_H */
