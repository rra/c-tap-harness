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
# corresponding *.output file.
ok_result () {
    "$2"/libtap/"$1" > "$1".result 2>&1
    status=$?
    ok "$1 exit status" [ $status -eq "$3" ]
    if [ "$1" = "c-diag" ] || [ "$1" = "c-sysbail" ] ; then
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
plan 48

# Run the individual tests.
ok_result c-bail         "$BUILD"  1
ok_result c-basic        "$BUILD"  0
ok_result c-diag         "$BUILD"  0
ok_result c-extra        "$BUILD"  0
ok_result c-extra-one    "$BUILD"  0
ok_result c-lazy         "$BUILD"  0
ok_result c-missing      "$BUILD"  0
ok_result c-missing-one  "$BUILD"  0
ok_result c-skip         "$BUILD"  0
ok_result c-skip-reason  "$BUILD"  0
ok_result c-success      "$BUILD"  0
ok_result c-success-one  "$BUILD"  0
ok_result c-sysbail      "$BUILD"  1
ok_result sh-bail        "$SOURCE" 1
ok_result sh-basic       "$SOURCE" 0
ok_result sh-diag        "$SOURCE" 0
ok_result sh-extra       "$SOURCE" 0
ok_result sh-extra-one   "$SOURCE" 0
ok_result sh-lazy        "$SOURCE" 0
ok_result sh-missing     "$SOURCE" 0
ok_result sh-missing-one "$SOURCE" 0
ok_result sh-skip        "$SOURCE" 0
ok_result sh-success     "$SOURCE" 0
ok_result sh-success-one "$SOURCE" 0

# Remove the output files created by c-diag and c-sysbail.
rm -f c-diag.output c-sysbail.output
