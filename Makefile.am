# Automake makefile for C TAP Harness.
#
# Copyright 2008, 2009 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

AUTOMAKE_OPTIONS = foreign subdir-objects
EXTRA_DIST = LICENSE autogen runtests.pod tap/libtap.sh tests/TESTS	     \
	tests/basic/abort-one.list tests/basic/abort-one.output		     \
	tests/basic/abort.list tests/basic/abort.output tests/basic/abort.t  \
	tests/basic/badnum.t tests/basic/bail-silent.t tests/basic/bail.t    \
	tests/basic/duplicate.t tests/basic/fail-count.t		     \
	tests/basic/fail.list tests/basic/fail.output tests/basic/fail.t     \
	tests/basic/hup.t tests/basic/missing.t tests/basic/nocount.t	     \
	tests/basic/order.t tests/basic/pass.list tests/basic/pass.output    \
	tests/basic/pass.t tests/basic/segv.t tests/basic/skip-all-quiet.t   \
	tests/basic/skip-all.t tests/basic/skip.list tests/basic/skip.output \
	tests/basic/skip.t tests/basic/status.t tests/basic/todo.t	     \
	tests/basic/too-many.t tests/basic/zero.t tests/basic.t		     \
	tests/env/env.list tests/env/env.output tests/env.t		     \
	tests/libtap/c-bail.output tests/libtap/c-basic.output		     \
	tests/libtap/c-extra-one.output tests/libtap/c-extra.output	     \
	tests/libtap/c-missing-one.output tests/libtap/c-missing.output	     \
	tests/libtap/c-skip.output tests/libtap/c-skip-reason.output	     \
	tests/libtap/c-success-one.output tests/libtap/c-success.output	     \
	tests/libtap/sh-bail tests/libtap/sh-bail.output		     \
	tests/libtap/sh-basic tests/libtap/sh-basic.output		     \
	tests/libtap/sh-extra tests/libtap/sh-extra-one			     \
	tests/libtap/sh-extra-one.output tests/libtap/sh-extra.output	     \
	tests/libtap/sh-missing tests/libtap/sh-missing-one		     \
	tests/libtap/sh-missing-one.output tests/libtap/sh-missing.output    \
	tests/libtap/sh-success tests/libtap/sh-success-one		     \
	tests/libtap/sh-success-one.output tests/libtap/sh-success.output    \
	tests/libtap/sh-skip tests/libtap/sh-skip.output tests/libtap.t	     \
	tests/pod.t tests/pod-spelling.t tests/search/build/build-t	     \
	tests/search/relative.t tests/search/search.list		     \
	tests/search/search.output tests/search/source/source.t		     \
	tests/single/test.output tests/single/test.t tests/single.t

bin_PROGRAMS = runtests
runtests_CPPFLAGS = -DSOURCE='"$(abs_top_srcdir)/tests"' \
	-DBUILD='"$(abs_top_builddir)/tests"'
noinst_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
dist_man_MANS = runtests.1

# Work around the GNU Coding Standards, which leave all the Autoconf and
# Automake stuff around after make maintainer-clean, thus making that command
# mostly worthless.
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 build-aux/depcomp		\
	build-aux/install-sh build-aux/missing configure runtests.1

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
check_PROGRAMS = tests/libtap/c-basic tests/libtap/c-bail		     \
	tests/libtap/c-extra tests/libtap/c-extra-one tests/libtap/c-missing \
	tests/libtap/c-missing-one tests/libtap/c-skip			     \
	tests/libtap/c-skip-reason tests/libtap/c-success		     \
	tests/libtap/c-success-one tests/libtap/c-sysbail
tests_libtap_c_basic_LDADD = tap/libtap.a
tests_libtap_c_bail_LDADD = tap/libtap.a
tests_libtap_c_extra_LDADD = tap/libtap.a
tests_libtap_c_extra_one_LDADD = tap/libtap.a
tests_libtap_c_missing_LDADD = tap/libtap.a
tests_libtap_c_missing_one_LDADD = tap/libtap.a
tests_libtap_c_skip_LDADD = tap/libtap.a
tests_libtap_c_skip_reason_LDADD = tap/libtap.a
tests_libtap_c_success_LDADD = tap/libtap.a
tests_libtap_c_success_one_LDADD = tap/libtap.a
tests_libtap_c_sysbail_LDADD = tap/libtap.a

check-local: $(check_PROGRAMS)
	cd tests && ../runtests $(abs_top_srcdir)/tests/TESTS
