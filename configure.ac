#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(cgtl, 0.01, leandro.costa@gmail.com)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LIBTOOL
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h malloc.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# CxxTest (cxxtest.tigris.org)
AC_PATH_PROG([CXXTESTGEN], [cxxtestgen.pl], [/usr/local/cxxtest-3.10.1/cxxtest/cxxtestgen.pl])

DIR_CXXTEST_INC_DEFAULT='/usr/local/cxxtest-3.10.1/cxxtest'
#DIR_CXXTEST_INC_DEFAULT='/usr/include'

# CxxTest code generator flags:
CXXTFLAGS='--error-printer'

# C e C++ compilers flags:
#CPPFLAGS='-g -Wall -Werror -O'
CPPFLAGS='-g -Wall -Werror -O -DCGTL_DO_NOT_USE_STL'
CFLAGS=
CXXFLAGS=

LDFLAGS='-lpthread'
INCLUDES='-I$(top_srcdir)/src'


dnl **********************************************************************
dnl Check for the presence of cxxtest headers
dnl **********************************************************************

AC_ARG_WITH(cxxtest-includes,
            AC_HELP_STRING([--with-cxxtest-includes=DIR],
                           [Specify location of cxxtest headers]),
                           [CPPFLAGS="$CPPFLAGS -I$withval"],
                           [CPPFLAGS="$CPPFLAGS -I${DIR_CXXTEST_INC_DEFAULT}"])


AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(INCLUDES)
AC_SUBST(CXXTFLAGS)

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/examples/Makefile
                 src/tests/Makefile
                 src/tests/cgt/Makefile
                 src/tests/cgt/base/Makefile
                 src/tests/cgt/base/alloc/Makefile
                 src/tests/cgt/base/exception/Makefile
                 src/tests/cgt/base/iterator/Makefile
                 src/tests/cgt/search/Makefile
                 src/tests/cgt/search/breadth/Makefile
                 src/tests/cgt/search/depth/Makefile])
AC_OUTPUT
