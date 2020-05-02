#include "ush.h"

void mx_bad_option(char *option, char *builtin_name) {
    char *msg  = "u$h: ";
    char *msg1 = ": bad option: ";

    write(2, msg,            mx_strlen(msg));
    write(2, builtin_name,   mx_strlen(builtin_name));
    write(2, msg1,           mx_strlen(msg1));
    write(2, option,         mx_strlen(option));
    write(2, "\n", 1);
}
