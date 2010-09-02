/*
 * Calls libtap basic functions for testing.
 *
 * Written by Russ Allbery <rra@stanford.edu>
 * Copyright 2008, 2009 Board of Trustees, Leland Stanford Jr. University
 *
 * See LICENSE for licensing terms.
 */

#include <stdlib.h>

#include <tap/basic.h>

/*
 * Test okv(), which requires having a separate stdargs function that
 * generates the va_list.
 */
static void
test_okv(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    okv(1, format, args);
    va_end(args);
}


int
main(void)
{
    plan(39);

    ok(1, NULL);
    ok(0, NULL);
    is_int(0, 0, NULL);
    is_int(1, 1, "an integer test");
    is_int(-1, -1, "comparing %d and %d", -1, -1);
    is_int(-1, 1, NULL);
    is_double(0, 0, 0, NULL);
    is_double(0.1, 0.11, 0.02, "a double test");
    is_double(0.1, -0.1, 0.1, "a failing double test");
    is_double(0, -0, 0.1, NULL);
    is_double(1.7e45, 1.7e45, 0.1, NULL);
    is_double(strtod("NAN", NULL), strtod("NAN", NULL), 0, "NaN");
    is_double(strtod("INF", NULL), strtod("INF", NULL), 0, "inf");
    is_double(strtod("-INF", NULL), strtod("-INF", NULL), 0, "-inf");
    is_double(strtod("INF", NULL), strtod("-INF", NULL), 0, "inf and -inf");
    is_string("", "", NULL);
    is_string("yes", "yes", "a string test");
    is_string("yes", "yes no", "%s", "");
    is_string(NULL, NULL, "null null");
    is_string("yes", NULL, NULL);
    is_string(NULL, "yes", NULL);
    skip("testing skip %s", "foo");
    ok_block(2, 1, NULL);
    ok_block(4, 0, "some %s", "block");
    skip_block(4, "testing skip block");
    skip(NULL);
    skip_block(2, NULL);
    is_hex(2147483649UL, 2147483649UL, "2^31 + 1 correct");
    is_hex(2147483649UL, 0, "2^31 + 1 incorrect");
    is_hex(0, 0, NULL);
    test_okv("testing %s", "okv");

    return 0;
}
