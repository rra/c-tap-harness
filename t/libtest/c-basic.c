/*
 * Calls libtest functions for testing.
 *
 * Copyright 2008 Board of Trustees, Leland Stanford Jr. University
 *
 * See LICENSE for licensing terms.
 */

#include <stdlib.h>

#include <libtest.h>

int
main(void)
{
    test_init(29);
    ok(1, 1);
    ok(2, 0);
    ok_int(3, 0, 0);
    ok_int(4, 1, 1);
    ok_int(5, -1, -1);
    ok_int(6, -1, 1);
    ok_double(7, 0, 0);
    ok_double(8, 0.1, 0.1);
    ok_double(9, 0.1, -0.1);
    ok_double(10, 0, -0);
    ok_double(11, 1.7e45, 1.7e45);
    ok_string(12, "", "");
    ok_string(13, "yes", "yes");
    ok_string(14, "yes", "yes no");
    ok_string(15, NULL, NULL);
    ok_string(16, "yes", NULL);
    ok_string(17, NULL, "yes");
    skip(18, "testing skip");
    ok_block(19, 2, 1);
    ok_block(21, 4, 0);
    skip_block(25, 4, "testing skip block");

    return 0;
}
