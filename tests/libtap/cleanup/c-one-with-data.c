/*
 * Test of the libtap test_cleanup_register_with_data function with one cleanup.
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>
#include <stdint.h>

#include <tests/tap/basic.h>


/*
 * The test function to call during cleanup.
 */
static void
test(int success, int primary, void *data)
{
    printf("Called cleanup with %d %d %d\n", success, primary, (int)(intptr_t)data);
}


int
main(void)
{
    test_cleanup_register_with_data(test, (void *)99);
    plan(1);
    ok(1, "some test");
    return 0;
}
