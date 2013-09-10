/*
 * Test of the libtap test_cleanup_register function with lazy bail.
 *
 * Copyright 2013 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>

#include <tests/tap/basic.h>


/*
 * The test function to call during cleanup.
 */
static void
test(int success)
{
    printf("Called cleanup with %d\n", success);
}


int
main(void)
{
    test_cleanup_register(test);
    plan_lazy();
    ok(1, "first test");
    ok(1, "second test");
    bail("aborting");
    return 0;
}
