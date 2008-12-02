dnl Autoconf configuration for C TAP Harness
dnl
dnl The C TAP harness is written in maximally portable C, so Autoconf is used
dnl here mostly for consistency in build process and to handle Automake, not
dnl for any portability of the code itself.
dnl
dnl Copyright 2008 Russ Allbery <rra@stanford.edu>
dnl
dnl See LICENSE for licensing terms.

AC_PREREQ([2.61])
AC_INIT([runtests], [1.0], [rra@stanford.edu])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.10])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([t/libtest/sh-basic], [chmod +x t/libtest/sh-basic])
AC_OUTPUT
