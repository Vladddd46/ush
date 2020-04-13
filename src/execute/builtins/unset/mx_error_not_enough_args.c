#include "ush.h"
/*
    * error, which occurs, when user entered:
      >>>unset
*/
int mx_error_not_enough_args(char **cmd_expr) {
    char *msg = "unset: not enough arguments\n";
    char *msg1 = "unset: usage: unset [-f] [-v] [name ...]\n";

    if(mx_strarr_size(cmd_expr) == 1) {
        write(2, msg,  mx_strlen(msg));
        write(2, msg1, mx_strlen(msg1));
        return 1;
    }
    return 0;
}

