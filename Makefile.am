# Automake makefile for C TAP Harness.
#
# Copyright 2008, 2009, 2010, 2011 Russ Allbery <rra@stanford.edu>
#
# See LICENSE for licensing terms.

EXTRA_DIST = .gitignore LICENSE autogen docs/api/bail.pod		   \
	docs/api/bmalloc.pod docs/api/diag.pod docs/api/is_int.pod	   \
	docs/api/ok.pod docs/api/plan.pod docs/api/skip.pod		   \
	docs/api/skip_all.pod docs/api/test_file_path.pod		   \
	docs/api/test_tmpdir.pod docs/runtests.pod docs/writing-tests	   \
	tap/libtap.sh tests/TESTS tests/basic/abort-one.list		   \
	tests/basic/abort-one.output tests/basic/abort.list		   \
	tests/basic/abort.output tests/basic/abort.t			   \
	tests/basic/badnum-delay.t tests/basic/badnum.t			   \
	tests/basic/bail-silent.t tests/basic/bail.t			   \
	tests/basic/duplicate.t tests/basic/fail-count.t		   \
	tests/basic/fail.list tests/basic/fail.output tests/basic/fail.t   \
	tests/basic/hup.t tests/basic/missing.t tests/basic/nocount.t	   \
	tests/basic/order.t tests/basic/pass.list tests/basic/pass.output  \
	tests/basic/pass.t tests/basic/plan-last.t tests/basic/plan-long.t \
	tests/basic/plan-middle.t tests/basic/plan-order.t		   \
	tests/basic/plan-twice.t tests/basic/segv.t			   \
	tests/basic/skip-all-case.t tests/basic/skip-all-late.t		   \
	tests/basic/skip-all-quiet.t tests/basic/skip-all.t		   \
	tests/basic/skip.list tests/basic/skip.output tests/basic/skip.t   \
	tests/basic/status.t tests/basic/todo.t tests/basic/too-many.t	   \
	tests/basic/zero.t tests/basic.t tests/env/env.list		   \
	tests/env/env.output tests/env.t tests/libtap/c-bail.output	   \
	tests/libtap/c-basic.output tests/libtap/c-extra-one.output	   \
	tests/libtap/c-extra.output tests/libtap/c-lazy.output		   \
	tests/libtap/c-missing-one.output tests/libtap/c-missing.output	   \
	tests/libtap/c-skip.output tests/libtap/c-skip-reason.output	   \
	tests/libtap/c-success-one.output tests/libtap/c-success.output	   \
	tests/libtap/sh-bail tests/libtap/sh-bail.output		   \
	tests/libtap/sh-basic tests/libtap/sh-basic.output		   \
	tests/libtap/sh-diag tests/libtap/sh-diag.output		   \
	tests/libtap/sh-extra tests/libtap/sh-extra-one			   \
	tests/libtap/sh-extra-one.output tests/libtap/sh-extra.output	   \
	tests/libtap/sh-file tests/libtap/sh-lazy			   \
	tests/libtap/sh-lazy.output tests/libtap/sh-missing		   \
	tests/libtap/sh-missing-one tests/libtap/sh-missing-one.output	   \
	tests/libtap/sh-missing.output tests/libtap/sh-strip-colon	   \
	tests/libtap/sh-strip-colon.output tests/libtap/sh-success	   \
	tests/libtap/sh-success-one tests/libtap/sh-success-one.output	   \
	tests/libtap/sh-success.output tests/libtap/sh-skip		   \
	tests/libtap/sh-skip.output tests/libtap/sh-tmpdir tests/libtap.t  \
	tests/pod.t tests/pod-spelling.t tests/search/build/build-t	   \
	tests/search/relative.t tests/search/search.list		   \
	tests/search/search.output tests/search/source/source.t		   \
	tests/single/test.output tests/single/test.t tests/single.t

bin_PROGRAMS = runtests
noinst_LIBRARIES = tap/libtap.a
tap_libtap_a_SOURCES = tap/basic.c tap/basic.h
dist_man_MANS = docs/api/bail.3 docs/api/bmalloc.3 docs/api/diag.3	\
	docs/api/is_int.3 docs/api/ok.3 docs/api/plan.3 docs/api/skip.3	\
	docs/api/skip_all.3 docs/api/test_tmpdir.3 docs/runtests.1

# Add symlinks for the man pages that document multiple functions.
install-data-hook:
	rm -f $(DESTDIR)$(man3dir)/sysbail.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) bail.3 sysbail.3
	rm -f $(DESTDIR)$(man3dir)/bcalloc.3
	rm -f $(DESTDIR)$(man3dir)/brealloc.3
	rm -f $(DESTDIR)$(man3dir)/bstrdup.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) bmalloc.3 bcalloc.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) bmalloc.3 brealloc.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) bmalloc.3 bstrdup.3
	rm -f $(DESTDIR)$(man3dir)/sysdiag.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) diag.3 sysdiag.3
	rm -f $(DESTDIR)$(man3dir)/is_double.3
	rm -f $(DESTDIR)$(man3dir)/is_string.3
	rm -f $(DESTDIR)$(man3dir)/is_hex.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) is_int.3 is_double.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) is_int.3 is_string.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) is_int.3 is_hex.3
	rm -f $(DESTDIR)$(man3dir)/ok_block.3
	rm -f $(DESTDIR)$(man3dir)/okv.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) ok.3 ok_block.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) ok.3 okv.3
	rm -f $(DESTDIR)$(man3dir)/plan_lazy.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) plan.3 plan_lazy.3
	rm -f $(DESTDIR)$(man3dir)/skip_block.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) skip.3 skip_block.3
	rm -f $(DESTDIR)$(man3dir)/test_tmpdir_free.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) test_tmpdir.3 test_tmpdir_free.3

uninstall-hook:
	rm -f $(DESTDIR)$(man3dir)/sysbail.3
	rm -f $(DESTDIR)$(man3dir)/bcalloc.3
	rm -f $(DESTDIR)$(man3dir)/brealloc.3
	rm -f $(DESTDIR)$(man3dir)/bstrdup.3
	rm -f $(DESTDIR)$(man3dir)/sysdiag.3
	rm -f $(DESTDIR)$(man3dir)/is_double.3
	rm -f $(DESTDIR)$(man3dir)/is_string.3
	rm -f $(DESTDIR)$(man3dir)/is_hex.3
	rm -f $(DESTDIR)$(man3dir)/ok_block.3
	rm -f $(DESTDIR)$(man3dir)/okv.3
	rm -f $(DESTDIR)$(man3dir)/plan_lazy.3
	rm -f $(DESTDIR)$(man3dir)/skip_block.3
	rm -f $(DESTDIR)$(man3dir)/test_tmpdir_free.3

# Work around the GNU Coding Standards, which leave all the Autoconf and
# Automake stuff around after make maintainer-clean, thus making that command
# mostly worthless.
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 build-aux/depcomp		   \
	build-aux/install-sh build-aux/missing configure docs/api/bail.3   \
	docs/api/bmalloc.3 docs/api/diag.3 docs/api/is_int.3 docs/api/ok.3 \
	docs/api/plan.3 docs/api/skip.3 docs/api/skip_all.3		   \
	docs/api/test_tmpdir.3 docs/runtests.1

# A set of flags for warnings.  Add -O because gcc won't find some warnings
# without optimization turned on.  Desirable warnings that can't be turned
# on due to other problems:
#
#     -Wconversion     http://bugs.debian.org/488884 (htons warnings)
#
# Last checked against gcc 4.6.1 (2011-05-04)
WARNINGS = -ansi -pedantic -g -O -Wall -Wextra -Wendif-labels -Wformat=2  \
	-Winit-self -Wswitch-enum -Wdeclaration-after-statement -Wshadow \
	-Wpointer-arith -Wbad-function-cast -Wwrite-strings		  \
	-Wjump-misses-init -Wlogical-op -Wstrict-prototypes		  \
	-Wmissing-prototypes -Wredundant-decls -Wnested-externs -Werror

warnings:
	$(MAKE) V=0 CFLAGS='$(WARNINGS)'
	$(MAKE) V=0 CFLAGS='$(WARNINGS)' $(check_PROGRAMS)

# The bits below are for the test suite.
check_PROGRAMS = tests/libtap/c-bail tests/libtap/c-basic		    \
	tests/libtap/c-diag tests/libtap/c-file tests/libtap/c-extra	    \
	tests/libtap/c-extra-one tests/libtap/c-lazy tests/libtap/c-missing \
	tests/libtap/c-missing-one tests/libtap/c-skip			    \
	tests/libtap/c-skip-reason tests/libtap/c-success		    \
	tests/libtap/c-success-one tests/libtap/c-sysbail		    \
	tests/libtap/c-tmpdir
tests_libtap_c_bail_LDADD = tap/libtap.a
tests_libtap_c_basic_LDADD = tap/libtap.a -lm
tests_libtap_c_diag_LDADD = tap/libtap.a
tests_libtap_c_extra_LDADD = tap/libtap.a
tests_libtap_c_extra_one_LDADD = tap/libtap.a
tests_libtap_c_file_LDADD = tap/libtap.a
tests_libtap_c_lazy_LDADD = tap/libtap.a
tests_libtap_c_missing_LDADD = tap/libtap.a
tests_libtap_c_missing_one_LDADD = tap/libtap.a
tests_libtap_c_skip_LDADD = tap/libtap.a
tests_libtap_c_skip_reason_LDADD = tap/libtap.a
tests_libtap_c_success_LDADD = tap/libtap.a
tests_libtap_c_success_one_LDADD = tap/libtap.a
tests_libtap_c_sysbail_LDADD = tap/libtap.a
tests_libtap_c_tmpdir_LDADD = tap/libtap.a

check-local: $(check_PROGRAMS)
	cd tests && ../runtests -s '$(abs_top_srcdir)/tests' \
	    -b '$(abs_top_builddir)/tests' $(abs_top_srcdir)/tests/TESTS
