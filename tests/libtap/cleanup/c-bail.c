/*
 * Test of the libtap test_cleanup_register function with bail.
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
    plan_lazy();
    bail("aborting");
    return 0;
}
