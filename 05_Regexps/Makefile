.PHONY: clean all test
GENERATES=esub
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: esub test

esub: esub.o

test: esub
	echo wow a test

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
