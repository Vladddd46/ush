#include "libmx.h"

void mx_print_strarr(char **strarr) {
    int i = 0;

    while(strarr[i]) {
        mx_printstr(strarr[i]);
        mx_printstr("\n");
        i++;
    }
}

