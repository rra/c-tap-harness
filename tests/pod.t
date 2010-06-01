#!/usr/bin/perl -w
#
# Test POD formatting for C TAP Harness documentation.
#
# Copyright 2009, 2010 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

use strict;
use Test::More;
eval 'use Test::Pod 1.00';
plan skip_all => "Test::Pod 1.00 required for testing POD" if $@;
my $srcdir = "$ENV{SOURCE}";
$srcdir =~ s,[^/]+/*$,,;
chdir "$srcdir" or die "$0: cannot chdir to $srcdir: $!\n";
my @poddirs = qw(docs);
all_pod_files_ok (all_pod_files (@poddirs));
