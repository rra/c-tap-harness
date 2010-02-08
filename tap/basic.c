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
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include <tap/basic.h>

/*
 * The test count.  Always contains the number that will be used for the next
 * test status.
 */
int testnum = 1;

/*
 * Status information stored so that we can give a test summary at the end of
 * the test case.  We store the planned final test and the count of failures.
 * We can get the highest test count from testnum.
 *
 * We also store the PID of the process that called plan() and only summarize
 * results when that process exits, so as to not misreport results in forked
 * processes.
 */
static int _planned = 0;
static int _failed  = 0;
static pid_t _process = 0;


/*
 * Our exit handler.  Called on completion of the test to report a summary of
 * results provided we're still in the original process.
 */
static void
finish(void)
{
    int highest = testnum - 1;

    if (_process != 0 && getpid() == _process && _planned > 0) {
        if (_planned > highest)
            printf("# Looks like you planned %d test%s but only ran %d\n",
                   _planned, (_planned > 1 ? "s" : ""), highest);
        else if (_planned < highest)
            printf("# Looks like you planned %d test%s but ran %d extra\n",
                   _planned, (_planned > 1 ? "s" : ""), highest - _planned);
        else if (_failed > 0)
            printf("# Looks like you failed %d test%s of %d\n", _failed,
                   (_failed > 1 ? "s" : ""), _planned);
        else if (_planned > 1)
            printf("# All %d tests successful or skipped\n", _planned);
        else
            printf("# %d test successful or skipped\n", _planned);
    }
}


/*
 * Initialize things.  Turns on line buffering on stdout and then prints out
 * the number of tests in the test suite.
 */
void
plan(int count)
{
    if (setvbuf(stdout, NULL, _IOLBF, BUFSIZ) != 0)
        fprintf(stderr, "# cannot set stdout to line buffered: %s\n",
                strerror(errno));
    printf("1..%d\n", count);
    testnum = 1;
    _planned = count;
    _process = getpid();
    atexit(finish);
}


/*
 * Skip the entire test suite and exits.  Should be called instead of plan(),
 * not after it, since it prints out a special plan line.
 */
void
skip_all(const char *format, ...)
{
    printf("1..0 # skip");
    if (format != NULL) {
        va_list args;

        putchar(' ');
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
    putchar('\n');
    exit(0);
}


/*
 * Print the test description.
 */
static void
print_desc(const char *format, va_list args)
{
    printf(" - ");
    vprintf(format, args);
}


/*
 * Takes a boolean success value and assumes the test passes if that value
 * is true and fails if that value is false.
 */
void
ok(int success, const char *format, ...)
{
    printf("%sok %d", success ? "" : "not ", testnum++);
    if (!success)
        _failed++;
    if (format != NULL) {
        va_list args;

        va_start(args, format);
        print_desc(format, args);
        va_end(args);
    }
    putchar('\n');
}


/*
 * Skip a test.
 */
void
skip(const char *reason, ...)
{
    printf("ok %d # skip", testnum++);
    if (reason != NULL) {
        va_list args;

        va_start(args, reason);
        putchar(' ');
        vprintf(reason, args);
        va_end(args);
    }
    putchar('\n');
}


/*
 * Report the same status on the next count tests.
 */
void
ok_block(int count, int status, const char *format, ...)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("%sok %d", status ? "" : "not ", testnum++);
        if (!status)
            _failed++;
        if (format != NULL) {
            va_list args;

            va_start(args, format);
            print_desc(format, args);
            va_end(args);
        }
        putchar('\n');
    }
}


/*
 * Skip the next count tests.
 */
void
skip_block(int count, const char *reason, ...)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("ok %d # skip", testnum++);
        if (reason != NULL) {
            va_list args;

            va_start(args, reason);
            putchar(' ');
            vprintf(reason, args);
            va_end(args);
        }
        putchar('\n');
    }
}


/*
 * Takes an expected integer and a seen integer and assumes the test passes
 * if those two numbers match.
 */
void
is_int(int wanted, int seen, const char *format, ...)
{
    if (wanted == seen)
        printf("ok %d", testnum++);
    else {
        printf("# wanted: %d\n#   seen: %d\n", wanted, seen);
        printf("not ok %d", testnum++);
        _failed++;
    }
    if (format != NULL) {
        va_list args;

        va_start(args, format);
        print_desc(format, args);
        va_end(args);
    }
    putchar('\n');
}


/*
 * Takes a string and what the string should be, and assumes the test passes
 * if those strings match (using strcmp).
 */
void
is_string(const char *wanted, const char *seen, const char *format, ...)
{
    if (wanted == NULL)
        wanted = "(null)";
    if (seen == NULL)
        seen = "(null)";
    if (strcmp(wanted, seen) == 0)
        printf("ok %d", testnum++);
    else {
        printf("# wanted: %s\n#   seen: %s\n", wanted, seen);
        printf("not ok %d", testnum++);
        _failed++;
    }
    if (format != NULL) {
        va_list args;

        va_start(args, format);
        print_desc(format, args);
        va_end(args);
    }
    putchar('\n');
}


/*
 * Takes an expected double and a seen double and assumes the test passes if
 * those two numbers match.
 */
void
is_double(double wanted, double seen, const char *format, ...)
{
    if (wanted == seen)
        printf("ok %d", testnum++);
    else {
        printf("# wanted: %g\n#   seen: %g\n", wanted, seen);
        printf("not ok %d", testnum++);
        _failed++;
    }
    if (format != NULL) {
        va_list args;

        va_start(args, format);
        print_desc(format, args);
        va_end(args);
    }
    putchar('\n');
}


/*
 * Takes an expected unsigned long and a seen unsigned long and assumes the
 * test passes if the two numbers match.  Otherwise, reports them in hex.
 */
void
is_hex(unsigned long wanted, unsigned long seen, const char *format, ...)
{
    if (wanted == seen)
        printf("ok %d", testnum++);
    else {
        printf("# wanted: %lx\n#   seen: %lx\n", (unsigned long) wanted,
               (unsigned long) seen);
        printf("not ok %d", testnum++);
        _failed++;
    }
    if (format != NULL) {
        va_list args;

        va_start(args, format);
        print_desc(format, args);
        va_end(args);
    }
    putchar('\n');
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


/*
 * Bail out with an error, appending strerror(errno).
 */
void
sysbail(const char *format, ...)
{
    va_list args;
    int oerrno = errno;

    fflush(stdout);
    printf("Bail out! ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(": %s\n", strerror(oerrno));
    exit(1);
}
