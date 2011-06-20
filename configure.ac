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
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# CxxTest (cxxtest.tigris.org)
AC_PATH_PROG([CXXTESTGEN], [cxxtestgen.pl], [/usr/local/cxxtest-3.10.1/cxxtest/cxxtestgen.pl])

DIR_CXXTEST_INC_DEFAULT='/usr/local/cxxtest-3.10.1/cxxtest'
#DIR_CXXTEST_INC_DEFAULT='/usr/include'

DIR_GLOG=/usr/local/glog-0.3.1
DIR_GLOG_LIB_DEFAULT=$DIR_GLOG/lib
DIR_GLOG_INC_DEFAULT=$DIR_GLOG/include

#DIR_GTEST=/usr/local/gtest-1.5.0
#DIR_GTEST_LIB_DEFAULT=$DIR_GTEST/lib
#DIR_GTEST_INC_DEFAULT=$DIR_GTEST/include

# CxxTest code generator flags:
CXXTFLAGS='--error-printer'

# C e C++ compilers flags:
#CPPFLAGS='-g -Wall -Werror -O'
CPPFLAGS='-g -Wall -Werror -O -DCGTL_DO_NOT_USE_STL'
CFLAGS=
CXXFLAGS=

LDFLAGS='-lpthread'
#INCLUDES='-I$(top_srcdir)/src'
INCLUDES='-I$(top_srcdir)/src -I$(top_srcdir)/src/tests/gtest/include'


dnl **********************************************************************
dnl Check for the presence of cxxtest headers
dnl **********************************************************************

AC_ARG_WITH(cxxtest-includes,
            AC_HELP_STRING([--with-cxxtest-includes=DIR],
                           [Specify location of cxxtest headers]),
                           [CPPFLAGS="$CPPFLAGS -I$withval"],
                           [CPPFLAGS="$CPPFLAGS -I${DIR_CXXTEST_INC_DEFAULT}"])


dnl **************************************************************************
dnl Check for presence of Google C++ Logging Library (glog)
dnl **************************************************************************

AC_ARG_WITH(glog-includes,
			AC_HELP_STRING([--with-glog-includes=DIR],
						   [Specify location of Google C++ Logging Library headers]),
						   [INCLUDES="$INCLUDES -I$withval"],
						   [INCLUDES="$INCLUDES -I${DIR_GLOG_INC_DEFAULT}"])

AC_ARG_WITH(glog-libs,
			AC_HELP_STRING([--with-glog-libs=DIR],
						   [Specify location of Google C++ Logging Library libs]),
						   [LIB_GLOG_PATH="$withval"],
						   [LIB_GLOG_PATH="${DIR_GLOG_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_GLOG_PATH} -lglog"


dnl **************************************************************************
dnl Check for presence of Google C++ Testing Framework
dnl **************************************************************************

#AC_ARG_WITH(gtest-includes,
#			AC_HELP_STRING([--with-gtest-includes=DIR],
#						   [Specify location of Google C++ Testing Framework headers]),
#						   [INCLUDES="$INCLUDES -I$withval"],
#						   [INCLUDES="$INCLUDES -I${DIR_GTEST_INC_DEFAULT}"])

#AC_ARG_WITH(gtest-libs,
#			AC_HELP_STRING([--with-gtest-libs=DIR],
#						   [Specify location of Google C++ Testing Framework libs]),
#						   [LIB_GTEST_PATH="$withval"],
#						   [LIB_GTEST_PATH="${DIR_GTEST_LIB_DEFAULT}"])

#LIBS="$LIBS -L${LIB_GTEST_PATH} -lgtest"


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
                 src/tests/cgt/search/depth/Makefile
                 src/tests/cgt/shortpath/Makefile
                 src/tests/cgt/shortpath/single/Makefile
                 src/tests/cgt/shortpath/single/bellford/Makefile
                 src/tests/cgt/shortpath/single/dijkstra/Makefile])
AC_OUTPUT
