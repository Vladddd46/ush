#include "ush.h"

void mx_no_job_found(char *str) {
    char *msg = "fg: job not found: ";
    write(2, msg, mx_strlen(msg));
    write(2, str, mx_strlen(str));
    write(2, "\n", 1);
}

