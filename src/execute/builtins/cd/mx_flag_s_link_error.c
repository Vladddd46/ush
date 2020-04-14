#include "ush.h"

// prints error if -s as flag and <link> as argument specified. 
void mx_flag_s_link_error(char *arg) {
    char *msg = "cd: not a directory: ";
    write(2, msg, mx_strlen(msg));
    write(2, arg, mx_strlen(arg));
    write(2, "\n", 1);
}

