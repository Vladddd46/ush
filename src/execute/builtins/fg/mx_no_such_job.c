#include "ush.h"

void mx_no_such_job(char *str) {
    char *msg1 = "fg: : ";
    char *msg2 = ": no such job\n"; 
    write(2, msg1, mx_strlen(msg1));
    write(2, str,  mx_strlen(str));
    write(2, msg2, mx_strlen(msg2));
}


