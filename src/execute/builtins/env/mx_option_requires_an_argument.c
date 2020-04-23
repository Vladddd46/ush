#include "ush.h"

void mx_option_requires_an_argument(char *option) {
    char *msg  = "env: option requires an argument -- ";
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    write(2, msg, mx_strlen(msg));
    write(2, option, mx_strlen(option));
    write(2, "\n", 1);
    write(2, msg1, mx_strlen(msg1));
    write(2, msg2, mx_strlen(msg2));
}

