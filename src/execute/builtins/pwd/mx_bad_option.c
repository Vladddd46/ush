#include "ush.h"

void mx_bad_option(char *option) {
    char *msg  = "u$h: pwd: ";
    char *msg1 = ": invalid option\n";
    char *msg2 = "pwd: usage: pwd [-LP]\n";

    write(2, msg,    mx_strlen(msg));
    write(2, option, mx_strlen(option));
    write(2, msg1,   mx_strlen(msg1));
    write(2, msg2,   mx_strlen(msg2));
}

