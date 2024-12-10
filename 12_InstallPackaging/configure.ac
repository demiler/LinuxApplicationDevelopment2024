AC_INIT([avg], [1.0.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
GETTEXT_PACKAGE=avg
AC_SUBST(GETTEXT_PACKAGE)
ALL_LINGUAS="ru"

AC_CONFIG_SRCDIR([src/avg.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([ Makefile, src/Makefile.am, po/Makefile.in ])
AC_OUTPUT
