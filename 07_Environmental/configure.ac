AC_INIT([repl], [1.0], [bug-automake@gnu.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC


AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([rhash is required])])

LIB_READLINE_FLAG=""

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--enable-readline], [Use readline instead of default i/o])],
  [AC_CHECK_LIB([readline], [readline], [
    AX_APPEND_FLAG([-lreadline])
    AC_DEFINE(USE_READLINE, [1], [Use readline])
  ], [AC_MSG_ERROR([Readline required with this option])]
  )], []
)


AC_CONFIG_FILES([ Makefile ])
AC_OUTPUT
