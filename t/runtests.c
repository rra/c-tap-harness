/* $Id$

   Run a set of tests, reporting results.

   Copyright 2000 Russ Allbery <rra@stanford.edu>

   This program is free software under an MIT-style license.  See the file
   LICENSE which should have accompanied this file for exact terms and
   conditions.

   Usage:

        runtests <test-list>

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

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* sys/time.h must be included before sys/resource.h on some platforms. */
#include <sys/resource.h>

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
    const char *file;           /* The file name of the test. */
    int count;                  /* Expected count of tests. */
    int current;                /* The last seen test number. */
    int passed;                 /* Count of passing tests. */
    int failed;                 /* Count of failing lists. */
    int skipped;                /* Count of skipped tests (passed). */
    enum test_status *results;  /* Table of results by test number. */
    int aborted;                /* Whether the set as aborted. */
    int status;                 /* The exit status of the test. */
};

/* Header used for test output.  %s is replaced by the file name of the list
   of tests. */
static const char banner[] = "\n\
Running all tests listed in %s.  If any tests fail, run the failing\n\
test program by hand to see more details.\n\n";

/* Internal prototypes. */
static int test_batch(const char *testlist);
static enum test_status test_checkline(const char *line, struct testset *);
static int test_init(const char *line, struct testset *);
static pid_t test_start(const char *path, int *fd);
static double tv_diff(const struct timeval *, const struct timeval *);
static double tv_seconds(const struct timeval *);
static double tv_sum(const struct timeval *, const struct timeval *);
static void wstat_print(int status);


/* Given a struct timeval, return the number of seconds it represents as a
   double.  Use difftime() to convert a time_t to a double. */
static double
tv_seconds(const struct timeval *tv)
{
    return difftime(tv->tv_sec, 0) + tv->tv_usec * 1e-6;
}

/* Given two struct timevals, return the difference in seconds. */
static double
tv_diff(const struct timeval *tv1, const struct timeval *tv0)
{
    return tv_seconds(tv1) - tv_seconds(tv0);
}

/* Given two struct timevals, return the sum in seconds as a double. */
static double
tv_sum(const struct timeval *tv1, const struct timeval *tv2)
{
    return tv_seconds(tv1) + tv_seconds(tv2);
}


/* Given a return status from waitpid(), print to stdout a human-readable
   description of the exit status. */
static void
wstat_print(int status)
{
    if (WIFEXITED(status)) {
        switch (WEXITSTATUS(status)) {
        case CHILDERR_DUP:
            puts("dup of file descriptors failed");
            break;
        case CHILDERR_EXEC:
            puts("Execution of test script failed");
            break;
        case CHILDERR_STDERR:
            puts("Unable to open /dev/null");
            break;
        default:
            printf("Test exited with status %d\n", WEXITSTATUS(status));
            break;
        }
    } else if (WIFSIGNALED(status)) {
        printf("Test terminated with signal %d%s\n", WTERMSIG(status),
               WCOREDUMP(status) ? " (core dumped)" : "");
    }
}


/* Read the first line of test output, which should contain the range of
   test numbers, and initialize the testset structure.  Assume it was zeroed
   before being passed in.  Return true if initialization succeeds, false
   otherwise. */
static int
test_init(const char *line, struct testset *ts)
{
    int i;

    /* Prefer a simple number of tests, but if the count is given as a range
       such as 1..10, accept that too for compatibility with Perl's
       Test::Harness. */
    while (isspace((unsigned char)(*line))) line++;
    if (!strncmp(line, "1..", 3)) line += 3;

    /* Get the count, check it for validity, and initialize the struct. */
    i = atoi(line);
    if (i <= 0) {
        puts("invalid test count");
        ts->aborted = 1;
        return 0;
    }
    ts->count = i;
    ts->results = malloc(ts->count * sizeof(enum test_status));
    if (!ts->results) sysdie("can't allocate memory");
    for (i = 0; i < ts->count; i++) ts->results[i] = TEST_INVALID;
    return 1;
}


/* Start a program, connecting its stdout to a pipe on our end and its
   stderr to /dev/null, and storing the file descriptor to read from in the
   two argument.  Returns the PID of the new process.  Errors are fatal. */
static pid_t
test_start(const char *path, int *fd)
{
    int fds[2], errfd;
    pid_t child;

    if (pipe(fds) == -1) sysdie("can't create pipe");
    child = fork();
    if (child == (pid_t) -1) {
        sysdie("can't fork");
    } else if (child == 0) {
        /* In child.  Set up our stdout and stderr. */
        errfd = open("/dev/null", O_WRONLY);
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


/* Given a single line of output from a test, parse it and return the
   success status of that test.  Print an error followed by a newline to
   stdout and return TEST_INVALID in the case of some parsing error.  Sets
   current to the test number that just reported status. */
static enum test_status
test_checkline(const char *line, struct testset *ts)
{
    enum test_status status = TEST_INVALID;
    int failed, current;

    /* If the given line isn't newline-terminated, it was too big for an
       fgets(), which means invalid output. */
    if (line[strlen(line) - 1] != '\n') {
        puts("excessive output");
    } else if (sscanf(line, "not ok %d", &current) == 1) {
        status = TEST_FAIL;
    } else if (sscanf(line, "ok %d", &current) == 1) {
        status = strstr(line, "# skip") ? TEST_SKIP : TEST_PASS;
    } else {
        puts("invalid output");
    }

    if (status == TEST_INVALID) return status;

    if (current < 1 || current > ts->count) {
        printf("invalid test number %d\n", current);
        status = TEST_INVALID;
    }
    if (ts->results[current - 1] != TEST_INVALID) {
        printf("duplicate test number %d\n", current);
        status = TEST_INVALID;
    }
    ts->current = current;
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
    pid_t testpid, child;
    enum test_status result;
    int outfd, status, i;
    int missing = 0;
    int failed = 0;

    /* Initialize the test and our data structures. */
    testpid = test_start(ts->file, &outfd);
    output = fdopen(outfd, "r");
    if (!output) sysdie("fdopen failed");
    if (!fgets(buffer, sizeof(buffer), output)) {
        puts("read failure");
        ts->aborted = 1;
    }
    if (!ts->aborted && !test_init(buffer, ts)) {
        while (fgets(buffer, sizeof(buffer), output))
            ;
        ts->aborted = 1;
    }

    /* Read each line the test prints to stdout, checking it for ok or not
       ok and failing the test set if we see anything odd. */
    while (!ts->aborted && fgets(buffer, sizeof(buffer), output)) {
        result = test_checkline(buffer, ts);
        switch (result) {
            case TEST_PASS:     ts->passed++;   break;
            case TEST_FAIL:     ts->failed++;   break;
            case TEST_SKIP:     ts->skipped++;  break;
        }
        ts->results[ts->current - 1] = result;
    }
    if (ferror(output)) {
        puts("read error");
        ts->aborted = 1;
    }

    /* Close the output descriptor, retrieve the exit status, and print out
       the status if appropriate. */
    fclose(output);
    child = waitpid(testpid, &ts->status, 0);
    if (child == (pid_t) -1)
        sysdie("waitpid for %u failed", (unsigned int) testpid);
    if (!WIFEXITED(ts->status) || WEXITSTATUS(ts->status) != 0) {
        if (!ts->aborted) puts("dubious");
        fputs("  ", stdout);
        wstat_print(ts->status);
        return 0;
    }
    if (ts->aborted) return 0;

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
    putchar('\n');
    return (!missing && !failed);
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
    struct timeval start, end;
    struct rusage stats;
    int total = 0;
    int passed = 0;
    int failed = 0;
    int aborted = 0;

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

    /* Start the wall clock timer. */
    gettimeofday(&start, NULL);

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
        test_run(&ts);
        aborted += ts.aborted;
        total += ts.count;
        passed += ts.passed;
        failed += ts.failed;
    }

    /* Stop the timer and get our child resource statistics. */
    gettimeofday(&end, NULL);
    getrusage(RUSAGE_CHILDREN, &stats);

    /* Print out our final results. */
    putchar('\n');
    if (aborted) {
        printf("Aborted %d test sets, passed %d/%d tests.\n", aborted,
               passed, total);
    } else if (failed == 0) {
        puts("All tests successful.");
    } else {
        printf("Failed %d/%d tests, %.2f%% okay.\n", failed, total,
               (total - failed) * 100.0 / total);
    }
    printf("Files=%d,  Tests=%d", line, total);
    printf(",  %.2f seconds", tv_diff(&end, &start));
    printf(" (%.2f usr + %.2f sys = %.2f CPU)\n",
           tv_seconds(&stats.ru_utime), tv_seconds(&stats.ru_stime),
           tv_sum(&stats.ru_utime, &stats.ru_stime));
    return (failed != 0);
}


/* Main routine.  Given a file listing tests, run each test listed. */
int
main(int argc, char *argv[])
{
    if (argc != 2) die("Usage: runtests <test-list>\n");
    printf(banner, argv[1]);
    return test_batch(argv[1]);
}
