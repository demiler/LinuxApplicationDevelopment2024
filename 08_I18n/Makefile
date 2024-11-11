.PHONY: clean all test template locales ru

LOCALE_DIR=/tmp/tmp.locales
PACKAGE=guesser

GENERATES=guesser $(LOCALE_DIR)
TRASH=*.o *.temp *.mo locales template.pot

CFLAGS=-O0 -g -D LOCALE_DIR="\"$(LOCALE_DIR)\"" -D PACKAGE="\"$(PACKAGE)\""

all: guesser

guesser: guesser.o

locales: ru

locales-update:
	for i in po/*_upd.po; do old=$$(echo $$i | sed 's/_upd//'); msgmerge -U $$old $$i && rm $$i; done

po:
	mkdir -p po

ru: po/ru.po po
	mkdir -p $(LOCALE_DIR)/$@/LC_MESSAGES
	msgfmt $< -o $(LOCALE_DIR)/$@/LC_MESSAGES/$(PACKAGE).mo

po/template.pot: guesser.c po
	xgettext -L C --keyword=_ -o po/template.pot $<

template: po/template.pot
	[ "$$LANG" != "C" ] && [ ! -f "po/$$LANG.po" ] && { msginit -i po/template.pot -l $$LANG -o po/$${LANG}.po; } || echo "Translation already exists"

template-upd: po/template.pot
	[ "$$LANG" != "C" ] && { msginit -i po/template.pot -l $$LANG -o po/$${LANG}_upd.po; } || { echo "LANG is required!" && false; }

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
