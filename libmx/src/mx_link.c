#include "libmx.h"

// Returns physical location of link
char *mx_link(char *file, struct stat sb) {
    char *buf;
    ssize_t nbytes;
    ssize_t bufsiz;
    char *result;

    bufsiz = sb.st_size + 1;
    if (sb.st_size == 0)
        bufsiz = PATH_MAX;
    buf = mx_strnew(bufsiz);
    nbytes = readlink(file, buf, bufsiz);
    if (nbytes == -1) {
        free(buf);
        return NULL;
    }
    result = buf;
    free(buf);
    return result;
}
