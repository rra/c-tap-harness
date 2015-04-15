dnl Autoconf configuration for C TAP Harness
dnl
dnl The C TAP harness is written in maximally portable C, so Autoconf is used
dnl here mostly for consistency in build process and to handle Automake, not
dnl for any portability of the code itself.
dnl
dnl Copyright 2008, 2009, 2010, 2011, 2013, 2014, 2015
dnl     Russ Allbery <eagle@eyrie.org>
dnl
dnl See LICENSE for licensing terms.

AC_PREREQ([2.64])
AC_INIT([C TAP Harness], [3.2], [eagle@eyrie.org], [c-tap-harness])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 check-news dist-xz foreign silent-rules subdir-objects
    -Wall -Werror])
AM_MAINTAINER_MODE

dnl Detect unexpanded macros.
m4_pattern_forbid([^_?RRA_])

AC_PROG_CC
RRA_PROG_CC_CLANG
AC_SYS_LARGEFILE
AM_PROG_CC_C_O
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_LN_S

dnl Enable appropriate warnings.
AM_CONDITIONAL([WARNINGS_GCC], [test x"$GCC" = xyes && test x"$CLANG" != xyes])
AM_CONDITIONAL([WARNINGS_CLANG], [test x"$CLANG" = xyes])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([tests/harness/env/env.t], [chmod +x tests/harness/env/env.t])
AC_CONFIG_FILES([tests/harness/search-t],  [chmod +x tests/harness/search-t])
AC_OUTPUT
