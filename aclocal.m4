# aclocal.m4 -- Some useful autoconf macros.
# $Id$
#
# Written by Russ Allbery <rra@stanford.edu>
# Copyright abandoned 2000 by author.  This work is in the public domain.
#
# This is a collection of miscellaneous autoconf macros that I've written
# and found generally useful.

# RRA_NETWORK_LIBS
# ----------------
#
# Searches for the headers necessary for networking functions and adds them
# to LIBS.  Mostly for picking up -lsocket -lnsl on Solaris.
AC_DEFUN(RRA_NETWORK_LIBS,
[AC_SEARCH_LIBS(gethostbyname, nsl)
AC_SEARCH_LIBS(socket, socket, ,
    [AC_CHECK_LIB(nsl, socket, LIBS="$LIBS -lsocket -lnsl", , -lsocket)])])
