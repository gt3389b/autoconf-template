#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([example], [1.0], [gt3389b@gmail.com])
AM_INIT_AUTOMAKE(example, 1.0)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

LT_INIT
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([curl], [curl_global_init], [],[AC_MSG_ERROR([curl development package not installed])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strstr])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
