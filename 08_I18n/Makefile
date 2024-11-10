.PHONY: clean all test make-template
GENERATES=guesser
TRASH=*.o *.temp *.mo locales template.pot

CFLAGS=-O0 -g

all: guesser

guesser: guesser.o

locales: po/ru/_.mo

po/ru/_.mo: po/ru/_.po
	msgfmt $^ -o $@

template: guesser.c
	xgettext -L C --keyword=_ -o template.pot $^

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
