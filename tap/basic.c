/*
 * Some utility routines for writing tests.
 *
 * Herein are a variety of utility routines for writing tests.  All routines
 * of the form ok*() take a test number and some number of appropriate
 * arguments, check to be sure the results match the expected output using the
 * arguments, and print out something appropriate for that test number.  Other
 * utility routines help in constructing more complex tests.
 *
 * Copyright 2009 Russ Allbery <rra@stanford.edu>
 * Copyright 2006, 2007, 2008
 *     Board of Trustees, Leland Stanford Jr. University
 * Copyright (c) 2004, 2005, 2006
 *     by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1991, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001,
 *     2002, 2003 by The Internet Software Consortium and Rich Salz
 *
 * See LICENSE for licensing terms.
 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <tap/basic.h>


/*
 * Initialize things.  Turns on line buffering on stdout and then prints out
 * the number of tests in the test suite.
 */
void
plan(int count)
{
    if (setvbuf(stdout, NULL, _IOLBF, BUFSIZ) != 0)
        fprintf(stderr, "cannot set stdout to line buffered: %s\n",
                strerror(errno));
    printf("1..%d\n", count);
}


/*
 * Takes a boolean success value and assumes the test passes if that value
 * is true and fails if that value is false.
 */
void
ok(int n, int success)
{
    printf("%sok %d\n", success ? "" : "not ", n);
}


/*
 * Skip a test.
 */
void
skip(int n, const char *reason)
{
    printf("ok %d # skip", n);
    if (reason != NULL)
        printf(" %s", reason);
    putchar('\n');
}


/*
 * Report the same status on the next count tests.
 */
void
ok_block(int n, int count, int status)
{
    int i;

    for (i = 0; i < count; i++)
        ok(n++, status);
}


/*
 * Skip the next count tests.
 */
void
skip_block(int n, int count, const char *reason)
{
    int i;

    for (i = 0; i < count; i++)
        skip(n++, reason);
}


/*
 * Takes an expected integer and a seen integer and assumes the test passes
 * if those two numbers match.
 */
void
is_int(int n, int wanted, int seen)
{
    if (wanted == seen)
        printf("ok %d\n", n);
    else
        printf("# wanted: %d\n#   seen: %d\nnot ok %d\n", wanted, seen, n);
}


/*
 * Takes a string and what the string should be, and assumes the test passes
 * if those strings match (using strcmp).
 */
void
is_string(int n, const char *wanted, const char *seen)
{
    if (wanted == NULL)
        wanted = "(null)";
    if (seen == NULL)
        seen = "(null)";
    if (strcmp(wanted, seen) != 0)
        printf("# wanted: %s\n#   seen: %s\nnot ok %d\n", wanted, seen, n);
    else
        printf("ok %d\n", n);
}


/*
 * Takes an expected integer and a seen integer and assumes the test passes if
 * those two numbers match.
 */
void
is_double(int n, double wanted, double seen)
{
    if (wanted == seen)
        printf("ok %d\n", n);
    else
        printf("# wanted: %g\n#   seen: %g\nnot ok %d\n", wanted, seen, n);
}


/*
 * Bail out with an error.
 */
void
bail(const char *format, ...)
{
    va_list args;

    fflush(stdout);
    printf("Bail out! ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
    exit(1);
}
