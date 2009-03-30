#! /bin/sh
#
# Test suite for runtests directory search support.
#
# Copyright 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

. "$SOURCE/../tap/libtap.sh"
cd "$BUILD"

# Total tests.
plan 2

# Run runtests, overriding the build and source directories.
"../runtests" -s "${SOURCE}/single" -o test > test.result
status=$?
ok 'test result status' [ $status -eq 4 ]
diff -u "${SOURCE}/single/test.output" test.result 2>&1
status=$?
ok 'test output' [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm test.result
fi
