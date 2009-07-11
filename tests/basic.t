#! /bin/sh
#
# Test suite for basic runtests functionality.
#
# Copyright 2008, 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

. "$SOURCE/../tap/libtap.sh"
cd "$BUILD"

# Run runtests on a list and compare the output to the expected output,
# printing ok if it matches.  Strip out the time information from the runtests
# result since it changes for each run.
ok_runtests () {
    "$BUILD"/../runtests -s "${SOURCE}/basic" -b "${BUILD}/basic" \
        "${SOURCE}/basic/$1".list | sed 's/\(Tests=[0-9]*\),  .*/\1/' \
        > "$1".result
    diff -u "${SOURCE}/basic/$1".output "$1".result 2>&1
    status=$?
    ok "$1 test set" [ $status -eq 0 ]
    if [ $status -eq 0 ] ; then
        rm "$1".result
    fi
    rm -f core
}

# Total tests.
plan 5

# Run the tests.
ok_runtests pass
ok_runtests skip
ok_runtests fail
ok_runtests abort
ok_runtests abort-one
