/*
 * Test of the libtap test_cleanup_register function with forking.
 *
 * Copyright 2013 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
    pid_t child;

    plan(1);
    test_cleanup_register(test);
    ok(1, "some test");
    child = fork();
    if (child < 0)
        sysbail("cannot fork");
    else if (child == 0) {
        diag("some output from child");
        exit(0);
    } else {
        waitpid(child, NULL, 0);
    }
    return 0;
}
