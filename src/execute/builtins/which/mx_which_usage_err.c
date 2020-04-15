#include "ush.h"

int mx_which_usage_err(char **cmd) {
    char *msg = "usage: which [-as] program ...\n";

    if(mx_strarr_size(cmd) == 1) {
        write(2, msg, mx_strlen(msg));
        return 1;
    }
    return 0;
}

