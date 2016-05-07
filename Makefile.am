# Automake makefile for C TAP Harness.
#
# Copyright 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
#     Russ Allbery <eagle@eyrie.org>
#
# See LICENSE for licensing terms.

ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = .gitignore LICENSE bootstrap docs/api/bail.pod		    \
	docs/api/bmalloc.pod docs/api/breallocarray.pod docs/api/diag.pod   \
	docs/api/diag_file_add.pod docs/api/is_int.pod docs/api/ok.pod	    \
	docs/api/plan.pod docs/api/skip.pod docs/api/skip_all.pod	    \
	docs/api/test_cleanup_register.pod docs/api/test_file_path.pod	    \
	docs/api/test_tmpdir.pod docs/runtests.pod docs/writing-tests	    \
	tests/TESTS tests/docs/pod-t tests/docs/pod-spelling-t		    \
	tests/harness/basic-t tests/harness/basic/abort-one.list	    \
	tests/harness/basic/abort-one.output tests/harness/basic/abort.list \
	tests/harness/basic/abort.output tests/harness/basic/abort.t	    \
	tests/harness/basic/badnum-delay.t tests/harness/basic/badnum.t	    \
	tests/harness/basic/bail-silent.t tests/harness/basic/bail.t	    \
	tests/harness/basic/duplicate.t tests/harness/basic/empty.list	    \
	tests/harness/basic/empty.output tests/harness/basic/fail-count.t   \
	tests/harness/basic/fail.list tests/harness/basic/fail.output	    \
	tests/harness/basic/fail.t tests/harness/basic/hup.t		    \
	tests/harness/basic/missing.t tests/harness/basic/nocount.t	    \
	tests/harness/basic/order.t tests/harness/basic/pass.list	    \
	tests/harness/basic/pass.output tests/harness/basic/pass.t	    \
	tests/harness/basic/plan-last.t tests/harness/basic/plan-long.t	    \
	tests/harness/basic/plan-middle.t tests/harness/basic/plan-order.t  \
	tests/harness/basic/plan-twice.t tests/harness/basic/segv.t	    \
	tests/harness/basic/skip-all-case.t				    \
	tests/harness/basic/skip-all-late.t				    \
	tests/harness/basic/skip-all-quiet.t tests/harness/basic/skip-all.t \
	tests/harness/basic/skip.list tests/harness/basic/skip.output	    \
	tests/harness/basic/skip.t tests/harness/basic/status.t		    \
	tests/harness/basic/todo.t tests/harness/basic/too-many.t	    \
	tests/harness/basic/zero.t tests/harness/env-t			    \
	tests/harness/env/env.list tests/harness/env/env.output		    \
	tests/libtap/basic/c-bail.output tests/harness/multiple-t	    \
	tests/harness/multiple/output					    \
	tests/harness/search/build/build-no-ext.tap			    \
	tests/harness/search/build/build-t				    \
	tests/harness/search/relative-no-ext				    \
	tests/harness/search/relative.t tests/harness/search/search.list    \
	tests/harness/search/search.output				    \
	tests/harness/search/source/source-no-ext			    \
	tests/harness/search/source/source.t tests/harness/single-t	    \
	tests/harness/single/test.output tests/harness/single/test.t	    \
	tests/harness/verbose/list.output				    \
	tests/harness/verbose/multiple.output tests/harness/verbose-t	    \
	tests/libtap/basic-t tests/libtap/basic/c-basic.output		    \
	tests/libtap/basic/c-bstrndup.output				    \
	tests/libtap/basic/c-diag-file.output				    \
	tests/libtap/basic/c-extra-one.output				    \
	tests/libtap/basic/c-extra.output tests/libtap/basic/c-lazy.output  \
	tests/libtap/basic/c-missing-one.output				    \
	tests/libtap/basic/c-missing.output				    \
	tests/libtap/basic/c-skip.output				    \
	tests/libtap/basic/c-skip-reason.output				    \
	tests/libtap/basic/c-success-one.output				    \
	tests/libtap/basic/c-success.output tests/libtap/basic/sh-bail	    \
	tests/libtap/basic/sh-bail.output tests/libtap/basic/sh-basic	    \
	tests/libtap/basic/sh-basic.output tests/libtap/basic/sh-diag	    \
	tests/libtap/basic/sh-diag.output tests/libtap/basic/sh-extra	    \
	tests/libtap/basic/sh-extra-one					    \
	tests/libtap/basic/sh-extra-one.output				    \
	tests/libtap/basic/sh-extra.output tests/libtap/basic/sh-file	    \
	tests/libtap/basic/sh-lazy tests/libtap/basic/sh-lazy.output	    \
	tests/libtap/basic/sh-missing tests/libtap/basic/sh-missing-one	    \
	tests/libtap/basic/sh-missing-one.output			    \
	tests/libtap/basic/sh-missing.output				    \
	tests/libtap/basic/sh-strip-colon				    \
	tests/libtap/basic/sh-strip-colon.output			    \
	tests/libtap/basic/sh-success tests/libtap/basic/sh-success-one	    \
	tests/libtap/basic/sh-success-one.output			    \
	tests/libtap/basic/sh-success.output tests/libtap/basic/sh-skip	    \
	tests/libtap/basic/sh-skip.output tests/libtap/basic/sh-tmpdir	    \
	tests/libtap/cleanup-t tests/libtap/cleanup/c-bail-lazy.output	    \
	tests/libtap/cleanup/c-bail.output				    \
	tests/libtap/cleanup/c-fork.output				    \
	tests/libtap/cleanup/c-lazy.output				    \
	tests/libtap/cleanup/c-many-fail.output				    \
	tests/libtap/cleanup/c-many.output				    \
	tests/libtap/cleanup/c-one-fail.output				    \
	tests/libtap/cleanup/c-one.output tests/tap/libtap.sh

# It's somewhat odd to have the TAP library and the runtests harness in the
# tests directory, since they're the primary point of this package.  But
# that way they're in the same locations as they are in packages into which
# they're copied, which simplifies things like include paths.
bin_PROGRAMS = tests/runtests
noinst_LIBRARIES = tests/tap/libtap.a
tests_tap_libtap_a_SOURCES = tests/tap/basic.c tests/tap/basic.h	\
	tests/tap/float.c tests/tap/float.h tests/tap/macros.h
dist_man_MANS = docs/api/bail.3 docs/api/bmalloc.3 docs/api/breallocarray.3 \
	docs/api/diag.3 docs/api/diag_file_add.3 docs/api/is_int.3	    \
	docs/api/ok.3 docs/api/plan.3 docs/api/skip.3 docs/api/skip_all.3   \
	docs/api/test_cleanup_register.3 docs/api/test_file_path.3	    \
	docs/api/test_tmpdir.3 docs/runtests.1

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
	cd $(DESTDIR)$(man3dir) && $(LN_S) bmalloc.3 bstrndup.3
	rm -f $(DESTDIR)$(man3dir)/sysdiag.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) diag.3 sysdiag.3
	rm -f $(DESTDIR)$(man3dir)/diag_file_remove.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) diag_file_add.3 diag_file_remove.3
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
	rm -f $(DESTDIR)$(man3dir)/test_file_path_free.3
	cd $(DESTDIR)$(man3dir) \
	    && $(LN_S) test_file_path.3 test_file_path_free.3
	rm -f $(DESTDIR)$(man3dir)/test_tmpdir_free.3
	cd $(DESTDIR)$(man3dir) && $(LN_S) test_tmpdir.3 test_tmpdir_free.3

uninstall-hook:
	rm -f $(DESTDIR)$(man3dir)/sysbail.3
	rm -f $(DESTDIR)$(man3dir)/bcalloc.3
	rm -f $(DESTDIR)$(man3dir)/brealloc.3
	rm -f $(DESTDIR)$(man3dir)/bstrdup.3
	rm -f $(DESTDIR)$(man3dir)/bstrndup.3
	rm -f $(DESTDIR)$(man3dir)/sysdiag.3
	rm -f $(DESTDIR)$(man3dir)/diag_file_remove.3
	rm -f $(DESTDIR)$(man3dir)/is_double.3
	rm -f $(DESTDIR)$(man3dir)/is_string.3
	rm -f $(DESTDIR)$(man3dir)/is_hex.3
	rm -f $(DESTDIR)$(man3dir)/ok_block.3
	rm -f $(DESTDIR)$(man3dir)/okv.3
	rm -f $(DESTDIR)$(man3dir)/plan_lazy.3
	rm -f $(DESTDIR)$(man3dir)/skip_block.3
	rm -f $(DESTDIR)$(man3dir)/test_file_path_free.3
	rm -f $(DESTDIR)$(man3dir)/test_tmpdir_free.3

# Work around the GNU Coding Standards, which leave all the Autoconf and
# Automake stuff around after make maintainer-clean, thus making that command
# mostly worthless.
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 build-aux/depcomp		 \
	build-aux/install-sh build-aux/missing configure docs/api/bail.3 \
	docs/api/bmalloc.3 docs/api/breallocarray.3 docs/api/diag.3	 \
	docs/api/diag_file_add.3 docs/api/is_int.3 docs/api/ok.3	 \
	docs/api/plan.3 docs/api/skip.3 docs/api/skip_all.3		 \
	docs/api/test_file_path.3 docs/api/test_tmpdir.3 docs/runtests.1

# A set of flags for warnings.  Add -O because gcc won't find some warnings
# without optimization turned on.  Desirable warnings that can't be turned
# on due to other problems:
#
#     -Wconversion     http://bugs.debian.org/488884 (htons warnings)
#
# Last checked against gcc 4.6.1 (2011-05-04).  -D_FORTIFY_SOURCE=2 enables
# warn_unused_result attribute markings on glibc functions on Linux, which
# catches a few more issues.
if WARNINGS_GCC
    WARNINGS = -ansi -pedantic -g -O -D_FORTIFY_SOURCE=2 -Wall -Wextra	\
	-Wendif-labels -Wformat=2 -Winit-self -Wswitch-enum		\
	-Wdeclaration-after-statement -Wshadow -Wpointer-arith		\
	-Wbad-function-cast -Wwrite-strings -Wjump-misses-init		\
	-Wlogical-op -Wstrict-prototypes -Wmissing-prototypes		\
	-Wredundant-decls -Wnested-externs -Werror
endif
if WARNINGS_CLANG
    WARNINGS = -Weverything -Wno-padded -Werror -pedantic-errors
endif

warnings:
	$(MAKE) V=0 CFLAGS='$(WARNINGS)'
	$(MAKE) V=0 CFLAGS='$(WARNINGS)' $(check_PROGRAMS)

# The bits below are for the test suite.
check_PROGRAMS = tests/libtap/basic/c-bail tests/libtap/basic/c-basic	\
	tests/libtap/basic/c-bstrndup tests/libtap/basic/c-diag		\
	tests/libtap/basic/c-diag-file tests/libtap/basic/c-file	\
	tests/libtap/basic/c-extra tests/libtap/basic/c-extra-one	\
	tests/libtap/basic/c-lazy tests/libtap/basic/c-missing		\
	tests/libtap/basic/c-missing-one tests/libtap/basic/c-skip	\
	tests/libtap/basic/c-skip-reason tests/libtap/basic/c-success	\
	tests/libtap/basic/c-success-one tests/libtap/basic/c-sysbail	\
	tests/libtap/basic/c-tmpdir tests/libtap/cleanup/c-bail		\
	tests/libtap/cleanup/c-bail-lazy tests/libtap/cleanup/c-fork	\
	tests/libtap/cleanup/c-lazy tests/libtap/cleanup/c-many		\
	tests/libtap/cleanup/c-many-fail tests/libtap/cleanup/c-one	\
	tests/libtap/cleanup/c-one-fail
tests_libtap_basic_c_bail_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_basic_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_bstrndup_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_diag_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_diag_file_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_extra_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_extra_one_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_file_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_lazy_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_missing_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_missing_one_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_skip_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_skip_reason_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_success_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_success_one_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_sysbail_LDADD = tests/tap/libtap.a -lm
tests_libtap_basic_c_tmpdir_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_bail_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_bail_lazy_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_fork_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_lazy_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_many_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_many_fail_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_one_LDADD = tests/tap/libtap.a -lm
tests_libtap_cleanup_c_one_fail_LDADD = tests/tap/libtap.a -lm

check-local: $(bin_PROGRAMS) $(check_PROGRAMS)
	cd tests && ./runtests -s '$(abs_top_srcdir)/tests' \
	    -b '$(abs_top_builddir)/tests' -l '$(abs_top_srcdir)/tests/TESTS'

# Used by maintainers to run the main test suite under valgrind.  Suppress
# the xmalloc and pod-spelling tests because the former won't work properly
# under valgrind (due to increased memory usage) and the latter is pointless
# to run under valgrind.
check-valgrind: $(bin_PROGRAMS) $(check_PROGRAMS)
	rm -rf $(abs_top_builddir)/tmp-valgrind
	mkdir $(abs_top_builddir)/tmp-valgrind
	env RRA_MAINTAINER_TESTS= valgrind --leak-check=full	\
	    --show-reachable=yes --trace-children=yes		\
	    --log-file=$(abs_top_builddir)/tmp-valgrind/log.%p	\
	    --trace-children-skip="/bin/sh,*/cat,*/diff,*/expr,*/grep,*/mkdir,*/rm,*/rmdir,*/sed,*/sleep,*/true,*/wc,*/docs/pod*-t,*/harness/*/*.t,*/libtap/basic/sh-*" \
	    tests/runtests -s '$(abs_top_srcdir)/tests'		\
	    -b '$(abs_top_builddir)/tests' -l '$(abs_top_srcdir)/tests/TESTS'
