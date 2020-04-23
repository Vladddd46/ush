#include "ush.h"


// Changes replaces value of PWD value with HOME value.
void mx_cd_home(char *oldcwd) {
    char *newcwd = mx_string_copy(getenv("HOME"));
    char *msg;

    if (newcwd == NULL) {
        msg = "cd: HOME variable is not set\n";
        write(2, msg, mx_strlen(msg));
        return;
    }
    mx_cwd_changer(newcwd, oldcwd);
}


