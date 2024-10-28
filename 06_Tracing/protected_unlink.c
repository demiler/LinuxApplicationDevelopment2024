#include <dlfcn.h>
#include <string.h>
#include <errno.h>

int (*orig_unlink)(const char *pathname);

int unlink(const char *pathname) {
    if (orig_unlink == NULL) orig_unlink = dlsym(RTLD_NEXT, "unlink");

    if (strstr(pathname, "PROTECTED") != NULL) {
        errno = EROFS;
        return -1;
    }
    return orig_unlink(pathname);
}
