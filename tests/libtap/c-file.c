/*
 * Test locating files with test_file_path().
 *
 * Written by Russ Allbery <rra@stanford.edu>
 * Copyright 2010 Board of Trustees, Leland Stanford Jr. University
 *
 * See LICENSE for licensing terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <tap/basic.h>


int
main(void)
{
    char *path;
    FILE *output;

    output = fopen("c-file.output", "w");
    if (output == NULL)
        sysbail("cannot create c-file.output");
    fprintf(output, "Path to c-file: %s/libtap/c-file\n", getenv("BUILD"));
    fprintf(output, "Path to c-basic.output: %s/libtap/c-basic.output\n",
            getenv("SOURCE"));
    fclose(output);
    path = test_file_path("libtap/c-file");
    printf("Path to c-file: %s\n", path);
    test_file_path_free(path);
    path = test_file_path("libtap/c-basic.output");
    printf("Path to c-basic.output: %s\n", path);
    test_file_path_free(path);

    return 0;
}
