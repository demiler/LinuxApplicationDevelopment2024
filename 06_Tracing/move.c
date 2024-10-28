#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 256
#define ERR_BUWR 1
#define ERR_INOPEN 2
#define ERR_INPERM 3
#define ERR_OUTCR 4
#define ERR_OUTPERM 5
#define ERR_OUTUNL 6
#define ERR_INUNL 7
#define ERR_SAMEFILE 8

int fatal(const char* msg, int exit_code) {
    int error = errno;
    printf("Error: %s", msg);
    if (error) {
        printf(" Reason: %s", strerror(error));
    }
    printf("\n");
    return exit_code;
}

int copy(int fd_in, int fd_out) {
    ssize_t num_read;
    char buf[BUF_SIZE];
    while ((num_read = read(fd_in, buf, BUF_SIZE)) > 0) {
        if (write(fd_out, buf, num_read) != num_read) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: move <in file> <out file>\n");
        return 0;
    }
    const char* infile = argv[1];
    const char* outfile = argv[2];

    if (strcmp(infile, outfile) == 0) {
        return fatal("Can't move file to itself", ERR_SAMEFILE);
    }

    int in_fd = open(infile, O_RDONLY);

    if (in_fd == -1) {
        return fatal("Failed to open input file", ERR_INOPEN);
    }

    struct stat perms;
    if (fstat(in_fd, &perms)) {
        close(in_fd);
        return fatal("Failed to obtain file permissions", ERR_INPERM);
    }

    if (unlink(outfile)) {
        if (errno != ENOENT) {
            return fatal("Failed to unlink outfile", ERR_OUTUNL);
        }
    }

    int out_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY);
    if (out_fd == -1) {
        close(in_fd);
        return fatal("Failed to open or create output file", ERR_OUTCR);
    }
    if (fchmod(out_fd, perms.st_mode)) {
        close(in_fd);
        close(out_fd);
        unlink(outfile);
        return fatal("Failed to change output file permissions", ERR_OUTPERM);
    }

    if (copy(in_fd, out_fd)) {
        close(in_fd);
        close(out_fd);
        unlink(outfile);
        return fatal("Fatal error: couldn't write whole buffer", ERR_BUWR);
    }
    close(in_fd);
    close(out_fd);

    if (unlink(infile)) {
        return fatal("Failed to unlink input file", ERR_INUNL);
    }

    return 0;
}
