.PHONY: clean all test
GENERATES=range
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: range test

range: range.o

test: range test-1-orig test-2-orig gdb1 gdb2
	gdb --batch -x gdb1 range 2>/dev/null | grep "^@" | sed 's/^@//' > test-1-gdb.temp
	gdb --batch -x gdb2 range 2>/dev/null | grep "^@" | sed 's/^@//' > test-2-gdb.temp
	diff test-1*
	diff test-2*

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
