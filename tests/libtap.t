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
    "$2"/libtap/"$1" > "$1".result 2>&1
    status=$?
    ok "$1 exit status" [ $status -eq "$3" ]
    if [ "$1" = "c-sysbail" ] ; then
        diff -u "${BUILD}/libtap/$1".output "$1".result 2>&1
    else
        diff -u "${SOURCE}/libtap/$1".output "$1".result 2>&1
    fi
    status=$?
    ok "$1 output" [ $status -eq 0 ]
    if [ $status -eq 0 ] ; then
        rm "$1".result
    fi
}

# Total tests.
plan 16

# Run the individual tests.
ok_result c-basic       "$BUILD"  0
ok_result c-bail        "$BUILD"  1
ok_result c-skip        "$BUILD"  0
ok_result c-skip-reason "$BUILD"  0
ok_result c-sysbail     "$BUILD"  1
ok_result sh-basic      "$SOURCE" 0
ok_result sh-bail       "$SOURCE" 1
ok_result sh-skip       "$SOURCE" 0

# Remove the output file created by c-sysbail.
rm -f c-sysbail.output
