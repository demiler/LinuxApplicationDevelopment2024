SUBDIRS = src po tests

@DX_RULES@

all-local: help-temp.dox doxygen-doc

doxygen-doc/man/man1/avg.c.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/avg.c.1

help-temp.dox: ./src/avg
	echo '```' > $@
	./src/avg --help >> $@
	echo '```' >> $@

docs-serve: doxygen-doc
	python3 -m http.server --directory $</html
