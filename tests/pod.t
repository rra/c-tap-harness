#!/usr/bin/perl
#
# Test POD formatting for C TAP Harness documentation.
#
# Copyright 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

use strict;
use Test::More;
eval 'use Test::Pod 1.00';
plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;
plan tests => 1;
pod_file_ok ("$ENV{SOURCE}/../runtests.pod", 'runtests');
