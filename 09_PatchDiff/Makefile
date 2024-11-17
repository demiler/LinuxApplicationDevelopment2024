.PHONY: clean all test
GENERATES=maze maze-patch1 maze-patch2 maze-patch2
TRASH=*.o *.temp

CFLAGS=-O0 -g

all: maze maze-patch1 maze-patch2 maze-patch3

maze: maze.c
	git reset --hard HEAD
	$(CC) $(CFLAGS) -o maze maze.c

maze-patch1: patch1-argv-maze-rooms.patch maze.c
	git reset --hard HEAD
	git apply $<
	$(CC) $(CFLAGS) -o maze-patch1 maze.c

maze-patch2: patch2-argv-maze-rooms-n-chars.patch maze.c
	git reset --hard HEAD
	git apply $<
	$(CC) $(CFLAGS) -o maze-patch2 maze.c

maze-patch3: patch3-argv-maze-rooms-n-chars-n-srand.patch maze.c
	git reset --hard HEAD
	git apply $<
	$(CC) $(CFLAGS) -o maze-patch3 maze.c

run: maze maze-patch1 maze-patch2 maze-patch3
	./maze
	./maze-patch1 3
	./maze-patch2 '! ' 4
	./maze-patch3 100 '$$ ' 5

clean:
	rm -rf $(TRASH)
	rm -rf $(GENERATES)
