/*
 * Test of the libtap sysbail function.
 *
 * Copyright 2009 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <tap/basic.h>

int
main(void)
{
    FILE *output;

    output = fopen("c-sysbail.output", "w");
    if (output == NULL)
        sysbail("cannot create c-sysbail.output");
    fprintf(output, "1..2\nok 1\nBail out! error: %s\n", strerror(EPERM));
    fclose(output);
    plan(2);
    ok(1, NULL);
    errno = EPERM;
    sysbail("error");
    ok(1, "second test");

    return 0;
}
