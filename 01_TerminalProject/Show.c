#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>

#define FRAME_OFX 2
#define FRAME_OFY 2

#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_H 104
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_Q 113


int min(int a, int b) {
    return a < b ? a : b;
}

size_t countLines(char *string, size_t len) {
    size_t lines = 0;
    for (size_t i = 0; i < len; ++i) {
        lines += (string[i] == '\n');
    }
    return lines;
}

void graphics(char *filein, size_t n_lines, char **lines) {
    initscr();
    noecho();
    cbreak();

    printw("File %s. Lines: %ld", filein, n_lines);
    refresh();

    WINDOW *frame;
    size_t maxstrlen = COLS - 2 * FRAME_OFX - 3;
    size_t maxlines = LINES - FRAME_OFX - 3;
    frame = newwin(maxlines + 2, maxstrlen + 2, FRAME_OFX, FRAME_OFY);
    keypad(stdscr, TRUE);

    int firsttime = 1;
    int done = 0;

    int curline = 0;
    int lineoffset = 0;

    while (!done) {
        int key = 0;
        if (firsttime != 1) {
            werase(frame);
            key = getch();
        }
        firsttime = 0;

        switch (key) {
            case KEY_Q:
            case KEY_ESC:
                done = 1;
                break;
            case KEY_K:
            case KEY_UP:
                if (curline > 0) --curline;
                break;
            case KEY_J:
            case KEY_DOWN:
                if (curline + 1 < n_lines) ++curline;
                break;

            case KEY_L:
            case KEY_RIGHT:
                ++lineoffset;
                break;

            case KEY_H:
            case KEY_LEFT:
                if (lineoffset > 0) --lineoffset;
                break;

            case KEY_SPACE:
                curline += 20;
                if (curline >= n_lines) curline = n_lines - 1;
                break;
        }

        box(frame, 0, 0);
        //wmove(frame, 0, 0);
        //wprintw(frame, "Key: \t%d\n", key);

        for (size_t i = 0; i < maxlines; ++i) {
            if (i + curline >= n_lines) break;
            char *curlineptr = lines[i + curline];
            size_t linelen = strlen(curlineptr);
            curlineptr += min(linelen, lineoffset);
            mvwaddnstr(frame, i + 1, 1, curlineptr, maxstrlen);
        }

        wrefresh(frame);
    }

    endwin();
}

char** splitLines(char *text, size_t textlen) {
    size_t n_lines = countLines(text, textlen);
    char **lines;
    lines = malloc(sizeof(void*) * n_lines);

    const char *worm = text;
    for (size_t i = 0; i < n_lines; ++i) {
        const char *lineend = strchr(worm, '\n');
        if (lineend == NULL) {
            lineend = text + textlen;
        }

        size_t linelen = lineend - worm;
        lines[i] = malloc(sizeof(char) * (linelen + 1));
        strncpy(lines[i], worm, linelen);
        lines[i][linelen] = 0;
        worm = lineend + 1;
    }

    return lines;
}

void freeLines(char **lines, size_t n_lines) {
    for (size_t i = 0; i < n_lines; ++i) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expected exactly one argument -- path to a file\n");
        return 1;
    }
    char* filein = argv[1];
    size_t filein_len = strlen(filein);

    struct stat st;
    if (stat(filein, &st) == -1) {
        printf("Error: Failed to open file: %s\n", strerror(errno));
        return 2;
    }
    size_t datasize = st.st_size;

    char *data = malloc(sizeof(char) * (datasize + 1));
    int fd = open(filein, O_RDONLY);
    read(fd, data, datasize);
    close(fd);
    data[datasize] = 0;

    size_t n_lines = countLines(data, datasize);
    char **lines = splitLines(data, datasize);
    free(data);

    graphics(filein, n_lines, lines);

    freeLines(lines, n_lines);
    return 0;
}
