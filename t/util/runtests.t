#! /bin/sh
# $Id$
#
# Test suite for runtests.

# The count starts at 1 and is updated each time ok is printed.  printcount
# takes "ok" or "not ok".
count=1
printcount () {
    echo "$1 $count"
    count=`expr $count + 1`
}

# Run runtests on a list and compare the output to the expected output,
# printing ok if it matches.
runsuccess () {
    ../../runtests "$1".list | sed 's/\(Tests=[0-9]*\),  .*/\1/' > "$1".result
    cmp "$1".out "$1".result > /dev/null 2>&1
    if test $? = 0 ; then
        printcount "ok"
        rm "$1".result
    else
        printcount "not ok"
    fi
    rm -f core
}

# Find where our test cases are.
for dir in ./t/util/runtests . ./runtests ./util/runtests ; do
    [ -f $dir/pass.list ] && cd $dir
done

# Total tests.
echo 4

# First run the tests expected to succeed.
runsuccess pass
runsuccess skip
runsuccess fail
runsuccess abort
