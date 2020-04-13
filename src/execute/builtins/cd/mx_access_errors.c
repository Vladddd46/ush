#include "ush.h"
/*
    * [cd help function]
    * access errors handler
*/
int mx_access_errors(char *newcwd) {
    char *msg;

    if (access(newcwd, 0) == -1) {
        msg = "cd: no such file or directory: ";
        write(2, msg, mx_strlen(msg));
        write(2, newcwd, mx_strlen(newcwd));
        write(2, "\n", 1);
        return 1;
    }
    else if (access(newcwd, 1) == -1) {
        msg = "cd: permission denied: ";
        write(2, msg, mx_strlen(msg));
        write(2, newcwd, mx_strlen(newcwd));
        write(2, "\n", 1);
        return 1;
    }
    return 0;
}



