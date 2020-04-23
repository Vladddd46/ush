#include "ush.h"

int mx_too_many_args(char **cmd_exp, char **flag, char **oldcwd) {
    char *msg;
    int status = 0;

    if (mx_strarr_size(cmd_exp) > 3)
        status = 1;
    else if (flag[0]  == NULL && mx_strarr_size(cmd_exp) > 2) 
        status = 1;
    if (status) {
        msg = "cd: too many arguments\n";
        write(2, msg, mx_strlen(msg));
        free(flag[0]);
        free(oldcwd[0]);
    }
    return status;
}

