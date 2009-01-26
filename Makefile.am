# Automake makefile for C TAP Harness.
#
# Copyright 2008 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

# The list of files needed by the test suite.  They're listed here to be added
# to EXTRA_DIST and so that they can be copied over properly for builddir !=
# srcdir builds.
TEST_FILES = tests/basic.t tests/basic/abort.list tests/basic/abort.out \
	tests/basic/abort.t tests/basic/badnum.t tests/basic/duplicate.t \
	tests/basic/fail.list tests/basic/fail.out tests/basic/fail.t \
	tests/basic/hup.t tests/basic/missing.t tests/basic/nocount.t \
	tests/basic/order.t tests/basic/pass.list tests/basic/pass.out \
	tests/basic/pass.t tests/basic/segv.t tests/basic/skip.list \
	tests/basic/skip.out tests/basic/skip.t tests/basic/status.t \
	tests/libtap.t

AUTOMAKE_OPTIONS = foreign subdir-objects
EXTRA_DIST = LICENSE autogen runtests.pod

bin_PROGRAMS = runtests
noinst_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
man_MANS = runtests.1

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
check_PROGRAMS = tests/libtap/c-basic
tests_libtap_c_basic_LDADD = tap/libtap.a

check-local: $(check_PROGRAMS)
	set -e; if [ x"$(builddir)" != x"$(srcdir)" ] ; then \
	    for f in $(TEST_FILES) ; do \
		cp "$(srcdir)/$$f" "$(builddir)/$$f" ; \
	    done \
	fi
	cd tests && ../runtests TESTS
