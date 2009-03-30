/*
 * Calls libtap basic functions for testing.
 *
 * Written by Russ Allbery <rra@stanford.edu>
 * Copyright 2008 Board of Trustees, Leland Stanford Jr. University
 *
 * See LICENSE for licensing terms.
 */

#include <stdlib.h>

#include <tap/basic.h>

int
main(void)
{
    plan(29);
    ok(1, NULL);
    ok(0, NULL);
    is_int(0, 0, NULL);
    is_int(1, 1, "an integer test");
    is_int(-1, -1, "comparing %d and %d", -1, -1);
    is_int(-1, 1, NULL);
    is_double(0, 0, NULL);
    is_double(0.1, 0.1, "a double test");
    is_double(0.1, -0.1, "a failing double test");
    is_double(0, -0, NULL);
    is_double(1.7e45, 1.7e45, NULL);
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

    return 0;
}
