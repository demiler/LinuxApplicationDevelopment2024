check_PROGRAMS = avg_test
avg_test_SOURCES = avg_test.c

%.c: %.checkmk
	checkmk $< > $@

# Use the Check library for linking
avg_test_LDADD = $(LDADD) $(top_builddir)/src/calc.o @CHECK_LIBS@
AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@

# Define the test program
TESTS = avg_test
TESTS_ENVIRONMENT = CK_FORK=no
