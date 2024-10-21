.PHONY: clean all test
GENERATES=esub
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: esub test

esub: esub.o

test: esub
	echo "Usage: ./esub <pattern> <substitution> <string>" > test-1-true.temp
	./esub > test-1-out.temp
	diff test-1-*.temp
	echo "2024 17 October Thrursday" | sed -E 's/([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/' > test-2-true.temp
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thrursday" > test-2-out.temp
	diff test-2-*.temp
	echo "Error: capture group 3 wasn't found!" > test-3-true.temp
	./esub "so(me)(thing)" "\3" "<something>" > test-3-out.temp
	diff test-3-*.temp
	./esub "some(thing" "where \1" "something else" > test-4-out.temp
	echo "Error: failed to compile regex. Reason: Unmatched ( or \(" > test-4-true.temp
	diff test-4-*.temp
	./esub "(a)b(c)d(e)" "<\3\2\1>" _abcdef_ > test-5-out.temp
	echo "_<eca>f_" > test-5-true.temp
	@echo -e "\nTESTS COMPLETED SUCCESSFULLY!\n"

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
