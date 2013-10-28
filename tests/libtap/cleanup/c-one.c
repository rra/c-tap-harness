/*
 * Test of the libtap test_cleanup_register function with one cleanup.
 *
 * Copyright 2013 Russ Allbery <eagle@eyrie.org>
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
    plan(1);
    ok(1, "some test");
    return 0;
}
