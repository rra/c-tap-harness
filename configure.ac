dnl Autoconf configuration for C TAP Harness
dnl
dnl The C TAP harness is written in maximally portable C, so Autoconf is used
dnl here mostly for consistency in build process and to handle Automake, not
dnl for any portability of the code itself.
dnl
dnl Copyright 2008, 2009, 2010 Russ Allbery <rra@stanford.edu>
dnl
dnl See LICENSE for licensing terms.

AC_PREREQ([2.64])
AC_INIT([C TAP Harness], [1.8], [rra@stanford.edu], [c-tap-harness])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.11 check-news silent-rules -Wall -Werror])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_LN_S

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([tests/env/env.t], [chmod +x tests/env/env.t])
AC_CONFIG_FILES([tests/search.t],  [chmod +x tests/search.t])
AC_OUTPUT
