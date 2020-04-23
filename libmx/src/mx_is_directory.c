#include "libmx.h"

/*
    * Checks wether file is directory
*/
int mx_is_directory(char *dir_name) {
    errno = 0;
    DIR *dir_opn = opendir(dir_name);

    if (errno == 0) {
        closedir(dir_opn);
        return 1;
    }
    free(dir_opn);
    return 0;
}
