#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createPath(char** maze, size_t n_rooms) {
    for (size_t i = 0; i < n_rooms; ++i) {
        for (size_t j = 0; j < n_rooms; ++j) {
            size_t x = j * 2 + 1, y = i * 2 + 1;
            int up    = i > 0           && maze[y - 1][x] == '#';
            int down  = i < n_rooms - 1 && maze[y + 1][x] == '#';
            int left  = j > 0           && maze[y][x - 1] == '#';
            int right = j < n_rooms - 1 && maze[y][x + 1] == '#';

            int possible_directions = up + down + left + right;
            if (possible_directions == 0) continue;
            int direction = rand() % possible_directions;
            switch (direction) {
                case 0:
                    if (up) {
                        maze[y - 1][x] = '.';
                        break;
                    }
                    else ++direction;
                case 1:
                    if (down) {
                        maze[y + 1][x] = '.';
                        break;
                    }
                    else ++direction;
                case 2:
                    if (left) {
                        maze[y][x - 1] = '.';
                        break;
                    }
                    else ++direction;
                case 3:
                    if (right) {
                        maze[y][x + 1] = '.';
                    }
                    break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    size_t n_rooms = 6;
    const size_t maze_size = n_rooms * 2 + 1;

    char **maze = (char**)malloc(sizeof(void*) * maze_size);
    for (size_t i = 0; i < maze_size; ++i) {
        maze[i] = (char*)malloc(sizeof(char) * (maze_size + 1));
        for (size_t j = 0; j < maze_size; ++j) {
            maze[i][j] = i % 2 && j % 2 ? '.' : '#';
        }
        maze[i][maze_size] = 0;
    }

    createPath(maze, n_rooms);
    for (size_t i = 0; i < maze_size; ++i) {
        printf("%s\n", maze[i]);
    }

    for (size_t i = 0; i < maze_size; ++i) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
