#include "ush.h"

void mx_suspended_process_msg(char *str) {
    char *msg = "\nu$h: suspended ";
    write(1, msg, mx_strlen(msg));
    write(1, str, mx_strlen(str));
    write(1, "\n", 1);
}

