# Automake makefile for C TAP Harness.
#
# Copyright 2008 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

# The list of files needed by the test suite.  They're listed here to be added
# to EXTRA_DIST and so that they can be copied over properly for builddir !=
# srcdir builds.
TEST_FILES = t/basic.t t/basic/abort.list t/basic/abort.out \
	t/basic/abort.t t/basic/badnum.t t/basic/duplicate.t \
	t/basic/fail.list t/basic/fail.out t/basic/fail.t t/basic/hup.t \
	t/basic/missing.t t/basic/nocount.t t/basic/order.t \
	t/basic/pass.list t/basic/pass.out t/basic/pass.t t/basic/segv.t \
	t/basic/skip.list t/basic/skip.out t/basic/skip.t t/basic/status.t \
	t/libtest.t

AUTOMAKE_OPTIONS = foreign subdir-objects
EXTRA_DIST = LICENSE autogen

bin_PROGRAMS = runtests
noinst_LIBRARIES = libtest.a
libtest_a_SOURCES = libtest.c libtest.h

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
	$(MAKE) CFLAGS='$(WARNINGS)' $(check_PROGRAMS)

# The bits below are for the test suite.
check_PROGRAMS = t/libtest/c-basic
t_libtest_c_basic_LDADD = libtest.a

check-local: $(check_PROGRAMS)
	set -e; if [ x"$(builddir)" != x"$(srcdir)" ] ; then \
	    for f in $(TEST_FILES) ; do \
		cp "$(srcdir)/$$f" "$(builddir)/$$f" ; \
	    done \
	fi
	cd t && ../runtests TESTS
