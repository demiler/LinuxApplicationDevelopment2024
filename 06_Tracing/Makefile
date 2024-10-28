.PHONY: clean all test
GENERATES=move protected_unlink.so input-file PROTECTED-input-file output-file
TRASH=input-file *.o *.temp

CFLAGS=-O0 -g

all: move test

move: move.o

protected_unlink.so: protected_unlink.c
	$(CC) $^ -o $@ -fPIC -shared -ldl

input-file:
	echo "Hello, World!" > input-file

test: test-faulty-write test-no-pre-unlink test-no-fstat test-no-open test-no-protected-unlink

test-no-protected-unlink: protected_unlink.so move input-file
	mv input-file PROTECTED-input-file
	LD_PRELOAD=./protected_unlink.so ./move PROTECTED-input-file output-file >/dev/null; [ $$? -eq 7 ] && [ -f PROTECTED-input-file ] && [ -f output-file ] && echo "SUCCESS ($@)" || false;

test-faulty-write: input-file move
	strace -e trace=write -e inject=write:when=1:retval=999 ./move input-file output-file >/dev/null 2>&1; [ $$? -eq 1 ] && [ -f input-file ] && echo "SUCCESS ($@)" || false;

test-no-pre-unlink: input-file move
	strace -f -e trace=unlink -e fault=unlink:when=1:error=EIO ./move input-file output-file >/dev/null 2>&1; [ $$? -eq 6 ] && [ -f input-file ] && echo "SUCCESS ($@)" || false;

test-no-fstat: input-file move
	strace -f -e trace=fstat -e fault=fstat:when=3:error=EOVERFLOW ./move input-file output-file >/dev/null 2>&1; [ $$? -eq 3 ] && [ -f input-file ] && echo "SUCCESS ($@)" || false;

test-no-open: input-file move
	strace -f -e trace=openat -e fault=openat:when=3:error=ELOOP ./move input-file output-file >/dev/null 2>&1; [ $$? -eq 2 ] && [ -f input-file ] && echo "SUCCESS ($@)" || false;

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
