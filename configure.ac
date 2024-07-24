# Init Autoconf and Automake 
AC_INIT([libbench], [alpha], [])

# Configure the auxiliary directories and initialize Automake
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Check for programs
AC_PROG_CC([gcc cc clang])
AM_PROG_AR

# Init libtool
LT_INIT

AC_CHECK_LIB([cunit], [CU_initialize_registry], [CUNITLIB=-lcunit])
AC_SUBST([CUNITLIB])
AC_CHECK_LIB([m], [tgammal], [MATHLIB=-lm])
AC_SUBST([MATHLIB])

# Check the existence of one of the source files
AC_CONFIG_SRCDIR([src/benchmarks.c])

# Configure the config header 
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
])

# This is not portable, check to use AX_CHECK_COMPILE_FLAG
# from the autotools archives. Later use AC_ARG_ENABLE to also 
# add optimization flags
CFLAGS="-Wall -Werror -Wall -Wshadow -Wold-style-definition -Wmissing-prototypes $CFLAGS"

AC_OUTPUT
