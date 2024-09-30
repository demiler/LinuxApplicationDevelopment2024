GENERATES = prog prog-a prog-so README libout.a
TRASH = *.o *~ o.* test-*.out
CFLAGS = -Wall

all: README prog prog-a prog-so

.SECONDARY: fun.o const.o
.INTERMEDIATE: liboutput_static.a(fun.o const.o) liboutput.so(fun.o const.o)

liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: liboutput.so(fun.o const.o)

prog: fun.o const.o

prog-%.o: prog.o
	ln -sf prog.o $@

prog-a: liboutput_static.a

prog-so: liboutput.so

README: prog
	./$< 2> $@

test: prog-a prog-so prog
	for p in $^; do ./$$p 2>&1 | sed "s/\b"$$p"\b/prog/g" > test-0-$$p.out; done
	for p in $^; do ./$$p wow > test-1-$$p.out 2>&1; done
	for p in $^; do ./$$p w o w > test-2-$$p.out 2>&1; done
	#
	for i in {0..2}; do for p1 in $^; do for p2 in $^; do \
		[ "$$p1" = "$$p2" ] && continue; \
		cmp test-$$i-{$$p1,$$p2}.out || \
			echo "uh oh! Files test-$$i-$$p1.out test-$$i-$$p2.out do not match!";\
	done; done; done;


fun.o prog.o: outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
