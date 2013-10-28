#!/bin/sh
#
# Test suite for running multiple tests listed on the command line.
#
# Copyright 2013 Russ Allbery <eagle@eyrie.org>
#
# See LICENSE for licensing terms.

. "$SOURCE/tap/libtap.sh"
cd "$BUILD"

# Total tests.
plan 4

# Run runtests, overriding the build and source directories, and passing a
# few tests from the basic directory to run.
"${BUILD}/runtests" -s "${SOURCE}/harness/basic" pass fail skip todo \
    > multiple.raw
status=$?
ok 'test result status' [ $status -eq 1 ]
sed 's/\(Tests=[0-9]*\),  .*/\1/' multiple.raw > multiple.result
rm multiple.raw
diff -u "${SOURCE}/harness/multiple/output" multiple.result 2>&1
status=$?
ok 'test output' [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm multiple.result
fi

# Verify that running runtests without any tests fails and prints a usage
# message.
output=`"${BUILD}/runtests" 2>&1`
status=$?
ok 'runtests with no arguments fails' [ $status -eq 1 ]
echo "$output" | grep Usage: >/dev/null 2>&1
status=$?
ok '...and produces usage message' [ $status -eq 0 ]
