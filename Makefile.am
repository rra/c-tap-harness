# Automake makefile for runtests.
#
# Copyright 2008 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

# The list of files needed by the test suite.  They're listed here to be added
# to EXTRA_DIST and so that they can be copied over properly for builddir !=
# srcdir builds.
TEST_FILES = t/runtests.t t/runtests/abort.list t/runtests/abort.out \
	t/runtests/abort.t t/runtests/badnum.t t/runtests/duplicate.t \
	t/runtests/fail.list t/runtests/fail.out t/runtests/fail.t \
	t/runtests/hup.t t/runtests/missing.t t/runtests/nocount.t \
	t/runtests/order.t t/runtests/pass.list t/runtests/pass.out \
	t/runtests/pass.t t/runtests/segv.t t/runtests/skip.list \
	t/runtests/skip.out t/runtests/skip.t t/runtests/status.t

AUTOMAKE_OPTIONS = foreign subdir-objects
EXTRA_DIST = LICENSE autogen

bin_PROGRAMS = runtests

# Work around the GNU Coding Standards, which leave all the Autoconf and
# Automake stuff around after make maintainer-clean, thus making that command
# mostly worthless.
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 build-aux/depcomp \
	build-aux/install-sh build-aux/missing configure

# A set of flags for warnings.  Add -O because gcc won't find some warnings
# without optimization turned on, and add -DDEBUG=1 so we'll also compile all
# debugging code and test it.
WARNINGS = -g -O -DDEBUG=1 -Wall -W -Wendif-labels -Wpointer-arith \
	-Wbad-function-cast -Wwrite-strings -Wstrict-prototypes \
	-Wmissing-prototypes -Wnested-externs -Werror

warnings:
	$(MAKE) CFLAGS='$(WARNINGS)'

# The bits below are for the test suite.
check-local:
	set -e; if [ x"$(builddir)" != x"$(srcdir)" ] ; then \
	    for f in $(TEST_FILES) ; do \
		cp "$(srcdir)/$$f" "$(builddir)/$$f" ; \
	    done \
	fi
	cd t && ../runtests TESTS
