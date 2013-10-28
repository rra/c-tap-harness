/*
 * Test creating a temporary directory with test_tmpdir().
 *
 * Copyright 2011, 2013 Russ Allbery <eagle@eyrie.org>
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <tests/tap/basic.h>


int
main(void)
{
    char *path, *tmp;
    FILE *output;
    const char *build;
    struct stat st;
    size_t length;

    output = fopen("c-tmpdir.output", "w");
    if (output == NULL)
        sysbail("cannot create c-tmpdir.output");
    fprintf(output, "Path to temporary directory: %s/tmp\n", getenv("BUILD"));
    fclose(output);
    build = getenv("BUILD");
    length = strlen(build) + strlen("/tmp") + 1;
    path = bmalloc(length);
    sprintf(path, "%s/tmp", build);
    if (access(path, F_OK) == 0)
        bail("%s already exists", path);
    free(path);
    path = test_tmpdir();
    printf("Path to temporary directory: %s\n", path);
    if (stat(path, &st) < 0)
        sysbail("cannot stat %s", path);
    if (!S_ISDIR(st.st_mode))
        sysbail("%s is not a directory", path);
    tmp = bstrdup(path);
    test_tmpdir_free(path);
    if (stat(tmp, &st) == 0)
        bail("temporary directory not removed");
    free(tmp);

    return 0;
}
