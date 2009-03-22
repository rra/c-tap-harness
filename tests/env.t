#! /bin/sh
#
# Test suite for runtests directory search support.
#
# Copyright 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

. "$SOURCE/../tap/libtap.sh"

# Total tests.
plan 1

# Be sure that we run from the source directory.
cd "$SOURCE/env"

# Run runtests, overriding the build and source directories.
"$BUILD/../runtests" env.list | sed 's/\(Tests=[0-9]*\),  .*/\1/' > env.result
diff -u env.out env.result 2>&1
status=$?
ok [ $status -eq 0 ]
if [ $status -eq 0 ] ; then
    rm env.result
fi
