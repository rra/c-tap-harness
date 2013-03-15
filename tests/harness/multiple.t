#!/bin/sh
#
# Test suite for running multiple tests listed on the command line.
#
# Copyright 2013 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

. "$SOURCE/tap/libtap.sh"
cd "$BUILD"

# Total tests.
plan 2

# Run runtests, overriding the build and source directories, and passing a
# few tests from the basic directory to run.
"${BUILD}/runtests" -s "${SOURCE}/harness/basic" pass fail skip todo \
    > multiple.result
status=$?
ok 'test result status' [ $status -eq 1 ]
diff -u "${SOURCE}/harness/multiple/output" multiple.result 2>&1
status=$?
ok 'test output' [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm multiple.result
fi
