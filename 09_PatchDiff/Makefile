.PHONY: clean all test
GENERATES=maze
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: maze

patch0-src:
	git reset --hard HEAD

patch1-src: patch1-argv-maze-rooms.patch
	git apply $<

patch1: patch0-src patch1-src maze 
	cp maze maze-patch1

maze-p0: patch0-src maze

maze: maze.o

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
