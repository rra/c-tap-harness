# aclocal.m4 -- Some useful autoconf macros.
# $Id$
#
# Written by Russ Allbery <rra@stanford.edu>
# Copyright abandoned 2000 by author.  This work is in the public domain.
#
# This is a collection of miscellaneous autoconf macros that I've written
# and found generally useful.

# _RRA_FUNC_INET_NTOA_SOURCE
# --------------------------
define([_RRA_FUNC_INET_NTOA_SOURCE],
[#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#if STDC_HEADERS || HAVE_STRING_H
# include <string.h>
#endif

int
main ()
{
  struct in_addr in;
  in.s_addr = 0x7f000000;
  exit (!strcmp (inet_ntoa (in), "127.0.0.0") ? 0 : 1);
}])# _RRA_FUNC_INET_NTOA_SOURCE

# RRA_FUNC_INET_NTOA
# ------------------
# Check whether inet_ntoa is present and working.  Since calling inet_ntoa
# involves passing small structs on the stack, present and working versions
# may still not function with gcc on some platforms (such as IRIX).
AC_DEFUN([RRA_FUNC_INET_NTOA],
[AC_CACHE_CHECK(for working inet_ntoa, rra_cv_func_inet_ntoa_works,
[AC_TRY_RUN(_RRA_FUNC_INET_NTOA_SOURCE(),
            [rra_cv_func_inet_ntoa_works=yes],
            [rra_cv_func_inet_ntoa_works=no],
            [rra_cv_func_inet_ntoa_works=no])
if test "$rra_cv_func_inet_ntoa_works" = yes ; then
  AC_DEFINE_UNQUOTED([HAVE_INET_NTOA], 1,
                     [Define if your system has a working `inet_ntoa'
                      function.])
fi[]dnl
])])# RRA_FUNC_INET_NTOA

# RRA_NETWORK_LIBS
# ----------------
# Searches for the headers necessary for networking functions and adds them
# to LIBS.  Mostly for picking up -lsocket -lnsl on Solaris.
AC_DEFUN([RRA_NETWORK_LIBS],
[AC_SEARCH_LIBS(gethostbyname, nsl)
AC_SEARCH_LIBS(socket, socket, ,
    [AC_CHECK_LIB(nsl, socket, LIBS="$LIBS -lsocket -lnsl", , -lsocket)])])
