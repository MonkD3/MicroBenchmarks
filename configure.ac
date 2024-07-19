# Init Autoconf and Automake 
AC_INIT([libbench], [alpha], [])

# Configure the auxiliary directories and initialize Automake
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Init libtool
LT_INIT

# Check for programs : GCC and Libtool
AC_PROG_CC([gcc])
AM_PROG_AR

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

AC_OUTPUT
