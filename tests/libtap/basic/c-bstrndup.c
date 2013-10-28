/*
 * Test bstrndup to duplicate strings.
 *
 * Copyright 2012 Russ Allbery <eagle@eyrie.org>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tests/tap/basic.h>


int
main(void)
{
    char *data, *copy;
    const char string[] = "Test string";

    copy = bstrndup(string, 100);
    printf("%s\n", copy);
    free(copy);
    copy = bstrndup(string, strlen(string));
    printf("%s\n", copy);
    free(copy);
    copy = bstrndup(string, 4);
    printf("%s\n", copy);
    free(copy);
    data = bmalloc(5);
    memset(data, 'a', 5);
    copy = bstrndup(data, 5);
    printf("%s\n", copy);
    free(data);
    free(copy);

    return 0;
}
