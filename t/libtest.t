#! /bin/sh
#
# Test suite for libtest functionality.
#
# Written by Russ Allbery <rra@stanford.edu>
# Copyright 2008 Board of Trustees, Leland Stanford Jr. University
#
# See LICENSE for licensing terms.

# The count starts at 1 and is updated each time ok is printed.  printcount
# takes "ok" or "not ok".
count=1
printcount () {
    echo "$1 $count"
    count=`expr $count + 1`
}

# Run a binary, saving its output, and then compare that output to the
# corresponding *.out file.
runsuccess () {
    ./"$1" > "$1".result
    diff -u "$1".out "$1".result 2>&1
    if test $? = 0 ; then
        printcount "ok"
        rm "$1".result
    else
        printcount "not ok"
    fi
}

# Find where our test cases are.
for dir in ./t/libtest . ./libtest ; do
    [ -f $dir/c-basic.out ] && cd $dir
done

# Total tests.
echo 1..1

# First run the tests expected to succeed.
runsuccess c-basic
