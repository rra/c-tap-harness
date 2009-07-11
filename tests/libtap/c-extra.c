/*
 * Calls libtap with more tests than planned.
 *
 * This test exists to test the atexit output from libtap in a case of more
 * tests than planned and a plan greater than 1.
 *
 * Copyright 2009 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <tap/basic.h>

int
main(void)
{
    plan(2);

    ok(1, "first");
    ok(2, "second");
    ok(3, "third");

    return 0;
}
