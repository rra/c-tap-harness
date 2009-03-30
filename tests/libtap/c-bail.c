/*
 * Test of the libtap bail function.
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
    ok(1, "first test");
    bail("some error message");
    ok(1, "second test");

    return 0;
}
