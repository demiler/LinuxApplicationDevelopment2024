.PHONY: clean all test
GENERATES=move
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: move test

move: move.o

test: move
	echo wow

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
