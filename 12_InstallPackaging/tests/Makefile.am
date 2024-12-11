check_PROGRAMS = avg
avg_SOURCES = avg.c

%.c: %.checkmk
	checkmk $< > $@

# Use the Check library for linking
avg_LDADD = $(LDADD) $(top_builddir)/src/calc.o @CHECK_LIBS@
AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@

# Define the test program
TESTS = avg
TESTS_ENVIRONMENT = CK_FORK=no
