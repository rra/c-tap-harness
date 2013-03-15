#!/usr/bin/perl
#
# Test POD formatting for C TAP Harness documentation.
#
# This could be done more easily by using some of the test infrastructure from
# rra-c-util, but it creates weird circular code sharing, so duplicate some of
# it here instead.
#
# Copyright 2009, 2010, 2013 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

use 5.006;
use strict;
use warnings;

use File::Spec;
use Test::More;

# Abort if SOURCE isn't set.
if (!$ENV{SOURCE}) {
    BAIL_OUT('SOURCE environment variable not set');
}

# Load the Test::Pod module.
if (!eval { require Test::Pod }) {
    plan skip_all => 'Test::Pod required for testing POD';
}
Test::Pod->import;

# SOURCE will be the test directory.  Change to the parent.
my ($vol, $dirs) = File::Spec->splitpath($ENV{SOURCE}, 1);
my @dirs = File::Spec->splitdir($dirs);
pop(@dirs);
if ($dirs[-1] eq File::Spec->updir) {
    pop(@dirs);
    pop(@dirs);
}
my $root = File::Spec->catpath($vol, File::Spec->catdir(@dirs), q{});
chdir($root) or BAIL_OUT("cannot chdir to $root: $!");

# Test all the POD in the docs directory.
all_pod_files_ok(all_pod_files('docs'));
