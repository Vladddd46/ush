#include "libmx.h"

char *mx_string_copy(char *str) {
    char *new_str = mx_strnew(mx_strlen(str));
    char *pointer = new_str;
    int i = 0;

    while(str[i]) {
        *pointer = str[i];
        pointer++;
        i++;
    }
    pointer = NULL;
    return new_str;
}
