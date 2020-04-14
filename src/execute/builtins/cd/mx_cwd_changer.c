#include "ush.h"

/*
    * [cd help funtion]
    *  changes cwd.
*/
void mx_cwd_changer(char *newcwd, char *oldcwd) {
    if (mx_access_errors(newcwd)) {
        free(newcwd);
        free(oldcwd);
        return;
    }
    else if (oldcwd == NULL) {
        free(newcwd);
        return;
    }
    setenv("PWD", newcwd, 1);
    setenv("OLDPWD", oldcwd, 1);
    chdir(newcwd);
}



