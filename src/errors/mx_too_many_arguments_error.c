#include "ush.h"

void mx_too_many_arguments_error(char *builtin_name) {
    char *msg = ": too many arguments\n";
    write(2, builtin_name, mx_strlen(builtin_name));
    write(2, msg, mx_strlen(msg));
}


