#! /bin/sh
#
# Test suite for runtests directory search support.
#
# Copyright 2009, 2012 Russ Allbery <eagle@eyrie.org>
#
# See LICENSE for licensing terms.

. "$SOURCE/tap/libtap.sh"
cd "$BUILD"

# Total tests.
plan 2

# Run runtests, overriding the build and source directories.
"${BUILD}/runtests" -s "${SOURCE}/harness/single" -o test > test.result
status=$?
ok 'test result status' [ $status -eq 4 ]
diff -u "${SOURCE}/harness/single/test.output" test.result 2>&1
status=$?
ok 'test output' [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm test.result
fi
