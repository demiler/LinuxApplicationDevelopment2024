bin_PROGRAMS=repl

repl_SOURCES=repl.c

TESTS=tests

tests:
	echo 'MD5 "something' | ./repl | sed 's/^> //' > test-md5-repl.temp
	echo -n something | md5sum | sed 's/\s\+-$$//' > test-md5-md5sum.temp
	diff test-md5-*.temp
	echo 'SHA1 "something' | ./repl | sed 's/^> //' > test-sha1-repl.temp
	echo -n something | sha1sum | sed 's/\s\+-$$//' > test-sha1-sha1sum.temp
	diff test-sha1-*.temp

deepclean:
	rm -rf *.temp
