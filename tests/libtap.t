#! /bin/sh
#
# Test suite for libtap functionality.
#
# Written by Russ Allbery <rra@stanford.edu>
# Copyright 2009 Russ Allbery <rra@stanford.edu>
# Copyright 2008 Board of Trustees, Leland Stanford Jr. University
#
# See LICENSE for licensing terms.

. "$SOURCE/../tap/libtap.sh"
cd "${BUILD}/libtap"

# Run a binary, saving its output, and then compare that output to the
# corresponding *.out file.
ok_result () {
    "$2"/libtap/"$1" > "$1".result
    diff -u "${SOURCE}/libtap/$1".output "$1".result 2>&1
    status=$?
    ok [ $status -eq 0 ]
    if [ $status -eq 0 ] ; then
        rm "$1".result
    fi
}

# Total tests.
plan 2

# Run the individual tests.
ok_result c-basic "$BUILD"
ok_result sh-basic "$SOURCE"
