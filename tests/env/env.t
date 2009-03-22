#!/bin/sh
. "$SOURCE/../tap/libtap.sh"
real_source="/home/eagle/dvl/c-tap-harness/tests"
real_build="/home/eagle/dvl/c-tap-harness/tests"
plan 2
ok [ "$SOURCE" = "$real_source" ]
ok [ "$BUILD" = "$real_build" ]
