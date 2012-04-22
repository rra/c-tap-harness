/*
 * Test of the libtap skip_all function with a reason.
 *
 * Copyright 2009 Russ Allbery <rra@stanford.edu>
 *
 * See LICENSE for licensing terms.
 */

#include <tests/tap/basic.h>

int
main(void)
{
    skip_all("the %s reason", "important");
    ok(1, "should never see this");

    return 0;
}
