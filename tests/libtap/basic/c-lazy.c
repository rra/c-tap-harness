/*
 * Calls libtap with lazy planning.
 *
 * This test exists to test the atexit output from libtap in a case of only
 * successful tests, more than one, and lazy planning.
 *
 * Copyright 2010 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <tests/tap/basic.h>

int
main(void)
{
    plan_lazy();

    ok(1, "first");
    skip("second");

    return 0;
}
