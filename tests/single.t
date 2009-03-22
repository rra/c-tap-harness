#! /bin/sh
#
# Test suite for runtests directory search support.
#
# Copyright 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

. "$SOURCE/../tap/libtap.sh"

# Total tests.
plan 2

# Be sure that we run from the source directory.
cd "$SOURCE/single"

# Run runtests, overriding the build and source directories.
"$BUILD/../runtests" -o test > test.result
status=$?
ok [ $status -eq 4 ]
diff -u test.out test.result 2>&1
status=$?
ok [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm test.result
fi
