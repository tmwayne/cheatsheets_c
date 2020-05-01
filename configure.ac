#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Cheatsheets], [1.0], [tylerwayne3@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

echo \
"--------------------------------------------------

  ${PACKAGE_NAME} Version ${PACKAGE_VERSION}

  Prefix: '${prefix}'
  Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

  Package features:

  Now type 'make @<:@<target>@:>@'
    where the optional <target> is:
      all               - build all binaries
      install           - install everything

--------------------------------------------------"
