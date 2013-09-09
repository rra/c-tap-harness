/*
 * Test of the libtap test_cleanup_register function with failure.
 *
 * Copyright 2013 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>

#include <tests/tap/basic.h>


/*
 * The first test function to call during cleanup.
 */
static void
one(int success)
{
    printf("Called cleanup with %d\n", success);
}


/*
 * The second test function to call during cleanup.
 */
static void
two(int success)
{
    printf("Second cleanup (%d)\n", success);
}


int
main(void)
{
    test_cleanup_register(one);
    plan(3);
    test_cleanup_register(two);
    test_cleanup_register(one);
    ok(1, "some test");
    test_cleanup_register(two);
    ok(0, "another test");
    ok(1, "third test");
    test_cleanup_register(one);
    return 0;
}
