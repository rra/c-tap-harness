/*
 * Test of the libtap test_cleanup_register function with lazy planning.
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
    plan_lazy();
    ok(1, "foo");
    test_cleanup_register(test);
    return 0;
}
