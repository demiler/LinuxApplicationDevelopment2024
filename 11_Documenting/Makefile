.PHONY: clean all test template ru locales-install

LOCALE_DIR=/tmp/tmp.locales
PACKAGE=guesser

GENERATES=guesser $(LOCALE_DIR)
TRASH=*.o *.temp *.mo locales template.pot *.man po/template.pot docs *-temp.dox

CFLAGS=-O0 -g -D LOCALE_DIR="\"$(LOCALE_DIR)\"" -D PACKAGE="\"$(PACKAGE)\""

all: guesser locales-install guesser.man docs

guesser: guesser.o

locales-install: ru

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

guesser.man: guesser
	help2man ./$< > $@

docs: Doxyfile.in help-temp.dox
	doxygen $<

docs-serve: docs
	python3 -m http.server 8080 --bind 127.0.0.1 --directory docs/html

help-temp.dox: guesser
	echo '```' > $@
	./guesser --help >> $@
	echo '```' >> $@

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
