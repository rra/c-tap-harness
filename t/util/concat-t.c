/* $Id$ */
/* concat() test suite. */

#include <stdio.h>
#include <string.h>

#include "concat.h"

#define END     (char *) 0

void
ok(int n, int success)
{
    printf("%sok %d\n", success ? "" : "not ", n);
}

int
main(void)
{
    int i = 1;

    printf("7\n");
    ok(i++, !strcmp("a",     concat("a",                   END)));
    ok(i++, !strcmp("ab",    concat("a", "b",              END)));
    ok(i++, !strcmp("ab",    concat("ab", "",              END)));
    ok(i++, !strcmp("ab",    concat("", "ab",              END)));
    ok(i++, !strcmp("",      concat("",                    END)));
    ok(i++, !strcmp("abcde", concat("ab", "c", "", "de",   END)));
    ok(i++, !strcmp("abcde", concat("abc", "de", END, "f", END)));
    return 0;
}
