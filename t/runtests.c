/* $Id$

   Run a set of tests, reporting results.

   Copyright 2000 Russ Allbery <rra@stanford.edu>

   This program is free software under an MIT-style license.  See the file
   LICENSE which should have accompanied this file for exact terms and
   conditions.

   Usage:

        test_batch(file);

   Expects a list of executables located in the given file, one line per
   executable.  For each one, runs it as part of a test suite, reporting
   results.  Test output should start with a line containing the number of
   tests (numbered from 1 to this number), and then each line should be in
   the following format:

        ok <number>
        not ok <number>
        ok <number> # skip

   where <number> is the number of the test.  ok indicates success, not ok
   indicates failure, and "# skip" indicates the test was skipped for some
   reason (maybe because it doesn't apply to this platform). */

#include "config.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error.h"
#include "xmalloc.h"

/* Test status codes. */
enum test_status {
    TEST_FAIL,
    TEST_PASS,
    TEST_SKIP,
    TEST_INVALID
};

/* Error exit statuses for test processes. */
#define CHILDERR_DUP    100     /* Couldn't redirect stderr or stdout. */
#define CHILDERR_EXEC   101     /* Couldn't exec child process. */
#define CHILDERR_STDERR 102     /* Couldn't open stderr file. */

/* Structure to hold data for a set of tests. */
struct testset {
    int count;                  /* Expected count of tests. */
    int passed;                 /* Count of passing tests. */
    int failed;                 /* Count of failing lists. */
    int skipped;                /* Count of skipped tests (passed). */
    enum test_status *results;  /* Table of results by test number. */
    const char *file;           /* The file name of the test. */
};

/* Internal prototypes. */
static int test_batch(const char *testlist);
static int test_init(const char *line, struct testset *ts);
static pid_t test_start(const char *path, const char *errfile, int *fd);
static int test_finish(int fd, pid_t pid);


/* Read the first line of test output, which should contain the range of
   test numbers, and initialize the testset structure except for the name
   (which should already be set).  Return true if initialization succeeded,
   false otherwise.  No more than 10,000 tests are allowed in one set. */
static int
test_init(const char *line, struct testset *ts)
{
    int *results;
    int i;

    i = atoi(line);
    if (!i) {
        warn("%s: invalid test count: %s", ts->file, line);
        return 0;
    }
    if (i > 10000) {
        warn("%s: claimed %d tests, maximum is 10,000", ts->file, i);
        return 0;
    }
    ts->count = i;
    ts->passed = 0;
    ts->failed = 0;
    ts->skipped = 0;
    ts->results = xmalloc(ts->count * sizeof(int));
    for (i = 0; i < ts->count; i++) ts->results[i] = TEST_INVALID;
    return 1;
}


/* Start a program, connecting its stdout to a pipe on our end, its stderr
   to the given file name, and storing the file descriptor to read from in
   the third argument.  Returns the PID of the new process.  Errors are
   fatal. */
static pid_t
test_start(const char *path, const char *errfile, int *fd)
{
    int fds[2], errfd;
    pid_t child;

    if (pipe(fds) == -1) sysdie("can't create pipe");
    child = fork();
    if (child == (pid_t) -1) {
        sysdie("can't fork");
    } else if (child == 0) {
        /* In child.  Set up our stdout and stderr. */
        errfd = open(errfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (errfd < 0) _exit(CHILDERR_STDERR);
        if (dup2(errfd, 2) == -1) _exit(CHILDERR_DUP);
        close(fds[0]);
        if (dup2(fds[1], 1) == -1) _exit(CHILDERR_DUP);

        /* Now, exec our process. */
        if (execl(path, path, (char *) 0) == -1) _exit(CHILDERR_EXEC);
    } else {
        /* In parent.  Close the extra file descriptor. */
        close(fds[1]);
    }
    *fd = fds[0];
    return child;
}


/* Finish off a child process behind the given file descriptor with the
   given PID.  Closes the file descriptor and waits for the child, returning
   its exit status in the same format as the second argument to waitpid.
   Errors are fatal. */
static int
test_finish(int fd, pid_t pid)
{
    pid_t child;
    int status;

    close(fd);
    child = waitpid(pid, &status, 0);
    if (child == (pid_t) -1)
        sysdie("waitpid for %u failed", (unsigned int) pid);
    return status;
}


/* Runs a single test set, redirecting stderr to harness.err and parsing
   stdout looking for "ok" and "not ok" lines.  Any other line on stdout is
   treated as a fatal error.  Takes the test set to run.  Returns true if
   the test set was successfully run (even if some tests failed), false
   otherwise. */
static int
test_run(struct testset *ts)
{
    char buffer[BUFSIZ];
    FILE *output;
    pid_t testpid;
    int outfd, current, status, i;
    int missing = 0;
    int failed = 0;

    /* Initialize the test and our data structures. */
    testpid = test_start(ts->file, "errors.out", &outfd);
    output = fdopen(outfd, "r");
    if (!output) sysdie("fdopen failed");
    if (!fgets(buffer, sizeof(buffer), output)) sysdie("fgets failed");
    if (!test_init(buffer, ts)) return 0;

    /* Read each line the test prints to stdout, checking it for ok or not
       ok and failing the test set if we see anything else. */
    while (fgets(buffer, sizeof(buffer), output)) {
        if (buffer[strlen(buffer) - 1] != '\n') {
            warn("%s: excessive output: %s", ts->file, buffer);
            return 0;
        }
        if (sscanf(buffer, "not ok %d", &current) == 1) {
            status = TEST_FAIL;
        } else if (sscanf(buffer, "ok %d", &current) == 1) {
            status = TEST_PASS;
        } else {
            warn("%s: invalid output: %s", ts->file, buffer);
            return 0;
        }
        if (current < 1 || current > ts->count) {
            warn("%s: invalid test number %d", ts->file, current);
            return 0;
        }
        if (ts->results[current - 1] != TEST_INVALID) {
            warn("%s: duplicate test number %d", ts->file, current);
        }
        ts->results[current - 1] = status;
        if (status == TEST_PASS) ts->passed++; else ts->failed++;
    }
    if (ferror(output)) sysdie("%s: error reading output");
    status = test_finish(outfd, testpid);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        warn("%s: non-zero exit status %d", ts->file, status);
        return 0;
    }

    /* This closes the output file descriptor twice, but we want to free the
       FILE structure as well and the second close should be harmless. */
    fclose(output);

    /* Summarize the results of the test set to stdout. */
    for (i = 0; i < ts->count; i++)
        if (ts->results[i] == TEST_INVALID)
            printf("%s%d", missing++ ? ", " : "MISSED ", i + 1);
    for (i = 0; i < ts->count; i++) {
        if (ts->results[i] == TEST_FAIL) {
            if (missing && !failed) fputs("; ", stdout);
            printf("%s%d", failed++ ? ", " : "FAILED ", i + 1);
        }
    }
    if (!missing && !failed) fputs("ok", stdout);
    return 1;
}


/* Run a batch of tests from a given file listing each test on a line by
   itself.  The file must be rewindable.  Returns true iff all tests
   passed. */
static int
test_batch(const char *testlist)
{
    char *p;
    FILE *tests;
    size_t length;
    size_t longest = 0;
    char buffer[BUFSIZ];
    int line, i;
    struct testset ts;
    int total = 0;
    int failed = 0;

    /* Open our file of tests to run and scan it, checking for lines that
       are too long and searching for the longest line. */
    tests = fopen(testlist, "r");
    if (!tests) sysdie("can't open %s", testlist);
    line = 0;
    while (fgets(buffer, sizeof(buffer), tests)) {
        line++;
        length = strlen(buffer) - 1;
        if (buffer[length] != '\n')
            die("%s:%d: line too long", testlist, line);
        if (length > longest) longest = length;
    }
    if (fseek(tests, 0, SEEK_SET) == -1)
        sysdie("can't rewind %s", testlist);

    /* Add two to longest and round up to the nearest tab stop.  This is how
       wide the column for printing the current test name will be. */
    longest += 2;
    if (longest % 8) longest += 8 - (longest % 8);

    /* Now, plow through our tests again, running each one.  Check line
       length again out of paranoia. */
    line = 0;
    while (fgets(buffer, sizeof(buffer), tests)) {
        line++;
        length = strlen(buffer) - 1;
        if (buffer[length] != '\n')
            die("%s:%d: line too long", testlist, line);
        buffer[length] = '\0';
        fputs(buffer, stdout);
        for (i = length; i < longest; i++) putchar('.');
        memset(&ts, 0, sizeof(ts));
        ts.file = buffer;
        if (test_run(&ts)) {
            total += ts.count;
            failed += ts.failed;
            putchar('\n');
        } else {
            printf("\nFailed!\n");
        }
    }

    /* Print out our final results. */
    if (failed == 0) {
        printf("All tests successful.\n");
    } else {
        printf("Failed %d/%d tests, %.2f%% okay.\n", failed, total,
               (total - failed) * 100.0 / total);
    }
    printf("Files=%d,  Tests=%d\n", line, total);
    return (failed != 0);
}


/* Main routine.  Given a file listing tests, run each test listed. */
int
main(int argc, char *argv[])
{
    if (argc != 2) die("Usage: runtests <test-list>\n");
    test_batch(argv[1]);
    return 0;
}
