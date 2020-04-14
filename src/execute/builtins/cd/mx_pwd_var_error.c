#include "ush.h"

int mx_pwd_var_error() {
    char *msg = "cd: PWD variable is not set\n";

    if (getenv("PWD") == NULL) {
        write(2, msg, mx_strlen(msg));
        return 1;
    }
    return 0;
}

