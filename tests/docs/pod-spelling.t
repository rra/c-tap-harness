#!/usr/bin/perl
#
# Test POD spelling for C TAP Harness documentation.
#
# Checks all POD files in the tree for spelling errors using Test::Spelling.
# This test is disabled unless RRA_MAINTAINER_TESTS is set, since spelling
# dictionaries vary too much between environments.
#
# This could be done more easily by using some of the test infrastructure from
# rra-c-util, but it creates weird circular code sharing, so duplicate some of
# it here instead.
#
# Copyright 2008, 2009, 2013 Russ Allbery <eagle@eyrie.org>
#
# See LICENSE for licensing terms.

use 5.006;
use strict;
use warnings;

use File::Spec;
use Test::More;

# Skip all spelling tests unless the maintainer environment variable is set.
if (!$ENV{RRA_MAINTAINER_TESTS}) {
    plan skip_all => 'Spelling tests only run for maintainer';
}

# Abort if SOURCE isn't set.
if (!$ENV{SOURCE}) {
    BAIL_OUT('SOURCE environment variable not set');
}

# Load the Test::Spelling module.
if (!eval { require Test::Spelling }) {
    plan skip_all => 'Test::Spelling required for testing spelling';
}
Test::Spelling->import;

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

# Check spelling of everything in docs.
all_pod_files_spelling_ok('docs');
