.PHONY: clean all test
GENERATES=build
TRASH=*.o *.temp

build/growbuf.o: build growbuf/buf.c
	$(CC) growbuf/buf.c -c -o build/growbuf.o

build:
	mkdir -p build

make-tests: build
	mkdir -p build/tests
	for i in tests/*.checkmk; do checkmk $$i > build/tests/`echo $$i | cut -d/ -f2 | cut -d. -f1;`.c; done

build-tests: make-tests build/growbuf.o
	for i in build/tests/*.c; do $(CC) build/growbuf.o $$i -g -lcheck -fprofile-arcs -ftest-coverage -o `echo $$i | sed 's/.c$$//'`; done

run-tests: build-tests
	for i in build/tests/*; do [ -x $$i ] && [ ! -d $$i ] && { echo "== TEST $$i ==" && $$i; } || true; done

coverage: run-tests
	for i in build/tests/*.gcno; do echo "== $$i =="; gcov $$i; done

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
