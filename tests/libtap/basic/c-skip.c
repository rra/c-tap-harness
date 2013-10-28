/*
 * Test of the libtap skip_all function without a reason.
 *
 * Copyright 2009 Russ Allbery <eagle@eyrie.org>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>

#include <tests/tap/basic.h>

int
main(void)
{
    skip_all(NULL);
    ok(1, "should never see this");

    return 0;
}
