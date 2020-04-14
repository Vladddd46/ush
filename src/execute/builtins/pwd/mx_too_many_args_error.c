#include "ush.h"

void mx_pwd_too_many_args() {
    char *msg = "pwd: too many arguments\n";
    write(2, msg, mx_strlen(msg));
}
