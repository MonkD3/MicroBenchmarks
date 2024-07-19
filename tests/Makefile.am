# Define the unit testing program
TESTS = unit_tests
check_PROGRAMS = unit_tests
unit_tests_SOURCES = unit_test.c $(top_builddir)/src/include/benchmarks.h

# Link the program to libbench andn cunit
unit_tests_LDADD = $(top_builddir)/src/libbench.la $(CUNITLIB)

