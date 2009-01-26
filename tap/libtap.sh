# Shell function library for test cases.
#
# Written by Russ Allbery <rra@stanford.edu>
# Copyright 2006, 2007, 2008 Board of Trustees, Leland Stanford Jr. University
#
# See LICENSE for licensing terms.

# The count starts at 1 and is updated each time ok is printed.  printcount
# takes "ok" or "not ok".
count=1
printcount () {
    if [ -n "$2" ] ; then
        echo "$1 $count $2"
    else
        echo "$1 $count"
    fi
    count=`expr $count + 1`
}

# Run a program expected to succeed, and print ok if it does and produces
# the correct output.  Takes the output as the first argument, the command to
# run as the second argument, and then all subsequent arguments are arguments
# to the command.
runsuccess () {
    w_output="$1"
    shift
    output=`"$@" 2>&1`
    status=$?
    if [ $status = 0 ] && [ x"$output" = x"$w_output" ] ; then
        printcount 'ok'
    else
        printcount 'not ok'
        echo "#  saw: $output"
        echo "#  not: $w_output"
    fi
}

# Run a program expected to fail and make sure it fails with the correct exit
# status and the correct failure message.  Takes the expected status, the
# expected output, and then everything else is the command and arguments.
# Strip the second colon and everything after it off the error message since
# it's system-specific.
runfailure () {
    w_status="$1"
    shift
    w_output="$1"
    shift
    output=`"$@" 2>&1`
    status=$?
    output=`echo "$output" | sed 's/\(:[^:]*\):.*/\1/'`
    if [ $status = $w_status ] && [ x"$output" = x"$w_output" ] ; then
        printcount 'ok'
    else
        printcount 'not ok'
        echo "#  saw: ($status) $output"
        echo "#  not: ($w_status) $w_output"
    fi
}

# Skip tests from $1 to $2 inclusive with reason $3.
skip () {
    n="$1"
    while [ "$n" -le "$2" ] ; do
        echo ok "$n # skip $3"
        n=`expr "$n" + 1`
    done
}
